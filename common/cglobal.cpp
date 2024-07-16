#include "cglobal.h"
#include <QTime>
#include <QDir>
#include <QDateTime>
Comom::CGlobal * s = Comom::CGlobal::getInstance();
namespace Comom
{
    CGlobal::CGlobal()
    {
         //m_log.init(e_debug,true);
         m_configure.init(DEFAULT_CONFIG_PATH);
         // for log test
         //m_log.print(e_debug,(char *)"%s,%s",QDateTime::currentDateTime().toString().toStdString().c_str(),"测试日志");
         //m_log.print(e_info,(char *)"%s,%s",QDateTime::currentDateTime().toString().toStdString().c_str(),"测试日志");
        // m_log.print(e_error,(char *)"%s,%s",QDateTime::currentDateTime().toString().toStdString().c_str(),"测试日志");
    }
    CGlobal::~CGlobal()
    {
        //delete m_configure;
        QRegExp rx = QRegExp("[^']*");  //限制以下特殊符号在lineEdit中的输入
        m_validator= new QRegExpValidator(rx);

    }
    Clog * CGlobal::getLog()
    {
        return &m_log;
    }
    CConfigure  * CGlobal::getConfigure()
    {
        return &m_configure;
    }

    CTools *CGlobal::getTools()
    {
        return &m_tools;
    }

    QString CGlobal::get_CalibrationTableID()
    {
        return m_CalibrationTableID;
    }

    QString CGlobal::get_snStr()
    {
        return m_snStr;
    }

    void CGlobal::set_snStr(QString snStr)
    {
        m_snStr=snStr;
    }

    void CGlobal::set_order(ST_Order d_order)
    {
        m_order=d_order;
    }

    ST_Order CGlobal::get_order()
    {
        return m_order;
    }

    bool CGlobal::get_isqcFlag()
    {
        return m_isqcFlag;
    }

    void CGlobal::set_isqcFlag(bool isqcFlag)
    {
        m_isqcFlag=isqcFlag;
    }

    void CGlobal::setConfigData(st_ConfigData nConfigData)
    {
        m_configData=nConfigData;
    }

    st_ConfigData CGlobal::getConfigData()
    {
        return m_configData;
    }

    st_PrintData CGlobal::getPrintData()
    {
        return m_printData;
    }

    void CGlobal::setCalibData(QQueue <st_CalibData> nCalibList)
    {
        m_calibData=nCalibList;
    }

    QQueue <st_CalibData> CGlobal::getCalibData()
    {
        return m_calibData;
    }

    void CGlobal::setitemData(QQueue<st_ItemQ> itemList)
    {
        m_itemData=itemList;
    }

    st_ItemQ CGlobal::getitemData(QString batchStr)
    {
        st_ItemQ itemData;
        for (int i = 0; i < m_itemData.size(); ++i)
        {
            //判断批号是否一致
            if(batchStr==m_itemData.at(i).Lot)
            {
                itemData=m_itemData.at(i);
                break;
            }
        }
        return itemData;
    }

    QString CGlobal::getClinicalStr(QString project)
    {
        QString clinicalStr;
        for (int i = 0; i < m_itemData.size(); ++i)
        {
            //判断批号是否一致
            if(project==m_itemData.at(i).ProjectName)
            {
                if(!m_itemData.at(i).Clinical.isEmpty())
                {
                    clinicalStr=m_itemData.at(i).Clinical;
                    break;
                }
            }
        }
        return clinicalStr;
    }

    QQueue<st_ItemQ> CGlobal::getitemQueue()
    {
        return m_itemData;
    }

    int CGlobal::getExitFlag()
    {
        return m_ExitFlag;

    }

    void CGlobal::setExitFlag(int exitFlag)
    {
        m_ExitFlag=exitFlag;
    }

    void CGlobal::addExitFlag()
    {
        m_ExitFlag++;
    }

}


