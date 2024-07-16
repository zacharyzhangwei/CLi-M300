#ifndef CLOGINMANAGER_H
#define CLOGINMANAGER_H
/////////////////////////////////////////
/// \brief The CDBManager class
/// 用于登录时候的一些控制逻辑

#include <QObject>
#include <QDebug>
#include <QQueue>
#include <QVector>
#include "control/imhelper.h"
namespace Control
{
    class CLoginManager: public QObject
    {
        Q_OBJECT
    private:
        CLoginManager();
    public:
        static CLoginManager * getInstances()
        {
            static CLoginManager s_msgRouter;
            return &s_msgRouter;
        }
        bool getDBUserList();
        bool getLoginType(int loginType,QString id,QString passwd);
        bool getUpdataPasswd(QString id, QString passwd);
    private slots:
        void slt_UserList(QQueue<st_User> userList);
        void slt_IDUserInfo(st_User userInfo);
    private:
        QString m_Passwd;
        int m_loginType=0;//输入操作类型 0登入，1管理员
    signals:
        void sgn_UserList(QQueue<st_User> userList);
        void sgn_loginState(int type,bool state);              //登陆状态
    };
}

#endif // CLOGINMANAGER_H
