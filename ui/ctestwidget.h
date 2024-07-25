#ifndef CTESTWIDGET_H
#define CTESTWIDGET_H

#include <QWidget>
#include <QTableWidgetItem>
#include <QTableWidget>
#include "cmsgdialog.h"
#include "ui_cmsgdialog.h"
#include "control/ctestmanager.h"
#include "control/cdbmanager.h"
#include "control/cmodbusmanager.h"
#include "control/csetmanager.h"

namespace Ui {
class CTestWidget;
}

class CTestWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CTestWidget(QWidget *parent = 0);
    ~CTestWidget();
    void selfCheck(int i);
    enum_Test_Cmd m_Cmd=enum_Test_Null;
    void slt_startTest();
    void slt_editInfo();
    void slt_Readresult();
    void set_testModel(bool m_test);

private slots:
    void on_mBtn_Edit_clicked();

    void on_mBtn_Diag_Retun_clicked();

    void on_mBtn_Edit_Info_clicked();

    void on_mBtn_Edit_Retun_clicked();

    void on_mBtn_Info_Retun_clicked();

    void on_mBtn_Info_Edit_clicked();

    void on_mBtn_Diag_Clear_clicked();

    void on_mBtn_Dept_add_clicked();

    void on_mBtn_Review_add_clicked();

    void on_mBtn_Test_add_clicked();

    void on_mBtn_Submit_add_clicked();

    void on_mBtn_Submit_delete_clicked();

    void on_mBtn_Test_delete_clicked();

    void on_mBtn_Review_delete_clicked();

    void on_mBtn_Dept_delete_clicked();

    void on_mBtn_Edit_Save_clicked();

    void on_mBtn_Diag_Save_clicked();

    void on_mBtn_Open_clicked();

    void slt_ReadModbusinfo(QStringList nstate);

    void slt_ReadData(QStringList nstate);

    void slt_ShowData(QStringList nstate);

    void p_table_reflash();


private:
    Ui::CTestWidget *ui;
    void initTable();
    void setTableScroller(QTableWidget *nTable);//设置类安卓滑动
    void init_Operator_table();
    int m_nowDialogNum;
    bool model;
    bool test_model=true;


signals:
    void sgn_selfcheck();
    void sgn_cysTest();


};

#endif // CTESTWIDGET_H
