#include "psession.h"

void  PSession::settype(char type)
{
    m_type =type;
}
char   PSession::gettype()
{
    return m_type;
}
void PSession::setcmd(char  cmd)
{
    m_cmd = cmd;
}
char  PSession::getcmd()
{
   return m_cmd;
}

QByteArray PSession::tostring()
{
    return m_data;
}

void PSession::setdata(QByteArray data)
{
    m_data= data;
}

QByteArray PSession::getdata()
{
    return m_data;
}

void PSession::setStr(QString Str)
{
    m_Str=Str;
}

QString PSession::getStr()
{
    return m_Str;
}
