#ifndef CSETMANAGER_H
#define CSETMANAGER_H
/////////////////////////////////////////
/// \brief 设置界面相关逻辑
///
///
#include "control/imhelper.h"
#include <QObject>

namespace Control
{
    class CSetManager: public QObject
    {
        Q_OBJECT
    private:
        CSetManager();
    public:
        static CSetManager * getInstances()
        {
            static CSetManager s_msgRouter;
            return &s_msgRouter;
        }
        void set_order(ST_Order d_order);
        ST_Order get_order();
    };

}

#endif // CSETMANAGER_H
