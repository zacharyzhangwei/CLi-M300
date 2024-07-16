#ifndef CCONFIGWIDGET_H
#define CCONFIGWIDGET_H

#include <QWidget>
#include "ui/calendarwidget.h"
#include "ui/advancedwidget.h"

namespace Ui {
class CConfigWidget;
}

class CConfigWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CConfigWidget(QWidget *parent = 0);
    ~CConfigWidget();
    CalendarWidget *CConfig_Calendar;
    AdvancedWidget *CConfig_Advanced;

private slots:
    void on_Confg_btn_time_clicked();
    void slots_ret_str(QString time_str);

    void on_Config_btn_Advanced_clicked();

    void on_tabWidget_tabBarClicked(int index);

private:
    Ui::CConfigWidget *ui;
};

#endif // CCONFIGWIDGET_H
