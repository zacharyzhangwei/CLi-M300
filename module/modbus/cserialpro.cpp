#include "cserialpro.h"
CSerialPro::CSerialPro(QObject *parent) : QObject(parent)
{

}

bool CSerialPro::init()
{ 
    QObject::connect(&m_modbusThread,&QThread::started,this,&CSerialPro::slt_run);
    this->moveToThread(&m_modbusThread);
    m_brun = true;
    m_modbustool=new ModbusTool();
    m_modbusThread.start();
    return false;
}

void CSerialPro::setcb(IModuleCB *cb)
{
    m_procb = cb;
}

bool CSerialPro::send(ISession *s)
{
    m_mutex.lock();
    m_sessionlist.push_back(s);
    m_mutex.unlock();
    m_cond.notify_one();
    return true;
}

void CSerialPro::slt_run()
{
    while(m_brun)
    {
        m_mutex.lock();
        while(m_sessionlist.empty()&&m_brun)
        {
            m_cond.wait(&m_mutex);
        }

        if(!m_brun)
        {
            m_mutex.unlock();
            break;
        }
        ISession * sess = m_sessionlist.front();
        //判断串口是否断联
        if((!m_modbusState))//串口断联
        {
//            qDebug()<<"串口断联"<<QDateTime::currentMSecsSinceEpoch()<<"size()"<<m_sessionlist.size() <<"sess->getcmd()"<<QString(sess->getcmd());
            m_sessionlist.pop_front();
            m_mutex.unlock();
            if(!m_brun) break;
            if(sess==nullptr)
            {
                continue;
            }
            if(sess->getcmd()!=0x03&&sess->getcmd()!=0x06)
            {
//                qDebug()<<"补充添加"<<QDateTime::currentMSecsSinceEpoch()<<"size()"<<m_sessionlist.size() <<"sess->getcmd()"<<QString(sess->getcmd());
                send(sess);
            }
            switch(sess->getcmd())
            {
            case 0x03://启动
            {
                qDebug()<<"0x03";
                CMOpenSession *opensesion = (CMOpenSession*) sess;
                m_comNum=opensesion->getport();
                m_baudNum=opensesion->getrate();
                bool cet =m_modbustool->Modbus_connect(m_comNum,m_baudNum);
                m_modbusState=cet;
                opensesion->setopentype(cet);
                opensesion->setModbusState(cet);
                m_procb->rev(opensesion);
            }
                break;
            case 0x06://重新连接
            {
                CMOpenSession *opensesion = (CMOpenSession*) sess;
                bool cet=m_modbustool->reconnect_modbus();
                m_modbusState=cet;
                opensesion->setModbusState(m_modbusState);
                m_procb->rev(opensesion);
                QThread::msleep(20);
            }
            break;
            }
            QThread::msleep(20);

        }
        else
        {
            m_sessionlist.pop_front();
            m_mutex.unlock();
            if(!m_brun) break;
            if(sess==nullptr)
            {
                continue;
            }
            switch(sess->getcmd())
            {
            case 0x00://状态读取
            {
                CMReadession *readesion = (CMReadession*) sess;
                QStringList DataList;//数据链表
                bool readFlag=true;
                if(m_modbusState)
                {
                    int readCount=0;
                    while(readFlag)
                    {
                        if(m_modbustool->Read_Client(readesion->getStartAddress(),readesion->getnData())&&m_modbusState)
                        {
                            for(int i=0;i<readesion->getnData();i++)
                            {
                                QString ndata=QString::number(m_modbustool->req16[i]);
                                DataList<<ndata;
                            }
                            readFlag=false;
                        }
                        else
                        {
                            if(readCount<10)
                            {
                                readCount++;
                            }
                            else
                            {
                                m_modbusState=false;
                                readFlag=false;
                            }
                        }
                        QThread::msleep(20);
                    }
                }
                readesion->setModbusState(m_modbusState);
                readesion->setList(DataList);
                m_procb->rev(readesion);
            }
                break;
            case 0x01://写入Data
            {
                CMWriteDataSsion *writesesion = (CMWriteDataSsion*) sess;
                int i=-1;
                int  readCount=0;
                if(m_modbusState)
                {
                    while (i<0)
                    {
                        i= m_modbustool->Write_Client(writesesion->getStartAddress(),writesesion->getnData());
                        if(readCount<10)
                        {
                            readCount++;
                        }
                        else
                        {
                            m_modbusState=false;
                            break;
                        }
                        QThread::msleep(20);
                    }
                }
                writesesion->setModbusState(m_modbusState);
                m_procb->rev(writesesion);
            }
                break;
            case 0x02://写入线圈
            {
                CMWriteBitSsion *writesesion = (CMWriteBitSsion*) sess;
                int i=-1;
                int  readCount=0;

                if(m_modbusState)
                {
                    while(i<0)
                    {
                        i=m_modbustool->Write_Bit_Client(writesesion->getStartAddress(),writesesion->getnData());
                        if(readCount<10)
                        {
                            readCount++;
                        }
                        else
                        {
                            m_modbusState=false;
                            break;
                        }
                        QThread::msleep(20);
                    }
                }
                writesesion->setModbusState(m_modbusState);
                m_procb->rev(writesesion);
            }
                break;
            case 0x03://启动
            {
                CMOpenSession *opensesion = (CMOpenSession*) sess;
                m_comNum=opensesion->getport();
                m_baudNum=opensesion->getrate();
                bool cet =m_modbustool->Modbus_connect(m_comNum,m_baudNum);
                m_modbusState=cet;
                opensesion->setopentype(cet);
                opensesion->setModbusState(cet);
                m_procb->rev(opensesion);
            }
                break;
            case 0x04://读取数据包
            {
                CMReadeDatassion *datasesion = (CMReadeDatassion*) sess;
                QStringList DataList;//数据链表
                int nStartAddress=datasesion->getStartAddress();
                int nData=datasesion->getnData();

                if(m_modbusState)
                {
                    for(int i=0;i<nData;i=i+100)
                    {
                        int readCount=0;
                        if(m_modbustool->Read_Client(nStartAddress+i,100)&&m_modbusState)
                        {
                            for(int i=0;i<100;i++)
                            {
                                QString ndata=QString::number(m_modbustool->req16[i]);
                                DataList<<ndata;
                            }
                        }
                        else
                        {
                            if(readCount<10)
                                readCount++;
                            else
                                m_modbusState=false;
                                break;
                        }
                        QThread::msleep(20);
                    }
                }
                datasesion->setModbusState(m_modbusState);
                datasesion->setList(DataList);
                m_procb->rev(datasesion);
            }
                break;
            case 0x05://断开连接
            {
                CMOpenSession *opensesion = (CMOpenSession*) sess;
                m_modbustool->disconnect_modbus();
                m_modbusState=false;
                opensesion->setModbusState(m_modbusState);
                m_procb->rev(opensesion);
                QThread::msleep(20);
            }
                break;
            case 0x06://重新连接
            {
                CMOpenSession *opensesion = (CMOpenSession*) sess;
                bool cet=m_modbustool->reconnect_modbus();
                m_modbusState=cet;
                opensesion->setModbusState(m_modbusState);
                m_procb->rev(opensesion);
                QThread::msleep(20);
            }
            break;
            }
            QThread::msleep(20);
        }

    }
}

bool CSerialPro::open(int port,int rate)
{
    bool cet =m_modbustool->Modbus_connect(port,rate);
    return cet;
}

bool CSerialPro::close()
{
//    return m_serial_port.close();
    return 0;
}


