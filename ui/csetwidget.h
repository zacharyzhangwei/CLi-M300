#ifndef CSETWIDGET_H
#define CSETWIDGET_H

#include <QWidget>
#include <QListView>
#include <QWidgetAction>
#include <QImage>
#include <QPrintPreviewDialog>
#include <QScrollerProperties>
#include <QScroller>
#include <QListWidget>
#include "calendarwidget.h"
#include "common/cglobal.h"
#include "control/csetmanager.h"
#include "cconfgmanager.h"
#include "csocketmanager.h"
#include "mypaint.h"

#include "cmsgdialog.h"
#include "ui_cmsgdialog.h"
#include "control/ctestmanager.h"
namespace Ui {
class CSetWidget;
}

class CSetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CSetWidget(QWidget *parent = 0);
    ~CSetWidget();

private slots:
    void on_mBtn_High_Login_clicked();

    void on_pushButton_clicked();

private:
    void setTableScroller(QTableWidget *nTable);//设置类安卓滑动
private:
    Ui::CSetWidget *ui;
    QButtonGroup *Group_Print;
    QButtonGroup *Group_PaperType;
    QButtonGroup *Group_Signature;
    QButtonGroup *Group_Temp;
    QButtonGroup *Group_Image;
    QButtonGroup *mGroup_BtnSignature;
    MyPaint*m_Paint;
    CalendarWidget *set_calendar;


    bool m_editInfoState=false;//编辑标志位
    QString m_sHtml;
    QButtonGroup *m_GroupReport;
    QString m_Lower_VersionsStr;
    bool itemWriteFlag=false;
    bool itemselectFlag=false;//选中标志位


};

#endif // CSETWIDGET_H
