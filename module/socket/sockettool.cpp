#include "sockettool.h"

SocketTool::SocketTool(QObject *parent) : QObject(parent)
{
    m_Socket=new QTcpSocket();
}

SocketTool::~SocketTool()
{
    this->m_Socket->abort();
    //delete this->m_Socket;
}

void SocketTool::slt_connected()
{
    QObject::connect(m_Socket,&QTcpSocket::readyRead,this,&SocketTool::slt_Read_Data);
    QObject::connect(m_Socket,&QTcpSocket::disconnected,this,&SocketTool::set_Socket_Disconnect);
}

void SocketTool::slt_Read_Data()
{
    m_TcpReq=m_Socket->readAll();
}

bool SocketTool::set_Socket_Connect(QString nIPStr, int nPort)//连接socket
{
    quint16 port=nPort;
   // QHostAddress IP(nIPStr);
    m_Socket->abort();
    m_Socket->connectToHost(QHostAddress(nIPStr),port);
    if(!m_Socket->waitForConnected(300))//连接失败
    {
        m_ErrorStr=m_Socket->error();
        return false;
    }
    else
    {
        QObject::connect(m_Socket,&QTcpSocket::connected,this,&SocketTool::slt_connected);
        m_TcpFlag=true;
        return true;
    }
}

bool SocketTool::set_Socket_Disconnect()
{
    m_Socket->close();
    m_TcpFlag=false;
    return true;
}

bool SocketTool::set_Write_Data(QByteArray nDatabyt)
{

    qDebug()<<"nDatabyt"<<nDatabyt;
    if(m_TcpFlag)
    {
//        QByteArray  nDataBit;
//        nDataBit.append(nData.toUtf8());
        qint64 writeResult=m_Socket->write(nDatabyt);
        bool nFlushFlag=m_Socket->flush();
        if(writeResult!=-1&&nFlushFlag==1)
        {
            if(writeResult==0)
            {
                //写返回值0
                qDebug()<<"0";
            }
            //写数据成功
            qDebug()<<"1"<<writeResult;
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

