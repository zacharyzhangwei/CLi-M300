#ifndef _PSession_H
#define _PSession_H
#include <QObject>
#include "ISession.h"
#include <QDebug>


class PSession : public ISession
{
public:
    PSession(){};
    virtual~PSession(){};
public:
    virtual void  settype(char type);
    virtual char  gettype();
    virtual void setcmd(char cmd);
    virtual char  getcmd();
    virtual QByteArray tostring();
    virtual void setdata(QByteArray data);
    virtual QByteArray getdata();
    virtual void  setStr(QString Str);
    virtual QString  getStr();
private:
    char m_cmd;
    char m_type;
    QByteArray m_data;
    QString m_Str;

};

#endif // PSession_H
