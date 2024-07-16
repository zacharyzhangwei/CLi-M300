#ifndef CQCWIDGET_H
#define CQCWIDGET_H

#include <QWidget>
#include "control/cmodbusmanager.h"
#include "control/chlcpeakmanager.h"
#include "control/cqcmanager.h"

#include "lib/qcustomplot/qcustomplot.h"
#include "control/ctestmanager.h"
#include "cmsgdialog.h"
#include "ui_cmsgdialog.h"
#include "calendarwidget.h"
#include "ccardmanager.h"



typedef struct QCState{
    QString Batch;
    int State1;
    int State2;//在控状态 未质控=0 脱靶未审核=1 在控未审核=2 脱靶已审核=3 在控已审核=4 过期=5
} st_QCState;


namespace Ui {
class CQCwidget;
}

class CQCwidget : public QWidget
{
    Q_OBJECT

public:
    explicit CQCwidget(QWidget *parent = 0);
    ~CQCwidget();

private slots:
    void on_mBtn_QC_Inquire_clicked();

    void on_mBtn_QC_SetInfo_clicked();

    void on_mBtn_Detail_Retun_clicked();

    void on_mBtn_Data_Retun_clicked();

private:
    Ui::CQCwidget *ui;
    CalendarWidget *m_QC_calendar;//日历工具

    void setTableScroller(QTableWidget *nTable);//设置类安卓滑动
    void setVerticalInfo(QLabel *name,QString text);//竖显示文字

};

#endif // CQCWIDGET_H
