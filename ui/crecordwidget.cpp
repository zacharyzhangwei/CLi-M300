#include "crecordwidget.h"
#include "ui_crecordwidget.h"

CRecordWidget::CRecordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CRecordWidget)
{
    ui->setupUi(this);

    QRegExp rx = QRegExp("[^']*");  //限制以下特殊符号在lineEdit中的输入
    QValidator *validator= new QRegExpValidator(rx);
    ui->mEdit_Course_ID->setValidator(validator);
    ui->mEdit_Course_Time->setValidator(validator);
    ui->mEdit_Doctor->setValidator(validator);
    ui->mEdit_End_Num->setValidator(validator);
    ui->mEdit_End_Time->setValidator(validator);
    ui->mEdit_Info_Age->setValidator(validator);
    ui->mEdit_Info_BedNum->setValidator(validator);
    ui->mEdit_Info_CaseNum->setValidator(validator);
    ui->mEdit_Info_Dept->setValidator(validator);
    ui->mEdit_Info_Doctor->setValidator(validator);
    ui->mEdit_Info_ID->setValidator(validator);
    ui->mEdit_Info_Name->setValidator(validator);
    ui->mEdit_Info_Note->setValidator(validator);
    ui->mEdit_Info_PatientsNum->setValidator(validator);
    ui->mEdit_Info_Phone->setValidator(validator);
    ui->mEdit_Info_Reported->setValidator(validator);
    ui->mEdit_Info_Submitted->setValidator(validator);
    ui->mEdit_Info_SubmittedBy->setValidator(validator);
    ui->mEdit_Info_Tested->setValidator(validator);
    ui->mEdit_Info_TestedBy->setValidator(validator);
    ui->mEdit_Name->setValidator(validator);
    ui->mEdit_Origin_Num->setValidator(validator);
    ui->mEdit_Origin_Time->setValidator(validator);
    ui->mEdit_SampleID->setValidator(validator);


    ui->mTable_Record->horizontalHeader()->setHidden(false);
    ui->mTable_Info_Info->horizontalHeader()->setHidden(false);
    ui->mTable_Info_Value->horizontalHeader()->setHidden(false);

    ui->mTable_Info_Info->horizontalHeader()->setHighlightSections(false);
    ui->mTable_Info_Value->horizontalHeader()->setHighlightSections(false);
    ui->mTable_Course->verticalHeader()->setHidden(false);

    setTableScroller(ui->mTable_Course);
    setTableScroller(ui->mTable_Record);
    setTableScroller(ui->mTable_Info_Info);
    setTableScroller(ui->mTable_Info_Value);


    Record_calendar=new CalendarWidget(this);
    Record_calendar->hide();

    QPushButton *Btn_Origin_Calendar = new QPushButton();
    QHBoxLayout *layout_Origin = new QHBoxLayout();
    Btn_Origin_Calendar->setText("▼");
    Btn_Origin_Calendar->setMinimumWidth(60);
    Btn_Origin_Calendar->setMaximumWidth(60);
    Btn_Origin_Calendar->setMinimumHeight(50);
    Btn_Origin_Calendar->setStyleSheet("QPushButton{ background-color:transparent;font-size:32px;color:rgb(64,64,64);}");
    Btn_Origin_Calendar->setCursor(QCursor(Qt::PointingHandCursor));
    layout_Origin->addStretch();
    layout_Origin->addWidget(Btn_Origin_Calendar);
    layout_Origin->setContentsMargins(0,0,0,0);
    ui->mEdit_Origin_Time->setLayout(layout_Origin);

    QPushButton *Btn_End_Calendar = new QPushButton();
    QHBoxLayout *layout_End = new QHBoxLayout();
    Btn_End_Calendar->setText("▼");
    Btn_End_Calendar->setMinimumWidth(60);
    Btn_End_Calendar->setMaximumWidth(60);
    Btn_End_Calendar->setMinimumHeight(50);
    Btn_End_Calendar->setStyleSheet("QPushButton{ background-color:transparent;font-size:32px;color:rgb(64,64,64);}");
    Btn_End_Calendar->setCursor(QCursor(Qt::PointingHandCursor));
    layout_End->addStretch();
    layout_End->addWidget(Btn_End_Calendar);
    layout_End->setContentsMargins(0,0,0,0);
    ui->mEdit_End_Time->setLayout(layout_End);


    QPushButton *Btn_Custom_Calendar = new QPushButton();
    QHBoxLayout *layout_Custom = new QHBoxLayout();
    Btn_Custom_Calendar->setText("▼");
    Btn_Custom_Calendar->setMinimumWidth(60);
    Btn_Custom_Calendar->setMaximumWidth(60);
    Btn_Custom_Calendar->setMinimumHeight(50);
    Btn_Custom_Calendar->setStyleSheet("QPushButton{ background-color:transparent;font-size:32px;color:rgb(64,64,64);}");
    Btn_Custom_Calendar->setCursor(QCursor(Qt::PointingHandCursor));
    layout_Custom->addStretch();
    layout_Custom->addWidget(Btn_Custom_Calendar);
    layout_Custom->setContentsMargins(0,0,0,0);
    ui->mEdit_Course_Time->setLayout(layout_Custom);
    ui->mTable_Record->setColumnWidth(0,80);
    ui->mTable_Record->setColumnWidth(3,230);
    ui->mTable_Record->setColumnWidth(4,230);
    ui->mCustom_Course->setInteractions(QCP::iRangeDrag);//添加鼠标拖放支持、滚轮缩放支持| QCP::iRangeZoom|QCP::iSelectPlottables
    QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
    dateTicker->setDateTimeFormat("MM-dd");//日期格式(可参考QDateTime::fromString()函数)
    ui->mCustom_Course->xAxis->setTicker(dateTicker);//设置X轴为时间轴
    dateTicker->setTickCount(31);//设置大刻度个数 有可能计算出来的刻度数不完全等于设置的刻度个数，取决于刻度生成策略
    ui->mCustom_Course->xAxis->setTickLabelRotation(35);//设置x坐标 旋转35° 横着显示可能显示不全


    //设置QTableWidget窗口滚动
    QScroller *pScroller = QScroller::scroller(ui->mTable_Record);
    pScroller->grabGesture(ui->mTable_Record,QScroller::LeftMouseButtonGesture);//设置手势识别
    QScrollerProperties properties = pScroller->scrollerProperties();
    properties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy,1);//设置越区策略为禁止越区
    pScroller->setScrollerProperties(properties);
    ui->mTable_Record->setVerticalScrollMode(QListWidget::ScrollPerPixel);//设置为像素移动



    connect(ui->mTable_Record->verticalScrollBar(),&QScrollBar::valueChanged,[=]()
    {
        
    });

    ui->mEdit_Info_Age->setValidator(new QIntValidator(0, 200, this));

    connect(Btn_Origin_Calendar,&QPushButton::clicked,[=]()
    {
        Calendar_flag=0;
        Record_calendar->move(ui->mEdit_Origin_Time->x()+200,ui->mEdit_Origin_Time->y()+220);
        Record_calendar->show();
    });
    connect(Btn_End_Calendar,&QPushButton::clicked,[=]()
    {
        Calendar_flag=1;
        Record_calendar->move(ui->mEdit_End_Time->x()+160,ui->mEdit_End_Time->y()+220);
        Record_calendar->show();
    });
    connect(Btn_Custom_Calendar,&QPushButton::clicked,[=]()
    {
        Calendar_flag=2;
        Record_calendar->move(ui->mEdit_Course_Time->x()+160,ui->mEdit_Course_Time->y()+220);
        Record_calendar->show();
    });

}

CRecordWidget::~CRecordWidget()
{
    delete ui;
}

void CRecordWidget::get_RecordInit()
{
    BTLOG->print(e_debug,"%d,%s",1,"get_RecordInit");
    if(Control::CRecordManger::getInstances()->getRecordInit())
    {
        ui->mEdit_SampleID->clear();
        ui->mEdit_Name->clear();
        ui->mEdit_Origin_Time->clear();
        ui->mEdit_End_Time->clear();
        ui->mEdit_Origin_Num->clear();
        ui->mEdit_End_Num->clear();
        ui->mEdit_Doctor->clear();
//        m_selectFlag=false;
//        m_initFlag=true;
    }
}



//设置类安卓滑动
void CRecordWidget::setTableScroller(QTableWidget *nTable)
{
    QScroller *pScroller = QScroller::scroller(nTable);
    pScroller->grabGesture(nTable,QScroller::LeftMouseButtonGesture);//设置手势识别
    QScrollerProperties properties = pScroller->scrollerProperties();
    properties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy,1);//设置越区策略为禁止越区
    pScroller->setScrollerProperties(properties);
    nTable->setVerticalScrollMode(QListWidget::ScrollPerPixel);//设置为像素移动
}

void CRecordWidget::setVerticalInfo(QLabel *name, QString text)
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
