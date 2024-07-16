#ifndef CCONFGMANAGER_H
#define CCONFGMANAGER_H
// 用于获取配置文件ini相关信息
//
#include <QObject>
#include "common/globals.h"
#include"common/cglobal.h"


Q_DECLARE_METATYPE(st_port_info)
namespace Control
{
    class CConfgManager: public QObject
    {
        Q_OBJECT
    public:
        static CConfgManager * getInstance()
        {
            static CConfgManager  s_config;
            return &s_config;
        }
    private:
        CConfgManager();

    private:
        int m_HisComNum;
        int m_PreComNum;
    public:
        void setLang(EM_BIO_LANGUAGE lang);//获取语言
        EM_BIO_LANGUAGE getLang();
        st_port_info getModbusPort();//modbus串口
        void setModbusPort(st_port_info t);//modbus串口
        st_port_info getPrintPort();//打印机串口
        void setPrintPort(st_port_info t);//打印机串口

        st_com_info get1Com();//串口连接  连接状态|串口号|port
        void set1Com(st_com_info comInfo);//串口连接  连接状态|串口号|port
        st_com_info get2Com();//串口连接  连接状态|串口号|port
        void set2Com(st_com_info comInfo);//串口连接  连接状态|串口号|port




        int getHisComNum();
        st_com_info getHisCom();//串口连接  连接状态|串口号|port
        void setHisCom(st_com_info comInfo);//串口连接  连接状态|串口号|port
        st_tcp_info getHisSocket();//Socket连接  连接状态|IP|端口
        void setHisSocket(st_tcp_info tcpInfo);//串口连接  连接状态|串口号|port


        int getPreComNum();
        st_com_info getPreCom();//串口连接  连接状态|串口号|port
        void setPreCom(st_com_info comInfo);//串口连接  连接状态|串口号|port


        void setLogStatus(bool state, bool refreshFlag=true); //日志
        int getLogStatus();//日志状态

        QStringList getDept();     //获取科室
        void setDept(QString DeptStr); // 设置科室
        QStringList getSubmit();//送检员
        void setSubmit(QString SubmitStr);//送检员
        QStringList getReview();//审核员后用于医生
        void setReview(QString ReviewStr);//审核员后用于医生
        QStringList getTest();//检验员
        void setTest(QString TestStr);//检验员

        int getPrintType();//打印类型
        void setPrintType(int nType, bool refreshFlag=true);//打印类型

        QString getTempData();//温度设置信息 设定温度|控制精度|温度补偿|报警温度
        void setTempData(QString nData, bool refreshFlag=true);//温度设置信息 设定温度|控制精度|温度补偿|报警温度

        QString getSetInfo();//一般信息 ID前缀|医院|设备管理员|联系电话|技术工程师|技术支持
        void setSetInfo(QString nInfo, bool refreshFlag=true);//一般信息 ID前缀|医院|设备管理员|联系电话|技术工程师|技术支持

        QString getHighInfo();//设备信息 设备名称|设备SN|安装时间
        void setHighInfo(QString nInfo, bool refreshFlag=true);//设备信息 设备名称|设备SN|安装时间
        void setCycleTime(int cycleTime, bool refreshFlag=true);//周期时间
        void setCardCount(int cardCount, bool refreshFlag=true);//废卡盒数
        int getCardCount();//废卡盒数
        int getCycleTime();//周期时间
        int getPrintSet();//打印类型
        int getAutoDoorInfo();//自动回收仓门
        void setPrintSet(int nNumber, bool refreshFlag=true);//打印类型
        void setAutoDoorInfo(int nState, bool refreshFlag=true);//自动回收仓门
        void setWindowInfo(bool state, bool refreshFlag=true);//窗口运行
        int getWindowInfo();//窗口运行
        void setModbusWindowInfo(bool state, bool refreshFlag=true);//modbus窗口
        int getModbusWindowInfo();//modbus窗口

        void setSetCalib(QString nInfo, bool refreshFlag=true);//校正设置 开启状态|显示状态|校正周期|提示周期
        QString getSetCalib();//校正设置 开启状态|显示状态|校正周期|提示周期

        void setSetQC(QString nInfo, bool refreshFlag=true);//质控设置 开启状态|显示状态|质控周期|提示周期
        QString getSetQC();//质控设置 开启状态|显示状态|质控周期|提示周期

        QString getPrintInfo();//打印信息 医院名称|床号|电话|提示
        void setPrintInfo(QString nInfo, bool refreshFlag=true);//打印信息 医院名称

        double getGainInfo();//增益系数
        void setGainInfo(double info, bool refreshFlag=true);

        void getConfigInfo();
        bool setConfigReview();

        int getSleepType();//休眠间隔
        void setSleepType(int sleepTime, bool refreshFlag=true);//休眠间隔

    };

}

#endif // CCONFGMANAGER_H
