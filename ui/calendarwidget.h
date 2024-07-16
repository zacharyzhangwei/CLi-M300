#ifndef CALENDARWIDGET_H
#define CALENDARWIDGET_H

#include <QWidget>
#include <QCalendarWidget>
#include <QDebug>
#include <QPainter>
#include "common/cglobal.h"

namespace Ui {
class CalendarWidget;
}

class CalendarWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CalendarWidget(QWidget *parent = 0);
    ~CalendarWidget();
    QCalendarWidget *mCalendar;
    void initWidget();

private slots:
    void setDataLabelTimeText(int year_num,int month_num);
    void on_Calendar_btn_YSubtract_clicked();
    void on_Calendar_btn_MSubtract_clicked();
    void on_Calendar_btn_MAdd_clicked();
    void on_Calendar_btn_YAdd_clicked();
    void on_Calendar_btn_Hour_clicked();
    void on_Calendar_btn_add_clicked();
    void on_Calendar_btn_subtract_clicked();
    void on_Calendar_btn_Minute_clicked();
    void on_Calendar_btn_Second_clicked();
    void on_Calendar_btn_Ok_clicked();
    void on_Calendar_btn_Cancel_clicked();
    void on_Calendar_btn_Now_clicked();
    void on_Calendar_Edit_num_textChanged(const QString &arg1);

private:
    int num_max=59;
    int time_flag;
    Ui::CalendarWidget *ui;
    void mousePressEvent(QMouseEvent *e);
signals:
    void time_out(QString time_str);

};

#endif // CALENDARWIDGET_H
