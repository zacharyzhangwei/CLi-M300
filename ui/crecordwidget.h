#ifndef CRECORDWIDGET_H
#define CRECORDWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "calendarwidget.h"
#include "common/cglobal.h"
#include "control/crecordmanger.h"
#include <QVector>
#include "data/cdbsession.h"
#include <QCheckBox>
#include <QHeaderView>
#include "control/chlcpeakmanager.h"
#include <QMessageBox>
#include "cmsgdialog.h"
#include "ui_cmsgdialog.h"
namespace Ui {
class CRecordWidget;
}

class CRecordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CRecordWidget(QWidget *parent = 0);
    ~CRecordWidget();
    void get_RecordInit();

private:
    Ui::CRecordWidget *ui;
    int Calendar_flag=0;
    CalendarWidget *Record_calendar;//日历工具
private:
    void setTableScroller(QTableWidget *nTable);//设置类安卓滑动
    void setVerticalInfo(QLabel *name,QString text);//竖显示文字


};

#endif // CRECORDWIDGET_H
