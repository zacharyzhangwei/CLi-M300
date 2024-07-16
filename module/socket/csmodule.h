#ifndef CSMODULE_H
#define CSMODULE_H

#include <QObject>
#include "TCPModule.h"
#include "cscoketpro.h"

class CSModule :public QObject,public TCPModule
{
    Q_OBJECT
public:
    CSModule();
    virtual ~CSModule();
public:
    virtual bool init();
    virtual void setcb(TCPModuleCB * cb);
    virtual bool open(QString ip, int port);
    virtual bool close();
    virtual bool send(ISession *s);
    virtual bool sends(QQueue<ISession *> *ssqueue);

private:
    CScoketPro m_socketpro;
};


#endif // CSMODULE_H
