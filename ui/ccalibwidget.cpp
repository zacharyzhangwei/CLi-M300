#include "ccalibwidget.h"
#include "ui_ccalibwidget.h"

CCalibWidget::CCalibWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CCalibWidget)
{

    ui->setupUi(this);

//    QRegExp rx = QRegExp("[^']*");  //限制以下特殊符号在lineEdit中的输入
//    QValidator *validator= new QRegExpValidator(rx);
//    ui->mEdit_StartDate->setValidator(validator);
//    ui->mEdit_EndDate->setValidator(validator);
    ui->Calib_mStacked->setCurrentIndex(0);


}

CCalibWidget::~CCalibWidget()
{
    delete ui;
}
