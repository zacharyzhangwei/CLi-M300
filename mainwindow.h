#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ui/cinitwidget.h"
#include "ui/crecordwidget.h"
#include "ui/cqcwidget.h"
#include "control/cconfgmanager.h"
#include "ui/csetwidget.h"
#include "ui/cpowerwidget.h"
#include "ui/cinitwidget.h"
#include "ui/cloginwidget.h"
#include "ui/cuserwidget.h"
#include "ui/ccalibwidget.h"
#include <QTranslator>
#include "control/cloginmanager.h"
#include <QGraphicsBlurEffect>
#include <QDebug>
#include "ctestwidget.h"
#include "control/imhelper.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void Init();
private:
    Ui::MainWindow *ui;
    CInitWidget *m_cinitWidget;
    CLoginWidget *m_cloginwidget;
    CPowerWidget*m_cpowerwidget;
    CSetWidget *m_csetWidget;
    CQCwidget * m_cqcwidget;
    CRecordWidget *m_crecordwidget;
    CUserWidget *m_cuserWidget;
    CTestWidget *m_ctestWidget;
    CCalibWidget *m_ccaliWidget;

    QButtonGroup *m_groupMain;
    QPoint m_lastPos;//上一光标位置
    QTimer*m_SleepTimer;
    QLabel *mLab_blure;
    QString m_ScanStr;//当前扫描信息
    QString m_LastScanStr;//上一条扫描信息
    int lastgroupId=6;


private:
    void setBtnEnabledState(QPushButton *btn,bool state);
    void keyPressEvent(QKeyEvent *event);
    void slt_Power(int lastpages);
private slots:
    void slt_blur(int effect);
    void slt_login();//获取登入
    void slt_groupMain(int i);
    void slt_M_DatatoMain(int dataType,QStringList nData);
    void slt_DevInit();
    void slt_Autotest(bool m_model);




};
#endif // MAINWINDOW_H
