#ifndef CQCMANAGER_H
#define CQCMANAGER_H

#include <QObject>
#include "cdbmanager.h"
namespace Control
{
    class CQCManager: public QObject
    {
        Q_OBJECT
    public:
        static CQCManager * getInstance()
        {
            static CQCManager g_QC;
            return &g_QC;
        }
    public:

    private:
        CQCManager();

    };

}

#endif // CQCMANAGER_H
