#include "ctestwidget.h"
#include "ui_ctestwidget.h"

CTestWidget::CTestWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CTestWidget)
{
    ui->setupUi(this);
    ui->Diag_mStacked->setCurrentIndex(0);
    initTable();
    QObject::connect(Control::CModBusManager::getInstance(),&Control::CModBusManager::sgn_M_readInfo,this,&CTestWidget::slt_ReadModbusinfo);
    QObject::connect(Control::CModBusManager::getInstance(),&Control::CModBusManager::sgn_M_scanData,this,&CTestWidget::slt_ReadData);
    QObject::connect(Control::CModBusManager::getInstance(),&Control::CModBusManager::sgn_M_testData,this,&CTestWidget::slt_ShowData);

    ui->mBtn_Open->setEnabled(false);

}

CTestWidget::~CTestWidget()
{ 
    delete ui;
}

void CTestWidget::selfCheck(int i)
{
    if(i==1){
        if(Control::CModBusManager::getInstance()->WriteBit(DEF_DEVICERESET,1)){
            m_Cmd = enum_Test_RESET;
            if(Control::CModBusManager::getInstance()->WriteBit(DEF_SELFTEST,1)){
                qDebug()<<"perform selfcheck";
                CGLOBAL->getTools()->setdelaymTime(300);
                m_Cmd = enum_Test_Self;
            }
        }
    }else if(i==2){
        if(Control::CModBusManager::getInstance()->WriteBit(DEF_INIT,1)){
            CGLOBAL->getTools()->setdelaymTime(100);
            m_Cmd=enum_Test_Init;
        }
    }


}

void CTestWidget::slt_startTest()
{
    if(Control::CModBusManager::getInstance()->WriteBit(DEF_DEVTEST,1)){
        CGLOBAL->getTools()->setdelaymTime(500);
        m_Cmd = enum_Test_DevTest;
        qDebug()<<"start Test";
    }
}

void CTestWidget::slt_editInfo()
{
    qDebug()<<"scan sucess";
    Control::CModBusManager::getInstance()->readData(0,1,450,30);
//    ui->Diag_mStacked->setCurrentIndex(1);
    //    ui->tabWidget_patient->setTabText(0,tr("盘1"));
}

void CTestWidget::slt_Readresult()
{
    qDebug()<<"devtestended";
    Control::CModBusManager::getInstance()->readData(1,1,300,50);
}

void CTestWidget::on_mBtn_Edit_clicked()
{

    CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,true);
    msgdlog->ui->mLabel_text1->setText(tr("请放置待测盘片\n完成放置后点击确认进入患者信息编辑界面"));
    msgdlog->ui->mLabel_text2->setText(tr("提示"));
    msgdlog->ui->mBtn_OK->setText(tr("确认"));
    msgdlog->ui->mBtn_Cancel->setText(tr("返回"));
    int nRes=msgdlog->exec();
    if(nRes==QDialog::Accepted)
    {
        if(Control::CModBusManager::getInstance()->WriteBit(DEF_SCAN,1)&&(Control::CModBusManager::getInstance()->getModbusFlag())){
            CGLOBAL->getTools()->setdelaymTime(200);
            m_Cmd = enum_Test_Scan;
        }else{
            qDebug()<<"modbus disconnect";
            ui->Diag_mStacked->setCurrentIndex(1);
            ui->tabWidget_patient->setTabText(0,tr("盘1"));
        }

    }
    else if(nRes==QDialog::Rejected)//软件重启
    {
        ui->Diag_mStacked->setCurrentIndex(0);
    }
    delete msgdlog;

}


void CTestWidget::on_mBtn_Diag_Retun_clicked()
{
    ui->Diag_mStacked->setCurrentIndex(0);
}

void CTestWidget::on_mBtn_Edit_Info_clicked()
{
    ui->Diag_mStacked->setCurrentIndex(2);
}

void CTestWidget::on_mBtn_Edit_Retun_clicked()
{
    ui->Diag_mStacked->setCurrentIndex(1);
}

void CTestWidget::initTable()
{
    ui->mTable_Diag->horizontalHeader()->setHidden(false);
    ui->mTable_Diag->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->mTable_Result->horizontalHeader()->setHidden(false);
    ui->mTable_Result->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->mTable_Diag->horizontalHeader()->setHighlightSections(false);
    ui->mTable_Result->horizontalHeader()->setHighlightSections(false);
    ui->mTable_Add_Dept->horizontalHeader()->setHidden(false);
    ui->mTable_Add_Dept->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->mTable_Add_Submit->horizontalHeader()->setHidden(false);
    ui->mTable_Add_Test->horizontalHeader()->setHidden(false);
    ui->mTable_Add_Review->horizontalHeader()->setHidden(false);
    ui->mTable_Info_Info->horizontalHeader()->setHidden(false);
    ui->mTable_Info_Info->horizontalHeader()->setHighlightSections(false);
    ui->mTable_Add_Dept->horizontalHeader()->setHighlightSections(false);
    ui->mTable_Add_Submit->horizontalHeader()->setHighlightSections(false);
    ui->mTable_Add_Test->horizontalHeader()->setHighlightSections(false);
    ui->mTable_Add_Review->horizontalHeader()->setHighlightSections(false);
    ui->mTable_Course->verticalHeader()->setHidden(false);

    setTableScroller(ui->mTable_Course);
    setTableScroller(ui->mTable_Diag);
    setTableScroller(ui->mTable_Result);
    setTableScroller(ui->mTable_Add_Dept);
    setTableScroller(ui->mTable_Add_Submit);
    setTableScroller(ui->mTable_Add_Test);
    setTableScroller(ui->mTable_Add_Review);
    setTableScroller(ui->mTable_Info_Info);
    setTableScroller(ui->mTable_Result);

    ui->mTable_Info_Info->setColumnWidth(0,280);
}

void CTestWidget::setTableScroller(QTableWidget *nTable)
{
    nTable->setFocusPolicy(Qt::NoFocus); //去除选中虚线框
    QScroller *pScroller = QScroller::scroller(nTable);
    pScroller->grabGesture(nTable,QScroller::LeftMouseButtonGesture);//设置手势识别
    QScrollerProperties properties = pScroller->scrollerProperties();
    properties.setScrollMetric(QScrollerProperties::VerticalOvershootPolicy,1);//设置越区策略为禁止越区
    properties.setScrollMetric(QScrollerProperties::HorizontalOvershootPolicy,1);//设置越区策略为禁止越区
    pScroller->setScrollerProperties(properties);
    nTable->setVerticalScrollMode(QListWidget::ScrollPerPixel);//设置为像素移动
}

void CTestWidget::init_Operator_table()
{
    ui->mCom_Doctor->clear();
    ui->mCom_SubmittedBy->clear();
    ui->mCom_TestedBy->clear();
    ui->mCom_SubmittedDept->clear();

    QStringList nDeptList=Control::CConfgManager::getInstance()->getDept();
    QStringList nSubmitList=Control::CConfgManager::getInstance()->getSubmit();
    QStringList nTestList=Control::CConfgManager::getInstance()->getTest();
    QStringList nReviewList=Control::CConfgManager::getInstance()->getReview();
    qDebug()<<"nReviewList"<<nReviewList;

    ui->mCom_Doctor->addItems(nReviewList);
    ui->mCom_SubmittedBy->addItems(nSubmitList);
    ui->mCom_TestedBy->addItems(nTestList);
    ui->mCom_SubmittedDept->addItems(nDeptList);
    ui->mTable_Add_Dept->setRowCount(nDeptList.size());
    ui->mTable_Add_Submit->setRowCount(nSubmitList.size());
    ui->mTable_Add_Test->setRowCount(nTestList.size());
    ui->mTable_Add_Review->setRowCount(nReviewList.size());
    for(int i=0;i<nDeptList.size();i++)//科室
    {
        ui->mTable_Add_Dept->setItem(i,0,new QTableWidgetItem(nDeptList.at(i)));
        if(ui->mTable_Add_Dept->item(i,0)!=0)
        {
            ui->mTable_Add_Dept->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
    for(int i=0;i<nSubmitList.size();i++)//送检医生
    {
        ui->mTable_Add_Submit->setItem(i,0,new QTableWidgetItem(nSubmitList.at(i)));
        if(ui->mTable_Add_Submit->item(i,0)!=0)
        {
            ui->mTable_Add_Submit->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
    for(int i=0;i<nTestList.size();i++)//检测医生
    {
        ui->mTable_Add_Test->setItem(i,0,new QTableWidgetItem(nTestList.at(i)));
        if(ui->mTable_Add_Test->item(i,0)!=0)
        {
            ui->mTable_Add_Test->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
    for(int i=0;i<nReviewList.size();i++)//检测医生
    {
        ui->mTable_Add_Review->setItem(i,0,new QTableWidgetItem(nReviewList.at(i)));
        if(ui->mTable_Add_Review->item(i,0)!=0)
        {
            ui->mTable_Add_Review->item(i,0)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        }
    }
}

void CTestWidget::on_mBtn_Info_Retun_clicked()
{
    ui->Diag_mStacked->setCurrentIndex(0);
}

void CTestWidget::on_mBtn_Info_Edit_clicked()
{
    ui->Diag_mStacked->setCurrentIndex(1);
}

void CTestWidget::on_mBtn_Diag_Clear_clicked()
{
    ui->mEdit_SampleID->clear();
    ui->mEdit_PatientsNum->clear();
    ui->mEdit_Name->clear();
    ui->mEdit_Age->clear();
    ui->mEdit_BedNum->clear();
    ui->mEdit_CaseNum->clear();
    ui->mEdit_Phone->clear();
    ui->mEdit_Note->clear();
}

void CTestWidget::on_mBtn_Dept_add_clicked()
{
    int iRow_add=ui->mTable_Add_Dept->rowCount();
    ui->mTable_Add_Dept->setRowCount(iRow_add+1);
}

void CTestWidget::on_mBtn_Dept_delete_clicked()
{
    int iRow_delete = ui->mTable_Add_Dept->currentRow();
    ui->mTable_Add_Dept->removeRow(iRow_delete);
}

void CTestWidget::on_mBtn_Review_add_clicked()
{
    int iRow_add=ui->mTable_Add_Review->rowCount();
    ui->mTable_Add_Review->setRowCount(iRow_add+1);
}

void CTestWidget::on_mBtn_Review_delete_clicked()
{
    int iRow_delete = ui->mTable_Add_Review->currentRow();
    ui->mTable_Add_Review->removeRow(iRow_delete);
}

void CTestWidget::on_mBtn_Test_add_clicked()
{
    int iRow_add=ui->mTable_Add_Test->rowCount();
    ui->mTable_Add_Test->setRowCount(iRow_add+1);
}

void CTestWidget::on_mBtn_Test_delete_clicked()
{
    int iRow_delete = ui->mTable_Add_Test->currentRow();
    ui->mTable_Add_Test->removeRow(iRow_delete);
}

void CTestWidget::on_mBtn_Submit_add_clicked()
{
    int iRow_add=ui->mTable_Add_Submit->rowCount();
    ui->mTable_Add_Submit->setRowCount(iRow_add+1);
}

void CTestWidget::on_mBtn_Submit_delete_clicked()
{
    int iRow_delete = ui->mTable_Add_Submit->currentRow();
    ui->mTable_Add_Submit->removeRow(iRow_delete);
}

void CTestWidget::on_mBtn_Edit_Save_clicked()
{
    //检验员
    QString nRow_str_Test;
    //送检员
    QString nRow_str_Submit;
    //科室
    QString nRow_str_Dept;
    //医生
    QString nRow_str_Review;
    for(int i=0;i<ui->mTable_Add_Test->rowCount();i++)
    {
        if(ui->mTable_Add_Test->item(i,0)!=0)
        {
            if(!ui->mTable_Add_Test->item(i,0)->text().isEmpty())
            {
                nRow_str_Test+=ui->mTable_Add_Test->item(i,0)->text();
                nRow_str_Test+="|";
            }
        }
    }
    for(int i=0;i<ui->mTable_Add_Submit->rowCount();i++)
    {
        if(ui->mTable_Add_Submit->item(i,0)!=0)
        {
            if(!ui->mTable_Add_Submit->item(i,0)->text().isEmpty())
            {
                nRow_str_Submit+=ui->mTable_Add_Submit->item(i,0)->text();
                nRow_str_Submit+="|";
            }
        }
    }
    for(int i=0;i<ui->mTable_Add_Dept->rowCount();i++)
    {
        if(ui->mTable_Add_Dept->item(i,0)!=0)
        {
            if(!ui->mTable_Add_Dept->item(i,0)->text().isEmpty())
            {
                nRow_str_Dept+=ui->mTable_Add_Dept->item(i,0)->text();
                nRow_str_Dept+="|";
            }
        }
    }for(int i=0;i<ui->mTable_Add_Review->rowCount();i++)
    {
        if(ui->mTable_Add_Review->item(i,0)!=0)
        {
            if(!ui->mTable_Add_Review->item(i,0)->text().isEmpty())
            {
                nRow_str_Review+=ui->mTable_Add_Review->item(i,0)->text();
                nRow_str_Review+="|";
            }
        }
    }
    nRow_str_Test.chop(1);
    nRow_str_Submit.chop(1);
    nRow_str_Dept.chop(1);
    nRow_str_Review.chop(1);
    Control::CConfgManager::getInstance()->setTest(nRow_str_Test);
    Control::CConfgManager::getInstance()->setSubmit(nRow_str_Submit);
    Control::CConfgManager::getInstance()->setDept(nRow_str_Dept);
    Control::CConfgManager::getInstance()->setReview(nRow_str_Review);
    init_Operator_table();
    on_mBtn_Edit_Retun_clicked();
}

void CTestWidget::on_mBtn_Diag_Save_clicked()
{
    if(ui->mEdit_SampleID->text().isEmpty())
    {
//        CUIMsgRouter::getInstances()->set_blur(40);
        CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,false);
        msgdlog->ui->mLabel_text1->setText(tr("样本ID为空,请检查输入框"));
        msgdlog->ui->mLabel_text2->setText(tr("提示"));
        msgdlog->ui->mBtn_OK->setText(tr("确定"));
        msgdlog->exec();
        delete msgdlog;
    }
    else
    {
        QString ctime = Comom::CGlobal::getInstance()->getTools()->get_current_StrTime();
        QString idStr=ui->mEdit_SampleID->text();
        st_Patient PatientInfo;
        //测试流水号
        PatientInfo.csNum=0;//bug
        //样本ID
        PatientInfo.SampleID=idStr;
        //姓名
        PatientInfo.Name=ui->mEdit_Name->text();
        //患者编码
        PatientInfo.PatientsNum=ui->mEdit_PatientsNum->text();
        //床号
        PatientInfo.BedNum=ui->mEdit_BedNum->text();
        //病例号
        PatientInfo.CaseNum=ui->mEdit_CaseNum->text();
        //电话
        PatientInfo.Phone=ui->mEdit_Phone->text();
        //备注
        PatientInfo.Note=ui->mEdit_Note->text();
        //年龄
        PatientInfo.Age=ui->mEdit_Age->text().toInt();
        //年龄类型
        PatientInfo.AgeType=ui->mCom_Age->currentIndex();
        //性别
        PatientInfo.Sex=ui->mCom_Sex->currentIndex();
        //样本类型
        PatientInfo.SampleType=ui->mCom_SampleType->currentIndex();
        //样本状态
        PatientInfo.SampleState=ui->mCom_SampleState->currentIndex();
        //送检医生
        PatientInfo.SubmittedBy=ui->mCom_SubmittedBy->currentText();
        //开单医生
        PatientInfo.BilledBy=ui->mCom_Doctor->currentText();
        //检验医生
        PatientInfo.TestedBy=ui->mCom_TestedBy->currentText();
        //送检科室
        PatientInfo.SubmittedDept=ui->mCom_SubmittedDept->currentText();
        //送检时间
        PatientInfo.Submitted=ctime;
        Control::CTestManager::getInstances()->setPatient1(PatientInfo);

        Control::CTestManager::getInstances()->setPatient1(PatientInfo);
        Control::CModBusManager::getInstance()->WriteData(DEF_R1R2TIME,60);
        Control::CModBusManager::getInstance()->WriteData(DEF_R2R3TIME,60);
        Control::CModBusManager::getInstance()->WriteData(DEF_PTIMEAT1,300);
        Control::CModBusManager::getInstance()->WriteData(DEF_PTIMEAT2,300);
        Control::CModBusManager::getInstance()->WriteData(DEF_PTIMEAT3,300);
        Control::CModBusManager::getInstance()->WriteData(DEF_PTIMEAT4,300);
        Control::CModBusManager::getInstance()->WriteData(DEF_PTIMEAT5,300);
        ui->Diag_mStacked->setCurrentIndex(0);
        ui->mBtn_Open->setEnabled(true);

    }
}



void CTestWidget::on_mBtn_Open_clicked()
{
    if(Control::CModBusManager::getInstance()->WriteBit(DEF_PREACTION,1)){
        qDebug()<<"preaction success";
        CGLOBAL->getTools()->setdelaymTime(500);
        m_Cmd=enum_Test_PreAction;
    }
}

void CTestWidget::slt_ReadModbusinfo(QStringList nstate)
{
    QStringList m_Mstate = nstate;
    QString n_state = m_Mstate.at(0);
    QString n_wasteLq = m_Mstate.at(14);
    QString n_flushLq = m_Mstate.at(15);
//    qDebug()<<"state:"<<nstate<<m_Cmd;
    if(m_Mstate.size()>0&&n_state=="0"){
        QString temp_in = m_Mstate.at(10);
        temp_in = QString::number(temp_in.toDouble()/10,'f',1);
        QString temp_out = m_Mstate.at(11);
        temp_out = QString::number(temp_out.toDouble()/10,'f',1);
        ui->mLab_Temp->setText(tr("托盘温度:")+temp_out+tr("℃  翻盖温度:")+temp_in+tr("℃"));
    }
    if(n_state=="65535"){
        CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,true);
        msgdlog->ui->mLabel_text1->setText(tr("设备异常\n请进入维护界面进行设备重置和初始化"));
        msgdlog->ui->mLabel_text2->setText(tr("提示"));
        msgdlog->ui->mBtn_OK->setText(tr("确认"));
        msgdlog->ui->mBtn_Cancel->setText(tr("返回"));
    }
    if(n_wasteLq=="1"){
        CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,true);
        msgdlog->ui->mLabel_text1->setText(tr("废液瓶将满\n请进入维护界面进行废液瓶更换"));
        msgdlog->ui->mLabel_text2->setText(tr("提示"));
        msgdlog->ui->mBtn_OK->setText(tr("确认"));
        msgdlog->ui->mBtn_Cancel->setText(tr("返回"));
    }
    if(n_flushLq=="1"){
        CMsgDialog *msgdlog=new CMsgDialog(true,true,false,false,true,true);
        msgdlog->ui->mLabel_text1->setText(tr("缓冲液不足\n请进入维护界面进行缓冲液补充"));
        msgdlog->ui->mLabel_text2->setText(tr("提示"));
        msgdlog->ui->mBtn_OK->setText(tr("确认"));
        msgdlog->ui->mBtn_Cancel->setText(tr("返回"));
    }
    if(m_Cmd == enum_Test_Self&&n_state=="0"){
        qDebug()<<"selfcheck success";
        emit sgn_selfcheck();
        m_Cmd=enum_Test_Null;
    }else if(m_Cmd==enum_Test_PreAction&&n_state=="0"){
        m_Cmd=enum_Test_Null;
        slt_startTest();
    }else if(m_Cmd==enum_Test_Scan&&n_state=="0"){
        m_Cmd=enum_Test_Null;
        slt_editInfo();
    }else if(m_Cmd==enum_Test_DevTest&&n_state=="0"){
        m_Cmd=enum_Test_Null;
        slt_Readresult();
    }


}

void CTestWidget::slt_ReadData(QStringList nstate)
{
    QString BarcodeStr1;
    QString BarcodeStr2;
    QString BarcodeStr3;
    QString debug1;
    for(int i=0;i<10;i++){
        debug1 += nstate.at(i);
        BarcodeStr1 += Comom::CGlobal::getInstance()->getTools()->StrtoHex(nstate.at(i));
        BarcodeStr2 += Comom::CGlobal::getInstance()->getTools()->StrtoHex(nstate.at(i+10));
        BarcodeStr3 += Comom::CGlobal::getInstance()->getTools()->StrtoHex(nstate.at(i+20));
    }
    qDebug()<<debug1<<"end";
    QStringList m_scan1 = BarcodeStr1.split("030d");
    BarcodeStr1 = m_scan1.at(0);
    BarcodeStr1 = BarcodeStr1.mid(2,BarcodeStr1.length()-2);
    QString nNowBatch = Control::ChlcpeakManager::getInstance()->BarcodeToBatch(Comom::CGlobal::getInstance()->getTools()->HexStrToByteArray(BarcodeStr1).data());
    qDebug()<<nNowBatch<<"ss";
    ui->Diag_mStacked->setCurrentIndex(1);
    ui->tabWidget_patient->setTabText(0,nNowBatch);


}

void CTestWidget::slt_ShowData(QStringList nstate)
{
    QStringList d_result;
    for(int i=0;i<5;i++){
        QString info = QString::number(Control::CTestManager::getInstances()->get_value(nstate.at(i*10+0),nstate.at(i*10+1))) +
                            QString::number(Control::CTestManager::getInstances()->get_value(nstate.at(i*10+2),nstate.at(i*10+3))) +
                            QString::number(Control::CTestManager::getInstances()->get_value(nstate.at(i*10+4),nstate.at(i*10+5))) +
                            QString::number(Control::CTestManager::getInstances()->get_value(nstate.at(i*10+6),nstate.at(i*10+7))) +
                            QString::number(Control::CTestManager::getInstances()->get_value(nstate.at(i*10+8),nstate.at(i*10+9)));
        d_result<<info;
    }
    qDebug()<<"result:"<<d_result;

    ui->mTable_Result->setItem(0,1,new QTableWidgetItem(d_result.at(0)));
    ui->mTable_Result->setItem(0,2,new QTableWidgetItem(d_result.at(1)));
    ui->mTable_Result->setItem(0,3,new QTableWidgetItem(d_result.at(2)));
    ui->mTable_Result->setItem(0,4,new QTableWidgetItem(d_result.at(3)));
    ui->mTable_Result->setItem(0,5,new QTableWidgetItem(d_result.at(4)));

}

void CTestWidget::p_table_reflash()
{

}
