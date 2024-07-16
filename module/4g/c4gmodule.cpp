#include "c4gmodule.h"
#include "c4gcache.h"

C4gModule::C4gModule(QObject* parent) : QObject(parent)
{
    QObject::connect(&m_thread, &QThread::started, this,
                     &C4gModule::sltRun);
    this->moveToThread(&m_thread);
    m_brun = true;
    m_thread.start();
}

C4gModule::~C4gModule()
{
    m_brun = false;
    m_cond.notify_all();
    m_thread.quit();
    m_thread.wait();
}

bool C4gModule::setSession(QJsonObject obj)
{
    qDebug()<<"setSessionQJsonObject";
    m_mutex.lock();
    m_commandlist.push_back(obj);
    //最大保留100条未上传记录
    while (m_commandlist.length() > 100) {
        m_commandlist.pop_front();
    }
    m_mutex.unlock();
    m_cond.notify_one();
    return true;
}

void C4gModule::sltRun()
{
    while (m_brun) {
        m_mutex.lock();
        while (m_commandlist.empty() && m_brun) {
            m_cond.wait(&m_mutex);
        }

        if (!m_brun) {
            m_mutex.unlock();
            break;
        }
        QJsonObject obj = m_commandlist.front();
        m_commandlist.pop_front();
        m_mutex.unlock();
        if (obj.size() == 0) {
            continue;
        }

        int dtype = obj.value("dtype").toInt();
        if (dtype == (int)EM_4G_DTYPE::e_get_info) {  //获取信息
            emit signal_session(obj);
            QThread::msleep(200);
        } else if (dtype == (int)EM_4G_DTYPE::e_result) {  //设备状态上报
            emit signal_session(obj);
            QThread::msleep(400);
        } else {
            emit signal_session(obj);
            QThread::msleep(200);
        }
    }
}
