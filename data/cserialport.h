#ifndef CSERIALPORT_H
#define CSERIALPORT_H

#include <QObject>
#include <QString>
#include <QDebug>
#include <QThread>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QTime>
#include <QTimer>
#include "common/cglobal.h"
#include "module/ISession.h"
#pragma execution_character_set("utf-8")
namespace  Data
{
    class ISerialPortCB
    {
      public:
        virtual int read(QString data) = 0;
        virtual void recv(ISession *sess) = 0;
    };

    class CSerialPort: public QObject
    {
        Q_OBJECT
    public:
        CSerialPort();
        virtual ~CSerialPort();
    public:
        void init();
        void setcb(ISerialPortCB * cb);
        bool open(int port,int rate);
        bool close();
        bool write(QByteArray str);
        EM_ERROR_CODE get_error();
    public slots:
        void slt_ready_read();                  //数据接收
    private:
        QSerialPort         m_serialport;
        int                 m_nport;            //串口号
        int                 m_nbate;            //波特率
        ISerialPortCB*      m_pcb;              //回调接口
        QThread             m_datathread;       //接收数据处理线程
        int                 m_ntout_send;       //发送的超时时间--毫秒
        EM_ERROR_CODE       m_error;            //错误码

    };
}
#endif // CSERIALPORT_H
