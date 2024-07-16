#include "cuserwidget.h"
#include "ui_cuserwidget.h"

CUserWidget::CUserWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CUserWidget)
{
    ui->setupUi(this);

    QRegExp rx = QRegExp("[^']*");  //限制以下特殊符号在lineEdit中的输入
    QValidator *validator= new QRegExpValidator(rx);
    ui->mEdit_Contact->setValidator(validator);
    ui->mEdit_Dept->setValidator(validator);
    ui->mEdit_End_Time->setValidator(validator);
    ui->mEdit_ID->setValidator(validator);
    ui->mEdit_Name->setValidator(validator);
    ui->mEdit_Origin_Time->setValidator(validator);
    ui->mEdit_Password1->setValidator(validator);
    ui->mEdit_Password2->setValidator(validator);
    ui->mEdit_Statistics_Login->setValidator(validator);

    ui->mTable_User->horizontalHeader()->setHidden(false);
    ui->mTable_User->horizontalHeader()->setHighlightSections(false);
    ui->mTable_Statistics_Project->horizontalHeader()->setHidden(false);
    ui->mTable_Statistics_Project->horizontalHeader()->setHighlightSections(false);
    ui->mTable_Statistics_Batch->horizontalHeader()->setHidden(false);
    ui->mTable_Statistics_Batch->horizontalHeader()->setHighlightSections(false);
    setTableScroller(ui->mTable_User);
    setTableScroller(ui->mTable_Statistics_Project);
    setTableScroller(ui->mTable_Statistics_Batch);


    Group_Statistics= new QButtonGroup(this);
    Group_Statistics->addButton(ui->mCheck_Statistics_Project,1);
    Group_Statistics->addButton(ui->mCheck_Statistics_Batch,2);
    m_User_calendar=new CalendarWidget(this);
    m_User_calendar->hide();

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



    connect(Btn_Origin_Calendar,&QPushButton::clicked,[=]()
    {
        Calendar_Type=0;
        m_User_calendar->move(ui->mEdit_Origin_Time->x()+200,ui->mEdit_Origin_Time->y()+220);
        m_User_calendar->show();
    });
    connect(Btn_End_Calendar,&QPushButton::clicked,[=]()
    {
        Calendar_Type=1;
        m_User_calendar->move(ui->mEdit_End_Time->x()+160,ui->mEdit_End_Time->y()+220);
        m_User_calendar->show();
    });


    QObject::connect(m_User_calendar,&CalendarWidget::time_out,this,&CUserWidget::slt_time);

}

CUserWidget::~CUserWidget()
{
    delete ui;
}

void CUserWidget::init_table()
{
    on_mBtn_User_Retun_clicked();

}


void CUserWidget::slt_time(QString timeStr)
{
    switch (Calendar_Type) {
    case 0:
        ui->mEdit_Origin_Time->setText(timeStr);
        break;
    case 1:
        ui->mEdit_End_Time->setText(timeStr);
        break;
    default:
        break;
    }
}

void CUserWidget::setTableScroller(QTableWidget *nTable)
{
    QScroller *pScroller = QScroller::scroller(nTable);
    pScroller->grabGesture(nTable,QScroller::LeftMouseButtonGesture);//设置手势识别
    QScrollerProperties properties = pScroller->scrollerProperties();
    properties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy,1);//设置越区策略为禁止越区
    pScroller->setScrollerProperties(properties);
    nTable->setVerticalScrollMode(QListWidget::ScrollPerPixel);//设置为像素移动
}



void CUserWidget::on_mBtn_User_Add_clicked()
{
    AddorUpdate=true;
    ui->mEdit_ID->setStyleSheet("QLineEdit{border:1px solid #e1e3e7;border-radius:5px;font-size:28px;color:rgb(64,64,64);background-color:rgb(255,255,255);}");
    ui->User_mStacked->setCurrentIndex(1);
    
}

void CUserWidget::on_mBtn_User_Retun_clicked()
{
    ui->mEdit_ID->clear();
    ui->mEdit_Name->clear();
    ui->mEdit_Password1->clear();
    ui->mEdit_Password2->clear();
    ui->mEdit_Dept->clear();
    ui->mEdit_Contact->clear();
    ui->mCheck_Text->setChecked(false);
    ui->mCheck_Record->setChecked(false);
    ui->mCheck_Maintain->setChecked(false);
    ui->mCheck_QC->setChecked(false);
    ui->mCheck_Set->setChecked(false);
    ui->mCheck_Print->setChecked(false);
    ui->mCheck_User->setChecked(false);
    ui->mCheck_Calib->setChecked(false);
    ui->mCheck_Upload->setChecked(false);
    ui->User_mStacked->setCurrentIndex(0);
}

void CUserWidget::on_mBtn_User_Ok_Add_clicked()
{
    if(!ui->mEdit_ID->text().isEmpty()&&!ui->mEdit_Name->text().isEmpty()&&
    !ui->mEdit_Password1->text().isEmpty()&&!ui->mEdit_Password2->text().isEmpty()&&
    !ui->mEdit_Dept->text().isEmpty()&&!ui->mEdit_Contact->text().isEmpty())
    {
        if(ui->mEdit_Password1->text()==ui->mEdit_Password2->text())
        {
            QString PowerStr;
            if( ui->mCheck_Text->isChecked())
                PowerStr+="1";
            else
                PowerStr+="0";
            if( ui->mCheck_Record->isChecked())
                PowerStr+="1";
            else
                PowerStr+="0";
            if( ui->mCheck_Maintain->isChecked())
                PowerStr+="1";
            else
                PowerStr+="0";
            if(  ui->mCheck_QC->isChecked())
                PowerStr+="1";
            else
                PowerStr+="0";
            if(  ui->mCheck_Set->isChecked())
                PowerStr+="1";
            else
                PowerStr+="0";
            if( ui->mCheck_Print->isChecked())
                PowerStr+="1";
            else
                PowerStr+="0";
            if( ui->mCheck_User->isChecked())
                PowerStr+="1";
            else
                PowerStr+="0";
            if( ui->mCheck_Calib->isChecked())
                PowerStr+="1";
            else
                PowerStr+="0";
            if( ui->mCheck_Upload->isChecked())
                PowerStr+="1";
            else
                PowerStr+="0";

          bool ok;
          int val = PowerStr.toInt(&ok,2);
          PowerStr = QString::number(val,10);
          if(AddorUpdate){
                if(Control::CDBManager::getInstance()->getUserAdd(ui->mEdit_ID->text(),
                                                                  ui->mEdit_Name->text(),
                                                                  ui->mEdit_Password1->text(),
                                                                  PowerStr.toInt(),
                                                                  ui->mEdit_Dept->text(),
                                                                  ui->mEdit_Contact->text()))
                    qDebug()<<"add user success";
                on_mBtn_User_Retun_clicked();
          }
        }
    }
}
