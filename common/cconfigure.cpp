#include "cconfigure.h"

#include <QApplication>
#include <QTextCodec>
#include <QDebug>
namespace Comom
{
    CConfigure::CConfigure()
    {
    }
    void CConfigure::init(QString strPath)
    {
        qDebug()<<"strPath"<<strPath;
        m_settings=new QSettings(strPath,QSettings::IniFormat);
        m_settings->sync();
        //m_settings.setPath(QSettings::IniFormat,QSettings::UserScope,strPath);
//        m_settings->beginGroup("Report");
//        m_settings->setIniCodec(QTextCodec::codecForName("utf-8"));
//        m_settings->setValue("Edit_Reserve_1","cscscs");
//        m_settings->endGroup();

    }



    void CConfigure::setParam(EM_SETTINGS_IDX idx, QVariant val)
    {
        m_settings->beginGroup("Biotime");
        QString str  = QString("ID%0").arg(idx);
        m_settings->setValue(str,val);
        m_settings->endGroup();
        m_settings->sync();
    }

    QVariant CConfigure::getParam(EM_SETTINGS_IDX idx)
    {
        m_settings->beginGroup("Biotime");
        QString str  = QString("ID%0").arg(idx);
        QVariant val = m_settings->value(str,-1);
        m_settings->endGroup();
        return val;
    }
    void CConfigure::setParamList(QQueue<EM_SETTINGS_IDX> idxList, QQueue<QVariant> valList)
    {
        m_settings->beginGroup("Biotime");
        while (idxList.size()) {
            QString str = QString("ID%0").arg(idxList.dequeue());
            m_settings->setValue(str,valList.dequeue());
        }
        m_settings->endGroup();
        m_settings->sync();
    }

    QQueue<QVariant> CConfigure::getParamList()
    {
        QQueue<QVariant> valList;
        m_settings->beginGroup("Biotime");
        int i=1;
        while (i<34) {
            QString str  = QString("ID%0").arg(i);
            QVariant val = m_settings->value(str,-1);
            valList<<val;
            i++;
        }
        m_settings->endGroup();
        m_settings->sync();
        return valList;
    }


     //     bool CConfigure::contains(EM_SETTINGS_IDX idx)
     //     {
     //         m_iniMutex.lock();
     //         QString str  = QString("ID%0").arg(idx);
     //         m_iniMutex.unlock();
     //         return  m_settings->contains(str);
     //     }
}
