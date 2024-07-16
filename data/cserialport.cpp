#include "cserialport.h"
namespace  Data
{
    CSerialPort::CSerialPort():m_ntout_send(5000)
    {

    }
    CSerialPort::~CSerialPort()
    {
        m_datathread.quit();
        m_datathread.wait();

    }
    //初始化  用于串口信号的注册
    void CSerialPort::init()
    {
        connect(&m_serialport, SIGNAL(readyRead()), this, SLOT(slt_ready_read()));
        this->moveToThread(&m_datathread);
        m_datathread.start();

    }
    //上层回调
    void CSerialPort::setcb(ISerialPortCB * cb)
    {
        m_pcb = cb;
    }
    //串口打开
    bool CSerialPort::open(int port,int rate)
    {
        QSerialPortInfo info;
        QString COMStr="COM"+QString::number(port);
        m_serialport.setPort(info);
        m_serialport.setPortName(COMStr);
        if(!m_serialport.open(QIODevice::ReadWrite))
        {
            return false;
        }
        m_serialport.setBaudRate(rate);
        m_serialport.setParity(QSerialPort::NoParity);
//        m_serialport.setDataBits(QSerialPort::Data8);
//        m_serialport.setStopBits(QSerialPort::OneStop);
//        m_serialport.setFlowControl(QSerialPort::NoFlowControl);
        //m_serialport.clearError();
        //m_serialport.clear();
        return true;
    }
    //串口关闭
    bool CSerialPort::close()
    {
         m_serialport.close();
         return true;
    }
    //串口写入
    bool CSerialPort::write(QByteArray str)
    {

        if(!m_serialport.isOpen())
        {
            return false;
        }


        QString sstr = QString(str);
        qDebug()<<"sstr"<<sstr;

        qint32 size = str.length();
        qint32 realbyte =  m_serialport.write(str.toStdString().c_str(),str.length());

        m_serialport.waitForBytesWritten();
        m_serialport.flush();

        QTime t1 = QTime::currentTime();
        //数据没有完全发送到缓冲区的时候循环发送，如果阻塞了
        while(realbyte <size)
        {
            str = str.mid(realbyte,size-realbyte);
            size = str.length();
            realbyte = m_serialport.write(str.toStdString().c_str(),str.length());
            m_serialport.flush();
            QTime t2 = QTime::currentTime();
            if(t2.msecsTo(t1) > m_ntout_send)
            {
                m_error = CODE_TIMEOUT;
                return false;
            }
        }
        return true;
    }
    //获取错误码
    EM_ERROR_CODE CSerialPort::get_error()
    {
        return m_error;
    }
   //串口异步读取
    void CSerialPort::slt_ready_read()
    {
          QByteArray data = m_serialport.readAll();
          qDebug()<<"data"<<data;
          //m_pcb->read(data);
    }
}
