#include "monitcurvewidget.h"
#include "ui_monitcurvewidget.h"

MonitCurveWidget::MonitCurveWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MonitCurveWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);

    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
    dateTicker->setDateTimeFormat("MM-dd");//日期格式(可参考QDateTime::fromString()函数)
    Monit_Curve_1= new QCustomPlot(this) ;
    Monit_Curve_1->setBackground(QBrush(QColor(240,240,240)));
    Monit_Curve_1->setInteractions(QCP::iRangeDrag |QCP::iSelectPlottables);//添加鼠标拖放支持、滚轮缩放支持| QCP::iRangeZoom
    Monit_Curve_1->xAxis->setTicker(dateTicker);//设置X轴为时间轴
    Monit_Curve_1->xAxis->setRange(0,0+24*3600*7*4);
    Monit_Curve_1->xAxis->setTickLabelRotation(35);//设置x坐标 旋转35° 横着显示可能显示不全
    Monit_Curve_1->yAxis->setRange(0,2500);
    ui->monit_layout_Curve1->addWidget(Monit_Curve_1);


    Monit_Curve_2= new QCustomPlot(this) ;
    Monit_Curve_2->setBackground(QBrush(QColor(240,240,240)));
    Monit_Curve_2->setInteractions(QCP::iRangeDrag |QCP::iSelectPlottables);//添加鼠标拖放支持、滚轮缩放支持| QCP::iRangeZoom
    Monit_Curve_2->xAxis->setTicker(dateTicker);//设置X轴为时间轴
    Monit_Curve_2->xAxis->setRange(0,0+24*3600*7*4);
    Monit_Curve_2->xAxis->setTickLabelRotation(35);//设置x坐标 旋转35° 横着显示可能显示不全
    Monit_Curve_2->yAxis->setRange(0,2500);
    ui->monit_layout_Curve2->addWidget(Monit_Curve_2);

    Monit_Curve_3= new QCustomPlot(this) ;
    Monit_Curve_3->setBackground(QBrush(QColor(240,240,240)));
    Monit_Curve_3->setInteractions(QCP::iRangeDrag |QCP::iSelectPlottables);//添加鼠标拖放支持、滚轮缩放支持| QCP::iRangeZoom
    Monit_Curve_3->xAxis->setTicker(dateTicker);//设置X轴为时间轴
    Monit_Curve_3->xAxis->setRange(0,0+24*3600*7*4);
    Monit_Curve_3->xAxis->setTickLabelRotation(35);//设置x坐标 旋转35° 横着显示可能显示不全
    Monit_Curve_3->yAxis->setRange(0,2500);
    ui->monit_layout_Curve3->addWidget(Monit_Curve_3);

    Monit_Curve_4= new QCustomPlot(this) ;
    Monit_Curve_4->setBackground(QBrush(QColor(240,240,240)));
    Monit_Curve_4->setInteractions(QCP::iRangeDrag |QCP::iSelectPlottables);//添加鼠标拖放支持、滚轮缩放支持| QCP::iRangeZoom
    Monit_Curve_4->xAxis->setTicker(dateTicker);//设置X轴为时间轴
    Monit_Curve_4->xAxis->setRange(0,0+24*3600*7*4);
    Monit_Curve_4->xAxis->setTickLabelRotation(35);//设置x坐标 旋转35° 横着显示可能显示不全
    Monit_Curve_4->yAxis->setRange(0,2500);
    ui->monit_layout_Curve4->addWidget(Monit_Curve_4);

    Monit_Curve_5= new QCustomPlot(this) ;
    Monit_Curve_5->setBackground(QBrush(QColor(240,240,240)));
    Monit_Curve_5->setInteractions(QCP::iRangeDrag |QCP::iSelectPlottables);//添加鼠标拖放支持、滚轮缩放支持| QCP::iRangeZoom
    Monit_Curve_5->xAxis->setTicker(dateTicker);//设置X轴为时间轴
    Monit_Curve_5->xAxis->setRange(0,0+24*3600*7*4);
    Monit_Curve_5->xAxis->setTickLabelRotation(35);//设置x坐标 旋转35° 横着显示可能显示不全
    Monit_Curve_5->yAxis->setRange(0,2500);
    ui->monit_layout_Curve5->addWidget(Monit_Curve_5);
}

MonitCurveWidget::~MonitCurveWidget()
{
    delete ui;
}

void MonitCurveWidget::mousePressEvent(QMouseEvent *e)
{
    setAttribute(Qt::WA_NoMouseReplay);
    QWidget::mousePressEvent(e);
}

void MonitCurveWidget::on_Monit_btn_Ret_clicked()
{
    this->hide();
}
