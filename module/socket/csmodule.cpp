#include "csmodule.h"
CSModule::CSModule()
{

}
CSModule::~CSModule(){

}

bool CSModule::init()
{
    return m_socketpro.init();
}

void CSModule::setcb(TCPModuleCB * cb)
{
    return m_socketpro.setcb(cb);
}

bool CSModule::send(ISession *s)
{
    return m_socketpro.setSession(s);
}

bool CSModule::sends(QQueue<ISession *> *ssqueue)
{
    return m_socketpro.setSessions(ssqueue);
}

bool CSModule::open(QString ip, int port)
{
    return m_socketpro.open(ip,port);
}
bool CSModule::close()
{
    return m_socketpro.close();
}

TCPModule * getSModuleInstance()
{
    TCPModule * mtmodule = (TCPModule *) new CSModule;
    return mtmodule;
}

void  destroySModuleInstance(TCPModule * print)
{
    if(print != nullptr)
    {
        delete (CSModule * ) print;
        print = nullptr;
    }
}
