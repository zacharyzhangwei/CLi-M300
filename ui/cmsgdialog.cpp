#include "cmsgdialog.h"
#include "ui_cmsgdialog.h"

//标题、内容、中间显示图片、进度条、确定键、退出键、分页
CMsgDialog::CMsgDialog(bool text1, bool text2, bool logo, bool nBar, bool nBtn1, bool nBtn2 ,int nIndex) :
    ui(new Ui::CMsgDialog)
{
    ui->setupUi(this);

    QRegExp rx = QRegExp("[^']*");  //限制以下特殊符号在lineEdit中的输入
    QValidator *validator= new QRegExpValidator(rx);
    ui->mEdit_Edit->setValidator(validator);



    this->setWindowFlags(Qt::Dialog |Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);//设置背景透明

//    //设置圆角
//    QBitmap bmp(this->size());
//    bmp.fill();
//    QPainter p(&bmp);
//    p.setPen(Qt::NoPen);
//    p.setBrush(Qt::black);
//    p.drawRoundedRect(bmp.rect(),20,20);
//    setMask(bmp);

    ui->m_SeackDialog->setCurrentIndex(nIndex);
    setType(text1,text2,logo,nBar,nBtn1,nBtn2);
}

CMsgDialog::~CMsgDialog()
{
    delete ui;
}

void CMsgDialog::setType(bool text1, bool text2, bool logo, bool nBar, bool nBtn1, bool nBtn2)
{
    if(!text1)
    {
        ui->mLabel_text1->hide();
    }
    if(!text2)
    {
        ui->mLabel_text2->hide();
    }
    if(!logo)
    {
        ui->mFrame_logo->hide();
    }
    if(!nBar)
    {
        ui->mFrame_Bar->hide();
    }
    if(!nBtn1)
    {
        ui->mBtn_OK->hide();
    }
    if(!nBtn2)
    {
        ui->mBtn_Cancel->hide();
        if(!nBtn1)
        {
            ui->mFrame_Btn->hide();
        }
    }
    if(nBtn1&&nBtn2)
    {
        ui->mBtn_OK->setStyleSheet("QPushButton{color:rgb(63,63,63);font-size:28px;background-color:rgb(255,255,255);border-bottom-left-radius:15px;}"
                                           "QPushButton:hover{color:rgb(31,78,121);background-color:rgb(255,255,255);border-bottom-left-radius:15px;}");
        ui->mBtn_Cancel->setStyleSheet("QPushButton{color:rgb(63,63,63);font-size:28px;background-color:rgb(255,255,255);border-bottom-right-radius:15px;}"
                                           "QPushButton:hover{color:rgb(31,78,121);background-color:rgb(255,255,255);border-bottom-right-radius:15px;}");
    }
    else if(nBtn1&&!nBtn2)
    {
        ui->mBtn_OK->setStyleSheet("QPushButton{color:rgb(63,63,63);font-size:28px;background-color:rgb(255,255,255);border-bottom-right-radius:15px;border-bottom-left-radius:15px;}"
                                           "QPushButton:hover{color:rgb(31,78,121);background-color:rgb(255,255,255);border-bottom-right-radius:15px;border-bottom-left-radius:15px;}");
    }
    else if(!nBtn1&&nBtn2)
    {
        ui->mBtn_Cancel->setStyleSheet("QPushButton{color:rgb(63,63,63);font-size:28px;background-color:rgb(255,255,255);border-bottom-right-radius:15px;border-bottom-left-radius:15px;}"
                                           "QPushButton:hover{color:rgb(31,78,121);background-color:rgb(255,255,255);border-bottom-right-radius:15px;border-bottom-left-radius:15px;}");
    }
}

void CMsgDialog::setBtnState(bool state)
{
    if(state)
    {
        on_mBtn_OK_clicked();
    }
    else
    {
        on_mBtn_Cancel_clicked();
    }
}

void CMsgDialog::mousePressEvent(QMouseEvent *qevent)//鼠标按下事件
{
    if(qevent->button() == Qt::LeftButton)
    {
        //鼠标相对于窗体的位置（或者使用event->globalPos() - this->pos()）
        move_point = qevent->pos();
        if(move_point.y()<65)
        {
            mouse_press = true;
        }
    }
}

void CMsgDialog::mouseReleaseEvent(QMouseEvent *qevent)//鼠标释放事件
{
    //若鼠标左键被按下
    if(mouse_press)
    {
        mouse_press = false;
        //鼠标相对于屏幕的位置
        QPoint move_pos = qevent->globalPos();
        //移动主窗体位置
        this->move(move_pos - move_point);
    }
}

void CMsgDialog::mouseMoveEvent(QMouseEvent *qevent)//鼠标移动事件
{
    //设置鼠标为未被按下
    if(mouse_press)
    {
        //鼠标相对于屏幕的位置
        QPoint move_pos = qevent->globalPos();
        //移动主窗体位置
        this->move(move_pos - move_point);
    }
}

void CMsgDialog::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<"keyPressEvent"<<event->key();
    if (event->key() == Qt::Key_Escape)
    {
        return;
    }
    else if (event->key() == Qt::Key_Enter)
    {
        qDebug()<<"Key_Enter";
        return;
    }
    else if (event->key() == Qt::Key_Return)
    {
        qDebug()<<"Key_Return";
        return;
    }
    else if (event->key() == Qt::Key_Space)
    {
        return;
    }
}

void CMsgDialog::on_mBtn_OK_clicked()
{
    //CUIMsgRouter::getInstances()->set_blur(0);
    this->accept();
}

void CMsgDialog::on_mBtn_Cancel_clicked()//取消
{
    //CUIMsgRouter::getInstances()->set_blur(0);
    this->reject();
}

void CMsgDialog::on_mBtn_Edit_OK_clicked()
{
    //CUIMsgRouter::getInstances()->set_blur(0);
    this->accept();
}

void CMsgDialog::on_mBtn_Edit_Cancel_clicked()
{
    //CUIMsgRouter::getInstances()->set_blur(0);
    this->reject();
}
