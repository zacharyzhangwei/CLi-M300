#include "qcfollowwidget.h"
#include "ui_qcfollowwidget.h"

QCFollowWidget::QCFollowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QCFollowWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
    dateTicker->setDateTimeFormat("MM-dd");//日期格式(可参考QDateTime::fromString()函数)
    dateTicker->setTickCount(28);//设置大刻度个数 有可能计算出来的刻度数不完全等于设置的刻度个数，取决于刻度生成策略
    QCFollow_Curve= new QCustomPlot(this) ;
    QCFollow_Curve->setInteractions(QCP::iRangeDrag);//添加鼠标拖放支持、滚轮缩放支持
    QCFollow_Curve->setBackground(QBrush(QColor(231,230,230)));//background-color:rgb(231,230,230);
    QCFollow_Curve->xAxis->setTicker(dateTicker);//设置X轴为时间轴
    QCFollow_Curve->xAxis->setRange(0,24*3600*7*4);
    QCFollow_Curve->xAxis->setTickLabelRotation(35);//设置x坐标 旋转35° 横着显示可能显示不全
    QCFollow_Curve->yAxis->setRange(0,2500);
    ui->Follow_layout_Curve->addWidget(QCFollow_Curve);

}

QCFollowWidget::~QCFollowWidget()
{
    delete ui;
}

void QCFollowWidget::mousePressEvent(QMouseEvent *e)
{
    setAttribute(Qt::WA_NoMouseReplay);
    QWidget::mousePressEvent(e);
}
