#include "qcdetailswidget.h"
#include "ui_qcdetailswidget.h"

QCDetailsWidget::QCDetailsWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCDetailsWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
}

QCDetailsWidget::~QCDetailsWidget()
{
    delete ui;
}

void QCDetailsWidget::mousePressEvent(QMouseEvent *e)
{
    setAttribute(Qt::WA_NoMouseReplay);
    QWidget::mousePressEvent(e);
}
