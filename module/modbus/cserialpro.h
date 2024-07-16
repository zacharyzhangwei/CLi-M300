#ifndef CSERIALMTPRO_H
#define CSERIALMTPRO_H

#include <QObject>

#include <QTimer>
#include <QByteArray>
#include "modbus.h"
#include "csession.h"
#include "modbustool.h"
#include "data/cserialport.h"
#include "IModule.h"
#include "control/cmodbusmanager.h"


class CSerialPro : public QObject
{
    Q_OBJECT
public:
    explicit CSerialPro(QObject *parent = nullptr);
    void setcb(IModuleCB *cb);
public:
    bool open(int port,int rate);
    bool close();
    bool init();
    bool send(ISession *s);

public slots:
    void slt_run();

private:
    void disconnect_proc();

private:
    QQueue<ISession * >  m_sessionlist;    //请求队列
    QThread           m_modbusThread;  //异步线程
    QMutex            m_mutex;      //线程锁
    QWaitCondition    m_cond;       //条件锁
    bool              m_brun;       //线程运行标志位
    ModbusTool*       m_modbustool;
    IModuleCB*        m_procb;       //上层的回调接口
    int               m_comNum;
    int               m_baudNum;
    bool              m_modbusState=false;      //连接状态


};

#endif // CSERIALMTPRO_H
