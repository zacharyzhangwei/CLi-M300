#ifndef C4GMODULE_H
#define C4GMODULE_H

#include <QJsonObject>
#include <QMutex>
#include <QObject>
#include <QQueue>
#include <QTcpSocket>
#include <QThread>
#include <QWaitCondition>

class C4gCache;
class C4gModule : public QObject {
    Q_OBJECT
public:
    explicit C4gModule(QObject* parent = nullptr);
    virtual ~C4gModule();
    bool setSession(QJsonObject obj);

private:
    bool                m_brun;         // 线程运行标志位
    QThread             m_thread;       // 异步线程
    QQueue<QJsonObject> m_commandlist;  // 请求队列
    QMutex              m_mutex;        // 线程锁
    QWaitCondition      m_cond;         // 条件锁

public slots:
    void sltRun();
signals:
    void signal_session(QJsonObject obj);
};

#endif  // C4GMODULE_H
