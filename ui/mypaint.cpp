#include "mypaint.h"
#include "ui_mypaint.h"

MyPaint::MyPaint(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::MyPaint)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::Dialog |Qt::FramelessWindowHint);
    QBitmap bmp(this->size());
    bmp.fill();
    QPainter p(&bmp);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    p.drawRoundedRect(bmp.rect(),10,10);
    setMask(bmp);
}

MyPaint::~MyPaint()
{
    delete ui;
}

void MyPaint::paintEvent(QPaintEvent *)
{
    m_pixmap = QPixmap(size());//新建pixmap
    m_pixmap.fill(Qt::white);//背景色填充为白色
    QPixmap pix = m_pixmap;//以m_pixmap作为画布
    QPainter p(&pix);//将m_pixmap作为画布
    p.setPen(QPen(QColor(0, 0, 0), 10));
    unsigned int i1=0;//各种图形的索引

    for(int c = 0;c<m_shape.size();++c)//控制用户当前所绘图形总数
    {
        if(m_shape.at(c) == 1)//线条
        {
            const QVector<QPoint>& line = m_lines.at(i1++);//取出一条线条
            for(int j=0; j<line.size()-1; ++j)//将线条的所有线段描绘出
            {
                p.drawLine(line.at(j), line.at(j+1));
            }
        }
    }
    p.end();
    p.begin(this);//将当前窗体作为画布
    p.drawPixmap(0,0, pix);//将pixmap画到窗体
}

void MyPaint::mouseMoveEvent(QMouseEvent *e)
{
    if(m_lpress)
    {
        if(m_lines.size()<=0) return;//线条集合为空，不画线
        QVector<QPoint>& lastLine = m_lines.last();//最后添加的线条，就是最新画的
        lastLine.append(e->pos());//记录鼠标的坐标(线条的轨迹)
        update();//触发窗体重绘
    }
}

void MyPaint::mousePressEvent(QMouseEvent *e)
{
    if(e->button() == Qt::LeftButton)//当鼠标左键按下
    {
        m_lpress = true;//左键按下标志
        QVector<QPoint> line;//鼠标按下，新的线条开始
        m_lines.append(line);//将新线条添加到线条集合
        QVector<QPoint>& lastLine = m_lines.last();//拿到新线条
        lastLine.append(e->pos());//记录鼠标的坐标(新线条的开始坐标)
        m_shape.append(1);
    }
}

void MyPaint::mouseReleaseEvent(QMouseEvent *e)
{
    if(m_lpress)
    {
        QVector<QPoint>& lastLine = m_lines.last();//最后添加的线条，就是最新画的
        lastLine.append(e->pos());//记录线条的结束坐标
        m_lpress = false;//标志左键释放
    }
}

void MyPaint::on_mBtn_OK_clicked()
{
    ui->mBtn_Cancel->hide();
    ui->mBtn_OK->hide();
    //新建窗体大小的pixmap
    QPixmap pixmap(size());
    //将pixmap作为画布
    QPainter painter(&pixmap);
    //设置绘画区域、画布颜色
    painter.fillRect(QRect(0, 0, size().width(), size().height()), Qt::white);
    //将窗体渲染到painter，再由painter画到画布
    this->render(&painter);
    //不包含工具栏
    pixmap.copy(QRect(0,0,size().width(),size().height()));

    switch (m_PaintNum) {
    case 0:
        pixmap.save(QCoreApplication::applicationDirPath()+"/Signature/Signature_1.jpg");
        break;
    case 1:
        pixmap.save(QCoreApplication::applicationDirPath()+"/Signature/Signature_2.jpg");
        break;
    case 2:
        pixmap.save(QCoreApplication::applicationDirPath()+"/Signature/Signature_3.jpg");
        break;
    default:
        break;
    }
    QPixmap clearPix =  QPixmap(size());
    clearPix.fill (Qt::white);
    m_pixmap = clearPix;
    this->update();//重绘
    //CUIMsgRouter::getInstances()->set_blur(0);
    this->accept();
}





void MyPaint::on_mBtn_Cancel_clicked()
{
    //CUIMsgRouter::getInstances()->set_blur(0);
    this->reject();
}

void MyPaint::set_PaintNum(int nPainNum)
{
    m_PaintNum=nPainNum;
    ui->mBtn_Cancel->show();
    ui->mBtn_OK->show();
    m_lines.clear();
    m_shape.clear();
    this->update();
    //CUIMsgRouter::getInstances()->set_blur(40);
}
