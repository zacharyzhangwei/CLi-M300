#ifndef C4GCACHE_H
#define C4GCACHE_H

#include <QJsonObject>
#include <QMutex>
#include <QObject>
#include <QTcpSocket>
#include <QWaitCondition>
#include <QDateTime>
#include <QCoreApplication>
#include <QQueue>
#include <QFile>
#include <QJsonArray>
#include <QSettings>
#include <Windows.h>
#include"common/cglobal.h"
#pragma execution_character_set("utf-8")

// 区分4G数据类型及命令类型
enum class EM_4G_DTYPE
{
    e_get_info = 0,  //本地信息获取
    e_regist = 1,    //注册设备
    e_login = 2,     //设备登录
    e_logout = -2,   //设备退出
    e_status = 3,    //设备状态上报
    e_result = 4,    //上报检测结果
    e_qc = 5,        //上报质控结果
    e_error = 6,     //故障码错误日志上报
    e_sd = 101,      //远程SD卡项目信息升级
    e_soft = 102,    //远程软件升级
};
enum class EM_4G_CMD_TYPE
{
    e_location = 1,  //获取iot-box定位信息
    e_imei=2,          //获取IMEI信息
    e_scsq=3,          //获取信号质量
    e_time=4,          //获取iot-link时间
    e_soft_path=5,      //设置软件包下载位置
};



typedef struct Item_Data{
    QString itemName ;      //项目名称
    QString detectRange ;   //检测范围 用|划分开 如0.0|22.0|
    QString referRange ;    //参考范围 如上
    QString result ;        //检测结果
    QString resultUnit ;    //单位
} st_Item_Data;

typedef struct Test_Data{
    QString projectName;//项目名称
    QString sampleId;   //样本ID
    QString resourceId; //测试流水号
    QString name ;      //患者姓名
    int sex ;       //性别   1 男 2 女 3 其他LLLK
    QString age;        //年龄 xx|x  (年xx|1,月xx|2,周xx|3,日xx|4,小时xx|5)
    QString detectTime; //检测时间 时间格式 xxxx/xx/xx xx:xx:xx
    int cardType;       //试剂卡类型 1单卡 2二联卡 3三联卡
    QString batch;      //试剂批次
    int sampleType; //样本类型
    //全血	1001
    //血清	1002
    //血浆	1003
    //尿液	1004
    //黄疸	1005
    //溶血	1006
    //脂血	1007
    //质控品	1008
    //其他	1009
    QQueue <st_Item_Data> itemData;
} st_Test_Data;




class C4gCache : public QObject
{
    Q_OBJECT
public:
    explicit C4gCache(QObject* parent = nullptr);
    ~C4gCache();
    bool      init();
    void      retryConnect();
    bool      m_4g_connected = false;
    bool      m_4g_registered = false;  //未注册过了
    bool      m_4g_update = false;  //未更新
    QString   m_softRetain;
    bool      m_4g_logined = false;//登入
    QDateTime m_4g_time;  // 4g时间


    QString    m_last_resource_id = "";  //数据库流水号
    QList<int> m_shard_num;              //数据库分片号

private:
    QTcpSocket* m_socket;  // socket客户端
    int getTimestamp(QString timeStr);

    void apkImport(QString newFile, QString oldFile);

public slots:
    void sltStateChanged(QAbstractSocket::SocketState);
    void sltConnected();
    void sltReadData();
    void sltDisconnect();
    void sltSession(QJsonObject sess);
    bool setBtcData(QString btcStr, QString dataStr);
signals:
    void signal_upload_finish(int resourceId);
    void sgn_C4g_State(bool state);


};

#endif  // C4GCACHE_H
