#ifndef CGLOBALIF_H
#define CGLOBALIF_H

#include <QObject>
#include "cconfigure.h"
#include "clog.h"
#include "globals.h"
#include "ctools.h"
#include "cdbsession.h"
#include <QValidator>


namespace Comom
{
    class CGlobal: public QObject
    {
        Q_OBJECT
    public:
        static CGlobal * getInstance()
        {
            static CGlobal s_global;
            return &s_global;
        }
        ~ CGlobal();
    private:
          CGlobal();
    public:
        Clog * getLog();
        CConfigure  * getConfigure();
        CTools  * getTools();
        void setValueNum(double aVlaue, double bValue, QString CalibrationTableID);
        QString get_CalibrationTableID();
        QString get_snStr();
        void set_snStr(QString snStr);
        void set_order(ST_Order d_order);
        ST_Order get_order();

        bool get_isqcFlag();
        void set_isqcFlag(bool isqcFlag);



    public:

        int m_ExitFlag=16;       //废卡盒已有数量
        st_ConfigData   m_configData;       //配置表结构体
        st_PrintData  m_printData; //打印要求
        st_User m_NowUser;//当前用户
        ST_Order m_order;
        QQueue <st_CalibData> m_calibData;//校正ab值结构体
        QQueue <st_ItemQ> m_itemData;//项目表结构体
        EM_BIO_LANGUAGE m_lang;//语言
        QValidator *m_validator;
        st_User m_userlist;//全部用户信息

        //st_CalibData m_calibData;
        void setConfigData(st_ConfigData nConfigData);
        st_ConfigData getConfigData();
        st_PrintData getPrintData();

        void setCalibData(QQueue <st_CalibData> nCalibList);
        QQueue <st_CalibData> getCalibData();

        void setitemData(QQueue <st_ItemQ> itemList);
        st_ItemQ getitemData(QString batchStr);
        QString getClinicalStr(QString project);
        QQueue <st_ItemQ> getitemQueue();

        int getExitFlag();
        void setExitFlag(int exitFlag);
        void addExitFlag();
        bool m_PowerOrSleep=true;//开机或者休眠


        //QString versionStr=;

    private:
        Clog            m_log;              //日志打印模块
        CConfigure      m_configure;        //配置文件模块
        CTools          m_tools;            //工具模块
        QString         m_CalibrationTableID;//校正表id
        QString         m_snStr; //sn号
        bool            m_isqcFlag=false; //是否内部结果
    };

}
//commom 入口实例
#define    CGLOBAL          Comom::CGlobal::getInstance()
//配置工具 入口实例
#define    CONFIG           Comom::CGlobal::getInstance()->getConfigure()
//日志
#define    BTLOG           Comom::CGlobal::getInstance()->getLog()

//日志打印宏
#define    PRINT_LOG_DEBUG(F,S)   Comom::CGlobal::getInstance()->getLog()->print(e_debug,F,S)
#define    PRINT_LOG_INFO(F,S)   Comom::CGlobal::getInstance()->getLog()->print(e_info,F,S)
#define    PRINT_LOG_WARN(F,S)   Comom::CGlobal::getInstance()->getLog()->print(e_warn,F,S)
#define    PRINT_LOG_ERROR(F,S)   Comom::CGlobal::getInstance()->getLog()->print(e_error,F,S)
#define    PREFLAG  true
#define    BATCHFLAG  false
#define    DATACSVFLAG  true




#endif // CGLOBALIF_H
