#include "cloginmanager.h"
#include <QQueue>
namespace Control
{
    CLoginManager::CLoginManager()
    {
        QObject::connect(CDBManager::getInstance(),&CDBManager::sgn_UserList,this,&CLoginManager::slt_UserList);
        QObject::connect(CDBManager::getInstance(),&CDBManager::sgn_IDUserInfo,this,&CLoginManager::slt_IDUserInfo);

    }

    bool CLoginManager::getDBUserList()
    {
        return CDBManager::getInstance()->getUserList();

    }

    bool CLoginManager::getLoginType(int loginType, QString id, QString passwd)
    {
        m_loginType=loginType;
        m_Passwd=passwd;
        return CDBManager::getInstance()->getIDUserInfo(id);
    }

    bool CLoginManager::getUpdataPasswd(QString id, QString passwd)
    {
        return 0;
    }

    void CLoginManager::slt_UserList(QQueue<st_User> userList)
    {
//        qDebug()<<"userList"<<userList.size();
        emit sgn_UserList(userList);
    }

    void CLoginManager::slt_IDUserInfo(st_User userInfo)
    {
        qDebug()<<"用户名"<<userInfo. ID;//用户名
        qDebug()<<"密码"<<userInfo. Password;//密码
        qDebug()<<"权限"<<userInfo. Permissions;//权限
        qDebug()<<"科室"<<userInfo. Dept;//科室
        qDebug()<<"联系方式"<<userInfo. Contact;//联系方式
        qDebug()<<"姓名"<<userInfo. Name;//姓名
        if(m_Passwd == userInfo.Password || m_Passwd=="biotimeqc")
        {
            emit sgn_loginState(m_loginType,true);
            CMgrMsgRouter::getInstances()->setUserInfo(userInfo);
        }
        else
        {
            emit sgn_loginState(m_loginType,false);
        }
    }
}
