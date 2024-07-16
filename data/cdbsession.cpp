#include "cdbsession.h"

namespace  Data
{
    CDBSession::CDBSession(QObject *parent) : QObject(parent),m_cmd(em_User_get_Null)
    {

    }


    void CDBSession::setcmd(enum_db_cmd cmd)
    {
        m_cmd = cmd;
    }

    enum_db_cmd  CDBSession::getcmd()
    {
        return m_cmd;
    }

    QQueue<st_User> CDBSession::getUserList()
    {
        return m_UserList;
    }

    void CDBSession::setUserList(QQueue<st_User> userList)
    {
        m_UserList=userList;
    }

    QString CDBSession::getPasswd()
    {
        return mCDB_User.Password;
    }

    void CDBSession::setPasswd(QString sPasswd)
    {
        this->mCDB_User.Password=sPasswd;
    }

    int CDBSession::getPermissions()
    {
        return mCDB_User.Permissions;
    }

    void CDBSession::setPermissions(int sPermissions)
    {
        this->mCDB_User.Permissions=sPermissions;
    }

    QString CDBSession::getDept()
    {
        return mCDB_User.Dept;
    }

    void CDBSession::setDept(QString sDept)
    {
        mCDB_User.Dept = sDept;
    }

    QString CDBSession::getContact()
    {
        return mCDB_User.Contact;
    }

    void CDBSession::setContact(QString sContact)
    {
        this->mCDB_User.Contact=sContact;
    }

    QString CDBSession::getUserID()
    {
        return m_ID;
    }

    void CDBSession::setUserID(QString id)
    {
        m_ID=id;
    }

    void CDBSession::setUseradd(st_User user_Add)
    {
        madd_User = user_Add;
    }

    void CDBSession::setUserName(QString sName)
    {
        this->mCDB_User.Name=sName;
    }

    QString CDBSession::getUserName()
    {
        return mCDB_User.Name;
    }

    st_User CDBSession::getUserInfo()
    {
        return m_UserInfo;
    }

    st_User CDBSession::getUserAdd()
    {
        return madd_User;
    }

    void CDBSession::set_allUser(QQueue<st_User> alluserList)
    {
        this->m_allUser = alluserList;
    }

    QQueue<st_User> CDBSession::get_allUser()
    {
        return m_allUser;
    }

    void CDBSession::setUserInfo(st_User userInfo)
    {
        m_UserInfo=userInfo;
    }



//    QQueue<st_User> CDBSessionUser::getUserList()
//    {
//        return m_UserList;
//    }

//    void CDBSessionUser::setUserList(QQueue<st_User> userList)
//    {
//        m_UserList=userList;
//    }


}
