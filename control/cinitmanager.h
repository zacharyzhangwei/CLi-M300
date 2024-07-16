#ifndef CINITMANAGER_H
#define CINITMANAGER_H
/////////////////////////////////////////
/// \brief The CDBManager class
/// 机器初始化的处理，获取机器的状态
#include "csocketmanager.h"
#include "cmodbusmanager.h"
#include "common/cglobal.h"
#include "common/globals.h"

namespace Control
{
    class CInitManager
    {
    public:
        static CInitManager* getInstances()
        {
            static CInitManager m_initManager;
            return &m_initManager;
        }
        CInitManager();
        virtual ~CInitManager();
    public:
        void Init();
        void HisInit();
    signals:
    };
}
#endif // CINITMANAGER_H
