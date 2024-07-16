#ifndef CUSERWIDGET_H
#define CUSERWIDGET_H

#include <QWidget>
#include <QScrollerProperties>
#include <QScroller>
#include <QListWidget>
#include "control/csetmanager.h"
#include "calendarwidget.h"
#include "cmsgdialog.h"
#include "ui_cmsgdialog.h"
namespace Ui {
class CUserWidget;
}

class CUserWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CUserWidget(QWidget *parent = nullptr);
    ~CUserWidget();

private:
    Ui::CUserWidget *ui;
    QButtonGroup *Group_Statistics;
    CalendarWidget *m_User_calendar;//日历工具
    int Calendar_Type=0;
    bool AddorUpdate=true;
    void init_table();

private slots:
    void slt_time(QString timeStr);
    void setTableScroller(QTableWidget *nTable);//设置类安卓滑动


    void on_mBtn_User_Add_clicked();//新增账户
    void on_mBtn_User_Retun_clicked();

    void on_mBtn_User_Ok_Add_clicked();

signals:
    void sgn_Logout();//退出登入
};

#endif // CUSERWIDGET_H
