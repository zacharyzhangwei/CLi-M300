#include "calendarwidget.h"
#include "ui_calendarwidget.h"

//日历控件
CalendarWidget::CalendarWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalendarWidget)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Popup);
    QDateTime begin_time= QDateTime::currentDateTime();//获取系统现在的时间
    QString year_btimestr = begin_time.toString("yyyy");
    QString month_btimestr = begin_time.toString("MM");
    QString day_btimestr = begin_time.toString("dd");
    QString hour_str=begin_time.toString("hh");
    QString minute_str=begin_time.toString("mm");
    QString second_str=begin_time.toString("ss");

    ui->Calendar_lab_Now->setText(year_btimestr+"/"+month_btimestr);
    ui->Calendar_lab_ntime->setText(year_btimestr+"/"+month_btimestr+"/"+day_btimestr);
    ui->Calendar_btn_Hour->setText(hour_str);
    ui->Calendar_btn_Minute->setText(minute_str);
    ui->Calendar_btn_Second->setText(second_str);

    mCalendar = new  QCalendarWidget(this);
    ui->Calendar_layout_btn->addWidget(mCalendar);
    mCalendar->setNavigationBarVisible(false);

    if(Comom::CGlobal::getInstance()->m_lang==LANG_BIO_CHINESE)
    {
        mCalendar->setLocale(QLocale(QLocale::Chinese));//设置中文
    }
    else if(Comom::CGlobal::getInstance()->m_lang==LANG_BIO_CHINESE_C)
    {
        mCalendar->setLocale(QLocale(QLocale::Chinese));//设置中文
    }
    else
    {
        mCalendar->setLocale(QLocale(QLocale::English));//设置英文
    }



    mCalendar->setVerticalHeaderFormat(QCalendarWidget::NoVerticalHeader);//去掉列表头
    mCalendar->setHorizontalHeaderFormat(QCalendarWidget::ShortDayNames);//我想要星期几的行表头

    mCalendar->setStyleSheet(
                "QCalendarWidget QAbstractItemView{font-size:28px;;font-weight:500;outline:0px;}"
                "QCalendarWidget QAbstractItemView{color:rgb(255,255,255);background-color:rgb(31, 78, 121);}"
                "QCalendarWidget QAbstractItemView:disabled{color:rgb(144,144,144);background-color:rgb(230,230,250)}"
                "QCalendarWidget QAbstractItemView:enabled{color:rgb(64, 64, 64);}"
                "QCalendarView#qt_calendar_calendarview {background-color:rgb(240,240,240);alternate-background-color:rgb(240,240,240);}"
                );
    //设置星期风格
    QTextCharFormat format;
    format.setBackground(QColor(240,240,240));
    mCalendar->setWeekdayTextFormat(Qt::Saturday, format);
    mCalendar->setWeekdayTextFormat(Qt::Sunday,format);
    initWidget();
    connect(mCalendar,&QCalendarWidget::selectionChanged,[=]()
    {
        ui->Calendar_lab_ntime->setText(mCalendar->selectedDate().toString("yyyy/MM/dd"));
       });

    //ui->Calendar_Edit_num->setMaxLength(2);





    ui->Calendar_btn_Hour->setCheckable(true);//设置点击下去的状态
    ui->Calendar_btn_Hour->setAutoExclusive(true);
    ui->Calendar_btn_Minute->setCheckable(true);//设置点击下去的状态
    ui->Calendar_btn_Minute->setAutoExclusive(true);
    ui->Calendar_btn_Second->setCheckable(true);//设置点击下去的状态
    ui->Calendar_btn_Second->setAutoExclusive(true);
}

CalendarWidget::~CalendarWidget()
{
    delete ui;
}

void CalendarWidget::initWidget()
{
    QDate cdate=QDate::currentDate();
    QTextCharFormat TodayFormat;
    TodayFormat.setForeground(QColor(244,244,244));
    TodayFormat.setBackground(QColor(210,220,228));
    mCalendar->setDateTextFormat(cdate,TodayFormat);

    ui->Calendar_btn_Hour->setAutoExclusive(false);
    ui->Calendar_btn_Hour->setCheckable(true);//设置点击下去的状态
    ui->Calendar_btn_Hour->setAutoExclusive(true);

    ui->Calendar_btn_Second->setAutoExclusive(false);
    ui->Calendar_btn_Second->setCheckable(true);//设置点击下去的状态
    ui->Calendar_btn_Second->setAutoExclusive(true);

    ui->Calendar_btn_Minute->setAutoExclusive(false);
    ui->Calendar_btn_Minute->setCheckable(true);//设置点击下去的状态
    ui->Calendar_btn_Minute->setAutoExclusive(true);

    ui->Calendar_Edit_num->hide();
    ui->Calendar_btn_subtract->hide();
    ui->Calendar_btn_add->hide();


    mCalendar->show();
    time_flag=0;

}

void CalendarWidget::mousePressEvent(QMouseEvent *e)
{
    setAttribute(Qt::WA_NoMouseReplay);
    QWidget::mousePressEvent(e);
}

void CalendarWidget::on_Calendar_btn_YSubtract_clicked()
{
    mCalendar->showPreviousYear();
    setDataLabelTimeText(mCalendar->yearShown(), mCalendar->monthShown());

}

void CalendarWidget::on_Calendar_btn_MSubtract_clicked()
{
    mCalendar->showPreviousMonth();
    setDataLabelTimeText(mCalendar->yearShown(), mCalendar->monthShown());
}

void CalendarWidget::on_Calendar_btn_MAdd_clicked()
{
    mCalendar->showNextMonth();
    setDataLabelTimeText(mCalendar->yearShown(), mCalendar->monthShown());
}

void CalendarWidget::on_Calendar_btn_YAdd_clicked()
{
    mCalendar->showNextYear();
    setDataLabelTimeText(mCalendar->yearShown(), mCalendar->monthShown());
}

void CalendarWidget::setDataLabelTimeText(int year_num, int month_num)
{
    ui->Calendar_lab_Now->setText(QString("%1-%2").arg(year_num,4,10,QLatin1Char('0')).arg(month_num,2,10,QLatin1Char('0')));
}

void CalendarWidget::on_Calendar_btn_Hour_clicked()
{
    if(mCalendar->isVisible())
    {
        time_flag=1;
        num_max=23;
        mCalendar->hide();
        ui->Calendar_Edit_num->setText(ui->Calendar_btn_Hour->text());
        ui->Calendar_Edit_num->show();
        ui->Calendar_btn_subtract->show();
        ui->Calendar_btn_add->show();
    }
    else
    {
        if(time_flag==1)
        {

            ui->Calendar_btn_Hour->setAutoExclusive(false);
            ui->Calendar_btn_Hour->setChecked(false);
            ui->Calendar_btn_Hour->setAutoExclusive(true);
            ui->Calendar_Edit_num->hide();
            ui->Calendar_btn_subtract->hide();
            ui->Calendar_btn_add->hide();
            mCalendar->show();
            time_flag=0;
        }
        else
        {
            time_flag=1;
            num_max=23;
            ui->Calendar_Edit_num->setText(ui->Calendar_btn_Hour->text());
        }
    }
}

void CalendarWidget::on_Calendar_btn_Minute_clicked()
{

    if(mCalendar->isVisible())
    {
        time_flag=2;
        num_max=59;
        mCalendar->hide();
        ui->Calendar_Edit_num->setText(ui->Calendar_btn_Minute->text());
        ui->Calendar_Edit_num->show();
        ui->Calendar_btn_subtract->show();
        ui->Calendar_btn_add->show();
    }
    else
    {
        if(time_flag==2)
        {
            ui->Calendar_btn_Minute->setAutoExclusive(false);
            ui->Calendar_btn_Minute->setChecked(false);
            ui->Calendar_btn_Minute->setAutoExclusive(true);
            ui->Calendar_Edit_num->hide();
            ui->Calendar_btn_subtract->hide();
            ui->Calendar_btn_add->hide();
            mCalendar->show();
            time_flag=0;
        }
        else
        {
            time_flag=2;
            num_max=59;
            ui->Calendar_Edit_num->setText(ui->Calendar_btn_Minute->text());
        }

    }
}

void CalendarWidget::on_Calendar_btn_Second_clicked()
{
    if(mCalendar->isVisible())
    {
        time_flag=3;
        num_max=59;
        mCalendar->hide();
        ui->Calendar_Edit_num->setText(ui->Calendar_btn_Second->text());
        ui->Calendar_Edit_num->show();
        ui->Calendar_btn_subtract->show();
        ui->Calendar_btn_add->show();
    }
    else
    {
        if(time_flag==3)
        {
            ui->Calendar_btn_Second->setAutoExclusive(false);
            ui->Calendar_btn_Second->setChecked(false);
            ui->Calendar_btn_Second->setAutoExclusive(true);
            ui->Calendar_Edit_num->hide();
            ui->Calendar_btn_subtract->hide();
            ui->Calendar_btn_add->hide();
            mCalendar->show();
            time_flag=0;
        }
        else
        {
            time_flag=3;
            num_max=59;
            ui->Calendar_Edit_num->setText(ui->Calendar_btn_Second->text());
        }

    }
}

void CalendarWidget::on_Calendar_btn_add_clicked()
{
    int num=ui->Calendar_Edit_num->text().toInt();
    if(num<num_max)
    {
        num++;
    }
    else
    {
        num=0;
    }
    ui->Calendar_Edit_num->setText(QString("%1").arg(num,2,10,QLatin1Char('0')));
    switch (time_flag) {
    case 1:
        ui->Calendar_btn_Hour->setText(ui->Calendar_Edit_num->text());
        break;
    case 2:
        ui->Calendar_btn_Minute->setText(ui->Calendar_Edit_num->text());
        break;
    case 3:
        ui->Calendar_btn_Second->setText(ui->Calendar_Edit_num->text());
        break;
    default:
        break;
    }
}

void CalendarWidget::on_Calendar_btn_subtract_clicked()
{
    int num=ui->Calendar_Edit_num->text().toInt();
    if(num>0)
    {
        num--;
    }
    else
    {
        num=num_max;
    }
    ui->Calendar_Edit_num->setText(QString("%1").arg(num,2,10,QLatin1Char('0')));
    switch (time_flag) {
    case 1:
        ui->Calendar_btn_Hour->setText(ui->Calendar_Edit_num->text());
        break;
    case 2:
        ui->Calendar_btn_Minute->setText(ui->Calendar_Edit_num->text());
        break;
    case 3:
        ui->Calendar_btn_Second->setText(ui->Calendar_Edit_num->text());
        break;
    default:
        break;
    }
}

void CalendarWidget::on_Calendar_btn_Ok_clicked()
{
    QString time_str=ui->Calendar_lab_ntime->text()+" "
            +ui->Calendar_btn_Hour->text()+":"
            +ui->Calendar_btn_Minute->text()+":"
            +ui->Calendar_btn_Second->text();
    emit time_out(time_str);
    this->hide();
}

void CalendarWidget::on_Calendar_btn_Cancel_clicked()
{
    this->hide();
}

void CalendarWidget::on_Calendar_btn_Now_clicked()
{
    QDateTime begin_time= QDateTime::currentDateTime();//获取系统现在的时间
    QString year_btimestr = begin_time.toString("yyyy");
    QString month_btimestr = begin_time.toString("MM");
    QString day_btimestr = begin_time.toString("dd");
    QString hour_str=begin_time.toString("hh");
    QString minute_str=begin_time.toString("mm");
    QString second_str=begin_time.toString("ss");
    ui->Calendar_lab_Now->setText(year_btimestr+"/"+month_btimestr);
    ui->Calendar_lab_ntime->setText(year_btimestr+"/"+month_btimestr+"/"+day_btimestr);
    ui->Calendar_btn_Hour->setText(hour_str);
    ui->Calendar_btn_Minute->setText(minute_str);
    ui->Calendar_btn_Second->setText(second_str);
    mCalendar->showToday();
}

void CalendarWidget::on_Calendar_Edit_num_textChanged(const QString &arg1)
{
    if(arg1.toInt()>num_max)
    {
        ui->Calendar_Edit_num->clear();
        switch (time_flag)
        {
        case 1:
            ui->Calendar_btn_Hour->setText("00");
            break;
        case 2:
            ui->Calendar_btn_Minute->setText("00");
            break;
        case 3:
            ui->Calendar_btn_Second->setText("00");
            break;
        default:
            break;
        }
    }
    else if(arg1.length()>2)
    {
        ui->Calendar_Edit_num->clear();
        switch (time_flag)
        {
        case 1:
            ui->Calendar_btn_Hour->setText("00");
            break;
        case 2:
            ui->Calendar_btn_Minute->setText("00");
            break;
        case 3:
            ui->Calendar_btn_Second->setText("00");
            break;
        default:
            break;
        }
    }
    else
    {
        QString number;
        if(arg1.toInt()<10&&arg1.length()==1)
            number="0"+arg1;
        else
            number=arg1;

        switch (time_flag)
        {
        case 1:
            ui->Calendar_btn_Hour->setText(number);
            break;
        case 2:
            ui->Calendar_btn_Minute->setText(number);
            break;
        case 3:
            ui->Calendar_btn_Second->setText(number);
            break;
        default:
            break;
        }
    }
}
