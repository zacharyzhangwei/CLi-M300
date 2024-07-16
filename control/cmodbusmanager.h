#ifndef CMODBUSMANAGER_H
#define CMODBUSMANAGER_H
/////////////////////////////////////////
/// \brief The CDBManager class
/// 与机器的控制逻辑操作modbus协议
///
#include <QObject>
#include <QTimer>

#include "csession.h"
#include "IModule.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include "control/cmgrmsgrouter.h"


namespace Control
{
    class CModBusManager: public QObject,public IModuleCB
    {
        Q_OBJECT
    public:
        static CModBusManager * getInstance()
        {
            static CModBusManager s_mtmodule;
            return &s_mtmodule;
        }
    private:
        CModBusManager();
        virtual ~CModBusManager();
    public:
        bool init(int port, int baud);
        bool reconnect();
        bool modBusClose();
        bool readData(int nType, int nDataType, unsigned int nStartAddress, int nData);
        bool ModBusData(unsigned int nStartAddress, int nData);
        bool WriteData(unsigned int nStartAddress, int nData);
        bool WriteBit(unsigned int nStartAddress, int nData);
        QStringList getPortNameList();//获取所有可用的串口列表

        void setTestType(int nType);
        int  getTestType();


    public:
        //回调
        virtual void rev(ISession *s);
        bool modbus_flag=false;
        int m_connectFlag=-2;
        bool getModbusFlag();

    private:
        void cb_ReadState(CMReadession *s);
        void cb_WriteBit(CMWriteBitSsion*s);
        void cb_OpenInit(CMOpenSession *s);
        void cb_CloseAgain(CMOpenSession *s);
        void cb_Reconnect(CMOpenSession *s);
        void cb_ReadData(CMReadeDatassion*s);
    private:
        IModule * m_modModule;
        int     m_port;         //modbus串口号
        int     m_baud;         //modbus波特率
        QTimer *m_modbusTimer;      //心跳读取
        bool m_ScanFlag=false;//扫描状态
        int m_TestType=0;//测试类型 0、测试，1、校正，2、质控


     public slots:
        void slt_readState();

    signals:

        void sgn_M_readInfo(QStringList nState);//将设备状态传入测试界面
        void sgn_M_scanData(QStringList nState);//将设备数据传入测试界面
        void sgn_M_testData(QStringList nState);//将设备数据传入测试界面
    };
}
#endif // CMTMODULEMANAGER_H
