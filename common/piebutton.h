#ifndef PIEBUTTON_H
#define PIEBUTTON_H

#include<QEvent>
#include<QDebug>
#include<QPainter>
#include<QMouseEvent>
#include<QPushButton>
#include<QLabel>
#include "cmgrmsgrouter.h"
#pragma execution_character_set("utf-8")

class PieButton : public QPushButton
{
    Q_OBJECT
public:
    explicit PieButton(QWidget*parent=NULL);
    ~PieButton();

    void updateDraw(int num, int state, QString info, QString batch="");
    void refreshDraw(bool batchOrText);
    void set_data(int mFontSize, double m_num_ratio , bool m_just);
    QPoint CustomRotate(QPointF point,qreal from_angle,qreal rotate);
    int getBitNum();
    int getBitSum();//获取总数
    int getErrorNum();

    void setBitNum(int num);
protected:
    void paintEvent(QPaintEvent *e);
    void resizeEvent(QResizeEvent *event);
private:
    int FontSize=0;
    double num_ratio=0;
    bool just=true;

    QRect m_drawArea;
    QRect m_circlesArea;
    QColor drawColor[16];
    QPen drawPen;
    QPen drawTextPen;
    QString m_text[16];
    bool mExist[16];
    QString m_lastText;//无批号 批号名
    QString m_lastBatch;//无批号 条码
    int m_lastNum;//无批号 条码
    int errorNum=-1;

    QColor white_Color = QColor(205,206,214);
    QColor empty_Color = QColor(255,127,80);
    QColor ready_Color = QColor(205,206,214);//空闲
    QColor exit_Color = QColor(31,78,121);//等待退卡
    QColor busy_Color = QColor(255,199,90);//忙

};

#endif // PIEBUTTON_H
