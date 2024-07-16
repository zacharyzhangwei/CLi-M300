#ifndef CDBMANAGER_H
#define CDBMANAGER_H

#include <QObject>
#include <data/IDBModuleCB.h>
#include <data/cdbmodule.h>
#include <data/IDBSession.h>
#include <data/cdbsession.h>
#include "cpmodule.h"
#include "c4gmanager.h"
#include "cmgrmsgrouter.h"
/////////////////////////////////////////
/// \brief The CDBManager class
/// 用于数据库交互的控制
///
namespace Control
{
class CDBManager : public QObject ,public Data::IDBModule_CB
{
    Q_OBJECT
public:
    static CDBManager * getInstance()
    {
        static CDBManager m_dbmgr(nullptr);
        return &m_dbmgr;
    }
    bool getUserList();//获取用户列表
    bool getIDUserInfo(QString id);//获取对应ID的数据
    bool getUserAdd(QString nID, QString nName,
                    QString nPasswd, int nPermissions,
                    QString nDept, QString nContact);//获取用户信息
    bool getUserIDName();

private:
    CDBManager(QObject *parent);
    void dispatch(Data::IDBSession * sess);

public:
    virtual void recv(Data::IDBSession *sess);
private:
    Data::CDBModule m_dbModule;


signals:
    void sgn_UserList(QQueue<st_User> userList);
    void sgn_IDUserInfo(st_User userInfo);
    void sgn_allUser(QQueue<st_User> alluserList);
    void sgn_maxTesnum(int i);

};
}
#endif // CDBMANAGER_H
