#ifndef CMODULE_H
#define CMODULE_H

#include <QObject>
#include "cserialpro.h"
#include "data/cserialport.h"

class CModule :public QObject,public IModule
{
    Q_OBJECT
public:
    CModule();
    virtual ~CModule();
public:
     virtual bool init();
     virtual void setcb(IModuleCB *cb);
     virtual bool open(int port, int rate);
     virtual bool close();
     virtual bool send(ISession *s);
private:
     CSerialPro m_serialmtpro;
};
#endif // CMTMODULE_H
