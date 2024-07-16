#include "piebutton.h"

PieButton::PieButton(QWidget *parent):QPushButton(parent)
{
    setFlat(true);
    setStyleSheet("QPushButton{background:transparent;}");
    for(int i=0;i<16;i++)
    {
        mExist[i]=false;
        drawColor[i] = QColor(205,206,214);
        m_text[i]=tr("空闲");
    }
    drawPen = QPen(Qt::white);
    drawTextPen = QPen(Qt::black);
}

PieButton::~PieButton()
{

}


void PieButton::updateDraw(int num,int state,QString info,QString batch)
{
    if(errorNum==num)
    {
        errorNum=-1;
    }
    switch (state) {
    case 0:
    {
        drawColor[num] = ready_Color;
    }
        break;//空闲
    case 1:
        drawColor[num] = exit_Color;
        break;//退卡
    case 2:
        drawColor[num] = busy_Color;
        break;//忙
    case 3:
        drawColor[num] = white_Color;
        break;
    case 4:
    {
        drawColor[num] = empty_Color;
        errorNum=num;
    }
        break;
    }
    m_text[num]=info;
    if(batch.isEmpty())
    {
        m_lastBatch=batch;
    }
    else
    {
        m_lastNum=num;
        m_lastText=info;
        m_lastBatch=batch;
    }
    update();
}

void PieButton::refreshDraw(bool batchOrText)
{
    qDebug()<<"batchOrText"<<batchOrText;
    qDebug()<<"m_lastNum"<<m_lastNum;
    qDebug()<<"m_lastText"<<m_lastText;
    qDebug()<<"m_lastBatch"<<m_lastBatch;
    if(!m_lastBatch.isEmpty())
    {
        qDebug()<<"isEmpty"<<m_lastBatch;
        switch (4) {
            case 0:drawColor[m_lastNum] = ready_Color;break;//空闲
            case 1:drawColor[m_lastNum] = exit_Color;break;//退卡
            case 2:drawColor[m_lastNum] = busy_Color;break;//忙
            case 3:drawColor[m_lastNum] = white_Color;break;
            case 4:drawColor[m_lastNum] = empty_Color;break;
        }
        if(batchOrText)
        {
            m_text[m_lastNum]=m_lastText;
        }
        else
        {
            m_text[m_lastNum]=m_lastBatch;
        }
        update();
    }
}

void PieButton::set_data(int mFontSize, double m_num_ratio,bool m_just)
{
    FontSize=mFontSize;
    num_ratio=m_num_ratio;
    just=m_just;
}

void PieButton::paintEvent(QPaintEvent *e)
{
    QPushButton::paintEvent(e);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);//抗锯齿
    painter.setPen(drawPen);
    painter.setBrush(QBrush(drawColor[0]));
    painter.drawPie(m_drawArea,90*16,1920);
    painter.setBrush(QBrush(drawColor[1]));
    painter.drawPie(m_drawArea,210*16,1920);
    painter.setBrush(QBrush(drawColor[2]));
    painter.drawPie(m_drawArea,330*16,1920);

    painter.setBrush(QBrush(Qt::white));
    painter.drawPie(m_circlesArea,360*1,360*16);

    painter.setPen(drawTextPen);
    QFont font;
    font.setPointSize(FontSize);
    painter.setFont(font);

    if(just)
    {
            int angle = 100;
            painter.setRenderHint(QPainter::Antialiasing,true);
            painter.translate(width()/2,height()/2);
            painter.drawRect(-2,-2,4,4);
            painter.setFont(font);
            QPoint point(height()/num_ratio,0);        //从(100,0)开始填文字
            for(int i=0;i<16;i++)
            {
               point=CustomRotate(point,angle,22.5);         //以当前angle度,顺时针旋转36度
               painter.drawText(point.x()-10,point.y()-10,20,20,Qt::AlignCenter,QString("%1").arg(QString::number(i+1)));
               angle -=22.5;                                  //更新度数,由于顺时针,所以用减
            }
    }
    else
    {
       painter.setRenderHint(QPainter::Antialiasing,true);
       painter.translate(width()/2,height()/2);
       painter.setFont(font);
       for(int i=1;i<17;i++)
       {
           painter.save();
           painter.rotate(i*22.5-90-15);
           painter.drawText(width()/10,0,width()/4,30,Qt::AlignCenter,QString("%1").arg(QString::number(i)));
           painter.restore();
       }
       font.setPointSize(FontSize-2);
       painter.setFont(font);
       for(int i=1;i<17;i++)
       {
           painter.save();
           painter.rotate(i*22.5-90-15);
           painter.drawText(width()/4,0,width()/4,30,Qt::AlignCenter,QString("%1").arg(m_text[i-1]));
           painter.restore();
       }
    }
}
void PieButton::resizeEvent(QResizeEvent *event)
{
    //以较短的边长作为绘制区域边长
    Q_UNUSED(event);
    m_drawArea = QRect(0,0,width(),height());
    m_circlesArea= QRect(width()/3,height()/3,width()/3,height()/3);
//    int r=width()/2;
//    QLabel *circles_lab=new QLabel(this);
//    QString label_style =QString("background-color:white;color:white;border-radius:%1px").arg(width()/6);
//    circles_lab->setStyleSheet(label_style);
//    circles_lab->setGeometry(r-width()/6,r-width()/6,width()/3,height()/3);

}

/*  point: 文字所在的点
 *  from_angle : 文字所在的度数
 *  rotate : 需要旋转的角度,值为-360~360(为负数表示逆时针旋转,为正数表示顺时针旋转)
 */
QPoint PieButton::CustomRotate(QPointF point,qreal from_angle,qreal rotate)
{
    qreal PI=3.141592653589;
    QPointF Tmp;
    qreal arc = (rotate-from_angle)/180*PI;
    qreal Length = sqrt(point.x()*point.x() +point.y()*point.y());
    Tmp.setX(Length*cos(arc));
    Tmp.setY(Length*sin(arc));
    return Tmp.toPoint();
}

int PieButton::getBitNum()//获取空槽位置
{
    for(int i=0;i<16;i++)
    {
        if(!mExist[i])
        {
           mExist[i]=true;
           return i;
        }
    }
    return 16;
}

int PieButton::getBitSum()//获取总数
{
    int num=0;
    for(int i=0;i<16;i++)
    {
        if(mExist[i])
        {
            num++;
            qDebug()<<"获取总数"<<num;
        }
    }
    return num;
}

int PieButton::getErrorNum()
{
    return errorNum;
}

void PieButton::setBitNum(int num)//将位置空闲
{
    mExist[num]=false;
}

