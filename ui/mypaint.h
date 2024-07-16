#ifndef MYPAINT_H
#define MYPAINT_H

#include <QDialog>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QToolBar>
#include <QAction>
#include <QPalette>
#include <QColor>
#include <QMenu>
#include <QFileDialog>
#include <QTextEdit>
#include <qDebug>
#include <QPushButton>
#include <QCoreApplication>
#include <QBitmap>




#pragma execution_character_set("utf-8")
namespace Ui {
class MyPaint;
}

class MyPaint : public QDialog
{
    Q_OBJECT

public:
    explicit MyPaint(QDialog *parent = nullptr);
    ~MyPaint();
    int m_PaintNum=1;
    QVector<QVector<QPoint> > m_lines;//线条集合(一条线条可包含多个线段)
    QVector<int>  m_shape;//图形类型集合，用于撤回功能
protected:
    void paintEvent(QPaintEvent *);//重写窗体重绘事件
    void mouseMoveEvent(QMouseEvent *);//重写鼠标移动事件
    void mousePressEvent(QMouseEvent *);//重写鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *);//重写鼠标释放事件
private:
    int m_lpress;//左键按下标志
    QPixmap m_pixmap;//画布图片
private slots:
    void on_mBtn_OK_clicked();//保存图片
    void on_mBtn_Cancel_clicked();

private:
    Ui::MyPaint *ui;

public:
    void set_PaintNum(int nPainNum);
};

#endif // MYPAINT_H
