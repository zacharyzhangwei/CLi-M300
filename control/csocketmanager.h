#ifndef CSOCKETMANAGER_H
#define CSOCKETMANAGER_H

#include <QObject>
#include "socket/TCPModule.h"
#include "socket/csmodule.h"
#include "common/cglobal.h"
#include "hl7_manage.h"
namespace Control
{
    class CSocketManager: public QObject,public TCPModuleCB
    {
        Q_OBJECT
    public:
        static CSocketManager * getInstance()
        {
            static CSocketManager m_Socket(nullptr);
            return &m_Socket;
        }
    private:
        CSocketManager(QObject *parent);
        virtual ~CSocketManager();
    public:
        bool Init();
        bool setSocketData(QQueue<st_TestInfo> testList);
        bool setSocketClose();
        bool setSocketOpen(QString IP, int port);
        bool getSocketOpen();
    private:
        CSModule m_Tcpmodule;
        bool m_tcpState=false;//tcp连接状态
    };

}
#endif // CSOCKETMANAGER_H
