#ifndef CPSERIALPRO_H
#define CPSERIALPRO_H

#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QThread>
#include "data/cserialport.h"
#include <QTimer>
#include <QByteArray>
#include <QDebug>
#include <ISession.h>
#include "IPModule.h"

class CPSerialPro : public QObject
{
    Q_OBJECT
public:
    explicit CPSerialPro(QObject *parent = nullptr);
    virtual ~CPSerialPro();
    bool setSession(ISession *s);
    bool setSessions(QQueue<ISession *> *sses);

public:
    bool init();
    void setcb(IPModuleCB * cb);
    bool open(int port,int rate);
    bool close();
    void setprintOrHis(bool printOrHis);

private slots:
    void slt_run();
private:
    bool send(QByteArray nStr);

private:
    QQueue<ISession *>  m_Sessionlist;    //请求队列
    QThread           m_pseriaThread;  //异步线程
    QMutex            m_mutex;      //线程锁
    QWaitCondition    m_cond;       //条件锁
    bool              m_brun;       //线程运行标志位
    Data::CSerialPort    *m_serial_port;  //串口下层模块，已经有异步线程
    int                 m_port;        //打开的串口
    int                 m_rate;        //波特率
    IPModuleCB                *m_cb;
    bool m_printOrHis;//判断打印或HIS
};

#endif // CSERIALMTPRO_H
