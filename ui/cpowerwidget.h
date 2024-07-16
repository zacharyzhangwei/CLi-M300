#ifndef CPOWERWIDGET_H
#define CPOWERWIDGET_H

#include <QWidget>
#include "control/cmodbusmanager.h"
#include "cmsgdialog.h"
#include "ui_cmsgdialog.h"
#include "common/cglobal.h"
namespace Ui {
class CPowerWidget;
}

class CPowerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CPowerWidget(QWidget *parent = 0);
    ~CPowerWidget();
    void setLastGroup(int pages);

private slots:
    void on_mBtn_OK_clicked();

    void on_mBtn_Cancel_clicked();

private:
    Ui::CPowerWidget *ui;
    int m_lastpages;
    int m_cardSize=0;
signals:
    void sgn_CancelPower(int lastpages);
};

#endif // CPOWERWIDGET_H


