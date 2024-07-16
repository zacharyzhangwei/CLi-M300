#ifndef CLOG_H
#define CLOG_H

#include <QObject>
#include <QString>
#include <QQueue>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QFile>
#include "globals.h"
#include <QDateTime>
#include <QDebug>


namespace Comom
{
    class Clog: public QObject
    {
        Q_OBJECT
    public:
        Clog();
        virtual ~Clog();
        void init(enum_level level, bool bopen =false);
        void close();
        void print(enum_level level, const char* format, ...);
        void setIdx(int idx);           //设置索引文件号
    public slots:
        void slt_run();
    private:
        int  getIdx();                  //当前滚动索引位置，在目录下有一个索引文件
        void removeIdx();               //循环删除保留最新的5个日志文件夹
    private:
        QQueue<QString>   m_logList;    //日志队列
        QThread           m_logthread;  //日志异步线程
        QMutex            m_mutex;      //线程锁
        QWaitCondition    m_cond;       //条件锁
        bool              m_bopen;      //日志开关
        enum_level        m_level;      //日志输出水平
        QString           m_sPath;      //log日志目录
        QString           m_sfull;      //日志全路径
        int               m_curIdx;     //日志文件当前滚动索引
        bool              m_brun;       //线程运行标志位
        int               m_addFlag=0;  //判断日志覆盖次数
    };
}

#endif // CLOG_H
