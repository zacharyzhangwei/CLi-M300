#ifndef CMGRMSGROUTER_H
#define CMGRMSGROUTER_H
/////////////////////////////////////////
/// \brief The CDBManager class
/// 用于控制层的消息路由
///
#include <QObject>
#include <QQueue>
#include <QDebug>
#include <QVector>
#include <QVariant>
#include <QMetaType>
#include <QVariant>
#include <QString>
#include "control/imhelper.h"


class CMgrMsgRouter : public QObject
{
Q_OBJECT
public:
    static CMgrMsgRouter * getInstances()
    {
        static CMgrMsgRouter s_msgRouter;
        return &s_msgRouter;
    }
    explicit CMgrMsgRouter(QObject *parent = nullptr);

public:
    void setUserInfo(st_User userInfo);
    st_User getUserInfo();

    void setStartType(bool powerOrsleep);//启动类型
    bool getStartType();//启动类型

    void set_M_readState(int nTestType, st_MState nState, bool scanFlag);//获取设备状态
    void set_M_readData(int nType, int nDataType, QStringList nData);//获取设备状态
    void setUserIDName(QQueue<QString> ID, QQueue<QString> Name);

private:
    bool m_UserState=false;//用户状态，在登入界面时为false
    st_User m_UserInfo;//当前用户
    bool m_PowerOrSleep=true;//启动类型

signals:

    void sgn_login();
    void sgn_M_readInfo(st_MState nState);//将设备状态传入调试工具
    void sgn_M_readtoDiag(st_MState nState);//将设备状态传入测试
    void sgn_M_StatetoQC(st_MState nState);//将设备状态传入质控
    void sgn_M_readtoCalib(st_MState nState);//将设备状态传入校正signals:

    void sgn_M_DatatoDiag(int nDataType,QStringList nData);//将设备数据传入测试
    void sgn_M_DatatoQC(int nDataType,QStringList nData);//将设备数据传入质控
    void sgn_M_DatatoCalib(int nDataType,QStringList nData);//将设备数据传入校正
    void sgn_M_DatatoMain(int nDataType,QStringList nData);//将设备数据传入main

    void sgn_ScanDialog();//测试扫描失败
    void sgn_ScanCalib();//校准扫描失败

    void sgn_userIDName(QVariant ID,QVariant Name);


};

#endif // CMGRMSGROUTER_H
