#ifndef CCALIBWIDGET_H
#define CCALIBWIDGET_H

#include <QWidget>
#include "ui/calendarwidget.h"
//#include "control/ccalibramanager.h"
#include "control/cmodbusmanager.h"
#include "control/chlcpeakmanager.h"

#include "lib/qcustomplot/qcustomplot.h"
#include "control/ctestmanager.h"
#include "cmsgdialog.h"
#include "ui_cmsgdialog.h"
#include "ccardmanager.h"

namespace Ui {
class CCalibWidget;
}

class CCalibWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CCalibWidget(QWidget *parent = 0);
    ~CCalibWidget();


private slots:

private slots:


public slots:


signals:

private:

public:


private:
    Ui::CCalibWidget *ui;

};

#endif // CCALIBWIDGET_H
