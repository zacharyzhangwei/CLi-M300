#ifndef SSESSION_H
#define SSESSION_H

#include <QObject>
#include "ISession.h"
#include <QDebug>


class SSession: public ISession
{
public:
    SSession(){};
    virtual~SSession(){};
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

#endif // SSESSION_H
