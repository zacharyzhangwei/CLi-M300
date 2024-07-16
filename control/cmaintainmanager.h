#ifndef CMAINTAINMANAGER_H
#define CMAINTAINMANAGER_H

#include <QObject>

class CMaintainManager : public QObject
{
    Q_OBJECT
public:
    static CMaintainManager * getInstances()
    {
        static CMaintainManager s_MaintainRouter;
        return &s_MaintainRouter;
    }
    explicit CMaintainManager(QObject *parent = nullptr);

signals:

};

#endif // CMAINTAINMANAGER_H
