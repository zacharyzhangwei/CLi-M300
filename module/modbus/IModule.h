#ifndef IMODULE_H
#define IMODULE_H
#include <QString>
#include "ISession.h"

class IModuleCB
{
public:
    virtual ~IModuleCB(){}
    virtual void rev(ISession *s) = 0;
    //virtual void comstatus(int status) = 0;
};

class IModule
{
public:
    virtual bool init() = 0;
    virtual void setcb(IModuleCB * cb) = 0;
    virtual bool open(int port, int rate) = 0;
    virtual bool close() = 0;
    virtual bool send(ISession *s)  = 0;
};

//串口模块实例获取
IModule * getModuleInstance() ;

//串口模块实例销毁
void   destroyModuleInstance(IModule *mt);

#endif // IMTMODULE_H
