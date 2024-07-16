#include "cmodule.h"


CModule::CModule()
{

}
CModule::~CModule()
{

}

bool CModule::init()
{
    return m_serialmtpro.init();
}

void CModule::setcb(IModuleCB * cb)
{
    m_serialmtpro.setcb(cb);
}

bool CModule::send(ISession *s)
{
    return m_serialmtpro.send(s);
    //return true;
}

bool CModule::open(int port, int bate)
{
    return m_serialmtpro.open(port,bate);
}

bool CModule::close()
{
    return m_serialmtpro.close();
}


IModule * getModuleInstance()
{
    IModule * mtmodule = (IModule *) new CModule;
    return mtmodule;
}

void  destroyModuleInstance(IModule * mod)
{
    if(mod != nullptr)
    {
        delete (CModule * ) mod;
        mod = nullptr;
    }
}
