#include "cscoketpro.h"

CScoketPro::CScoketPro(QObject *parent) : QObject(parent)
{
    m_Tcpcb= nullptr;
}

CScoketPro::~CScoketPro()
{
    m_brun = false;
    m_cond.notify_all();
    m_TcpThread.quit();
    m_TcpThread.wait();
    if(m_SocketTool!=nullptr)
        delete  m_SocketTool;
    m_SocketTool = nullptr;
}

bool CScoketPro::setSession(ISession *s)
{
    m_mutex.lock();
    m_Sessionlist.push_back(s);
    m_mutex.unlock();
    m_cond.notify_one();
    return true;
}

bool CScoketPro::setSessions(QQueue<ISession *> *sses)
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
    qDebug()<<"CScoketProsses->true()"<<true;
    return true;
}

bool CScoketPro::init()
{
    m_SocketTool=new SocketTool();
    QObject::connect(&m_TcpThread,&QThread::started,this,&CScoketPro::slt_run);
    this->moveToThread(&m_TcpThread);
    return true;;
}

void CScoketPro::setcb(TCPModuleCB *cb)
{
    m_Tcpcb = cb;
}

bool CScoketPro::open(QString ip, int port)
{
    m_brun = true;
    bool cet =m_SocketTool->set_Socket_Connect(ip,port);
    m_TcpThread.start();
    return cet;
}

bool CScoketPro::close()
{
    bool cet =m_SocketTool->set_Socket_Disconnect();
    if(cet)
    {
        //m_cond.notify_all();
        m_brun = false;
    }
    return cet;;
}

void CScoketPro::slt_run()
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
            break;
        }
        ISession * sess = m_Sessionlist.front();
        m_Sessionlist.pop_front();
        m_mutex.unlock();
        if(!m_brun)
        {
            break;
        }
        if(sess==nullptr)
        {
            continue;
        }
        this->send(sess->getdata());
        delete  (SSession *)sess;
//        CMReadession *readesion = (CMReadession*) sess;
//        m_Tcpcb->rev();


    }
}

bool CScoketPro::send(QByteArray nStr)
{
    qDebug()<<"nStr"<<nStr;
    if(m_SocketTool == nullptr)
        return false;
    return m_SocketTool->set_Write_Data(nStr);
}
