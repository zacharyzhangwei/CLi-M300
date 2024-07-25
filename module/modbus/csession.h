#ifndef CSESSION_H
#define CSESSION_H
#include <QObject>
#include "ISession.h"

typedef struct ModbusState{
    QString nTemp;
    QString nKPa;//扫描结果
    QString nMState;//当前主状态操作（用于判断检验类型）
    QString nOperation;//当前检验状态
    QStringList mState_List;
} st_MState;
Q_DECLARE_METATYPE(st_MState)




//控制枚举
enum  EM_Bit_IDX
{
    DEF_DEVICERESET=200, //设备重置开关
    DEF_SELFTEST=202,   //设备自检开关
    DEF_INIT=203,    //初始化开关
    DEF_PUSHAIR=204,     //排气开关
    DEF_SCAN=205,   //扫码开关
    DEF_CLEANTP=206,//洗针
    DEF_CLEANSHOT=207,//清洗镜头
    DEF_PREACTION=230, //前处理开关
    DEF_DEVTEST=231,  //单周期开关分步法
    DEF_STEST=232, //单周期开关一步法
};

//数据枚举
enum  EM_DATA_IDX
{
    DEF_CONTROL_STATE =200, //设备状态
    DEF_ACTIONSTA=201,
    DEF_STATIE=202,
    DEF_ERRORA=203,
    DEF_ERRORB=204,
    DEF_ERRORC=205,
    DEF_ERRORD=206,
    DEF_ERRORE=207,
    DEF_ERRORF=208,
    DEF_COVERTEM=210,
    DEF_PLATETEM=211,
    DEF_COVERSTA=212,
    DEF_DOORSTA=213,
    DEF_DEVILLIQUOR=214,
    DEF_BUFFER=215,
    DEF_RFCARD=216,


 };



class CSession : public ISession
{
public:
    CSession(){};
    virtual ~CSession(){};
public:
    virtual void  settype(char type);
    virtual char  gettype();
    virtual void setcmd(char cmd);
    virtual char  getcmd();
    virtual QByteArray tostring();
    virtual void setdata(QByteArray data);
    virtual QByteArray getdata();
private:
    char m_cmd;//0读取 1写入data 2写入Bit 3连接 4读取数据
    char m_type;
    QByteArray m_data;

};

//控制板指令。。。。

//打开modbus
class CMOpenSession :public CSession
{
public:
    CMOpenSession(){};
    virtual ~CMOpenSession()override{};
    void setport(int nPort);
    void setrate(int baud);
    int getport();
    int getrate();
    void setopentype(bool type);
    bool getopentype();
    void setModbusState(bool state);
    bool getModbusState();

private:
    int m_Port;
    int m_Baud;
    bool m_Type;
    bool m_state=true;

};



//读取modbus
class CMReadession :public CSession
{
public:
    CMReadession(){};
    virtual ~CMReadession()override{};
    void setStartAddress(unsigned int nStartAddress);//设置起始地址
    unsigned int getStartAddress();
    void setnData(int nData);//设置长度
    int getnData();
    void setList(QStringList nList);
    QStringList getList();
    void setModbusState(bool state);
    bool getModbusState();
private:
    bool m_state=true;
    unsigned int m_startAddress;
    int m_data;
    QStringList m_list;

};
//读取modbus数据
class CMReadeDatassion :public CSession
{
public:
    CMReadeDatassion(){};
    virtual ~CMReadeDatassion()override{};
    void setStartAddress(unsigned int nStartAddress);//设置起始地址
    unsigned int getStartAddress();
    void setnData(int nData);//设置长度
    int getnData();
    void setList(QStringList nList);
    QStringList getList();
    void setnType(int nType);//设置数据返回位置
    int getnType();
    void setDataType(int nDataType);//数据类型
    int getDataType();
    void setModbusState(bool state);
    bool getModbusState();
private:
    bool m_state=true;
    int m_type;//测试类型
    int m_DataType;//测试类型
    unsigned int m_startAddress;
    int m_data;
    QStringList m_list;

};

//写modbus线圈，单位
class CMWriteBitSsion :public CSession
{
public:
    CMWriteBitSsion(){};
    virtual ~CMWriteBitSsion()override{};
    void setStartAddress(unsigned int nStartAddress);//设置起始地址
    unsigned int getStartAddress();
    void setnData(int nData);//写入数据
    int getnData();
    void setModbusState(bool state);
    bool getModbusState();
private:
    bool m_state=true;
    unsigned int m_startAddress;
    int m_data;
};

//写modbus Data，单位
class CMWriteDataSsion :public CSession
{
public:
    CMWriteDataSsion(){};
    virtual ~CMWriteDataSsion()override{};
    void setStartAddress(unsigned int nStartAddress);//设置起始地址
    unsigned int getStartAddress();
    void setnData(int nData);//写入数据
    int getnData();
    void setModbusState(bool state);
    bool getModbusState();
private:
    bool m_state=true;
    unsigned int m_startAddress;
    int m_data;
};



#endif // CSESSION_H
