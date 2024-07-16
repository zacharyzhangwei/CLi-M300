#include "cdbmanager.h"
namespace Control
{
CDBManager::CDBManager(QObject *parent) : QObject(parent)
{
    qRegisterMetaType<QVariant>("QVariant");
    qRegisterMetaType<st_User>("st_User");
    qRegisterMetaType<st_QCSample>("st_QCSample");
    qRegisterMetaType<st_QCResult>("st_QCResult");
    qRegisterMetaType<st_Item>("st_Item");
    qRegisterMetaType<st_Batch>("st_Batch");
    qRegisterMetaType<st_TestInfo>("st_TestInfo");
    qRegisterMetaType<st_TestResult>("st_TestResult");


    qRegisterMetaType<QQueue<st_User>>("QQueue<st_User>");
    qRegisterMetaType<QQueue<st_QCSample>>("QQueue<st_QCSample>");
    qRegisterMetaType<QQueue<st_QCResult>>("QQueue<st_QCResult>");
    qRegisterMetaType<QQueue<st_Item>>("QQueue<st_Item>");
    qRegisterMetaType<QQueue<st_Batch>>("QQueue<st_Batch>");
    qRegisterMetaType<QQueue<st_TestInfo>>("QQueue<st_TestInfo>");
    qRegisterMetaType<QQueue<st_TestResult>>("QQueue<st_TestResult>");


    m_dbModule.setcb(this);
}

//获取用户列表
bool CDBManager::getUserList()
{
    Data::CDBSession *sess =new Data::CDBSession();
    sess->setcmd(em_User_get_List);
    return m_dbModule.setSession(sess);
}
bool CDBManager::getIDUserInfo(QString id)
{
    Data::CDBSession *sess =new Data::CDBSession();
    sess->setcmd(em_User_get_ID);
    sess->setUserID(id);
    return m_dbModule.setSession(sess);
}


bool CDBManager::getUserAdd(QString nID, QString nName, QString nPasswd, int nPermissions, QString nDept, QString nContact)
{

    Data::CDBSession *sess =new Data::CDBSession();
    sess->setcmd(em_user_get_Add);
    st_User add_user;
    add_user.ID=nID;
    add_user.Name=nName;
    add_user.Password=nPasswd;
    add_user.Permissions=nPermissions;
    add_user.Dept=nDept;
    add_user.Contact=nContact;
    sess->setUseradd(add_user);
    return m_dbModule.setSession(sess);
}

bool CDBManager::getUserIDName()
{
    Data::CDBSession *sess =new Data::CDBSession();
    sess->setcmd(em_user_get_IDName);
    return m_dbModule.setSession(sess);
}

void CDBManager::recv(Data::IDBSession *sess)
{
    dispatch(sess);
}

 void CDBManager::dispatch(Data::IDBSession * sess)
 {
     switch(sess->getcmd())
     {
         case em_User_get_List:
         {
             Data::CDBSession *userSsesion=(Data::CDBSession*)sess;
             emit sgn_UserList(userSsesion->getUserList());
         }
             break;
         case em_User_get_ID:
         {
             Data::CDBSession *userSsesion=(Data::CDBSession*)sess;
             emit sgn_IDUserInfo(userSsesion->getUserInfo());
         }
             break;
        case em_user_get_IDName:
        {
            Data::CDBSession *userSsesion=(Data::CDBSession*)sess;
            emit sgn_allUser(userSsesion->get_allUser());
        }
            break;
        case em_user_get_Add:
            break;
     }
     delete (Data::CDBSession *)sess;
 }





}
