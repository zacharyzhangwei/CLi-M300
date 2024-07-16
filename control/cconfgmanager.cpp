#include "cconfgmanager.h"

namespace Control
{
    CConfgManager::CConfgManager()
    {
        getConfigInfo() ;
    }

    void CConfgManager::setLang(EM_BIO_LANGUAGE lang)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setLang");
        CONFIG->setParam(DEF_LANGUAGE,QVariant(lang));

    }
    EM_BIO_LANGUAGE CConfgManager::getLang()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getLang",123123123);
        QVariant lang = CONFIG->getParam(DEF_LANGUAGE);

        Comom::CGlobal::getInstance()->m_configData.m_LanguageFlag=lang.toInt();
        switch (lang.toInt()) {
        case 0:
            return LANG_BIO_CHINESE;
        case 1:
            return LANG_BIO_CHINESE_C;
        case 2:
            return LANG_BIO_ENGLISH;
        default:
            return LANG_BIO_CHINESE;
        }
    }

    void CConfgManager::setSleepType(int sleepType, bool refreshFlag)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setLang");
        CONFIG->setParam(DEF_SLEEP,sleepType);
        if(refreshFlag)
        {
            getSleepType();
        }
    }

    int CConfgManager::getSleepType()
    {
        int sleepType=1;
        QString sleepStr = CONFIG->getParam(DEF_SLEEP).toString();
        qDebug()<<"sleepStr1"<<sleepStr;
        if(sleepStr!="-1")
        {
            sleepType = sleepStr.toInt();
        }
        Comom::CGlobal::getInstance()->m_configData.m_SleepType=sleepType;
        return sleepType;
    }

    st_port_info CConfgManager::getPrintPort()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getPrintPort",123123123);
        QString v = CONFIG->getParam(DEF_PRINTPORT).toString();
        QStringList l = v.split('|');

        st_port_info t;
        t.port = 1;
        t.rate = 115200;
        if(l.size() ==2)
        {
          t.port = l[0].toInt();
          t.rate = l[1].toInt();
        }
        return t;
    }

    void CConfgManager::setPrintPort(st_port_info t)
    {
        CGLOBAL->getConfigure()->setParam(DEF_PRINTPORT,QString::number(t.port)+"|"+QString::number(t.rate));
    }

    st_port_info CConfgManager::getModbusPort()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getModbusPort",123123123);
        QString v = CONFIG->getParam(DEF_MODBUSPORT).toString();
        QStringList l = v.split('|');
        st_port_info t;
        t.port = 3;
        t.rate = 115200;
        if(l.size() ==2)
        {
          t.port = l[0].toInt();
          t.rate = l[1].toInt();
        }
        return t;
    }

    void CConfgManager::setModbusPort(st_port_info t)
    {
       BTLOG->print(e_debug,"%d,%s",111333222,"setModbusPort");
        CONFIG->setParam(DEF_MODBUSPORT,QString::number(t.port)+"|"+QString::number(t.rate));//QVariant::fromValue(t)
    } 

    void CConfgManager::setLogStatus(bool state,bool refreshFlag)
    {
        BTLOG->print(e_debug,"%d,%s",1113332221,"setLogStatus");
        if(state)
        {
            CONFIG->setParam(DEF_LOG,1);
        }
        else
        {
            CONFIG->setParam(DEF_LOG,0);
        }
        if(refreshFlag)
        {
            getLogStatus();
        }
    }

    int CConfgManager::getLogStatus()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getLogStatus",123123123);
        QVariant v = CONFIG->getParam(DEF_LOG);
        Comom::CGlobal::getInstance()->m_configData.m_LogFlag=v.toInt();
        return  v.toInt();
    }

    QStringList CConfgManager::getReview()//审核员后用于医生
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getReview",123123123);
        QString nReviewStr=CONFIG->getParam(DEF_REVIEW).toString();
        return nReviewStr.split("|");
    }

    void CConfgManager::setReview(QString ReviewStr)
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"setReview",123123123);
        CONFIG->setParam(DEF_REVIEW,ReviewStr);
    }

    QStringList CConfgManager::getDept()//科室
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getDept",123123123);
        QString nDeptStr=CONFIG->getParam(DEF_DEPT).toString();
        return nDeptStr.split("|");
    }

    void CConfgManager::setDept(QString DeptStr)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setDept");
        CONFIG->setParam(DEF_DEPT,DeptStr);
    }

    QStringList CConfgManager::getSubmit()//送检医生
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getSubmit",123123123);
        QString nSubmitStr=CONFIG->getParam(DEF_SUBMIT).toString();
        return nSubmitStr.split("|");
    }

    void CConfgManager::setSubmit(QString SubmitStr)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setSubmit");
        CONFIG->setParam(DEF_SUBMIT,SubmitStr);
    }

    void CConfgManager::setTest(QString TestStr)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setTest");
        CONFIG->setParam(DEF_TEST,TestStr);
    }

    QStringList CConfgManager::getTest()//检验医生
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getTest",123123123);
        QString nTestStr=CONFIG->getParam(DEF_TEST).toString();
        return nTestStr.split("|");
    }

    void CConfgManager::setPrintType(int nType,bool refreshFlag)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setPrintType");
        CONFIG->setParam(DEF_PRINTTYPE,nType);
        if(refreshFlag)
        {
            getPrintType();
        }
    }

    int CConfgManager::getPrintType()//打印类型
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getPrintType",123123123);
        //默认为非自动打印热敏0，外置2-A4，4-A5
        //自动打印热敏1，外置3-A4，5-A5
        int r = 0;
        QString nPrintStr=CONFIG->getParam(DEF_PRINTTYPE).toString();
        if(nPrintStr != "-1")
        {
           r = nPrintStr.toInt();
        }

        Comom::CGlobal::getInstance()->m_configData.m_PrintType=r;
        return r;
    }

    //温度设置信息 设定温度|控制精度|温度补偿|报警温度

    void CConfgManager::setTempData(QString nData,bool refreshFlag)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setTempData");
        CONFIG->setParam(DEF_TEMPDATA,nData);
        if(refreshFlag)
        {
            getTempData();
        }
    }

    QString CConfgManager::getTempData()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getTempData",123123123);
        QString r = "0|0|0|0";
        QString nTempStr=CONFIG->getParam(DEF_TEMPDATA).toString();
        if(nTempStr != "-1")
        {
           r = nTempStr;
        }
        QStringList nTempList=r.split("|");

        for (int i = 0; i < nTempList.size(); ++i) {
            QString nTempAtStr=nTempList.at(i);
            switch (i) {
            case 0:
                Comom::CGlobal::getInstance()->m_configData.m_Temp_Set=nTempAtStr.toDouble();
                break;
            case 1:
                Comom::CGlobal::getInstance()->m_configData.m_Temp_Precision=nTempAtStr.toDouble();
                break;
            case 2:
                Comom::CGlobal::getInstance()->m_configData.m_Temp_Alter=nTempAtStr.toDouble();
                break;
            case 3:
                Comom::CGlobal::getInstance()->m_configData.m_Temp_Warning=nTempAtStr.toDouble();
                break;
            default:
                break;
            }
        }

        return r;
    }

    void CConfgManager::setSetInfo(QString nInfo,bool refreshFlag)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setSetInfo");
        CONFIG->setParam(DEF_SETINFO,nInfo);
        if(refreshFlag)
        {
            getSetInfo();
        }
    }

    //一般信息 ID前缀|医院|设备管理员|联系电话|技术工程师|技术支持
    QString CConfgManager::getSetInfo()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getSetInfo",123123123);
        QString r = "|||||";
        QString nSetInfoStr=CONFIG->getParam(DEF_SETINFO).toString();
        if(nSetInfoStr != "-1")
        {
           r = nSetInfoStr;
        }
        Comom::CGlobal::getInstance()->m_configData.m_Set_Info=r;
        return r;

    }
    //设备信息 设备名称|设备SN|安装时间
    void CConfgManager::setHighInfo(QString nInfo,bool refreshFlag)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setHighInfo");
        CONFIG->setParam(DEF_HIGHINFO,nInfo);
        if(refreshFlag)
        {
            getHighInfo();
        }
    }
    QString CConfgManager::getHighInfo()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getHighInfo",123123123);
        QString r = "||";
        QString nHighInfoStr=CONFIG->getParam(DEF_HIGHINFO).toString();
        if(nHighInfoStr != "-1")
        {
           r = nHighInfoStr;
        }
        Comom::CGlobal::getInstance()->m_configData.m_High_Info=r;
        return r;
    }



    void CConfgManager::setPrintSet(int nNumber,bool refreshFlag)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setPrintSet");
        CONFIG->setParam(DEF_PRINTSET,nNumber);
        if(refreshFlag)
        {
            getPrintSet();
        }
    }

    //打印条件10进制转2进制字符串按位判断
    int CConfgManager::getPrintSet()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getPrintSet",123123123);
        int r = 0;
        QString nPrintStr=CONFIG->getParam(DEF_PRINTSET).toString();
        if(nPrintStr != "-1")
        {
           r = nPrintStr.toInt();
        }
        Comom::CGlobal::getInstance()->m_configData.m_PrintSet=r;
        return r;
    }
    //周期时间
    void CConfgManager::setCycleTime(int cycleTime,bool refreshFlag)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setCycleTime");
        CONFIG->setParam(DEF_CYCLETIME,cycleTime);
        if(refreshFlag)
        {
            getCycleTime();
        }
    }

    int CConfgManager::getCycleTime()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getCycleTime",123123123);
        int r = 30;
        QString cycleTimeStr=CONFIG->getParam(DEF_CYCLETIME).toString();
        if(cycleTimeStr != "-1")
        {
           r = cycleTimeStr.toInt();
        }
        if(r<0)
        {
            r = 30;
        }
        Comom::CGlobal::getInstance()->m_configData.m_CycleTime=r;
        return r;
    }

    void CConfgManager::setCardCount(int cardCount, bool refreshFlag)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setCardCount");
        qDebug()<<"setCardCount"<<cardCount;
        CONFIG->setParam(DEF_CARDCOUNT,cardCount);
        if(refreshFlag)
        {
            getCardCount();
        }
    }

    int CConfgManager::getCardCount()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getCardCount",123123123);
        int r = 30;
        QString cardCountStr=CONFIG->getParam(DEF_CARDCOUNT).toString();
        if(cardCountStr != "-1")
        {
           r = cardCountStr.toInt();
        }
        Comom::CGlobal::getInstance()->m_configData.m_CardCount=r;
        qDebug()<<"Comom::CGlobal::getInstance()->m_configData.m_CardCount"<<Comom::CGlobal::getInstance()->m_configData.m_CardCount;
        return r;
    }


    //自动回收仓门默认为1，回收仓门
    void CConfgManager::setAutoDoorInfo(int nState,bool refreshFlag)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setAutoDoorInfo");
        CONFIG->setParam(DEF_AutoDoor,nState);
        if(refreshFlag)
        {
            getAutoDoorInfo();
        }
    }

    int CConfgManager::getAutoDoorInfo()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getAutoDoorInfo",123123123);
        int r = 1;
        QString nPrintStr=CONFIG->getParam(DEF_AutoDoor).toString();
        if(nPrintStr != "-1")
        {
           r = nPrintStr.toInt();
        }
        Comom::CGlobal::getInstance()->m_configData.m_AutoDoor=r;
        return r;
    }
    //窗口运行
    void CConfgManager::setWindowInfo(bool state,bool refreshFlag)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setWindowInfo");
        if(state)
        {
            CONFIG->setParam(DEF_Window,1);
        }
        else
        {
            CONFIG->setParam(DEF_Window,0);
        }
        if(refreshFlag)
        {
            getWindowInfo();
        }
    }

    int CConfgManager::getWindowInfo()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getWindowInfo",123123123);
        int r = 0;
        QString nPrintStr=CONFIG->getParam(DEF_Window).toString();
        qDebug()<<"nPrintStr"<<nPrintStr;
        if(nPrintStr != "-1")
        {
           qDebug()<<"DEF_Window"<<DEF_Window;
           r = nPrintStr.toInt();
        }
        Comom::CGlobal::getInstance()->m_configData.m_Window=r;
        return r;
    }

    //modbus窗口
    void CConfgManager::setModbusWindowInfo(bool state,bool refreshFlag)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setModbusWindowInfo");
        if(state)
        {
            CONFIG->setParam(DEF_ModbusWindow,1);
        }
        else
        {
            CONFIG->setParam(DEF_ModbusWindow,0);
        }
        if(refreshFlag)
        {
            getModbusWindowInfo();
        }
    }

    int CConfgManager::getModbusWindowInfo()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getModbusWindowInfo",123123123);
        int r = 0;
        QString nPrintStr=CONFIG->getParam(DEF_ModbusWindow).toString();
        if(nPrintStr != "-1")
        {
           r = nPrintStr.toInt();
        }
        Comom::CGlobal::getInstance()->m_configData.m_ModbusWindow=r;
        return r;
    }



    //校正设置 开启状态|显示状态|校正周期|提示周期
    void CConfgManager::setSetCalib(QString nInfo,bool refreshFlag)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setSetCalib");
        CONFIG->setParam(DEF_CALIBSET,nInfo);
        if(refreshFlag)
        {
            getSetCalib();
        }
    }

    QString CConfgManager::getSetCalib()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getSetCalib",123123123);
        QString r = "1|1|1|1";
        QString nSetInfoStr=CONFIG->getParam(DEF_CALIBSET).toString();
        qDebug()<<"nSetInfoStr"<<nSetInfoStr;
        if(nSetInfoStr != "-1")
        {
           r = nSetInfoStr;
        }
        qDebug()<<"r"<<r;
        Comom::CGlobal::getInstance()->m_configData.m_Calib_Set=r;
        return r;
    }

    //质控设置 开启状态|显示状态|质控周期|提示周期
    void CConfgManager::setSetQC(QString nInfo,bool refreshFlag)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setSetQC");
        CONFIG->setParam(DEF_QCSET,nInfo);
        if(refreshFlag)
        {
            getSetQC();
        }
    }

    QString CConfgManager::getSetQC()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getSetQC",123123123);
        //质控设置 开启状态|显示状态|质控周期|提示周期
        QString r = "1|1|1|1";
        QString nSetInfoStr=CONFIG->getParam(DEF_QCSET).toString();
        if(nSetInfoStr != "-1")
        {
           r = nSetInfoStr;
        }
        Comom::CGlobal::getInstance()->m_configData.m_QC_Set=r;
        return r;
    }

    //打印信息 医院名称|床号|电话|提示
    void CConfgManager::setPrintInfo(QString nInfo,bool refreshFlag)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setPrintInfo");
        CONFIG->setParam(DEF_PRINTINFO,nInfo);
        if(refreshFlag)
        {
            getPrintInfo();
        }
    }
    QString CConfgManager::getPrintInfo()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getPrintInfo",123123123);
        //打印信息 医院名称|床号|电话|提示
        QString r = "|||";
        QString nSetInfoStr=CONFIG->getParam(DEF_PRINTINFO).toString();
        if(nSetInfoStr != "-1")
        {
           r = nSetInfoStr;
        }
        Comom::CGlobal::getInstance()->m_configData.m_PrintInfo=r;
        return r;
    }



    st_com_info CConfgManager::get1Com()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"get1Com",123123123);
        //串口连接  连接状态|串口号
        st_com_info hisCom;
        hisCom.state=0;
        hisCom.port=0;
        hisCom.rate=115200;

        QString hisComInfo=CONFIG->getParam(DEF_COM1).toString();
        QStringList l = hisComInfo.split('|');
        if(l.size()==3)
        {
            hisCom.state=l[0].toInt();
            hisCom.port=l[1].toInt();
            hisCom.rate=l[2].toInt();
        }
        return hisCom;
    }

    void CConfgManager::set1Com(st_com_info comInfo)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"set1Com");
        CONFIG->setParam(DEF_COM1,QString::number(comInfo.state)+"|"+QString::number(comInfo.port)+"|"+QString::number(comInfo.rate));
    }

    st_com_info CConfgManager::get2Com()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"get2Com",123123123);
        //串口连接  连接状态|串口号
        st_com_info hisCom;
        hisCom.state=0;
        hisCom.port=0;
        hisCom.rate=115200;

        QString hisComInfo=CONFIG->getParam(DEF_COM2).toString();
        QStringList l = hisComInfo.split('|');
        if(l.size()==3)
        {
            hisCom.state=l[0].toInt();
            hisCom.port=l[1].toInt();
            hisCom.rate=l[2].toInt();
        }
        return hisCom;
    }

    void CConfgManager::set2Com(st_com_info comInfo)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"set2Com");
        CONFIG->setParam(DEF_COM2,QString::number(comInfo.state)+"|"+QString::number(comInfo.port)+"|"+QString::number(comInfo.rate));
    }

    int CConfgManager::getHisComNum()
    {
        return m_HisComNum;
    }


    //His串口连接  连接状态|串口号
    st_com_info CConfgManager::getHisCom()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getHisCom",123123123);
        //串口连接  连接状态|串口号
        st_com_info hisCom;
        hisCom.state=0;
        hisCom.port=0;
        hisCom.rate=115200;

        QString hisComInfo=CONFIG->getParam(DEF_HISCOM).toString();
        QStringList l = hisComInfo.split('|');
        if(l.size()==3)
        {
            hisCom.state=l[0].toInt();
            hisCom.port=l[1].toInt();
            hisCom.rate=l[2].toInt();
        }
        if(hisCom.port==1)
        {
            hisCom.port=get1Com().port;
            m_HisComNum=1;
        }
        else
        {
            hisCom.port=get2Com().port;
            m_HisComNum=2;
        }
        return hisCom;
    }

    void CConfgManager::setHisCom(st_com_info comInfo)
    {
        m_HisComNum=comInfo.port;
        BTLOG->print(e_debug,"%d,%s",111333222,"setHisCom");
        CONFIG->setParam(DEF_HISCOM,QString::number(comInfo.state)+"|"+QString::number(comInfo.port)+"|"+QString::number(comInfo.rate));
    }

    int CConfgManager::getPreComNum()
    {
        return m_PreComNum;
    }

    st_com_info CConfgManager::getPreCom()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getpreCom",123123123);
        //串口连接  连接状态|串口号
        st_com_info preCom;
        preCom.state=0;
        preCom.port=0;
        preCom.rate=115200;
        QString preComInfo=CONFIG->getParam(DEF_PRECOM).toString();
        QStringList l = preComInfo.split('|');
        if(l.size()==3)
        {
            preCom.state=l[0].toInt();
            preCom.port=l[1].toInt();
            preCom.rate=l[2].toInt();
        }
        if(preCom.port==1)
        {
            preCom.port=get1Com().port;
            m_PreComNum=1;
        }
        else
        {
            preCom.port=get2Com().port;
            m_PreComNum=2;
        }
        return preCom;
    }

    void CConfgManager::setPreCom(st_com_info comInfo)
    {
        m_PreComNum=comInfo.port;
        BTLOG->print(e_debug,"%d,%s",111333222,"setPreCom");
        CONFIG->setParam(DEF_PRECOM,QString::number(comInfo.state)+"|"+QString::number(comInfo.port)+"|"+QString::number(comInfo.rate));
    }

    //His Socket连接
    st_tcp_info CConfgManager::getHisSocket()
    {
        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getHisSocket",123123123);
        st_tcp_info hisTcp;
        hisTcp.state=0;
        hisTcp.ip="0.0.0.0";
        hisTcp.port=0;

        QString hisTcpInfo=CONFIG->getParam(DEF_HISSOCKET).toString();
        QStringList l = hisTcpInfo.split('|');

        if(l.size()==3)
        {
            hisTcp.state=l[0].toInt();
            hisTcp.ip=l[1];
            hisTcp.port=l[2].toInt();
        }
        return hisTcp;
    }

    void CConfgManager::setHisSocket(st_tcp_info tcpInfo)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setHisSocket");
        CONFIG->setParam(DEF_HISSOCKET,QString::number(tcpInfo.state)+"|"+tcpInfo.ip+"|"+QString::number(tcpInfo.port));
    }



    //增益系数
    void CConfgManager::setGainInfo(double info,bool refreshFlag)
    {
        BTLOG->print(e_debug,"%d,%s",111333222,"setGainInfo");
        CONFIG->setParam(DEF_Gain,info);
        if(refreshFlag)
        {
            getGainInfo();
        }
    }


    double CConfgManager::getGainInfo()
    {

        BTLOG->print(e_debug,"%d,%s,%d",123456789,"getGainInfo",123123123);
        double r = 1;
        QString gainStr=CONFIG->getParam(DEF_Gain).toString();
        qDebug()<<"gainStr"<<gainStr ;
        if(gainStr.toDouble()>0)
        {
           r = gainStr.toDouble();
        }
        Comom::CGlobal::getInstance()->m_configData.m_Gain=r;
        qDebug()<<"m_Gain"<<DEF_Gain<<"r"<<r;
        return r;
    }




    //获取全部信息
    void CConfgManager::getConfigInfo()
    {
        BTLOG->print(e_debug,"%d,%s,%d",11111,"获取开始getConfigInfo",111);
        qDebug()<<"获取getConfigInfo";

        QQueue<QVariant> varList;
        varList=CONFIG->getParamList();

        int i=1;
        while (varList.size()) {
            QVariant val=varList.dequeue();
            BTLOG->print(e_debug,"%d,%s,%s",i,"getConfigInfo",val.toString());
            switch (i)
            {
                case DEF_PRINTTYPE://打印类型
                {
                    //默认为非自动打印热敏0，外置2-A4，4-A5
                    //自动打印热敏1，外置3-A4，5-A5
                    int r = 0;
                    QString nPrintStr=val.toString();
                    if(nPrintStr != "-1")
                    {
                       r = nPrintStr.toInt();
                    }
                    Comom::CGlobal::getInstance()->m_configData.m_PrintType=r;
                }
                    break;
                case DEF_TEMPDATA://温度设置信息
                {
                    QString r = "0|0|0|0";
                    QString nTempStr=val.toString();
                    if(nTempStr != "-1")
                    {
                       r = nTempStr;
                    }
                    QStringList nTempList=r.split("|");

                    for (int i = 0; i < nTempList.size(); ++i) {
                        QString nTempAtStr=nTempList.at(i);
                        switch (i) {
                        case 0:
                            Comom::CGlobal::getInstance()->m_configData.m_Temp_Set=nTempAtStr.toDouble();
                            break;
                        case 1:
                            Comom::CGlobal::getInstance()->m_configData.m_Temp_Precision=nTempAtStr.toDouble();
                            break;
                        case 2:
                            Comom::CGlobal::getInstance()->m_configData.m_Temp_Alter=nTempAtStr.toDouble();
                            break;
                        case 3:
                            Comom::CGlobal::getInstance()->m_configData.m_Temp_Warning=nTempAtStr.toDouble();
                            break;
                        default:
                            break;
                        }
                    }
                }
                    break;
                case DEF_SETINFO://一般信息
                {
                    QString r = "|||||";
                    QString nSetInfoStr=val.toString();
                    if(nSetInfoStr != "-1")
                    {
                       r = nSetInfoStr;
                    }
                    Comom::CGlobal::getInstance()->m_configData.m_Set_Info=r;
                }
                    break;
                case DEF_HIGHINFO://设备信息
                {
                    QString r = "||";
                    QString nHighInfoStr=val.toString();
                    if(nHighInfoStr != "-1")
                    {
                       r = nHighInfoStr;
                    }
                    Comom::CGlobal::getInstance()->m_configData.m_High_Info=r;
                }
                    break;
                case DEF_PRINTSET://打印条件
                {
                    int r = 0;
                    QString nPrintStr=val.toString();
                    if(nPrintStr != "-1")
                    {
                       r = nPrintStr.toInt();
                    }
                    Comom::CGlobal::getInstance()->m_configData.m_PrintSet=r;
                }
                    break;
                case DEF_CALIBSET://校正设置
                {
                    QString r = "1|1|1|1";
                    QString nSetInfoStr=val.toString();
                    if(nSetInfoStr != "-1")
                    {
                       r = nSetInfoStr;
                    }
                    Comom::CGlobal::getInstance()->m_configData.m_Calib_Set=r;
                }
                    break;
                case DEF_QCSET://质控设置
                {
                    //质控设置 开启状态|显示状态|质控周期|提示周期
                    QString r = "1|1|1|1";
                    QString nSetInfoStr=val.toString();
                    if(nSetInfoStr != "-1")
                    {
                       r = nSetInfoStr;
                    }
                    Comom::CGlobal::getInstance()->m_configData.m_QC_Set=r;
                }
                    break;
                case DEF_PRINTINFO://打印信息
                {
                    //打印信息 医院名称|床号|电话|提示
                    QString r = "|||";
                    QString nSetInfoStr=val.toString();
                    if(nSetInfoStr != "-1")
                    {
                       r = nSetInfoStr;
                    }
                    Comom::CGlobal::getInstance()->m_configData.m_PrintInfo=r;
                }
                    break;
                case DEF_HISCOM://串口连接
                {
                    //串口连接  连接状态|串口号
                    st_com_info hisCom;
                    hisCom.state=0;
                    hisCom.port=0;
                    hisCom.rate=115200;

                    QString hisComInfo=val.toString();
                    QStringList l = hisComInfo.split('|');
                    if(l.size()==3)
                    {
                        hisCom.state=l[0].toInt();
                        hisCom.port=l[1].toInt();
                        hisCom.rate=l[2].toInt();
                    }
                    if(hisCom.port==1)
                    {
                        hisCom.port=get1Com().port;
                        m_HisComNum=1;
                    }
                    else
                    {
                        hisCom.port=get2Com().port;
                        m_HisComNum=2;
                    }
                }
                    break;
                case DEF_HISSOCKET://Socket连接
                {
                    st_tcp_info hisTcp;
                    hisTcp.state=0;
                    hisTcp.ip="0.0.0.0";
                    hisTcp.port=0;

                    QString hisTcpInfo=val.toString();
                    QStringList l = hisTcpInfo.split('|');

                    if(l.size()==3)
                    {
                        hisTcp.state=l[0].toInt();
                        hisTcp.ip=l[1];
                        hisTcp.port=l[2].toInt();
                    }
                }
                    break;
                case DEF_AutoDoor://自动回收仓门
                {
                    int r = 1;
                    QString nPrintStr=val.toString();
                    if(nPrintStr != "-1")
                    {
                       r = nPrintStr.toInt();
                    }
                    Comom::CGlobal::getInstance()->m_configData.m_AutoDoor=r;
                }
                    break;
                case DEF_LOG://日志
                {
                    Comom::CGlobal::getInstance()->m_configData.m_LogFlag=val.toInt();
                }
                    break;
                case DEF_Window://窗口运行
                {
                    int r = 0;
                    QString nPrintStr=val.toString();
                    if(nPrintStr != "-1")
                    {
                       r = nPrintStr.toInt();
                    }
                    Comom::CGlobal::getInstance()->m_configData.m_Window=r;
                }
                    break;
                case DEF_Gain://增益系数
                {
                    double r = 1;
                    QString gainStr=val.toString();
                    if(gainStr.toDouble()>0)
                    {
                       r = gainStr.toDouble();
                    }
                    Comom::CGlobal::getInstance()->m_configData.m_Gain=r;
                }
                    break;
                case DEF_ModbusWindow://modbus窗口
                {
                    int r = 0;
                    QString nPrintStr=val.toString();
                    if(nPrintStr != "-1")
                    {
                       r = nPrintStr.toInt();
                    }
                    Comom::CGlobal::getInstance()->m_configData.m_ModbusWindow=r;
                }
                    break;
                case DEF_CYCLETIME://周期时间
                {
                    int r = 30;
                    QString cycleTimeStr=val.toString();
                    if(cycleTimeStr != "-1")
                    {
                       r = cycleTimeStr.toInt();
                    }
                    if(r<0)
                    {
                        r = 30;
                    }
                    Comom::CGlobal::getInstance()->m_configData.m_CycleTime=r;
                }
                    break;
                case DEF_CARDCOUNT://废卡盒数
                {
                    int r = 30;
                    QString cardCountStr=val.toString();
                    if(cardCountStr != "-1")
                    {
                       r = cardCountStr.toInt();
                    }
                    Comom::CGlobal::getInstance()->m_configData.m_CardCount=r;
                }
                    break;
                case DEF_SLEEP://休眠间隔
                {
                    int sleepType=1;
                    QString sleepStr = CONFIG->getParam(DEF_SLEEP).toString();
                    qDebug()<<"sleepStr"<<sleepStr;
                    if(sleepStr!="-1")
                    {
                        sleepType = sleepStr.toInt();
                    }
                    Comom::CGlobal::getInstance()->m_configData.m_SleepType=sleepType;
                }
                    break;
                default:
                    break;
            }
            i++;
        }

//        getPrintType();//打印类型
//        getTempData();//温度设置信息
//        getSetInfo();//一般信息
//        getHighInfo();//设备信息
//        getPrintSet();//打印条件
//        getSetCalib();//校正设置
//        getSetQC();//质控设置
//        getPrintInfo();//打印信息
//        getHisCom();//串口连接
//        getHisSocket();//Socket连接
//        getAutoDoorInfo();//自动回收仓门
////      getLang();//语言
//        getLogStatus();//日志
//        getWindowInfo();//窗口运行
//        getGainInfo();//增益系数
//        getModbusWindowInfo();//modbus窗口
//        getCycleTime();//周期时间
//        getCardCount();//废卡盒数
//        getSleepType();//休眠间隔



        BTLOG->print(e_debug,"%s,%s,%d","m_PrintType",QString::number(Comom::CGlobal::getInstance()->m_configData.m_PrintType),20230418);//打印机状态非自动打印热敏0，外置2-A4，4-A5 //自动打印热敏1，外置3-A4，5-A5
        BTLOG->print(e_debug,"%s,%s,%d","m_PrintSet",QString::number(Comom::CGlobal::getInstance()->m_configData.m_PrintSet),20230418);//打印条件10进制转2进制字符串按位判断
        BTLOG->print(e_debug,"%s,%s,%d","m_Temp_Set",QString::number(Comom::CGlobal::getInstance()->m_configData.m_Temp_Set),20230418);//温度
        BTLOG->print(e_debug,"%s,%s,%d","m_Temp_Precision",QString::number(Comom::CGlobal::getInstance()->m_configData.m_Temp_Precision),20230418);//精度
        BTLOG->print(e_debug,"%s,%s,%d","m_Temp_Alter",QString::number(Comom::CGlobal::getInstance()->m_configData.m_Temp_Alter),20230418);//补偿
        BTLOG->print(e_debug,"%s,%s,%d","m_Temp_Warning",QString::number(Comom::CGlobal::getInstance()->m_configData.m_Temp_Warning),20230418);//报警
        BTLOG->print(e_debug,"%s,%s,%d","m_Temp_Warning",Comom::CGlobal::getInstance()->m_configData.m_Set_Info,20230418); //一般信息 ID前缀|医院|设备管理员|联系电话|技术工程师|技术支持
        BTLOG->print(e_debug,"%s,%s,%d","m_Temp_Warning",Comom::CGlobal::getInstance()->m_configData.m_High_Info,20230418); //设备信息 设备名称|设备SN|安装时间
        BTLOG->print(e_debug,"%s,%s,%d","m_Temp_Warning",Comom::CGlobal::getInstance()->m_configData.m_Calib_Set,20230418); //校正设置 开启状态|显示状态|校正周期|提示周期
        BTLOG->print(e_debug,"%s,%s,%d","m_Temp_Warning",Comom::CGlobal::getInstance()->m_configData.m_QC_Set,20230418); //质控设置 开启状态|显示状态|质控周期|提示周期
        BTLOG->print(e_debug,"%s,%s,%d","m_Temp_Warning",Comom::CGlobal::getInstance()->m_configData.m_PrintInfo,20230418); //打印信息 医院名称|床号|电话|提示
        BTLOG->print(e_debug,"%s,%s,%d","m_LogFlag",QString::number(Comom::CGlobal::getInstance()->m_configData.m_LogFlag),20230418);//日志标志位
        BTLOG->print(e_debug,"%s,%s,%d","m_LanguageFlag",QString::number(Comom::CGlobal::getInstance()->m_configData.m_LanguageFlag),20230418);//语言标志位
        BTLOG->print(e_debug,"%s,%s,%d","m_AutoDoor",QString::number(Comom::CGlobal::getInstance()->m_configData.m_AutoDoor),20230418);//自动回仓
        BTLOG->print(e_debug,"%s,%s,%d","m_Window",QString::number(Comom::CGlobal::getInstance()->m_configData.m_Window),20230418);//窗口运行
        BTLOG->print(e_debug,"%s,%s,%d","m_Gain",QString::number(Comom::CGlobal::getInstance()->m_configData.m_Gain),20230418);//增值系数
        BTLOG->print(e_debug,"%s,%s,%d","m_ModbusWindow",QString::number(Comom::CGlobal::getInstance()->m_configData.m_ModbusWindow),20230418);//Modbus窗口
        BTLOG->print(e_debug,"%s,%s,%d","m_CycleTime",QString::number(Comom::CGlobal::getInstance()->m_configData.m_CycleTime),20230418);//周期时间
        BTLOG->print(e_debug,"%s,%s,%d","m_CardCount",QString::number(Comom::CGlobal::getInstance()->m_configData.m_CardCount),20230418);//废卡盒数
        BTLOG->print(e_debug,"%s,%s,%d","m_SleepType",QString::number(Comom::CGlobal::getInstance()->m_configData.m_SleepType),20230418);//休眠间隔




        qDebug()<<"m_PrintType"<<Comom::CGlobal::getInstance()->m_configData.m_PrintType;
        qDebug()<<"m_Temp_Precision"<<Comom::CGlobal::getInstance()->m_configData.m_Temp_Precision;
        qDebug()<<"m_Temp_Set"<<Comom::CGlobal::getInstance()->m_configData.m_Temp_Set;
        qDebug()<<"m_Temp_Alter"<<Comom::CGlobal::getInstance()->m_configData.m_Temp_Alter;
        qDebug()<<"m_Temp_Warning"<<Comom::CGlobal::getInstance()->m_configData.m_Temp_Warning;
        qDebug()<<"m_Set_Info"<<Comom::CGlobal::getInstance()->m_configData.m_Set_Info;
        qDebug()<<"m_High_Info"<<Comom::CGlobal::getInstance()->m_configData.m_High_Info;
        qDebug()<<"m_PrintSet"<<Comom::CGlobal::getInstance()->m_configData.m_PrintSet;
        qDebug()<<"m_Calib_Set"<<Comom::CGlobal::getInstance()->m_configData.m_Calib_Set;
        qDebug()<<"m_QC_Set"<<Comom::CGlobal::getInstance()->m_configData.m_QC_Set;
        qDebug()<<"m_PrintInfo"<<Comom::CGlobal::getInstance()->m_configData.m_PrintInfo;
        qDebug()<<"m_LogFlag"<<Comom::CGlobal::getInstance()->m_configData.m_LogFlag;
        qDebug()<<"m_LanguageFlag"<<Comom::CGlobal::getInstance()->m_configData.m_LanguageFlag;
        qDebug()<<"m_AutoDoor"<<Comom::CGlobal::getInstance()->m_configData.m_AutoDoor;
        qDebug()<<"m_Window"<<Comom::CGlobal::getInstance()->m_configData.m_Window;
        qDebug()<<"m_Gain"<<Comom::CGlobal::getInstance()->m_configData.m_Gain;
        qDebug()<<"m_ModbusWindow"<<Comom::CGlobal::getInstance()->m_configData.m_ModbusWindow;
        qDebug()<<"m_CycleTime"<<Comom::CGlobal::getInstance()->m_configData.m_CycleTime;
        qDebug()<<"m_CardCount"<<Comom::CGlobal::getInstance()->m_configData.m_CardCount;
        qDebug()<<"m_SleepType"<<Comom::CGlobal::getInstance()->m_configData.m_SleepType;
        qDebug()<<"获取结束getConfigInfo";
        BTLOG->print(e_debug,"%d,%s,%d",11111,"获取结束getConfigInfo",222);
    }

    //设置初始化
    bool CConfgManager::setConfigReview()
    {
        QQueue<EM_SETTINGS_IDX> idxList;
        QQueue<QVariant> valList;


        st_com_info comData;
        comData.port=2;
        comData.state=0;
        comData.rate=115200;

        st_tcp_info tcpInfo;
        tcpInfo.ip="0.0.0.0";
        tcpInfo.port=0;
        tcpInfo.state=0;

        st_com_info comPreData;
        comPreData.port=1;
        comPreData.state=0;
        comPreData.rate=115200;
        /*

        CONFIG->setParam(DEF_HISCOM,QString::number(comData.state)+"|"+QString::number(comData.port)+"|"+QString::number(comData.rate));
        QThread::msleep(100);

        CONFIG->setParam(DEF_HISSOCKET,QString::number(tcpInfo.state)+"|"+tcpInfo.ip+"|"+QString::number(tcpInfo.port));
        QThread::msleep(100);

        CONFIG->setParam(DEF_LOG,1); //日志
        QThread::msleep(100);

        CONFIG->setParam(DEF_DEPT,"");// 设置科室
        QThread::msleep(100);

        CONFIG->setParam(DEF_SUBMIT,"");//送检员
        QThread::msleep(100);

        CONFIG->setParam(DEF_REVIEW,"");//审核员后用于医生
        QThread::msleep(100);

        CONFIG->setParam(DEF_TEST,"");//检验员
        QThread::msleep(100);

        CONFIG->setParam(DEF_PRINTTYPE,0);//打印类型
        QThread::msleep(100);

        CONFIG->setParam(DEF_TEMPDATA,"37|1|0|45");//温度设置信息 设定温度|控制精度|温度补偿|报警温度
        QThread::msleep(100);

        CONFIG->setParam(DEF_SETINFO,"00|||||");//一般信息 ID前缀|医院|设备管理员|联系电话|技术工程师|技术支持
        QThread::msleep(100);

        CONFIG->setParam(DEF_PRINTSET,524282);//打印类型
        QThread::msleep(100);

        CONFIG->setParam(DEF_AutoDoor,1);//自动回收仓门
        QThread::msleep(100);

        CONFIG->setParam(DEF_Window,0);//窗口运行
        QThread::msleep(100);

        CONFIG->setParam(DEF_ModbusWindow,0);//modbus窗口
        QThread::msleep(100);

        CONFIG->setParam(DEF_CALIBSET,"1|1|1|1");//校正设置 开启状态|显示状态|校正周期|提示周期
        QThread::msleep(100);

        CONFIG->setParam(DEF_QCSET,"1|1|1|1");//质控设置 开启状态|显示状态|质控周期|提示周期
        QThread::msleep(100);

        CONFIG->setParam(DEF_PRINTINFO,"检验报告单");//打印信息 医院名称
        QThread::msleep(100);
        qDebug()<<"设置初始化";
        */

        //串口连接  连接状态|串口号|port
        idxList<<DEF_HISCOM;
        valList<<QString::number(comData.state)+"|"+QString::number(comData.port)+"|"+QString::number(comData.rate);
        //Socket连接  连接状态|IP|端口
        idxList<<DEF_HISSOCKET;
        valList<<QString::number(tcpInfo.state)+"|"+tcpInfo.ip+"|"+QString::number(tcpInfo.port);
        //Pre串口连接  连接状态|串口号|port
        idxList<<DEF_PRECOM;
        valList<<QString::number(comPreData.state)+"|"+QString::number(comPreData.port)+"|"+QString::number(comPreData.rate);
        //日志
        idxList<<DEF_LOG;
        valList<<1;
        // 设置科室
        idxList<<DEF_DEPT;
        valList<<"";
        //送检员
        idxList<<DEF_SUBMIT;
        valList<<"";
        //审核员后用于医生
        idxList<<DEF_REVIEW;
        valList<<"";
        //检验员
        idxList<<DEF_TEST;
        valList<<"";
        //打印类型
        idxList<<DEF_PRINTTYPE;
        valList<<0;
        //温度设置信息 设定温度|控制精度|温度补偿|报警温度
        idxList<<DEF_TEMPDATA;
        valList<<"37|1|0|45";
        //一般信息 ID前缀|医院|设备管理员|联系电话|技术工程师|技术支持
        idxList<<DEF_SETINFO;
        valList<<"00|||||";
        //打印类型
        idxList<<DEF_PRINTSET;
        valList<<524282;
        //自动回收仓门
        idxList<<DEF_AutoDoor;
        valList<<1;
        //窗口运行
        idxList<<DEF_Window;
        valList<<0;
        //modbus窗口
        idxList<<DEF_ModbusWindow;
        valList<<0;
        //校正设置 开启状态|显示状态|校正周期|提示周期
        idxList<<DEF_CALIBSET;
        valList<<"1|1|1|1";
        //质控设置 开启状态|显示状态|质控周期|提示周期
        idxList<<DEF_QCSET;
        valList<<"1|1|1|1";
        //打印信息 医院名称
        idxList<<DEF_PRINTINFO;
        valList<<"检验报告单|床号 |电话 |提示";
        //废卡盒数
        idxList<<DEF_CARDCOUNT;
        valList<<30;
        //休眠间隔
        idxList<<DEF_SLEEP;
        valList<<1;

        BTLOG->print(e_debug,"%d,%s",111333222,"setConfigReview");
        CONFIG->setParamList(idxList,valList);


        return true;
    }

}

