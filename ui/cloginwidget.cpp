#include "cloginwidget.h"
#include "ui_cloginwidget.h"
#include <Windows.h>
CLoginWidget::CLoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CLoginWidget)
{
    ui->setupUi(this);
    QRegExp rx = QRegExp("[^']*");  //限制以下特殊符号在lineEdit中的输入
    QValidator *validator= new QRegExpValidator(rx);
    ui->mEdit_Backup_Password->setValidator(validator);
    ui->mEdit_Password->setValidator(validator);
    ui->mEdit_Password_Admin->setValidator(validator);
    ui->mEdit_Password_Set->setValidator(validator);
    ui->mEdit_Password_Set2->setValidator(validator);
    ui->lab_Login_1->hide();
    ui->lab_Login_2->hide();
    ui->lab_Login_5->hide();
    ui->lab_Login_6->hide();
    ui->lab_Login_7->hide();
    ui->lab_Login_8->hide();
    ui->lab_Login_9->hide();

    ui->mCom_Modbus->blockSignals(true);   //锁上。addItem更改值时不触发currentIndexChanged信号
    ui->mCom_Modbus->addItems(Control::CModBusManager::getInstance()->getPortNameList());
    ui->mCom_Modbus->blockSignals(false);   //解锁

    ui->mCom_Print->blockSignals(true);   //锁上。addItem更改值时不触发currentIndexChanged信号
    ui->mCom_Print->addItems(Control::CModBusManager::getInstance()->getPortNameList());
    ui->mCom_Print->blockSignals(false);   //解锁

    ui->mCom_COM1->blockSignals(true);   //锁上。addItem更改值时不触发currentIndexChanged信号
    ui->mCom_COM1->addItems(Control::CModBusManager::getInstance()->getPortNameList());
    ui->mCom_COM1->blockSignals(false);   //解锁
    ui->mCom_COM2->blockSignals(true);   //锁上。addItem更改值时不触发currentIndexChanged信号
    ui->mCom_COM2->addItems(Control::CModBusManager::getInstance()->getPortNameList());
    ui->mCom_COM2->blockSignals(false);   //解锁
    //串口设置刷新
    config_refresh();

    ui->mLab_Version->setText(DEFAULT_WEVERSION);
    ui->mBtn_Pre_State->hide();

    ui->mStacked_login->setCurrentIndex(0);

    Control::CLoginManager::getInstances()->getDBUserList();

    QObject::connect(Control::CLoginManager::getInstances(),&Control::CLoginManager::sgn_UserList,this,&CLoginWidget::slt_UserList);
    QObject::connect(Control::CLoginManager::getInstances(),&Control::CLoginManager::sgn_loginState,this,&CLoginWidget::slt_loginState);
 }

CLoginWidget::~CLoginWidget()
{
    delete ui;
}

void CLoginWidget::setLoginBtnDisabled(bool state)
{
    ui->mBtn_Login->setDisabled(state);
}

//初始化用户列表信息
void CLoginWidget::slt_UserList(QQueue<st_User> userList)
{
    QStringList idList;
    QStringList  idSetList;
    QStringList idAdminList;
    while (userList.size())
    {
        st_User userData=userList.dequeue();
        QString nPermissionsBitStr=qPrintable(QString::number(userData.Permissions,2));
        for (int var = nPermissionsBitStr.length(); var < 9; ++var) {
            nPermissionsBitStr="0"+nPermissionsBitStr;
        }
        if(nPermissionsBitStr.mid(6,1).toInt()==1)
        {
            idAdminList<<userData.ID;
        }
        if(userData.ID!="admin")
        {
            idSetList<<userData.ID;
        }
        idList<<userData.ID;
    }
    ui->mCombo_ID->clear();
    ui->mCombo_ID_Admin->clear();
    ui->mCombo_ID_Set->clear();

    ui->mCombo_ID->addItems(idList);
    ui->mCombo_ID_Admin->addItems(idAdminList);
    ui->mCombo_ID_Set->addItems(idSetList);
}

//登入返回结果
void CLoginWidget::slt_loginState(int type,bool state)
{
    //判断密码是否正确
    if(!state)
    {
        switch (type)
        {
        case 0:
        {
            setLoginBtnDisabled(false);
            //::getInstances()->set_blur(40);
            CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,true);
            msgdlog->ui->mLabel_text1->setText(tr("密码错误，请重试"));
            msgdlog->ui->mLabel_text2->setText(tr("提示"));
            msgdlog->ui->mBtn_OK->setText(tr("重新输入"));
            msgdlog->ui->mBtn_Cancel->setText(tr("忘记密码"));
            int nRes=msgdlog->exec();
            if(nRes==QDialog::Accepted)
            {
                ui->mEdit_Password->clear();
            }
            else if(nRes==QDialog::Rejected)
            {
                //处理按下取消或者关闭按钮的语句
                on_mBtn_Reset_Password_clicked();
            }
            delete msgdlog;
        }
            break;
        case 1:
        {
            //CUIMsgRouter::getInstances()->set_blur(40);
            CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false);
            msgdlog->ui->mLabel_text1->setText(tr("密码错误，请重试"));
            msgdlog->ui->mLabel_text2->setText(tr("提示"));
            msgdlog->ui->mBtn_OK->setText(tr("重新输入"));
            int nRes=msgdlog->exec();
            if(nRes==QDialog::Accepted)
            {
                ui->mEdit_Password_Admin->clear();
            }
            delete msgdlog;
        }
            break;
        }
    }
    else
    {
        switch (type){
        case 0:
        {
            ui->mEdit_Password->clear();
        }
            break;
        case 1:
        {
            ui->mEdit_Password_Admin->clear();
            ui->mStacked_login->setCurrentIndex(2);
        }
            break;
        }
    }
}

//取消登入，用于清空密码
void CLoginWidget::on_mBtn_Cancel_clicked()
{
    ui->mEdit_Password->clear();
    modbusNum++;
    if(modbusNum==7)
    {
        ui->mStacked_login->setCurrentIndex(3);
        modbusNum=0;
    }
}

//登入
void CLoginWidget::on_mBtn_Login_clicked()
{
    if(ui->mEdit_Password->text().isEmpty())
    {
        //CUIMsgRouter::getInstances()->set_blur(40);
        CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false);
        msgdlog->ui->mLabel_text1->setText(tr("输入框为空"));
        msgdlog->ui->mLabel_text2->setText(tr("提示"));
        msgdlog->exec();
        delete msgdlog;
    }
    else
    {
        if(Control::CLoginManager::getInstances()->getLoginType(0,ui->mCombo_ID->currentText(),ui->mEdit_Password->text()))
        {
            setLoginBtnDisabled(true);
        }
    }
}

//管理员验证
void CLoginWidget::on_mBtn_Login_Admin_clicked()
{
    if(ui->mEdit_Password_Admin->text().isEmpty())
    {
        //CUIMsgRouter::getInstances()->set_blur(40);
        CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false);
        msgdlog->ui->mLabel_text1->setText(tr("输入框为空"));
        msgdlog->ui->mLabel_text2->setText(tr("提示"));
        msgdlog->exec();
        delete msgdlog;
    }
    else
    {
        if(Control::CLoginManager::getInstances()->getLoginType(1,ui->mCombo_ID_Admin->currentText(),ui->mEdit_Password_Admin->text()))
        {
        }
    }
}

//取消管理员验证
void CLoginWidget::on_mBtn_Cancel_Admin_clicked()
{
    ui->mStacked_login->setCurrentIndex(0);
}

//取消修改密码
void CLoginWidget::on_mBtn_Cancel_Set_clicked()
{
    ui->mStacked_login->setCurrentIndex(0);
}

//修改密码
void CLoginWidget::on_mBtn_Login_Set_clicked()
{
    if(ui->mEdit_Password_Set->text().isEmpty()||ui->mEdit_Password_Set2->text().isEmpty())
    {
        //CUIMsgRouter::getInstances()->set_blur(40);
        CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false);
        msgdlog->ui->mLabel_text1->setText(tr("输入框为空"));
        msgdlog->ui->mLabel_text2->setText(tr("提示"));
        msgdlog->exec();
        delete msgdlog;
    }
    else
    {
        if(ui->mEdit_Password_Set->text()!=ui->mEdit_Password_Set2->text())
        {
            //CUIMsgRouter::getInstances()->set_blur(40);
            CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false);
            msgdlog->ui->mLabel_text1->setText(tr("两次输入密码不一致！"));
            msgdlog->ui->mLabel_text2->setText(tr("提示"));
            msgdlog->exec();
            delete msgdlog;
        }
        else
        {
            QString msgStr=QString(tr("确认对账户:")+"%1"+tr("进行密码修改")).arg(ui->mCombo_ID_Set->currentText());
            //CUIMsgRouter::getInstances()->set_blur(40);
            CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,true);
            msgdlog->ui->mLabel_text1->setText(msgStr);
            msgdlog->ui->mLabel_text2->setText(tr("提示"));
            int nRes=msgdlog->exec();
            if(nRes==QDialog::Accepted)
            {
                if(Control::CLoginManager::getInstances()->getUpdataPasswd(ui->mCombo_ID_Set->currentText(),ui->mEdit_Password_Set->text()))
                {
                    ui->mEdit_Password->setText(ui->mEdit_Password_Set->text());
                    ui->mEdit_Password_Set->clear();
                    ui->mEdit_Password_Set2->clear();
                    ui->mStacked_login->setCurrentIndex(0);
                }
            }
            else if(nRes==QDialog::Rejected)
            {
                //处理按下取消或者关闭按钮的语句
            }
        }
    }
}

//手动开启修改密码
void CLoginWidget::on_mBtn_Reset_Password_clicked()
{
    qDebug()<<"修改密码";
    ui->mStacked_login->setCurrentIndex(1);
}

//关机按钮
void CLoginWidget::on_mBtn_login_Power_clicked()
{
    //CUIMsgRouter::getInstances()->set_blur(40);
    CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,true);
    msgdlog->ui->mLabel_text1->setText(tr("是否退出登入？"));
    msgdlog->ui->mLabel_text2->setText(tr("提示"));
    msgdlog->ui->mBtn_OK->setText(tr("确定"));
    msgdlog->ui->mBtn_Cancel->setText(tr("取消"));
    int nRes=msgdlog->exec();
    if(nRes==QDialog::Accepted)
    {
        Comom::CGlobal::getInstance()->getTools()->setWinShutdown();//立马关机
    }
    else if(nRes==QDialog::Rejected)
    {
    }
    delete msgdlog;
}

//设置modbus串口号
void CLoginWidget::on_mCom_Modbus_currentIndexChanged(const QString &arg1)
{
    st_port_info nModbus;
    nModbus.port=arg1.mid(3,arg1.length()-3).toInt();
    nModbus.rate=115200;
    //Control::CConfgManager::getInstance()->setModbusPort(nModbus);
}

//设置打印机串口号
void CLoginWidget::on_mCom_Print_currentIndexChanged(const QString &arg1)
{
    st_port_info nPrint;
    nPrint.port=arg1.mid(3,arg1.length()-3).toInt();
    nPrint.rate=115200;
    //Control::CConfgManager::getInstance()->setPrintPort(nPrint);
}

//设置串口1串口号
void CLoginWidget::on_mCom_COM1_currentIndexChanged(const QString &arg1)
{
    st_com_info nLis;
    nLis.state=0;
    nLis.port=arg1.mid(3,arg1.length()-3).toInt();
    nLis.rate=115200;
    //Control::CConfgManager::getInstance()->set1Com(nLis);
}

//设置串口2串口号
void CLoginWidget::on_mCom_COM2_currentIndexChanged(const QString &arg1)
{

    st_com_info nLis;
    nLis.state=0;
    nLis.port=arg1.mid(3,arg1.length()-3).toInt();
    nLis.rate=115200;
    //Control::CConfgManager::getInstance()->set2Com(nLis);
}



//串口界面返回
void CLoginWidget::on_mBtn_Com_Return_clicked()
{
    ui->mStacked_login->setCurrentIndex(0);
}

//备份界面返回
void CLoginWidget::on_mBtn_Backup_Re_clicked()
{
    ui->mStacked_login->setCurrentIndex(0);
}

//备份导出
void CLoginWidget::on_mBtn_Backup_Derive_clicked()
{
    QString nDisk=Comom::CGlobal::getInstance()->getTools()->getDisk();
    if(nDisk!="NODisk")
    {
        QString newFileName = QCoreApplication::applicationDirPath()+"/FLI1200.db";//获取程序Btc文件目录

        if(ui->mEdit_Backup_Password->text().compare("biotime-FLI1200")== 0)
        {
            CMsgDialog *msgDelay=new CMsgDialog(true,true,false,false,false,false,0);
            //CUIMsgRouter::getInstances()->set_blur(40);
            msgDelay->ui->mLabel_text1->setText(tr("导出操作中，请稍等"));
            msgDelay->ui->mLabel_text2->setText(tr("提示"));
            msgDelay->setModal(true);
            msgDelay->show();
            set_Backup_Loop(nDisk+"FLI1200.db",newFileName,false);
            msgDelay->accept();
            delete msgDelay;
            ui->mEdit_Backup_Password->clear();
        }
        else
        {
            //CUIMsgRouter::getInstances()->set_blur(40);
            CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false);
            msgdlog->ui->mLabel_text1->setText(tr("密码错误"));
            msgdlog->ui->mLabel_text2->setText(tr("提示"));
            msgdlog->ui->mBtn_OK->setText(tr("确定"));
            msgdlog->exec();
            delete msgdlog;
        }

    }
    else
    {
        //CUIMsgRouter::getInstances()->set_blur(40);
        CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false,0);
        msgdlog->ui->mLabel_text1->setText(tr("未插入U盘"));
        msgdlog->ui->mLabel_text2->setText(tr("提示"));
        msgdlog->ui->mBtn_OK->setText(tr("确定"));
        msgdlog->exec();
        delete msgdlog;
    }

}

//备份导入
void CLoginWidget::on_mBtn_Backup_Inport_clicked()
{
    QString nDisk=Comom::CGlobal::getInstance()->getTools()->getDisk();
    if(nDisk!="NODisk")
    {
        if(ui->mEdit_Backup_Password->text().compare("biotime-FLI1200")== 0)
        {
            //int CTools::setPathData(QString newFile, QString oldFile)//将文件拷贝至新文件
            QString newFileName = QCoreApplication::applicationDirPath()+"/newFLI1200.db";//获取程序Btc文件目录
            CMsgDialog *msgDelay=new CMsgDialog(true,true,false,false,false,false,0);
            //CUIMsgRouter::getInstances()->set_blur(40);
            msgDelay->ui->mLabel_text1->setText(tr("导入操作中，请稍等"));
            msgDelay->ui->mLabel_text2->setText(tr("提示"));
            msgDelay->setModal(true);
            msgDelay->show();
            set_Backup_Loop(newFileName,nDisk+"FLI1200.db",true);
            msgDelay->accept();
            delete msgDelay;
            ui->mEdit_Backup_Password->clear();


            if(m_backUp>0)
            {
                //CUIMsgRouter::getInstances()->set_blur(40);
                CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false);
                msgdlog->ui->mLabel_text1->setText(tr("数据库导入成功,点击确定后将重启系统"));
                msgdlog->ui->mLabel_text2->setText(tr("提示"));
                msgdlog->ui->mBtn_OK->setText(tr("确定"));
                int nRes=msgdlog->exec();
                if(nRes==QDialog::Accepted)
                {
                    //qApp->exit(777);//软件重启
                    qApp->quit();   // 或者   aApp->closeAllWindows();
                    QProcess::startDetached(qApp->applicationFilePath(), QStringList());
                }
                delete msgdlog;
            }

        }
        else
        {
            //CUIMsgRouter::getInstances()->set_blur(40);
            CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false);
            msgdlog->ui->mLabel_text1->setText(tr("密码错误"));
            msgdlog->ui->mLabel_text2->setText(tr("提示"));
            msgdlog->ui->mBtn_OK->setText(tr("确定"));
            msgdlog->exec();
            delete msgdlog;
        }
    }
    else
    {
        //CUIMsgRouter::getInstances()->set_blur(40);
        CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false,0);
        msgdlog->ui->mLabel_text1->setText(tr("未插入U盘"));
        msgdlog->ui->mLabel_text2->setText(tr("提示"));
        msgdlog->ui->mBtn_OK->setText(tr("确定"));
        msgdlog->exec();
        delete msgdlog;
    }
}

//临时线程函数
void CLoginWidget::set_Backup_Loop(QString newFile, QString oldFile,bool backupFlag)
{
    int backUp=-1;
    // 假设需要知道线程的执行结果runResult
    bool runResult{ false };

    // 定义一个loop对象
    QEventLoop loop;
    // 绑定信号  在loop收到界面发送的signalRunOver信号后，退出循环
    connect(this, &CLoginWidget::signalRunOver, &loop, &QEventLoop::quit);

    // 声明一个线程，处理耗时任务  传入匿名函数  在声明testThread后直接开启一个线程执行匿名函数体
    std::thread testThread([&]
    {
        // runResult = 连接网络 、拷贝文件、等等耗时操作  实际执行的任务放在这个位置执行
        // 执行耗时操作完成后 发出信号  告知线程执行结束
        backUp=Comom::CGlobal::getInstance()->getTools()->setPathData(newFile,oldFile);
        if(backUp!=-1)
        {
            runResult=false;
            emit signalRunOver();
        }
    });
    // 分离线程  让其自生自灭(销毁线程)
    testThread.detach();

    // 在此处执行循环  等待线程的执行结果
    loop.exec();

    // 以上线程执行完成后执行以下代码
    if (!runResult)
    {
        m_backUp=backUp;
        qDebug()<<"backUp"<<backUp;
        // 处理结果  整个过程界面不会卡死
        switch (backUp) {
        case 0://文件不存在
        {
            //CUIMsgRouter::getInstances()->set_blur(40);
            CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false,0);
            if(backupFlag)
            {
                msgdlog->ui->mLabel_text1->setText(tr("导入失败"));
            }
            else
            {
                msgdlog->ui->mLabel_text1->setText(tr("导出失败"));
            }
            msgdlog->ui->mLabel_text2->setText(tr("提示"));
            msgdlog->ui->mBtn_OK->setText(tr("确定"));
            msgdlog->exec();
            delete msgdlog;
        }
            break;
        case 1://导入成功
        {
            //CUIMsgRouter::getInstances()->set_blur(40);
            CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false,0);
            if(backupFlag)
            {
                msgdlog->ui->mLabel_text1->setText(tr("导入成功"));
            }
            else
            {
                msgdlog->ui->mLabel_text1->setText(tr("导出成功"));
            }
            msgdlog->ui->mLabel_text2->setText(tr("提示"));
            msgdlog->ui->mBtn_OK->setText(tr("确定"));
            msgdlog->exec();
            delete msgdlog;
        }
            break;
        case 2://覆盖成功
        {
            //CUIMsgRouter::getInstances()->set_blur(40);
            CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false,0);
            msgdlog->ui->mLabel_text1->setText(tr("覆盖成功"));
            msgdlog->ui->mLabel_text2->setText(tr("提示"));
            msgdlog->ui->mBtn_OK->setText(tr("确定"));
            msgdlog->exec();
            delete msgdlog;
        }
            break;
        default:
        {
            //CUIMsgRouter::getInstances()->set_blur(40);
            CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false,0);
            if(backupFlag)
            {
                msgdlog->ui->mLabel_text1->setText(tr("导入失败"));
            }
            else
            {
                msgdlog->ui->mLabel_text1->setText(tr("导出失败"));
            }
            msgdlog->ui->mLabel_text2->setText(tr("提示"));
            msgdlog->ui->mBtn_OK->setText(tr("确定"));
            msgdlog->exec();
            delete msgdlog;
        }
            break;
        }
    }
}

//备份按钮
void CLoginWidget::on_mBtn_Backup_clicked()
{
    m_BackupNum++;
    if(m_BackupNum==7)
    {
        ui->mStacked_login->setCurrentIndex(4);
        m_BackupNum=0;
    }
}

//串口配置信息刷新
void CLoginWidget::config_refresh()
{
    ui->mCom_Modbus->blockSignals(true);   //锁上。addItem更改值时不触发currentIndexChanged信号
    ui->mCom_Print->blockSignals(true);   //锁上。addItem更改值时不触发currentIndexChanged信号
    ui->mCom_COM1->blockSignals(true);   //锁上。addItem更改值时不触发currentIndexChanged信号
    ui->mCom_COM2->blockSignals(true);   //锁上。addItem更改值时不触发currentIndexChanged信号
    ui->mCom_Modbus->setCurrentText("COM"+QString::number(Control::CConfgManager::getInstance()->getModbusPort().port));
    ui->mCom_Print->setCurrentText("COM"+QString::number(Control::CConfgManager::getInstance()->getPrintPort().port));
    ui->mCom_COM1->setCurrentText("COM"+QString::number(Control::CConfgManager::getInstance()->get1Com().port));
    ui->mCom_COM2->setCurrentText("COM"+QString::number(Control::CConfgManager::getInstance()->get2Com().port));
    ui->mCom_Modbus->blockSignals(false);   //解锁
    ui->mCom_Print->blockSignals(false);   //解锁
    ui->mCom_COM1->blockSignals(false);   //解锁
    ui->mCom_COM2->blockSignals(false);   //解锁
}


