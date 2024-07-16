#include "cmodbusmanager.h"
namespace Control
{
    CModBusManager::CModBusManager()
    {
        m_modbusTimer= new QTimer(this);//读取定时器
        m_modbusTimer->setInterval(100);//设置定时器的时间间隔
        m_modbusTimer->start();

        m_modModule = getModuleInstance();
        m_modModule->init();
        m_modModule->setcb(this);

        QObject::connect(m_modbusTimer,&QTimer::timeout,this,&CModBusManager::slt_readState);//心跳处理
    }

    CModBusManager::~CModBusManager()
    {

    }


    bool CModBusManager::init(int port,int baud)//启动modbus
    {
        m_port=port;
        m_baud=baud;
        CMOpenSession *ss = new CMOpenSession();
        ss->setcmd(0x03);
        ss->setport(port);
        ss->setrate(baud);
        return m_modModule->send(ss);
    }

    //心跳状态，获取全部状态信息，按需求分配
    void CModBusManager::slt_readState()
    {
        CMReadession *ss= new CMReadession();
        ss->setcmd(0x00);
        ss->setStartAddress(200);
        ss->setnData(100);
        m_modModule->send(ss);
    }

    //写入数据
    bool CModBusManager::WriteData(unsigned int nStartAddress, int nData)
    {
        CMWriteBitSsion *ss= new CMWriteBitSsion();
        ss->setcmd(0x01);
        ss->setStartAddress(nStartAddress);
        ss->setnData(nData);
        return m_modModule->send(ss);
    }

    //写入线圈
    bool CModBusManager::WriteBit(unsigned int nStartAddress, int nData)
    {
        CMWriteBitSsion *ss= new CMWriteBitSsion();
        ss->setcmd(0x02);
        ss->setStartAddress(nStartAddress);
        ss->setnData(nData);
        return m_modModule->send(ss);
    }

    //获取串口号
    QStringList CModBusManager::getPortNameList()
    {
        QStringList m_serialName;
        foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
        {
            m_serialName << info.portName();
        }
        return m_serialName;
    }

    void CModBusManager::setTestType(int nType)
    {
        m_TestType=nType;
    }

    int CModBusManager::getTestType()
    {
        return m_TestType;
    }

    //重新连接
    bool CModBusManager::reconnect()
    {
        CMOpenSession *ss = new CMOpenSession();
        ss->setcmd(0x06);
        return m_modModule->send(ss);
    }

    //断开连接
    bool CModBusManager::modBusClose()
    {
        CMOpenSession *ss = new CMOpenSession();
        ss->setcmd(0x05);
        return m_modModule->send(ss);
    }

    //读取数据包
    bool CModBusManager::readData(int nType,int nDataType,unsigned int nStartAddress,int nData)
    {
        CMReadeDatassion *ss= new CMReadeDatassion();
        ss->setcmd(0x04);
        ss->setDataType(nDataType);
        ss->setnType(nType);
        ss->setStartAddress(nStartAddress);
        ss->setnData(nData);
        return m_modModule->send(ss);
    }

    //调试数据包
    bool CModBusManager::ModBusData(unsigned int nStartAddress,int nData)
    {
        CMReadeDatassion *ss= new CMReadeDatassion();
        ss->setcmd(0x04);
        ss->setStartAddress(nStartAddress);
        ss->setnData(nData);
        return m_modModule->send(ss);
    }

    void CModBusManager::rev(ISession *s)
    {
        switch (s->getcmd())
        {
        case 0x00://状态读取
            cb_ReadState((CMReadession*)s);
            break;
        case 0x01://写入data
            break;
        case 0x02://写入线圈
            cb_WriteBit((CMWriteBitSsion*)s);
            break;
        case 0x03://开启modbus
            cb_OpenInit((CMOpenSession*)s);
            break;
        case 0x04://读取数据包
            cb_ReadData((CMReadeDatassion*)s);
            break;
        case 0x05://断联
            cb_CloseAgain((CMOpenSession*)s);
        case 0x06://重新连接
            cb_Reconnect((CMOpenSession*)s);
            break;
        }
        delete (CSession*)s;
    }

    bool CModBusManager::getModbusFlag()
    {
        return modbus_flag;
    }

    void CModBusManager::cb_ReadState(CMReadession *s)
    {
        if(s->getModbusState())
        {
            QStringList m_readstate;
            m_readstate=s->getList();
            emit sgn_M_readInfo(m_readstate);
//            CMgrMsgRouter::getInstances()->set_M_readState(m_TestType,nState,m_ScanFlag);
//            if(m_ScanFlag)
//            {
//                m_ScanFlag=false;
//            }
        }
        else
        {
            qDebug()<<"modbus_flag1"<<modbus_flag;
            modbus_flag=false;
            m_connectFlag=-1;
        }
    }

    void CModBusManager::cb_WriteBit(CMWriteBitSsion *s)
    {
//        if(s->getModbusState())
//        {
//            m_WriteFlag=true;
//        }
//        else
//        {
//            qDebug()<<"modbus_flag2"<<modbus_flag;
//            modbus_flag=false;
//            m_connectFlag=-1;
//        }
    }

    void CModBusManager::cb_OpenInit(CMOpenSession *s)
    {
        qDebug()<<"cb_OpenInit";
        if(s->getModbusState())
        {
            modbus_flag=s->getopentype();
            m_connectFlag=0;
        }
        else
        {
            qDebug()<<"modbus_flag3"<<modbus_flag;
            qDebug()<<"m_connectFlag"<<m_connectFlag;
            if(m_connectFlag==-2)
            {
                modbus_flag=false;
                qDebug()<<"modbus初始开启失败"<<modbus_flag;
            }
        }
    }

    void CModBusManager::cb_CloseAgain(CMOpenSession *s)
    {
    }

    void CModBusManager::cb_Reconnect(CMOpenSession *s)
    {
    }

    void CModBusManager::cb_ReadData(CMReadeDatassion *s)
    {
        switch (s->getnType()) {
        case 0:
            if(s->getModbusState()){
                QStringList m_readdata;
                m_readdata=s->getList();
                emit sgn_M_scanData(m_readdata);
            }else{
                qDebug()<<"modbus_flag4"<<modbus_flag;
                modbus_flag=false;
                m_connectFlag=-1;
            }

            break;
        case 1:
            if(s->getModbusState()){
                QStringList m_readdata;
                m_readdata=s->getList();
                emit sgn_M_testData(m_readdata);

            }
//        default:
//            break;
        }
    }


}
