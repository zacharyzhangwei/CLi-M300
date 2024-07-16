#include "cpmodule.h"

CPModule::CPModule()
{

}
CPModule::~CPModule(){

}

bool CPModule::init()
{
    return m_printpro.init();
}

void CPModule::setcb(IPModuleCB * cb)
{
 return m_printpro.setcb(cb);
}
bool CPModule::send(ISession *s)
{
    return m_printpro.setSession(s);
}

bool CPModule::sends(QQueue<ISession *> *ssqueue)
{
    return m_printpro.setSessions(ssqueue);
}

void CPModule::setprintOrHis(bool printOrHis)
{
    return m_printpro.setprintOrHis(printOrHis);
}

bool CPModule::open(int port, int bate)
{
    return m_printpro.open(port,bate);
}
bool CPModule::close()
{
    return m_printpro.close();
}

IPModule * getPModuleInstance()
{
    IPModule * mtmodule = (IPModule *) new CPModule;
    return mtmodule;
}

void  destroyPModuleInstance(IPModule * print)
{
    if(print != nullptr)
    {
        delete (CPModule * ) print;
        print = nullptr;
    }
}
