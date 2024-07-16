#ifndef CINITWIDGET_H
#define CINITWIDGET_H

#include <QWidget>
#include "control/cinitmanager.h"
#include "control/cmodbusmanager.h"
#include <QTimer>

namespace Ui {
class CInitWidget;
}

class CInitWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CInitWidget(QWidget *parent = nullptr);
    ~CInitWidget();
    void init();


public:
    int m_BarNumber=6;
    void set_Open();
private:
    Ui::CInitWidget *ui;

    QTimer *m_ErrTimer;


private slots:
    void slt_state_Power();
    void on_progressBar_valueChanged(int value);
    void slt_SelfStatus(bool status);
};

#endif // CINITWIDGET_H
