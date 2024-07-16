#include "cinitwidget.h"
#include "ui_cinitwidget.h"

CInitWidget::CInitWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CInitWidget)
{
    ui->setupUi(this);


    ui->progressBar->setRange(0,100); //设置进度条最小值和最大值(取值范围)

    m_ErrTimer= new QTimer(this);//读取定时器
    m_ErrTimer->setInterval(60);//设置定时器的时间间隔

    QObject::connect(m_ErrTimer,&QTimer::timeout,this,&CInitWidget::slt_state_Power);//心跳处理
}

CInitWidget::~CInitWidget()
{
    delete ui;
}

void CInitWidget::init()
{
    Control::CInitManager().getInstances()->Init();
}

void CInitWidget::set_Open()
{
    m_ErrTimer->start();
}

void CInitWidget::slt_state_Power()
{
    if(m_BarNumber<30)
    {
        m_BarNumber=m_BarNumber+4;
    }else if(m_BarNumber<80){
        m_BarNumber++;
    }
    else if(m_BarNumber==80)
    {
        m_ErrTimer->stop();
    }
    else if(m_BarNumber>80&&m_BarNumber<100)
    {
        m_BarNumber++;
    }
    else if(m_BarNumber==100)
    {
        m_ErrTimer->stop();
    }
    ui->progressBar->setValue((m_BarNumber));
}

void CInitWidget::on_progressBar_valueChanged(int value)
{
    if(value==100)
    {
        m_ErrTimer->stop();
        this->hide();
        ui->progressBar->setValue((0));
    }
}

void CInitWidget::slt_SelfStatus(bool status)
{
    if(status)
    {
        m_BarNumber=81;
        m_ErrTimer->start();
        //ui->progressBar->setValue(100);
    }
}
