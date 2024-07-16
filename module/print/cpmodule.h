#ifndef CPMODULE_H
#define CPMODULE_H

#include <QObject>
#include "IPModule.h"
#include "cpserialpro.h"


class CPModule :public QObject,public IPModule
{
    Q_OBJECT
public:
    CPModule();
    virtual ~CPModule();
public:
    virtual bool init();
    virtual void setcb(IPModuleCB * cb);
    virtual bool open(int port, int rate);
    virtual bool close();
    virtual bool send(ISession *s);
    virtual bool sends(QQueue<ISession *> *ssqueue);
    virtual void setprintOrHis(bool printOrHis);

private:
    CPSerialPro m_printpro;
};

#endif // CMTMODULE_H
