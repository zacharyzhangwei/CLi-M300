#ifndef CSQLCACHE_H
#define CSQLCACHE_H
#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include <QThread>
#include <QQueue>
#include "IDBModuleCB.h"
#include "cdbsession.h"
#include "cdbsqllite.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDebug>
#include "common/cglobal.h"


#pragma execution_character_set("utf-8")


namespace  Data
{
    class CDBCache: public QObject
    {
        Q_OBJECT
    public:
        CDBCache();
        virtual ~CDBCache();
    public:
        int getSessionSize();
        void init();
        void setcb(IDBModule_CB * cb);
        bool setSession(IDBSession * sess);
        void vacuum();//数据库压缩
        QQueue<st_User> getUserTable(QString ItemName="",QString ItemStr="");
        bool addUserTable(st_User User);

    public slots:
        void slt_run();
    private:
        QQueue<IDBSession * >  m_sessionlist;    //请求队列
        QThread           m_sqlThread;  //异步线程
        QMutex            m_mutex;      //线程锁
        QWaitCondition    m_cond;       //条件锁
        bool              m_brun;       //线程运行标志位
        CSQLLite          m_DBlite;
    private:
        IDBModule_CB*    m_mgr_cb;         //sql管理器上层回调
    };
}
#endif // CSQLCACHE_H















