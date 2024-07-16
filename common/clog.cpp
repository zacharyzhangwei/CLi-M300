#include "clog.h"
#include <QDir>
namespace Comom
{
    Clog::Clog()
    {
    }
    Clog::~Clog()
    {
        m_brun = false;
        m_cond.notify_all();
        m_logthread.quit();
        m_logthread.wait();
    }

    void Clog::init(enum_level level,bool bopen)
    {
        m_bopen = bopen;
        m_level = level;
        m_logList.clear();
        m_sPath = DEFAULT_LOG_PATH;
        if(!QDir(m_sPath).exists())
        {
           QDir().mkdir(m_sPath);

        }
        m_curIdx = getIdx();
        removeIdx();
        QString sfull  = QString(m_sPath+"/bo%1.log").arg(m_curIdx);
        m_sfull = sfull;
        if(m_bopen)
        {
            QObject::connect(&m_logthread,&QThread::started,this,&Clog::slt_run);
            this->moveToThread(&m_logthread);     
            m_brun = true;
            m_logthread.start();
        }
    }

    void Clog::close()
    {
        m_bopen = false;
    }

    void Clog::print(enum_level level, const char * format, ...)
    {
        if(!m_bopen)return;       //日志开关
        if(level < m_level) return ; //日志水平
        QString slev;
        va_list argp;
        va_start(argp,format);
        //char * p = va_arg(argp,char*);
        switch(level)
        {
        case e_debug:
            slev+="Debug:---";
            break;
        case e_info:
             slev+="Info:---";
            break;
        case e_warning:
             slev+="Warn:---";
            break;
        case e_error:
             slev+= "Error:---";
            break;
        }
        char szlog[256];
        memset(szlog,0x00,256);
        vsprintf(szlog,format,argp);
        va_end(argp);
        m_mutex.lock();
//        QDateTime current_DateTime =QDateTime::currentDateTime();
//        QString current_StrTime ="--"+current_DateTime.toString("yyyy/MM/dd hh:mm:ss");
        QString s = slev+szlog+"--"+QDateTime::currentDateTime().toString().toStdString().c_str();
        m_logList.push_back(s);
        m_mutex.unlock();
        m_cond.notify_one();
    }

    void Clog::slt_run()
    {
        while(m_brun)
        {
            m_mutex.lock();
            while(m_logList.empty()&&m_brun)
            {
                m_cond.wait(&m_mutex);
            }

            if(!m_brun)
            {
                m_mutex.unlock();
                break;
            }
            QString slog = m_logList.front();
            m_logList.pop_front();
            m_mutex.unlock();

            if(!m_brun) break;

            QFile logfile(m_sfull);
            logfile.open(QFile::WriteOnly| QFile::Append);
            if(logfile.isOpen())
            {
               if(logfile.size()> DEFAULT_LOG_SIZE)
               {
                   QString sfull = m_sPath+"/bo%1.log";
                   m_curIdx++;
                   m_addFlag++;
                   int idx = m_curIdx;
                   sfull = QString(sfull).arg(idx);
                   setIdx(idx);
                   m_sfull = sfull;
                   logfile.close();
                   logfile.setFileName(m_sfull);
                   if(m_addFlag>5)
                   {
                       removeIdx();
                   }
               }
               else
               {
                   logfile.write(slog.toStdString().c_str());
                   logfile.write("\r\n");
               }
            }
            logfile.close();
        }
     }

    int  Clog::getIdx()
    {
       int idx = 0;
       QString sfull = m_sPath+"/idx.cfg";
       QFile file(sfull);
       file.open(QFile::ReadOnly);
       if(!file.exists())
       {
          file.open(QFile::WriteOnly);
          //file.write(QString::number(0).toStdString().c_str());
          file.close();
          return 0;
       }
       if(!file.isOpen())
       {
          return 0;
       }
       idx = file.readAll().toUInt();
       file.close();
       return idx;

    }

    void Clog::setIdx(int idx)
    {
        QString sfull = m_sPath+"/idx.cfg";
        QFile file(sfull);
        file.open(QFile::WriteOnly);
        if(!file.isOpen())
        {
           return;
        }
        QString idxStr=QString::number(idx);
        file.write(idxStr.toStdString().c_str());;
        file.close();
        return;
    }

    void Clog::removeIdx()
    {
        QDir dir(m_sPath);
        if(dir.exists())
        {
            QStringList filters;
            filters<<QString("*.log");
            dir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
            dir.setNameFilters(filters);  //设置文件名称过滤器，只为filters格式
            //统计log格式的文件个数
            int dirCount = dir.count();
            if(dirCount > 0)
            {
                //存储文件名称
                for(int i=0; i<dirCount; i++)
                {
                    QString file_name = dir[i];  //文件名称
                    bool removeFlag=true;
                    for(int i=0; i<5; i++)
                    {
                        QString sfull  = QString("bo%1.log").arg(m_curIdx-i);
                        if(file_name==sfull)
                        {
                            removeFlag=false;
                            break;
                        }
                    }
                    if(removeFlag)
                    {
                        QFile::remove(m_sPath+"/"+file_name);
                    }
                }
            }
        }
    }
}
