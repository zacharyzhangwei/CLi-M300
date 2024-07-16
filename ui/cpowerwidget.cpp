#include "cpowerwidget.h"
#include "ui_cpowerwidget.h"
#include <Windows.h>

CPowerWidget::CPowerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CPowerWidget)
{
    ui->setupUi(this);
}

CPowerWidget::~CPowerWidget()
{
    delete ui;
}

void CPowerWidget::setLastGroup(int pages)
{
    m_lastpages=pages;
//    m_cardSize=cardSize;
}

void CPowerWidget::on_mBtn_OK_clicked()
{
    qDebug()<<"m_cardSize"<<m_cardSize;
    if(m_cardSize==0)
    {
        //CUIMsgRouter::getInstances()->set_blur(40);
        CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,true);
        msgdlog->ui->mLabel_text1->setText(tr("确定关闭设备吗？"));
        msgdlog->ui->mLabel_text2->setText(tr("提示"));
        msgdlog->ui->mBtn_OK->setText(tr("确定"));
        msgdlog->ui->mBtn_Cancel->setText(tr("取消"));
        int nRes=msgdlog->exec();
        //软件重启
        if(nRes==QDialog::Accepted)
        {
            Comom::CGlobal::getInstance()->getTools()->setWinShutdown();//立马关机
        }
        else if(nRes==QDialog::Rejected)
        {
            emit sgn_CancelPower(m_lastpages);
        }
        delete msgdlog;
    }
    else
    {
        //CUIMsgRouter::getInstances()->set_blur(40);
        CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false);
        msgdlog->ui->mLabel_text1->setText(tr("请在空闲状态下关闭系统"));
        msgdlog->ui->mLabel_text2->setText(tr("提示"));
        msgdlog->ui->mBtn_OK->setText(tr("确认"));
        msgdlog->exec();
        delete msgdlog;
    }



}

void CPowerWidget::on_mBtn_Cancel_clicked()
{
    emit sgn_CancelPower(m_lastpages);
}
