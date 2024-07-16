#ifndef CCARDMANAGER_H
#define CCARDMANAGER_H
//生成测试项
#include <QObject>
#include <QTime>
#include <QTimer>
#include <QObject>
#include <stdlib.h>
#include <QDebug>

class CCardManager: public QObject
{
    Q_OBJECT
public:
    explicit CCardManager(QObject *parent = nullptr);

private:
    QTimer *m_Time;
    int m_CardCsNum;//测试流水号（对应患者信息）
    int m_CardBitNum;//位号
    QString m_CardBatch;//批号
    bool m_BtcExist;//Btc文件是否存在
    int m_TimeSec;//孵育时间
    int m_TimeNow=0;//当前赋予时长
    bool m_TestFlag=false;//测试结束标志位
    int msecNum=1000;
    bool m_TestWriteFlag=false;
public:
    void set_Card_Num(int nCsNum, int nBitNum, QString nBatch, int payTime=0);//传入测试流水号,位号,批号
    void set_Card_Time(int nTimeSec, bool nBtcExist);//传入时间
    void set_CardBatch(QString batch);//批号


    int get_CardCsNum();//测试流水号（对应患者信息）
    int get_CardBitNum();//位号
    QString get_CardBatch();//批号
    bool get_BtcExist();//Btc文件是否存在
    int get_TimeSec();//孵育时间
    int get_TimeNow();//当前赋予时长
    bool get_TestFlag();//测试结束标志位
    int get_RemainingTime();//返回定时器剩余时间


public slots:
    void set_Now_Time();

signals:
    void time_out(CCardManager*);
    void test_out(CCardManager*);

};

#endif // CCARDMANAGER_H
