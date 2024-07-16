#include "cconfgwidget.h"
#include "ui_cconfgwidget.h"

CConfgWidget::CConfgWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CConfgWidget)
{
    ui->setupUi(this);
}

CConfgWidget::~CConfgWidget()
{
    delete ui;
}
