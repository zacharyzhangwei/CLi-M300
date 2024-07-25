#ifndef GLOBALS_H
#define GLOBALS_H
#include <QString>
#include <QVariant>
#include <QCoreApplication>

//多国家语言
enum EM_BIO_LANGUAGE{
     LANG_BIO_CHINESE,
     LANG_BIO_CHINESE_C,
     LANG_BIO_ENGLISH
};

typedef struct ConfigData{
    int m_PrintType;//打印机状态非自动打印热敏0，外置2-A4，4-A5 //自动打印热敏1，外置3-A4，5-A5
    int m_PrintSet;//打印条件10进制转2进制字符串按位判断
    double m_Temp_Set;//温度
    double m_Temp_Precision;//精度
    double m_Temp_Alter;//补偿
    double m_Temp_Warning;//报警
    QString m_Set_Info;//一般信息 ID前缀|医院|设备管理员|联系电话|技术工程师|技术支持
    QString m_High_Info;//设备信息 设备名称|设备SN|安装时间
    QString m_Calib_Set;//校正设置 开启状态|显示状态|校正周期|提示周期
    QString m_QC_Set;//质控设置 开启状态|显示状态|质控周期|提示周期
    QString m_PrintInfo;//打印信息 医院名称|床号|电话|提示
    int m_LogFlag;//日志标志位
    int m_LanguageFlag;//语言标志位
    int m_AutoDoor;//自动回仓
    int m_Window;//窗口运行
    double m_Gain;//增值系数
    int m_ModbusWindow;//Modbus窗口
    int m_CycleTime;//周期时间
    int m_CardCount;//废卡盒数
    int m_SleepType;//休眠间隔标志位
} st_ConfigData;




typedef struct CalibData{
    QString m_ID;
    QString m_BatchStr;//批号
    double m_aValue;
    double m_bValue;
} st_CalibData;

typedef struct Order
{
    QList<QString> order_type;
    QList<QStringList> t_order;
    int n_order;
    bool model;
}ST_Order;

typedef struct ItemQ{
    QString ProjectName;//项目名称
    QString ChName;//中文名
    double MinValue;//最小值
    double MaxValue;//最大值
    QString PrintRefer;//打印参考范围
    double CrisisValue;//危急值
    QString Clinical;//临床意义
    int TestTime;//测试时间(s)
    QString Unit;//单位
    double Ratio;//比率
    QString NewUnit;//新单位
    int Language;//语言
    QString Lot;//批号
    int sampleType;//类型
} st_ItemQ;

typedef struct PrintData{
    bool report_Reserve1=false;
    bool report_Reserve2=false;
    bool report_Reserve3=false;
    bool report_TSample=false;
    bool report_TReport=false;
    bool report_TText=false;
    bool report_TSubmit=false;
    bool report_Doctor=false;
    bool report_SubmitBy=false;
    bool report_TextBy=false;
    bool report_ReviewBy=false;
    bool report_Dept=false;
    bool report_Way=false;
    bool report_Type=false;
    bool report_State=false;
    bool report_Range=false;
    int signature_Num=0;
    QString report_Head;
    QString report_reserve1Str;
    QString report_reserve2Str;
    QString report_reserve3Str;
} st_PrintData;



//参数索引号
enum  EM_SETTINGS_IDX
{
    DEF_LANGUAGE =1,  //%1 语言
    DEF_PRINTPORT,   //%2 打印端口
    DEF_MODBUSPORT,  //%3Modbus端口
    DEF_LOG,  //%4日志开关
    DEF_DEPT,//%5科室
    DEF_SUBMIT,//%6送检员
    DEF_REVIEW,//%7审核医生
    DEF_TEST, //%8检验医生
    DEF_PEAK_L, //%9出峰左位置
    DEF_PEAK_R, //%10出峰右位置
    DEF_PEAK_ALL, //%11出峰的总长度
    DEF_BASE_HEAD, //%12基线起始
    DEF_BASE_END, //%13基线结束
    DEF_PRINTTYPE,//%14默认为非自动打印热敏0，外置2-A4，4-A5 //自动打印热敏1，外置3-A4，5-A5
    DEF_TEMPDATA,//%15温度设置信息 设定温度|控制精度|温度补偿|报警温度
    DEF_SETINFO,//%16设备信息 ID前缀|医院|设备管理员|联系电话|技术工程师|技术支持
    DEF_HIGHINFO,//%17设备信息 设备名称|设备SN|安装时间
    DEF_PRINTSET,//%18打印条件
    DEF_CALIBSET,//%19校正设置 开启状态|显示状态|校正周期|提示周期
    DEF_QCSET,//%20质控设置 开启状态|显示状态|质控周期|提示周期
    DEF_PRINTINFO,//21%打印信息 医院名称
    DEF_HISCOM,//%22串口连接  连接状态|串口号|port
    DEF_HISSOCKET,//%23Socket连接  连接状态|IP|端口
    DEF_AutoDoor,//%24仓门自动回收
    DEF_Window,//%25窗口运行
    DEF_Gain,//%26增益系数
    DEF_ModbusWindow,//%27Modbus窗口
    DEF_CYCLETIME,//%28周期时间
    DEF_COM1,//%29串口1  连接状态|串口号|port
    DEF_COM2,//%30串口2  连接状态|串口号|port
    DEF_CARDCOUNT,//%31废卡盒数
    DEF_PRECOM,//%32 Pre串口连接  连接状态|串口号|port
    DEF_SLEEP,//%33 休眠间隔标志位 x*30 0时不休眠

};

typedef struct iniData{
    int type;//类型
    EM_SETTINGS_IDX idx;//iniID
    QVariant val;//数据
} st_iniData;

//系统错误码
enum EM_ERROR_CODE
{
    CODE_SUCCESS,
    CODE_FAILER,
    CODE_TIMEOUT
};
//用于日志模块的一些宏定义
enum enum_level
{
    e_debug,
    e_info,
    e_warning,
    e_error
};

//用于串口相关信息的结构体
typedef struct port_info{
    int port;
    int rate;
} st_port_info;

//用于Socket系统的连接信息
typedef struct tcp_info{
    int state;
    QString ip;
    int port;
}st_tcp_info;

typedef struct com_info{
    int state;
    int port;
    int rate;
} st_com_info;


typedef struct btn_State{
    int btnNumber;
    bool btnState;
} st_btn_State;


//参数默认值, 系统第一次默认值在这里调整，也可以在首次运行后的.ini文件中配置
#define DEFAULT_LANGUAGE        LANG_CHINESE
#define DEFAULT_CONFIG_PATH  QDir::currentPath()+"/config.ini"       //配置文件的默认路径QDir::currentPath()+"/config.ini"
#define DEFAULT_LOG_PATH  QCoreApplication::applicationDirPath()+"/Log"          //日志的默认路径
#define DEFAULT_BTC_PATH  QCoreApplication::applicationDirPath()+"/BtcData"          //BTC的默认路径
#define DEFAULT_SIGNATURE_PATH  QCoreApplication::applicationDirPath()+"/Signature"          //签名的默认路径
#define DEFAULT_LOG_BACKUP_COUNT   5            //日志文件的翻滚数量
#define DEFAULT_LOG_SIZE  (1024*1024*10)        //日志单文件大小10M (1024*1024*10)
#define DEFAULT_VERSION        "V1.0.0.231112"
#define DEFAULT_WEVERSION        "V1.0.231112.1900"
#define DEFAULT_OLDVERSION        "V1.0.231112.1900"




#endif // GLOBALS_H
