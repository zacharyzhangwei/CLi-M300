#include "cdbmodule.h"
namespace  Data
{
    CDBModule::CDBModule()
    {
        m_dbCache.init();
    }
    CDBModule::~CDBModule()
    {
    }
    void CDBModule::setcb(IDBModule_CB * cb)
    {
         m_dbCache.setcb(cb);
    }
    bool CDBModule::setSession(IDBSession * sess)
    {
        return m_dbCache.setSession(sess);
    }

    int CDBModule::getSessionSize()
    {
        return m_dbCache.getSessionSize();
    }

}
