#ifndef CSQLMGR_H
#define CSQLMGR_H

#include <QObject>
#include "IDBSession.h"
#include "cdbcache.h"
#include "IDBModuleCB.h"
namespace  Data
{
    class CDBModule: public QObject
    {
        Q_OBJECT
    public:
        CDBModule();
        virtual ~CDBModule();
    public:
        void setcb(IDBModule_CB * cb);
        bool setSession(IDBSession * sess);
        int getSessionSize();
    private:
        CDBCache  m_dbCache;
    };
}
#endif // CSQLMGR_H
