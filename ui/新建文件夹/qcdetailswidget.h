#ifndef QCDETAILSWIDGET_H
#define QCDETAILSWIDGET_H

#include <QWidget>

namespace Ui {
class QCDetailsWidget;
}

class QCDetailsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QCDetailsWidget(QWidget *parent = 0);
    ~QCDetailsWidget();

private:
    Ui::QCDetailsWidget *ui;
    void mousePressEvent(QMouseEvent *e);
};

#endif // QCDETAILSWIDGET_H
