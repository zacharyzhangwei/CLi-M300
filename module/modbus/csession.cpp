#include "csession.h"
#include <qdebug.h>

void  CSession::settype(char type)
{
    m_type =type;
}
char   CSession::gettype()
{
    return m_type;
}
void CSession::setcmd(char  cmd)
{
    m_cmd = cmd;
}
char  CSession::getcmd()
{
   return m_cmd;
}

QByteArray CSession::tostring()
{
    QByteArray data;
    char v = 0xA0;
    data.append(4,v);
    data.append(m_type);
    data.append(m_cmd);
    data.append(m_data);
    char v1 = 0x0A;
    data.append(4,v1);
    return data;
}

void CSession::setdata(QByteArray data)
{
    m_data= data;
}

QByteArray CSession::getdata()
{
    return m_data;
}

void CMOpenSession::setport(int nPort)
{
    m_Port=nPort;
}

void CMOpenSession::setrate(int baud)
{
    m_Baud=baud;
}

int CMOpenSession::getport()
{
    return m_Port;
}

int CMOpenSession::getrate()
{
    return m_Baud;
}

void CMOpenSession::setopentype(bool type)
{
    m_Type=type;
}

bool CMOpenSession::getopentype()
{
    return m_Type;
}

void CMOpenSession::setModbusState(bool state)
{
    m_state=state;
}

bool CMOpenSession::getModbusState()
{
    return m_state;
}


void CMReadession::setStartAddress(unsigned int nStartAddress)
{
    m_startAddress=nStartAddress;
}

unsigned int CMReadession::getStartAddress()
{
    return m_startAddress;
}

void CMReadession::setnData(int nData)
{
    m_data=nData;
}

int CMReadession::getnData()
{
    return m_data;
}

void CMReadession::setList(QStringList nList)
{
    m_list=nList;
}

QStringList CMReadession::getList()
{
    return m_list;
}

void CMReadession::setModbusState(bool state)
{
    m_state=state;
}

bool CMReadession::getModbusState()
{
    return m_state;
}



void CMReadeDatassion::setStartAddress(unsigned int nStartAddress)
{
    m_startAddress=nStartAddress;
}

unsigned int CMReadeDatassion::getStartAddress()
{
    return m_startAddress;
}

void CMReadeDatassion::setnData(int nData)
{
    m_data=nData;
}

int CMReadeDatassion::getnData()
{
    return m_data;
}

void CMReadeDatassion::setList(QStringList nList)
{
    m_list=nList;
}

QStringList CMReadeDatassion::getList()
{
    return m_list;
}

void CMReadeDatassion::setnType(int nType)
{
    m_type=nType;
}

int CMReadeDatassion::getnType()
{
    return m_type;
}

void CMReadeDatassion::setDataType(int nDataType)
{
    m_DataType=nDataType;
}

int CMReadeDatassion::getDataType()
{
    return m_DataType;
}

void CMReadeDatassion::setModbusState(bool state)
{
    m_state=state;
}

bool CMReadeDatassion::getModbusState()
{
    return m_state;
}


void CMWriteBitSsion::setStartAddress(unsigned int nStartAddress)
{
    m_startAddress=nStartAddress;
}

unsigned int CMWriteBitSsion::getStartAddress()
{
    return m_startAddress;
}

void CMWriteBitSsion::setnData(int nData)
{
    m_data=nData;
}

int CMWriteBitSsion::getnData()
{
    return m_data;
}

void CMWriteBitSsion::setModbusState(bool state)
{
    m_state=state;
}

bool CMWriteBitSsion::getModbusState()
{
    return m_state;
}


void CMWriteDataSsion::setStartAddress(unsigned int nStartAddress)
{
    m_startAddress=nStartAddress;
}

unsigned int CMWriteDataSsion::getStartAddress()
{
    return m_startAddress;
}

void CMWriteDataSsion::setnData(int nData)
{
    m_data=nData;
}

int CMWriteDataSsion::getnData()
{
    return m_data;
}

void CMWriteDataSsion::setModbusState(bool state)
{
    m_state=state;
}

bool CMWriteDataSsion::getModbusState()
{
    return m_state;
}
