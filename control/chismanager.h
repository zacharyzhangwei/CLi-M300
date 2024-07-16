#ifndef CHISMANAGER_H
#define CHISMANAGER_H

#include <QObject>
#include "IPModule.h"
#include "print/cpmodule.h"
#include "print/psession.h"
#include "common/cglobal.h"
#include "hl7_manage.h"
namespace Control
{

class CHISManager: public QObject, public IPModuleCB

{
    Q_OBJECT
public:
    static CHISManager * getInstance()
    {
        static CHISManager m_HIS(nullptr);
        return &m_HIS;
    }
private:
    CHISManager(QObject *parent);

public:
    bool Init();
    bool setHISData(QQueue<st_TestInfo> testList);
    bool setHISOpen(int port,int rate);
    bool getHISState();
    bool setHISClose();
    virtual void comstatus(int status);//判断连接状态
private:
    CPModule m_HISmodule;
    bool m_comState=false;//串口连接状态


};

}

#endif // CHISMANAGER_H
