#include "ssession.h"

void  SSession::settype(char type)
{
    m_type =type;
}
char   SSession::gettype()
{
    return m_type;
}
void SSession::setcmd(char  cmd)
{
    m_cmd = cmd;
}
char  SSession::getcmd()
{
   return m_cmd;
}

QByteArray SSession::tostring()
{
    return m_data;
}

void SSession::setdata(QByteArray data)
{
    m_data= data;
}

QByteArray SSession::getdata()
{
    return m_data;
}

void SSession::setStr(QString Str)
{
    m_Str=Str;
}

QString SSession::getStr()
{
    return m_Str;
}
