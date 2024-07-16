#include "cmgrmsgrouter.h"

CMgrMsgRouter::CMgrMsgRouter(QObject *parent) : QObject(parent)
{
}

void CMgrMsgRouter::setUserInfo(st_User userInfo)
{
    m_UserState=true;
    m_UserInfo=userInfo;
    emit sgn_login();
}

st_User CMgrMsgRouter::getUserInfo()
{
    return m_UserInfo;
}

void CMgrMsgRouter::setStartType(bool powerOrsleep)
{
    m_PowerOrSleep=powerOrsleep;
}

bool CMgrMsgRouter::getStartType()
{
    return m_PowerOrSleep;
}

void CMgrMsgRouter::set_M_readState(int nTestType, st_MState nState, bool scanFlag)
{
    emit sgn_M_readInfo(nState);
    switch (nTestType)
    {
    case 0:
        emit sgn_M_readtoDiag(nState);//将设备状态传入测试
        break;
    case 1:
        emit sgn_M_StatetoQC(nState);//将设备状态传入质控
        break;
    case 2:
        emit sgn_M_readtoCalib(nState);//将设备状态传入校正
        break;
    default:
        emit sgn_M_readtoDiag(nState);//将设备状态传入测试
        break;
    }
    if(scanFlag)
    {
        switch (nTestType)
        {
        case 0:
            emit sgn_ScanDialog();
            break;
        case 1:
            break;
        case 2:
            emit sgn_ScanCalib();
            break;
        default:
            break;
        }
    }
}

void CMgrMsgRouter::set_M_readData(int nType, int nDataType, QStringList nData)
{
    qDebug()<<"nType"<<nType;
    switch (nType)
    {
    case 0:
        emit sgn_M_DatatoDiag(nDataType,nData);//将数据传入测试
        break;
    case 1:
        emit sgn_M_DatatoQC(nDataType,nData);//将数据传入质控
        break;
    case 2:
        emit sgn_M_DatatoCalib(nDataType,nData);//将数据传入校正
        break;
    case 3:
        emit sgn_M_DatatoMain(nDataType,nData);//将数据传入main
        break;
    default:
        break;
    }
}

void CMgrMsgRouter::setUserIDName(QQueue<QString> ID, QQueue<QString> Name)
{
    QVariant IDVar;
    QVariant NameVar;
    IDVar.setValue(ID);
    NameVar.setValue(Name);
    emit sgn_userIDName(IDVar,NameVar);
}
