#ifndef CMSGDIALOG_H
#define CMSGDIALOG_H

#include <QDialog>
#include <QBitmap>
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

namespace Ui {
class CMsgDialog;
}

class CMsgDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CMsgDialog(bool text1, bool text2, bool logo, bool nBar, bool nBtn1, bool nBtn2, int nIndex=0);
    ~CMsgDialog();

    Ui::CMsgDialog *ui;
private:
public:
    void setType(bool text1, bool text2, bool logo, bool nBar, bool nBtn1, bool nBtn2);
    void setBtnState(bool state);//设置按键
protected:
    QPoint move_point;                                    //移动的距离
    bool mouse_press;
    void mousePressEvent(QMouseEvent *qevent);            //鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *qevent);         //鼠标释放事件
    void mouseMoveEvent(QMouseEvent *qevent);             //鼠标移动事件
    void keyPressEvent(QKeyEvent *event);
public slots:
    void on_mBtn_Cancel_clicked();
private slots:
    void on_mBtn_OK_clicked();
    void on_mBtn_Edit_OK_clicked();
    void on_mBtn_Edit_Cancel_clicked();
};

#endif // CMSGDIALOG_H
