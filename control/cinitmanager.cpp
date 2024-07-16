#include "cinitmanager.h"
#include "cdbmanager.h"
#include "cmodbusmanager.h"
#include "chismanager.h"
#include "csetmanager.h"
#include "cconfgmanager.h"
#include "chlcpeakmanager.h"
#include "common/cglobal.h"

namespace Control
{

    CInitManager::CInitManager()
    {


    }

    CInitManager::~CInitManager()
    {

    }

    void CInitManager::Init()
    {
        //打开日志
        int log = 0;
        log = CConfgManager::getInstance()->getLogStatus();
        qDebug()<<"log"<<log;
        Comom::CGlobal::getInstance()->getLog()->init(e_debug,log);
        //获取modbus串口,并初始化
        st_port_info t1 = CConfgManager::getInstance()->getModbusPort();
        qDebug()<<"t1"<<t1.port;
        CModBusManager::getInstance()->init(t1.port,t1.rate);
        //获取print串口，并初始化
        st_port_info t2 = CConfgManager::getInstance()->getPrintPort();
        CPrintManager::getInstance()->Init(t2.port,t2.rate);
        //初始化算法模块
        ChlcpeakManager::getInstance()->Init();
        //初始化前置处理模块
    }

    void CInitManager::HisInit()
    {
        //获取HIS串口，并初始化
        st_com_info t3 = CConfgManager::getInstance()->getHisCom();
        qDebug()<<"t3Ip"<<t3.port;
        qDebug()<<"t3port"<<t3.rate;
        qDebug()<<"t3state"<<t3.state;
        CHISManager::getInstance()->Init();
        if(t3.state==1)
        {
         //   CSetManager::getInstances()->setComLabState(CHISManager::getInstance()->setHISOpen(t3.port,t3.rate));
        }
        //获取HIS tcp，并初始化
        st_tcp_info tcp = CConfgManager::getInstance()->getHisSocket();
        qDebug()<<"Ip"<<tcp.ip;
        qDebug()<<"port"<<tcp.port;
        CSocketManager::getInstance()->Init();
        if(tcp.state==1)
        {
            //CSetManager::getInstances()->setTcpLabState(CSocketManager::getInstance()->setSocketOpen(tcp.ip,tcp.port));
        }
    }


}
