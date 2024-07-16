#include "cdbcache.h"
namespace  Data
{
    CDBCache::CDBCache()
    {

    }

    CDBCache::~CDBCache()
    {
        m_brun = false;
        m_cond.notify_all();
        m_sqlThread.quit();
        m_sqlThread.wait();
    }

    int CDBCache::getSessionSize()
    {
        return m_sessionlist.size();
    }

    void CDBCache::init()
    {
        QObject::connect(&m_sqlThread,&QThread::started,this,&CDBCache::slt_run);
        this->moveToThread(&m_sqlThread);
        m_brun = true;
        m_sqlThread.start();
        m_DBlite.init();
    }

    void CDBCache::setcb(IDBModule_CB * cb)
    {
         m_mgr_cb =cb;
    }

    bool CDBCache::setSession(IDBSession * sess)
    {
        m_mutex.lock();
        m_sessionlist.push_back(sess);
        m_mutex.unlock();
        m_cond.notify_one();
        return true;
    }

    void CDBCache::slt_run()
    {
        while(m_brun)
        {
            m_mutex.lock();
            while(m_sessionlist.empty()&&m_brun)
            {
                m_cond.wait(&m_mutex);
            }
            if(!m_brun)
            {
                m_mutex.unlock();
                break;
            }
            IDBSession * sess = m_sessionlist.front();
            m_sessionlist.pop_front();
            m_mutex.unlock();
            if(!m_brun) break;
            if(sess==nullptr)
            {
                continue;
            }
            switch(sess->getcmd())
            {
                case em_User_get_List:
                {
                    CDBSession *usersesion = (CDBSession*) sess;
                    vacuum();//数据库压缩
                    QQueue<st_User> userList=getUserTable();
                    usersesion->setUserList(userList);//ID
                    m_mgr_cb->recv(usersesion);
                }
                     break;
                case em_User_get_ID:
                {
                    CDBSession *usersesion = (CDBSession*) sess;
                    QQueue<st_User> userList=getUserTable("ID",usersesion->getUserID());
                    usersesion->setUserInfo(userList.dequeue());//ID
                    m_mgr_cb->recv(usersesion);
                }
                     break;
                case em_user_get_Add:
                {
                    CDBSession *usersesion = (CDBSession*) sess;
                    st_User User_Add;
                    User_Add=usersesion->getUserAdd();
                    addUserTable(User_Add);
                    m_mgr_cb->recv(usersesion);
                }
                    break;
                case em_user_get_IDName:
                {
                    CDBSession *usersesion = (CDBSession*) sess;
                    QQueue<st_User> userList = getUserTable("","");
                    usersesion->set_allUser(userList);//ID
                    m_mgr_cb->recv(usersesion);
                }
                    break;
            }
        }
    }

    void CDBCache::vacuum()
    {
        QSqlQuery sql_query;
        QString Sql_str=QString("VACUUM") ;
        sql_query=m_DBlite.sql_query(Sql_str);
    }

    QQueue<st_User> CDBCache::getUserTable(QString ItemName, QString ItemStr)
    {
        st_User User_re;
        QQueue<st_User> userList_re;
        QSqlQuery sql_query;
        QString Sql_str;
        if(ItemName.isEmpty()||ItemStr.isEmpty())
        {
            Sql_str=QString("select * from UserTable");
        }
        else
        {
            Sql_str=QString("select * from UserTable where %1='%2'").arg(ItemName).arg(ItemStr);
        }
        sql_query=m_DBlite.sql_query(Sql_str);
        while(sql_query.next())
        {

            User_re.ID=sql_query.value(0).toString();//用户名
            User_re.Password=sql_query.value(1).toString();//密码
            User_re.Permissions=sql_query.value(2).toInt();//权限
            User_re.Dept=sql_query.value(3).toString();//科室
            User_re.Contact=sql_query.value(4).toString();//联系方式
            User_re.Name=sql_query.value(5).toString();//姓名
            userList_re<<User_re;
        }
        return userList_re;
    }


    bool CDBCache::addUserTable(st_User User)
    {
        QSqlQuery sql_query;
        QString Sql_str=QString("insert into UserTable values('%1','%2','%3','%4','%5','%6')")
                .arg(User.ID)
                .arg(User.Password)
                .arg(User.Permissions)
                .arg(User.Dept)
                .arg(User.Contact)
                .arg(User.Name);
        sql_query=m_DBlite.sql_query(Sql_str);
        qDebug()<<"success";
        return true;
    }



}
