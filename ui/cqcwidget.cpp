#include "cqcwidget.h"
#include "ui_cqcwidget.h"

CQCwidget::CQCwidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CQCwidget)
{
    ui->setupUi(this);
    QRegExp rx = QRegExp("[^']*");  //限制以下特殊符号在lineEdit中的输入
    QValidator *validator= new QRegExpValidator(rx);
    ui->mEdit_Data_Batch->setValidator(validator);
    ui->mEdit_Data_SD->setValidator(validator);
    ui->mEdit_Data_TargetValue->setValidator(validator);
    ui->mEdit_Detail_Time->setValidator(validator);

    ui->mBtn_QC_Open->hide();

    //日历工具
    m_QC_calendar=new CalendarWidget(this);
    m_QC_calendar->hide();

    ui->mTable_QC_Inquire->horizontalHeader()->setHidden(false);
    ui->mTable_Detail_Value->horizontalHeader()->setHidden(false);
    ui->mTable_Detail_Data->horizontalHeader()->setHidden(false);
    ui->mTable_Data->horizontalHeader()->setHidden(false);
    ui->mTable_QC_Batch->verticalHeader()->setHidden(false);

    setTableScroller(ui->mTable_QC_Inquire);
    setTableScroller(ui->mTable_Detail_Value);
    setTableScroller(ui->mTable_Detail_Data);
    setTableScroller(ui->mTable_Data);
    setTableScroller(ui->mTable_QC_Batch);

    QPushButton *Btn_DetailTime = new QPushButton();
    QHBoxLayout *layout_DetailTime = new QHBoxLayout();
    Btn_DetailTime->setText("▼");
    Btn_DetailTime->setMinimumWidth(60);
    Btn_DetailTime->setMaximumWidth(60);
    Btn_DetailTime->setMinimumHeight(50);
    Btn_DetailTime->setStyleSheet("QPushButton{ background-color:transparent;font-size:32px;color:rgb(63,63,63);}"
    "QPushButton:hover {background-color:transparent;font-size:32px;color:rgb(63,63,63);}");
    Btn_DetailTime->setCursor(QCursor(Qt::PointingHandCursor));
    layout_DetailTime->addStretch();
    layout_DetailTime->addWidget(Btn_DetailTime);
    layout_DetailTime->setContentsMargins(0,0,0,0);
    ui->mEdit_Detail_Time->setLayout(layout_DetailTime);
    ui->mEdit_Detail_Time->setInputMask("0000/00");

    QObject::connect(Btn_DetailTime,&QPushButton::clicked,[=]()
    {
        m_QC_calendar->move(ui->mEdit_Detail_Time->x()+460,ui->mEdit_Detail_Time->y());
        m_QC_calendar->show();
    });

  //  ui->mCustom_QC->setInteractions(QCP::iRangeDrag);//添加鼠标拖放支持、滚轮缩放支持| QCP::iRangeZoom|QCP::iSelectPlottables
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
    dateTicker->setDateTimeFormat("MM-dd");//日期格式(可参考QDateTime::fromString()函数)
    ui->mCustom_QC->xAxis->setTicker(dateTicker);//设置X轴为时间轴
    dateTicker->setTickCount(31);//设置大刻度个数 有可能计算出来的刻度数不完全等于设置的刻度个数，取决于刻度生成策略
    ui->mCustom_QC->xAxis->setTickLabelRotation(35);//设置x坐标 旋转35° 横着显示可能显示不全



    ui->mTable_Data->setColumnWidth(0,80);
    ui->mTable_Data->setColumnWidth(3,210);
    ui->mTable_QC_Inquire->setColumnWidth(0,100);
    ui->mTable_QC_Inquire->setColumnWidth(2,210);
    ui->mTable_QC_Inquire->setColumnWidth(3,80);


}

CQCwidget::~CQCwidget()
{
    delete ui;
}

void CQCwidget::setTableScroller(QTableWidget *nTable)
{
    QScroller *pScroller = QScroller::scroller(nTable);
    pScroller->grabGesture(nTable,QScroller::LeftMouseButtonGesture);//设置手势识别
    QScrollerProperties properties = pScroller->scrollerProperties();
    properties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy,1);//设置越区策略为禁止越区
    pScroller->setScrollerProperties(properties);
    nTable->setVerticalScrollMode(QListWidget::ScrollPerPixel);//设置为像素移动
}

void CQCwidget::setVerticalInfo(QLabel *name, QString text)
{

    QPixmap *j_pix;
    QMatrix j_matrix;
    QPainter*j_painter;
    QFont j_font;
    j_matrix.rotate(270);
    j_pix = new QPixmap(name->height(),name->width());
    j_pix->fill(Qt::transparent);
    //创建绘画对象
    j_painter = new QPainter(j_pix);
    j_painter->begin(j_pix);
    j_painter->setPen(Qt::white);
    //设置字体大小.另可以根据画笔改变颜色等属性
    j_font = j_painter->font();
    j_font.setPixelSize(30);//改变字体大小
    j_painter->setFont(j_font);
    //将文字写在图片上，例如是int型的数字123，居中
    j_painter->drawText(j_pix->rect(), Qt::AlignCenter, QString(text).toStdString().c_str());
    j_painter->end();
    name->setPixmap(j_pix->transformed(j_matrix, Qt::SmoothTransformation));
}



void CQCwidget::on_mBtn_QC_Inquire_clicked()
{
    ui->QC_mStacked->setCurrentIndex(1);
}

void CQCwidget::on_mBtn_QC_SetInfo_clicked()
{
    ui->QC_mStacked->setCurrentIndex(2);
}

void CQCwidget::on_mBtn_Detail_Retun_clicked()
{
    ui->QC_mStacked->setCurrentIndex(0);
}

void CQCwidget::on_mBtn_Data_Retun_clicked()
{
    ui->QC_mStacked->setCurrentIndex(0);
}
