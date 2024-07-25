#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QDir>
#include "cinitmanager.h"
#include "ui_cmsgdialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const QSize MAIN_SIZE_MAX = QSize(16777215, 16777215);
    this->setMaximumSize(MAIN_SIZE_MAX);
    this->setWindowFlag(Qt::WindowMaximizeButtonHint, true);

    //休眠定时器
    m_SleepTimer= new QTimer(this);//读取定时器;
    m_SleepTimer->setInterval(60000);//设置定时器的时间间隔
    m_lastPos=QCursor().pos();
    connect(m_SleepTimer,&QTimer::timeout,[=]()//全选
    {

//        if (//测试列表为空
//                (!Control::CTestManager::getInstances()->getTestState())//无卡
//                &&m_btnState//非不可操作（如校正中，质控中）
//                )//测试界面下
//        {
//            if(QCursor().pos()!=m_lastPos)
//            {
//                m_lastPos=QCursor().pos();
//                m_sleepTamp=Comom::CGlobal::getInstance()->getTools()->get_Timestamp(Comom::CGlobal::getInstance()->getTools()->get_current_StrTime());
//            }
//            else
//            {
//                int nowTamp=Comom::CGlobal::getInstance()->getTools()->get_Timestamp(Comom::CGlobal::getInstance()->getTools()->get_current_StrTime());
//                //间隔是秒

//                if((nowTamp-m_sleepTamp)>(Comom::CGlobal::getInstance()->m_configData.m_SleepType*1800))
//                {
//                    //返回登入界面
//                    m_cloginwidget->show();
//                    ui->stackedWidget->setCurrentIndex(1);
//                    m_SleepTimer->stop();
//                    Comom::CGlobal::getInstance()->m_PowerOrSleep=false;
//                    BTLOG->print(e_debug,"%d,%s,%d",m_sleepTamp,"已修眠",nowTamp);
//                }
//            }
//        }
//        else
//        {
//            m_lastPos.setX(QCursor().pos().x()-1);
//            m_lastPos.setY(QCursor().pos().y()-1);
//        }
    });


    mLab_blure=new QLabel(this);
    mLab_blure->setGeometry(0,0,this->width(),this->height());
    mLab_blure->setStyleSheet("QLabel{background-color:rgb(23,23,23,95);}");
    mLab_blure->hide();
    Init();

    QObject::connect(CMgrMsgRouter::getInstances(),&CMgrMsgRouter::sgn_login,this,&MainWindow::slt_login);
    QObject::connect(m_groupMain, SIGNAL(buttonClicked(int)), this, SLOT(slt_groupMain(int)));
    QObject::connect(m_cpowerwidget,&CPowerWidget::sgn_CancelPower,this,&MainWindow::slt_Power);
//    QObject::connect(CMgrMsgRouter::getInstances(),&CMgrMsgRouter::sgn_M_DatatoMain,this,&MainWindow::slt_M_DatatoMain);
    QObject::connect(m_ctestWidget,&CTestWidget::sgn_selfcheck,this,&MainWindow::slt_DevInit);
    QObject::connect(m_csetWidget,&CSetWidget::sgn_Autotest,this,&MainWindow::slt_Autotest);

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    m_ctestWidget =new CTestWidget(this);
    m_cqcwidget=new CQCwidget(this);
    m_crecordwidget =new CRecordWidget(this);
    m_cpowerwidget=new CPowerWidget(this);
    m_csetWidget=new CSetWidget(this);
    m_cuserWidget=new CUserWidget(this);
    m_ccaliWidget=new CCalibWidget(this);

    ui->mStacked_0_Layout->addWidget(m_ctestWidget);
    ui->mStacked_1_Layout->addWidget(m_cqcwidget);
    ui->mStacked_2_Layout->addWidget(m_ccaliWidget);
    ui->mStacked_3_Layout->addWidget(m_crecordwidget);
    ui->mStacked_4_Layout->addWidget(m_csetWidget);
    ui->mStacked_5_Layout->addWidget(m_cuserWidget);
    ui->mStacked_6_Layout->addWidget(m_cpowerwidget);

    m_cinitWidget =new CInitWidget(this);
    m_cinitWidget->hide();
    m_cloginwidget =new CLoginWidget(this);
    m_cloginwidget->show();

    ui->mLayout->addWidget(m_cinitWidget);
    ui->mLayout->addWidget(m_cloginwidget);

    ui->stackedWidget->setCurrentIndex(1);

    m_groupMain=new QButtonGroup(this);
    m_groupMain->addButton(ui->mBtn_Test,0);
    m_groupMain->addButton(ui->mBtn_QC,1);
    m_groupMain->addButton(ui->mBtn_calib,2);
    m_groupMain->addButton(ui->mBtn_Record,3);
    m_groupMain->addButton(ui->mBtn_Set,4);
    m_groupMain->addButton(ui->mBtn_User,5);
    m_groupMain->addButton(ui->mBtn_Power,6);
    lastgroupId=0;

}

//判断键盘扫描
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"m_ScanStr"<<m_ScanStr;
    qDebug()<<"event->text()"<<event->text();
    qDebug()<<"event->key()"<<event->key();
    //判断是否在测试界面
    if(m_groupMain->checkedId()==0)
    {
        if(event->key() == Qt::Key_Return
                &&(!m_ctestWidget->isHidden())
                &&m_ScanStr.size()!=0)
        {
            qDebug()<<"m_ScanStrkey"<<m_ScanStr;
            if(m_ScanStr==m_LastScanStr)
            {
                //CUIMsgRouter::getInstances()->set_blur(40);
                CMsgDialog *msgdlog;
                msgdlog=new CMsgDialog(true,true,false,false,true,true);
                msgdlog->ui->mLabel_text1->setText(tr("输入重复，是否继续输入?"));
                msgdlog->ui->mLabel_text2->setText(tr("提示"));
                msgdlog->ui->mBtn_OK->setText(tr("确认"));
                msgdlog->ui->mBtn_Cancel->setText(tr("取消"));
                int nRes=msgdlog->exec();
                if(nRes==QDialog::Accepted)
                {
                    m_LastScanStr=m_ScanStr;
                    m_ScanStr.clear();
                }
                else if(nRes==QDialog::Rejected)
                {
                    m_ScanStr.clear();
                }
                delete msgdlog;
            }
            else
            {
                m_LastScanStr=m_ScanStr;
                m_ScanStr.clear();
            }
        }
        else if(event->key() == Qt::Key_Return)
        {
            qDebug()<<"m_ScanStr1key"<<m_ScanStr;
            m_ScanStr.clear();
        }
        else
        {
            m_ScanStr += event->text();
            qDebug()<<"m_ScanStr1"<<m_ScanStr;
        }
    }
}

void MainWindow::slt_Power(int lastpages)
{
    m_groupMain->button(lastpages)->setChecked(true);
    slt_groupMain(lastpages);
}


void MainWindow::slt_blur(int effect)
{
    if(effect==0)
    {
        mLab_blure->hide();
    }
    else
    {
        mLab_blure->show();
    }

}

void MainWindow::slt_login()
{
    //开机登入还是休眠登入
    if(CMgrMsgRouter::getInstances()->getStartType())
    {
        m_cinitWidget->init();
        QThread::msleep(2000);
        if(Control::CModBusManager::getInstance()->getModbusFlag()){
//            if(Control::CModBusManager::getInstance()->WriteBit(DEF_SELFTEST,1)){
//                QThread::msleep(5500);
//                if(Control::CModBusManager::getInstance()->readData(3,1,200,1)){
//                    qDebug()<<"read device state";
//                    m_cloginwidget->setLoginBtnDisabled(false);
//                    m_cloginwidget->hide();
//                    m_cinitWidget->hide();
//                    ui->stackedWidget->setCurrentIndex(0);
//                    ui->mBtn_Test->setChecked(true);
//                    m_cinitWidget->set_Open();
//                }

//            }
            m_cloginwidget->setLoginBtnDisabled(false);
            m_cloginwidget->hide();
            m_cinitWidget->show();
            m_cinitWidget->set_Open();
            m_ctestWidget->selfCheck(1);
//            st_User userinfo = CMgrMsgRouter::getUserInfo();//权限配置实现？

        }else{
            CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,true);
            msgdlog->ui->mLabel_text1->setText(tr("串口连接失败，您可选择进入系统或重新启动"));
            msgdlog->ui->mLabel_text2->setText(tr("提示"));
            msgdlog->ui->mBtn_OK->setText(tr("进入系统"));
            msgdlog->ui->mBtn_Cancel->setText(tr("重新启动"));
            int nRes=msgdlog->exec();
            if(nRes==QDialog::Accepted)
            {
                m_cloginwidget->setLoginBtnDisabled(false);
                m_cloginwidget->hide();
                m_cinitWidget->hide();
                ui->stackedWidget->setCurrentIndex(0);
                ui->mBtn_Test->setChecked(true);
    //            if(Comom::CGlobal::getInstance()->m_configData.m_SleepType==0)
    //            {
    //                m_SleepTimer->stop();
    //            }
    //            else
    //            {
    //                m_SleepTimer->start();
    //            }
            }
            else if(nRes==QDialog::Rejected)//软件重启
            {
                qApp->quit();   // 或者   aApp->closeAllWindows();
                QProcess::startDetached(qApp->applicationFilePath(), QStringList());
            }
            delete msgdlog;
        }

    }
    else
    {

    }
}

void MainWindow::slt_groupMain(int i)
{
    qDebug()<<"lastgroupId"<<lastgroupId<<i;
    BTLOG->print(e_debug,"%d,%s",lastgroupId,"lastgroupId");
    int groupId = m_groupMain->checkedId();
    if(lastgroupId!=m_groupMain->checkedId()){
        ui->mStackedUI->setCurrentIndex(m_groupMain->checkedId());
        switch (groupId){
        case 0:
            m_ctestWidget->show();
            break;
        case 1:
            m_cqcwidget->show();
            break;
        case 2:
            m_ccaliWidget->show();
            break;
        case 3:
            m_crecordwidget->get_RecordInit();
            break;
        case 4:
        case 5:
        case 6:
            m_cpowerwidget->setLastGroup(lastgroupId);
            break;
        default:
            break;
        }
        lastgroupId=groupId;
    }

}

void MainWindow::slt_M_DatatoMain(int dataType, QStringList nData)
{
    if(dataType==1&&nData.size()>0)
    {
        qDebug()<<"device state:"<<nData.at(0);
        if(nData.at(0)=="0"){
            qDebug()<<"selfcheck success";
            if(Control::CModBusManager::getInstance()->WriteBit(DEF_INIT,1)){
                qDebug()<<"init success";

            }
        }


    }
}

void MainWindow::slt_DevInit()
{
//    if(Control::CModBusManager::getInstance()->WriteBit(DEF_INIT,1)){
        m_ctestWidget->selfCheck(2);
        qDebug()<<"init success";
        m_cloginwidget->setLoginBtnDisabled(false);
        m_cloginwidget->hide();
        m_cinitWidget->hide();
        ui->stackedWidget->setCurrentIndex(0);
        ui->mBtn_Test->setChecked(true);
        m_cinitWidget->set_Open();
        //    }
}

void MainWindow::slt_Autotest(bool m_model)
{
    m_ctestWidget->set_testModel(m_model);
}

//设置按键状态
void MainWindow::setBtnEnabledState(QPushButton *btn, bool state)
{
    QString imageStr;
    if(btn->text()==tr("测试"))
    {
        imageStr="background-image: url(:/image/images/icon-测试/Default.png);";
    }
    else if(btn->text()==tr("校正"))
    {
        imageStr="background-image: url(:/image/images/icon-校准/Default.png);";
    }
    else if(btn->text()==tr("质控"))
    {
        imageStr="background-image: url(:/image/images/icon-质控/Default.png);";
    }
    else if(btn->text()==tr("记录"))
    {
        imageStr="background-image: url(:/image/images/icon-历史/Default.png);";
    }
    else if(btn->text()==tr("设置"))
    {
        imageStr="background-image: url(:/image/images/icon-设置/Default.png);";
    }
    else if(btn->text()==tr("账户"))
    {
        imageStr="background-image: url(:/image/images/icon-维护/Default.png);";
    }

    if(state)
    {
        btn->setStyleSheet("QPushButton{ "
                           +imageStr+
                           "background-repeat: no-repeat;"
                           "background-position:left;/*图片位置*/"
                           "background-origin: content;/*图片区域*/"
                           "padding-left: 35px;"
                           "border-radius:12px;"
                           "background-color:rgb(64,64,64);"
                           "font-size:32px; "
                           "color:white;"
                           "}"
                           "QPushButton:hover{"
                           "font-size:32px; "
                           "}"
                           "QPushButton:checked{"
                           "background-color:rgb(31, 78, 121);"
                           "};");
    }
    else
    {
        btn->setStyleSheet("QPushButton{ "
                           +imageStr+
                           "background-repeat: no-repeat;"
                           "background-position:left;/*图片位置*/"
                           "background-origin: content;/*图片区域*/"
                           "padding-left: 35px;"
                           "border-radius:12px;"
                           "background-color:rgb(137,137,137);"
                           "font-size:32px; "
                           "color:white;"
                           "}");
    }
    btn->setEnabled(state);

}


