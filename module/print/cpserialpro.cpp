#include "cpserialpro.h"
#include "psession.h"
#include "IPModule.h"
CPSerialPro::CPSerialPro(QObject *parent) : QObject(parent)
{
    m_cb = nullptr;

}

CPSerialPro::~CPSerialPro()
{
    m_brun = false;
    m_cond.notify_all();
    m_pseriaThread.quit();
    m_pseriaThread.wait();
    if(m_serial_port!=nullptr)
        delete  m_serial_port;
    m_serial_port = nullptr;
}

bool CPSerialPro::setSession(ISession *s)
{
    m_mutex.lock();
    m_Sessionlist.push_back(s);
    m_mutex.unlock();
    m_cond.notify_one();
    return true;
}

bool CPSerialPro::setSessions(QQueue<ISession *> *sses)
{
    m_mutex.lock();
    qDebug()<<"sses->size()"<<sses->size();
    while (sses->size())
    {
        //qDebug()<<"getdata"<<sses->dequeue()->getdata();
        m_Sessionlist.push_back(sses->dequeue());
    }
    m_mutex.unlock();
    m_cond.notify_one();
    qDebug()<<"sses->true()"<<true;
    return true;
}

bool CPSerialPro::init()
{
    m_brun = true;
    QObject::connect(&m_pseriaThread,&QThread::started,this,&CPSerialPro::slt_run);
    this->moveToThread(&m_pseriaThread);
    return true;;
}

void CPSerialPro::setcb(IPModuleCB * cb)
{
    m_cb = cb;
}

void CPSerialPro::setprintOrHis(bool printOrHis)
{
    m_printOrHis=printOrHis;
}

bool CPSerialPro::open(int port,int rate)
{
    m_port  = port;
    m_rate = rate;
    if(m_serial_port == nullptr) //子线程线程创建串口
    {
        m_serial_port = new Data::CSerialPort();

    }
    m_serial_port->init();
    bool ret = m_serial_port->open(m_port,m_rate);
    if(m_cb!=nullptr)
    {
        m_cb->comstatus(ret?1:0);
    }

    if(!ret)
    {
        return false;    //失败返回
    }
    else
    {
        m_brun = true;
        m_pseriaThread.start();
    }
    return true;
}

bool CPSerialPro::close()
{
    //m_cond.notify_all();
    m_serial_port->close();//关闭串口并释放相关
    m_brun = false;
    return true;;
}

void CPSerialPro::slt_run()
{

    while(m_brun)
    {
        m_mutex.lock();
        while(m_Sessionlist.empty()&&m_brun)
        {
            m_cond.wait(&m_mutex);
        }
        if(!m_brun)
        {
            m_mutex.unlock();
            m_serial_port->close();//关闭串口并释放相关
            if(m_serial_port!=nullptr)
                delete  m_serial_port;
            m_serial_port = nullptr;
            break;
        }
        if(m_Sessionlist.size() == 0) continue; //空数据回环
        ISession *sess = m_Sessionlist.front();
        m_Sessionlist.pop_front();
        m_mutex.unlock();
        if(!m_brun) break;
        if(sess==nullptr)
        {
            continue;
        }
        this->send(sess->getdata());
        delete  (PSession *)sess;
        if(m_printOrHis)
        {
            QThread::msleep(8000);
        }
        else
        {
            QThread::msleep(500);
        }
        //这里可以判断串口状态 如果串口断开可以重连或发送串口状态信号
    }
}


bool CPSerialPro::send(QByteArray nStr)
{
    if(m_serial_port == nullptr) return false;
    return m_serial_port->write(nStr);
}



