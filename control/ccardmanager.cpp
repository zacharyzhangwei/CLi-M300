#include "ccardmanager.h"

CCardManager::CCardManager(QObject *parent) : QObject(parent)
{

    m_Time=new QTimer();
    m_Time->setInterval(1000);  //设置定时器的时间间隔
    m_Time->setTimerType(Qt::PreciseTimer);
    connect(m_Time,SIGNAL(timeout()),this,SLOT(set_Now_Time()));//定时时间到达时  执行按钮槽函数内容
}

void CCardManager::set_Card_Num(int nCsNum, int nBitNum, QString nBatch,int payTime)//传入测试流水号,位号,批号,补偿时间
{
    m_CardCsNum = nCsNum;//测试流水号（对应患者信息）
    m_CardBitNum = nBitNum;//位号
    m_CardBatch = nBatch;//批号
    msecNum=1000-payTime;
    if(msecNum<0)
    {
        m_Time->start(1000);
    }
    else
    {
        m_Time->start(msecNum);
    }

}

void CCardManager::set_Card_Time(int nTimeSec, bool nBtcExist)
{
    m_BtcExist=nBtcExist;//Btc文件是否存在(也用于判断测试状态(作废))
   // nTimeSec=10;
    nTimeSec=nTimeSec*60;
    m_TimeSec=nTimeSec;
    m_TimeNow=nTimeSec-m_TimeNow;//倒计时(减去已有时间)=nTimeSec-m_TimeNow;//倒计时(减去已有时间)
    if(m_BtcExist)
    {
        int card_abs_time=abs(m_TimeNow);//绝对值
        if(card_abs_time>(nTimeSec/10)&&m_TimeNow<0)//超时进行报废
        {
            m_BtcExist=false;
            m_TestFlag=true;
            m_Time->stop();
            emit time_out(this);
        }
        else if(m_TimeNow<0)//未超时开始测试
        {
            m_TestFlag=true;
            m_Time->stop();
            emit time_out(this);
        }
    }
}

void CCardManager::set_CardBatch(QString batch)
{
    m_CardBatch = batch;
}

void CCardManager::set_Now_Time()//倒计时结束
{

   // qDebug()<<"倒计时结束"<<QDateTime::currentMSecsSinceEpoch()/1000<<"m_CardBitNum"<<m_CardBitNum<<"m_TimeNow"<<m_TimeNow;
    if(msecNum!=1000)
    {
        msecNum=1000;
        m_Time->start(msecNum);
    }
    if(m_BtcExist)//判断是否存在Btc文件
    {
        if(m_TimeNow==0)
        {
            qDebug()<<"m_TimeNow"<<m_TimeNow;
            m_TestFlag=true;
            m_Time->stop();
            emit time_out(this);
        }
        else if(m_TimeNow<15&&(!m_TestWriteFlag))
        {
            m_TestWriteFlag=true;
            emit test_out(this);
        }
        m_TimeNow--;
    }
    else
    {
        if(m_TimeNow>1800)//设置报废倒计时
        {
            m_TestFlag=true;
            m_Time->stop();
            emit time_out(this);
        }
        m_TimeNow++;
    }
}
int CCardManager::get_CardCsNum()//测试流水号（对应患者信息）
{
    return m_CardCsNum;
}
int CCardManager::get_CardBitNum()//位号
{
    return m_CardBitNum;
}
QString CCardManager::get_CardBatch()//批号
{
    return m_CardBatch;
}
bool CCardManager::get_BtcExist()//Btc文件是否存在
{
    return m_BtcExist;
}
int CCardManager::get_TimeSec()//孵育时间
{
    return m_TimeSec;
}
int CCardManager::get_TimeNow()//当前孵育时长
{
    return m_TimeNow;
}
bool CCardManager::get_TestFlag()//测试结束标志位
{
    return m_TestFlag;
}

int CCardManager::get_RemainingTime()
{
    return m_Time->remainingTime();
}
