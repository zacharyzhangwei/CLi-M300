#include "csetwidget.h"
#include "ui_csetwidget.h"

CSetWidget::CSetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CSetWidget)
{
    ui->setupUi(this);
    QRegExp rx = QRegExp("[^']*");  //限制以下特殊符号在lineEdit中的输入
    QValidator *validator= new QRegExpValidator(rx);
    ui->mEdit_High_CsTime->setValidator(validator);
    ui->mEdit_High_Gain->setValidator(validator);
    ui->mEdit_High_CardCount->setValidator(validator);
    ui->mEdit_High_Login->setValidator(validator);
    ui->mEdit_High_Name->setValidator(validator);
    ui->mEdit_High_SN->setValidator(validator);
    ui->mEdit_High_Time->setValidator(validator);
    ui->mEdit_Info_Admin->setValidator(validator);
    ui->mEdit_Info_Hospital->setValidator(validator);
    ui->mEdit_Info_IDName->setValidator(validator);
    ui->mEdit_Info_Phone->setValidator(validator);
    ui->mEdit_Info_Support->setValidator(validator);
    ui->mEdit_Info_SupportMan->setValidator(validator);
    ui->mEdit_Report_Head->setValidator(validator);
    ui->mEdit_SetTemp_Alter->setValidator(validator);
    ui->mEdit_SetTemp_Precision->setValidator(validator);
    ui->mEdit_SetTemp_Temp->setValidator(validator);
    ui->mEdit_SetTemp_Warning->setValidator(validator);
    ui->mEdit_Set_Calendar->setValidator(validator);

    ui->mEdit_High_CardCount->setValidator(new QIntValidator(0,999,this));
    ui->TabWidget_Set->setCurrentIndex(0);

    ui->mLab_Version->setText(tr("发布版本号")+":V1.0   "+tr("完整版本号")+DEFAULT_VERSION);
    set_calendar=new CalendarWidget(this);
    set_calendar->hide();
    QPushButton *Btn_Calendar = new QPushButton();
    QHBoxLayout *layout = new QHBoxLayout();
    Btn_Calendar->setText("▼");
    Btn_Calendar->setMinimumWidth(60);
    Btn_Calendar->setMaximumWidth(60);
    Btn_Calendar->setMinimumHeight(50);
    Btn_Calendar->setStyleSheet("QPushButton{ background-color:transparent;font-size:32px;color:rgb(64,64,64);}");
    Btn_Calendar->setCursor(QCursor(Qt::PointingHandCursor));
    layout->addStretch();
    layout->addWidget(Btn_Calendar);
    layout->setContentsMargins(0,0,0,0);
    ui->mEdit_Set_Calendar->setLayout(layout);


    Group_Signature= new QButtonGroup(this);
    Group_Signature->addButton(ui->mCheck_Signature_1,0);
    Group_Signature->addButton(ui->mCheck_Signature_2,1);
    Group_Signature->addButton(ui->mCheck_Signature_3,2);


    Group_Image= new QButtonGroup(this);
    Group_Image->addButton(ui->mBtn_image_1,0);
    Group_Image->addButton(ui->mBtn_image_2,1);
    Group_Image->addButton(ui->mBtn_image_3,2);


    mGroup_BtnSignature= new QButtonGroup(this);
    mGroup_BtnSignature->addButton(ui->mBtn_Signature_SubmitBy,0);
    mGroup_BtnSignature->addButton(ui->mBtn_Signature_TestBy,1);
    mGroup_BtnSignature->addButton(ui->mBtn_Signature_ReviewBy,2);

    Group_Print= new QButtonGroup(this);
    Group_Print->addButton(ui->mCheck_In_Printer,0);
    Group_Print->addButton(ui->mCheck_Out_Printer,1);
    Group_PaperType= new QButtonGroup(this);
    Group_PaperType->addButton(ui->mBtn_A4_Printer,0);
    Group_PaperType->addButton(ui->mBtn_A5_Printer,1);
    Group_Temp= new QButtonGroup(this);
    Group_Temp->addButton(ui->mBtn_SetTemp_Temp,0);
    Group_Temp->addButton(ui->mBtn_SetTemp_Precision,1);
    Group_Temp->addButton(ui->mBtn_SetTemp_Alter,2);
    Group_Temp->addButton(ui->mBtn_SetTemp_Warning,3);

    m_GroupReport= new QButtonGroup();
    m_GroupReport->setExclusive(false);//不互斥-【重点】
    m_GroupReport->addButton(ui->mCheck_Report_Reserve1,0);
    m_GroupReport->addButton(ui->mCheck_Report_Reserve2,1);
    m_GroupReport->addButton(ui->mCheck_Report_Reserve3,2);
    m_GroupReport->addButton(ui->mCheck_Report_TSample,3);
    m_GroupReport->addButton(ui->mCheck_Report_TReport,4);
    m_GroupReport->addButton(ui->mCheck_Report_TText,5);
    m_GroupReport->addButton(ui->mCheck_Report_TSubmit,6);
    m_GroupReport->addButton(ui->mCheck_Report_Doctor,7);
    m_GroupReport->addButton(ui->mCheck_Report_SubmitBy,8);
    m_GroupReport->addButton(ui->mCheck_Report_TextBy,9);
    m_GroupReport->addButton(ui->mCheck_Report_ReviewBy,10);
    m_GroupReport->addButton(ui->mCheck_Report_Dept,11);
    m_GroupReport->addButton(ui->mCheck_Report_Way,12);
    m_GroupReport->addButton(ui->mCheck_Report_Type,13);
    m_GroupReport->addButton(ui->mCheck_Report_State,14);
    m_GroupReport->addButton(ui->mCheck_Report_Range,15);

    ui->mCheck_Server_PIMS->setEnabled(false);

    m_Paint=new MyPaint();

    ui->mCom_Server_Com->blockSignals(true);   //锁上。addItem更改值时不触发currentIndexChanged信号
    ui->mCom_Server_Com->addItem("COM1");
    ui->mCom_Server_Com->addItem("COM2");
    ui->mCom_Server_Com->setCurrentText("COM"+QString::number(Control::CConfgManager::getInstance()->getHisComNum()));
    ui->mCom_Server_Com->blockSignals(false);   //解锁

    ui->mCom_Server_Com->setEditable(true);
    ui->mCom_Server_Com->lineEdit()->setAlignment(Qt::AlignCenter);
    ui->mCom_Server_Com->setEditable(false);



//    ui->mCom_Pre_Com->blockSignals(true);   //锁上。addItem更改值时不触发currentIndexChanged信号
//    ui->mCom_Pre_Com->addItem("COM1");
//    ui->mCom_Pre_Com->addItem("COM2");
//    ui->mCom_Pre_Com->setCurrentText("COM"+QString::number(Control::CConfgManager::getInstance()->getPreComNum()));
//    ui->mCom_Pre_Com->blockSignals(false);   //解锁

//    ui->mCom_Pre_Com->setEditable(true);
//    ui->mCom_Pre_Com->lineEdit()->setAlignment(Qt::AlignCenter);
//    ui->mCom_Pre_Com->setEditable(false);


    ui->mEdit_Set_Calendar->setInputMask("0000/00/00 00:00:00");


    if(PREFLAG)
    {
        qDebug()<<"初始化前置处理模块Open";
        ui->mFrame_Pre->hide();
        ui->mFrame_Btn_Pre->show();
    }
    else
    {
        qDebug()<<"初始化前置处理模块Over";
        ui->mFrame_Pre->hide();
        ui->mFrame_Btn_Pre->hide();
    }




    auto lineEdit = new QLineEdit();
    lineEdit->setReadOnly(true);
    lineEdit->setAlignment(Qt::AlignCenter);
    lineEdit->installEventFilter(ui->mCom_Server_Com);
    ui->mCom_Server_Com->setLineEdit(lineEdit);


//    auto editPre = new QLineEdit();
//    editPre->setReadOnly(true);
//    editPre->setAlignment(Qt::AlignCenter);
//    editPre->installEventFilter(ui->mCom_Pre_Com);
//    ui->mCom_Pre_Com->setLineEdit(editPre);


    ui->mBtn_SetTemp_Add->setAutoRepeat(true); //启用长按
    ui->mBtn_SetTemp_Add->setAutoRepeatDelay(400);//触发长按的时间
    ui->mBtn_SetTemp_Add->setAutoRepeatInterval(50);//长按时click信号间隔
    ui->mBtn_SetTemp_Minus->setAutoRepeat(true); //启用长按
    ui->mBtn_SetTemp_Minus->setAutoRepeatDelay(400);//触发长按的时间
    ui->mBtn_SetTemp_Minus->setAutoRepeatInterval(50);//长按时click信号间隔

    ui->mEdit_Info_IDName->setValidator(new QIntValidator(0, 99, this));

    ui->mTable_item_info->horizontalHeader()->setHidden(false);
    ui->mTable_item_info->horizontalHeader()->setHighlightSections(false);
    ui->mTable_item_info->setColumnWidth(8,60);
    ui->mTable_item_info->setColumnWidth(0,220);
    ui->mTable_item_info->setColumnWidth(1,165);

    setTableScroller(ui->mTable_item_info);

    ui->mFrame_Signature->hide();


    connect(Btn_Calendar,&QPushButton::clicked,[=]()
    {
        if(this->width()>800&&this->height()>100)
        {
            set_calendar->move(ui->mEdit_Set_Calendar->x()+800,ui->mEdit_Set_Calendar->y()+100);
            set_calendar->show();
        }
        else
        {
            set_calendar->move(ui->mEdit_Set_Calendar->x()+200,ui->mEdit_Set_Calendar->y()+50);
            set_calendar->show();
        }
    });

}


CSetWidget::~CSetWidget()
{
    delete ui;
}


void CSetWidget::setTableScroller(QTableWidget *nTable)
{
    QScroller *pScroller = QScroller::scroller(nTable);
    pScroller->grabGesture(nTable,QScroller::LeftMouseButtonGesture);//设置手势识别
    QScrollerProperties properties = pScroller->scrollerProperties();
    properties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy,1);//设置越区策略为禁止越区
    pScroller->setScrollerProperties(properties);
    nTable->setVerticalScrollMode(QListWidget::ScrollPerPixel);//设置为像素移动
}



void CSetWidget::on_mBtn_High_Login_clicked()
{
    if(ui->mEdit_High_Login->text()=="111111")
    {

    }else
    {
        CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false);
        msgdlog->ui->mLabel_text1->setText(tr("密码错误，请重试"));
        msgdlog->ui->mLabel_text2->setText(tr("提示"));
        msgdlog->ui->mBtn_OK->setText(tr("确定"));
        msgdlog->exec();
        delete msgdlog;
        ui->mEdit_High_Login->clear();
    }
}

void CSetWidget::on_pushButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(NULL,"Open File","","CSV File (*.csv)");
    QFileInfo fi(fileName);
    if(fi.exists()){
        QFile fl(fi.absoluteFilePath());
        if(fl.open(QFile::ReadOnly)){
            QTextStream *inf = new QTextStream(&fl);
            QStringList f_data = inf->readAll().split("\n",QString::SkipEmptyParts);
            ST_Order d_data1;
            for(int i=0;i<f_data.length();i++){
                QStringList orderinfo = f_data.at(i).split(",");
                d_data1.order_type<<orderinfo.at(1);
                d_data1.t_order<<orderinfo;
//                d_data1.n_order=0;
                Control::CSetManager::getInstances()->set_order(d_data1);
            }
            ui->file_name->setText(fi.baseName());
        }
    }
}
