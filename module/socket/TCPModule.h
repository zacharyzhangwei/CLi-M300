#ifndef TCPMODULE_H
#define TCPMODULE_H

#include <QString>
#include "ISession.h"

class TCPModuleCB
{
public:
    virtual ~TCPModuleCB(){}
//    virtual void TCPstatus(ISession *s) = 0;
//    virtual void comstatus(int status) = 0;
};

class TCPModule
{
public:
    virtual bool init() = 0;
    virtual void setcb(TCPModuleCB * cb) = 0;
    virtual bool open(QString port, int rate) = 0;
    virtual bool close() = 0;
    virtual bool send(ISession *s)  = 0;
    virtual bool sends(QQueue<ISession *> *ssqueue) =0;
};
////串口模块实例获取
TCPModule * getSModuleInstance();

////串口模块实例销毁
void   destroySModuleInstance(TCPModule *socket);


#endif // TCPMODULE_H
