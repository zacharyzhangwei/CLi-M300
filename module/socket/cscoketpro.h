#ifndef CSCOKETPRO_H
#define CSCOKETPRO_H


#include <QObject>
#include <QQueue>
#include <QMutex>
#include <QWaitCondition>
#include <QThread>
#include <QTimer>
#include <QByteArray>
#include <QDebug>
#include <ISession.h>
#include "TCPModule.h"
#include "sockettool.h"
#include "ssession.h"


class CScoketPro: public QObject
{
    Q_OBJECT
public:
    explicit CScoketPro(QObject *parent = nullptr);
    virtual ~CScoketPro();
    bool setSession(ISession *s);
    bool setSessions(QQueue<ISession *> *sses);

public:
    bool init();
    void setcb(TCPModuleCB * cb);
    bool open(QString ip,int port);
    bool close();

private slots:
    void slt_run();
private:
    bool send(QByteArray nStr);

private:
    QQueue<ISession *>  m_Sessionlist;    //请求队列
    QThread           m_TcpThread;  //异步线程
    QMutex            m_mutex;      //线程锁
    QWaitCondition    m_cond;       //条件锁
    bool              m_brun;       //线程运行标志位


    SocketTool        *m_SocketTool;  //socket
    int               m_IP;        //打开的串口
    int               m_Port;        //波特率
    TCPModuleCB       *m_Tcpcb; //上层的回调接口
};

#endif // CSCOKETPRO_H
