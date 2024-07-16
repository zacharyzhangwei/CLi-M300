#ifndef IPMODULE_H
#define IPMODULE_H
#include <QString>
#include "ISession.h"

class IPModuleCB
{
public:
    virtual ~IPModuleCB(){}
    virtual void comstatus(int status) = 0;
};

class IPModule
{
public:
    virtual bool init() =0;
    virtual void setcb(IPModuleCB * cb) = 0;
    virtual bool open(int port, int rate) =0;
    virtual bool close() =0;
    virtual bool send(ISession *s) =0;
    virtual bool sends(QQueue<ISession *> *ssqueue) =0;
};

//串口模块实例获取
IPModule * getPModuleInstance() ;

//串口模块实例销毁
void   destroyPModuleInstance(IPModule *print);


#endif // IMTMODULE_H
