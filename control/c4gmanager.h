#ifndef C4GMANAGER_H
#define C4GMANAGER_H

#include <QObject>
#include <QJsonArray>
#include <Windows.h>
#include "common/cglobal.h"
#include <module/4g/c4gcache.h>
#include <module/4g/c4gmodule.h>
#include "cdbmanager.h"

#pragma execution_character_set("utf-8")

namespace Control
{
    class C4gManager : public QObject
    {
        Q_OBJECT
    public:
        static C4gManager * getInstances()
        {
            static C4gManager m_4gManager;
            return &m_4gManager;
        }
    private:
        C4gManager();
    private:
        C4gModule*  m_4g_module;
        C4gCache*   m_4g_cache;
        bool        m_resuleState=true;
        bool        m_recordEnd=false;

    public:
        bool get_C4gRecordEnd();
        void set_C4gRecordEnd(bool state);
        bool get_update();//获取更新信息
        void init();
        void get4GTime();
        void sendErrorMsg(QString faultcode);
        void sendTestData(QString curvStr, st_Test_Data testData, bool testOrRecord=true);
        bool getResultState();
        void setResultState(bool state);
        void setComputerInfo();
        double getCpuUsage();
        st_Test_Data stTestToC4TestData(st_TestInfo stTestInfo);
        bool getC4gState();
    signals:
        void sgn_CacheC4g_State(bool state);
    public slots:
        void slt_upload_finish(int resourceId);
        void slt_C4g_State(bool state);

    public slots:
    };
}
#endif // C4GMANAGER_H
