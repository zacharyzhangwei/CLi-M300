#ifndef CLOGINWIDGET_H
#define CLOGINWIDGET_H

#include <QWidget>
#include "control/cloginmanager.h"
#include <QDebug>
#include "control/cmodbusmanager.h"
#include "cmsgdialog.h"
#include "ui_cmsgdialog.h"
#include <QEventLoop>
#include <thread>
#include <QProcess>


namespace Ui {
class CLoginWidget;
}

class CLoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CLoginWidget(QWidget *parent = 0);
    ~CLoginWidget();
    void setLoginBtnDisabled( bool state);
private slots:
    void slt_loginState(int type, bool state);

    void on_mBtn_Cancel_clicked();

    void on_mBtn_Login_clicked();

    void on_mBtn_Reset_Password_clicked();

    void on_mBtn_login_Power_clicked();

    void on_mBtn_Cancel_Admin_clicked();

    void on_mBtn_Login_Admin_clicked();

    void on_mBtn_Cancel_Set_clicked();

    void on_mBtn_Login_Set_clicked();

    void on_mCom_Modbus_currentIndexChanged(const QString &arg1);

    void on_mCom_Print_currentIndexChanged(const QString &arg1);

    void on_mCom_COM1_currentIndexChanged(const QString &arg1);

    void on_mCom_COM2_currentIndexChanged(const QString &arg1);

    void on_mBtn_Com_Return_clicked();

    void on_mBtn_Backup_Re_clicked();

    void on_mBtn_Backup_Derive_clicked();

    void on_mBtn_Backup_Inport_clicked();

    void on_mBtn_Backup_clicked();


public slots:

private slots:
    void slt_UserList(QQueue<st_User> userList);

private:
    Ui::CLoginWidget *ui;
private:
    int modbusNum=0;//记录取消点击次数，7次开启串口号设置
    int m_BackupNum=0;//记录取消点击次数，7次开启备份设置
    int m_backUp=-1;//导出操作标志位

    void config_refresh();
    void set_Backup_Loop(QString newFile, QString oldFile, bool backupFlag);
signals:
    // 线程执行结束后发送此信号
    void signalRunOver();

};

#endif // CLOGINWIDGET_H
