#include "cprintmanager.h"
namespace Control
{
    CPrintManager::CPrintManager(QObject *parent): QObject(parent)
    {

    }



    void CPrintManager::comstatus(int status)
    {
        int i=0;
        i++;
        //串口i连接状态
        if(!status)
        {
            //打开失败
        }
    }

    bool CPrintManager::Init(int port,int rate)
    {
        m_printmodule.init();
        m_printmodule.setprintOrHis(true);
        m_printmodule.setcb((this));
        m_printmodule.open(port,rate);
        return true;
    }

    /*
     * 发送患者打印信息
     * 参数1：患者信息
     * 参数2：是否合并打印
     */
    bool CPrintManager::setPrintData(QQueue<st_TestInfo> testInfo,bool mergeFlag)
    {
        bool printFlag=false;
        //合并打印
        if(mergeFlag)
        {
            //打印机状态非自动打印热敏0，外置2-A4，4-A5 //自动打印热敏1，外置3-A4，5-A5
            switch (Comom::CGlobal::getInstance()->getConfigData().m_PrintType)
            {
                case 0:
                {
                    QQueue<ISession *> *ssqueue=new QQueue<ISession *>;
                    PSession *sess=new PSession();
                    QString LineStr="\n\n\n";
                    QByteArray SetByt=Printer_merge_In_Str(testInfo).toLocal8Bit();
                    SetByt.append(LineStr.toLocal8Bit());
                    sess->setdata(SetByt);
                    ssqueue->enqueue(sess);
                    printFlag= m_printmodule.sends(ssqueue);
                }
                    break;
                case 1:
                {
                    QQueue<ISession *> *ssqueue=new QQueue<ISession *>;
                    PSession *sess=new PSession();
                    QString LineStr="\n\n\n";
                    QByteArray SetByt=Printer_merge_In_Str(testInfo).toLocal8Bit();
                    SetByt.append(LineStr.toLocal8Bit());
                    sess->setdata(SetByt);
                    ssqueue->enqueue(sess);
                    printFlag= m_printmodule.sends(ssqueue);
                }
                    break;
                /*
                case 2:
                {
                    while (m_mergeFlag)
                    {
                        QPrinter printer;
                        printer.setOrientation(QPrinter::Portrait);
                        printer.setPageSize(QPrinter::A4);
                        printer.setResolution(150);//设置像素
                        QTextDocument textDocument;
                        textDocument.setHtml(Printer_merge_A4(stTest));
                        textDocument.setPageSize(printer.pageRect().size());
                        textDocument.print(&printer);
                        textDocument.clear();
                    }
                    m_mergeFlag=true;
                    printFlag= 1;
                }
                    break;
                case 3:
                {
                    while (m_mergeFlag)
                    {
                        QPrinter printer;
                        printer.setOrientation(QPrinter::Portrait);
                        printer.setPageSize(QPrinter::A4);
                        printer.setResolution(150);//设置像素
                        QTextDocument textDocument;
                        textDocument.setHtml(Printer_merge_A4(stTest));
                        textDocument.setPageSize(printer.pageRect().size());
                        textDocument.print(&printer);
                        textDocument.clear();
                    }
                    m_mergeFlag=true;
                    printFlag= 1;
                }
                    break;
                case 4:
                {
                    while (m_mergeFlag)
                    {
                    QPrinter printer;
                    printer.setOrientation(QPrinter::Landscape);
                    printer.setPageSize(QPrinter::A5);
                    printer.setResolution(150);//设置像素
                    QTextDocument textDocument;
                    textDocument.setHtml(Printer_merge_A5(stTest));
                    textDocument.setPageSize(printer.pageRect().size());
                    textDocument.print(&printer);
                    textDocument.clear();
                    }
                    m_mergeFlag=true;
                    printFlag= 1;
                }
                    break;
                case 5:
                {
                    while (m_mergeFlag)
                    {
                    qDebug()<<"A5";
                    QPrinter printer;
                    printer.setOrientation(QPrinter::Landscape);
                    printer.setPageSize(QPrinter::A5);
                    printer.setResolution(150);//设置像素
                    QTextDocument textDocument;
                    textDocument.setHtml(Printer_merge_A5(stTest));
                    textDocument.setPageSize(printer.pageRect().size());
                    textDocument.print(&printer);
                    textDocument.clear();
                    }
                    m_mergeFlag=true;
                    printFlag= 1;
                }
                    break;
                default:
                    return 1;
                    break;
                    */
            }
        }
        else
        {
            while(testInfo.size())
            {
                st_TestInfo stTest=testInfo.dequeue();//打印数据结构体


                //判断打印纸张
                //打印机状态非自动打印热敏0，外置2-A4，4-A5 //自动打印热敏1，外置3-A4，5-A5
                switch (Comom::CGlobal::getInstance()->getConfigData().m_PrintType)
                {
                    case 0:
                    case 1:
                    {
                        QQueue<ISession *> *ssqueue=new QQueue<ISession *>;
                        PSession *sess=new PSession();
                        QString LineStr="\n\n\n";
                        QByteArray SetByt=Printer_In_Str(stTest).toLocal8Bit();
                        //SetByt.append(ImageToStrHex(DataToImage(setTest.CurveData.dequeue()).scaled(384,384,Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
                        SetByt.append(LineStr.toLocal8Bit());
                        sess->setdata(SetByt);
                        ssqueue->enqueue(sess);
                        printFlag= m_printmodule.sends(ssqueue);
                    }
                        break;
                   /*
                    case 2:
                    case 3:
                    {
                        QPrinter printer;
                        printer.setOrientation(QPrinter::Portrait);
                        printer.setPageSize(QPrinter::A4);
                        printer.setResolution(150);//设置像素
                        QTextDocument textDocument;
                        textDocument.setHtml(Printer_A4(stTest));
                        textDocument.setPageSize(printer.pageRect().size());
                        textDocument.print(&printer);
                        textDocument.clear();
                        printFlag= 1;
                    }
                        break;
                    case 4:
                    case 5:
                    {
                        QPrinter printer;
                        printer.setOrientation(QPrinter::Landscape);
                        printer.setPageSize(QPrinter::A5);
                        printer.setResolution(150);//设置像素
                        QTextDocument textDocument;
                        textDocument.setHtml(Printer_A5(stTest));
                        textDocument.setPageSize(printer.pageRect().size());
                        textDocument.print(&printer);
                        textDocument.clear();
                        printFlag= 1;
                    }
                        break;
                    default:
                        return 1;
                        break;
                        */
                }
            }
        }
        return printFlag;
    }

    QString CPrintManager::Printer_In_Str(st_TestInfo testInfo)//数据转热敏打印信息
    {
        QString headStr=Comom::CGlobal::getInstance()->getPrintData().report_Head;
        int number=0;
        int nCount = headStr.count();
        for(int i = 0; i < nCount; i++)
        {
            QChar schar = headStr.at(i);
            ushort uNum =schar.unicode();
            if(uNum >= 0x4E00 && uNum <= 0x9FA5)
            {
                number=number+2;
            }
            else
            {
                number++;
            }
        }
        QString m_Re_str;
        m_Re_str+="\n";
        if(number<28)
        {
            m_Re_str+=getDataToInfo(headStr,29);
        }
        else
        {
            m_Re_str+=getDataToInfo(tr("检验报告单"),29);
        }
        m_Re_str+="\n"+tr("序号")+":"+QString::number(testInfo.Num);
        m_Re_str+="\n"+tr("姓名")+":"+testInfo.Name ;
        switch (testInfo.Sex) {
        case 0:
            m_Re_str+="\n"+tr("性别:男");
            break;
        case 1:
            m_Re_str+="\n"+tr("性别:女");
            break;
        case 2:
            m_Re_str+="\n"+tr("性别:其他");
            break;
        default:
            m_Re_str+="\n"+tr("性别:");
            break;
        }
        QString ageStr="";
        if(testInfo.Age>0)
        {
            ageStr=QString::number(testInfo.Age);
        }
        m_Re_str+="\n"+tr("年龄")+":"+ageStr;
        switch (testInfo.AgeType) {
        case 0:
            m_Re_str+=tr("岁");
            break;
        case 1:
            m_Re_str+=tr("月");
            break;
        case 2:
            m_Re_str+=tr("周");
            break;
        case 3:
            m_Re_str+=tr("日");
            break;
        case 4:
            m_Re_str+=tr("小时");
            break;
        default:
            break;
        }
        m_Re_str+="\n"+tr("样本ID")+":"+testInfo.SampleID;

        if(Comom::CGlobal::getInstance()->getPrintData().report_Type)//样本类型
        {
            m_Re_str+="\n"+tr("样本类型:");
            switch (testInfo.SampleType) //样本类型
            {
            case 0:
                m_Re_str +=tr("其他");//样本类型
                break;
            case 1:
                m_Re_str +=tr("全血");//样本类型
                break;
            case 2:
                m_Re_str +=tr("血清");//样本类型
                break;
            case 3:
                m_Re_str +=tr("血浆");//样本类型
                break;
            case 4:
                m_Re_str +=tr("尿液");//样本类型
                break;
            default:
                m_Re_str +=tr("其他");//样本类型
                break;
            }
        }
        if(Comom::CGlobal::getInstance()->getPrintData().report_State)//样本状态
        {
            m_Re_str+="\n"+tr("样本状态:");
            switch (testInfo.SampleState)
            {
            case 0:
                m_Re_str+=tr("正常");
                break;
            case 1:
                m_Re_str+=tr("溶血");
                break;
            case 2:
                m_Re_str+=tr("黄疸");
                break;
            case 3:
                m_Re_str+=tr("脂血");
                break;
            case 4:
                m_Re_str+=tr("其他");
                break;
            default:
                m_Re_str+=tr("正常");
                break;
            }
        }
        if(Comom::CGlobal::getInstance()->getPrintData().report_Reserve1)//床号
        {
            Comom::CGlobal::getInstance()->getPrintData().report_reserve1Str+":"+testInfo.BedNum;
        }
        if(Comom::CGlobal::getInstance()->getPrintData().report_Reserve2)//电话
        {
            Comom::CGlobal::getInstance()->getPrintData().report_reserve2Str+":"+testInfo.Phone;
        }
        if(Comom::CGlobal::getInstance()->getPrintData().report_Doctor)//申请医生
        {
            m_Re_str+="\n"+tr("医生")+":"+testInfo.ReviewedBy;
        }
        if(Comom::CGlobal::getInstance()->getPrintData().report_SubmitBy)//送检
        {
            m_Re_str+="\n"+tr("送检医生")+":"+testInfo.SubmittedBy ;
        }
        if(Comom::CGlobal::getInstance()->getPrintData().report_TextBy)//检验
        {
            m_Re_str+="\n"+tr("检验医生")+":"+testInfo.TestedBy ;
        }
        if(Comom::CGlobal::getInstance()->getPrintData().report_Dept)//科室
        {
            m_Re_str+="\n"+tr("科室")+":"+testInfo.SubmittedDept;
        }
        if(Comom::CGlobal::getInstance()->getPrintData().report_TSample)//采血
        {
            m_Re_str+="\n"+tr("采血时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_TimeStr(testInfo.Submitted-58);
        }
        if(Comom::CGlobal::getInstance()->getPrintData().report_TSubmit)//送检
        {
            m_Re_str+="\n"+tr("送检时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_TimeStr(testInfo.Submitted);
        }
        if(Comom::CGlobal::getInstance()->getPrintData().report_TText)//检验
        {
            m_Re_str+="\n"+tr("检测时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_TimeStr(testInfo.Tested);
        }
        if(Comom::CGlobal::getInstance()->getPrintData().report_TReport)//报告时间
        {
            m_Re_str+="\n"+tr("报告时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_TimeStr(testInfo.Reported);
        }
        m_Re_str+="\n"+tr("打印时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_current_StrTime();
        m_Re_str+="\n-----------------------------";
        m_Re_str+="\n";
        m_Re_str+=getDataToInfo(tr("项目"),10);
        m_Re_str+="|";
        m_Re_str+=getDataToInfo(tr("结果"),10);
        m_Re_str+="|";
        m_Re_str+=getDataToInfo(tr("单位"),7);
        m_Re_str+="\n";


        QQueue<st_TestResult> referList;
        while (testInfo.resultList.size()) {
            st_TestResult resultInfo= testInfo.resultList.dequeue();
            referList<<resultInfo;
            m_Re_str+="\n";
            m_Re_str+=getDataToInfo(resultInfo.Project,10);
            m_Re_str+=getDataToInfo(resultInfo.Result+resultInfo.Hint,12);
            m_Re_str+=getDataToInfo(resultInfo.Unit,7);
        }
        m_Re_str+="\n-----------------------------\n";
        if(Comom::CGlobal::getInstance()->getPrintData().report_Range)//参考范围
        {
            m_Re_str+=getDataToInfo(tr("参考范围"),29);
            m_Re_str+="\n-----------------------------";
            m_Re_str+="\n"+getDataToInfo(tr("项目"),10);
            m_Re_str+="|";
            m_Re_str+=getDataToInfo(tr("参考范围"),10);
            m_Re_str+="|";
            m_Re_str+=getDataToInfo(tr("单位"),7);
            QStringList  projectList;
            while (referList.size())
            {
                st_TestResult referInfo=referList.dequeue();
                if(!projectList.contains(referInfo.Project))
                {
                    m_Re_str+="\n";
                    m_Re_str+=getDataToInfo(referInfo.Project,10);
                    m_Re_str+=getDataToInfo(referInfo.Refer,12);
                    m_Re_str+=getDataToInfo(referInfo.Unit,7);
                    projectList<<referInfo.Project;
                }

            }
            m_Re_str+="\n-----------------------------";

        }
        m_Re_str+="\r\n*"+tr("声明:结果仅供临床参考")+"*\r\n\r\n\r\n";
        qDebug()<<"m_Re_str"<<m_Re_str;
        return m_Re_str;
    }

    QString CPrintManager::Printer_merge_In_Str(QQueue<st_TestInfo> testList)
    {
        bool infoFlag=true;
        QString m_Re_str;
        QQueue<st_TestResult> referList;
        while (testList.size())
        {
            st_TestInfo testInfo=testList.dequeue();
            if(infoFlag)
            {
                infoFlag=false;
                QString headStr=Comom::CGlobal::getInstance()->getPrintData().report_Head;
                int headLength=0;
                int nCount = headStr.count();
                //判断表头长度
                for(int i = 0; i < nCount; i++)
                {
                    QChar schar = headStr.at(i);
                    ushort uNum =schar.unicode();
                    if(uNum >= 0x4E00 && uNum <= 0x9FA5)
                    {
                        headLength=headLength+2;
                    }
                    else
                    {
                        headLength++;
                    }
                }

                m_Re_str+="\n";
                if(headLength<28)
                {
                    m_Re_str+=getDataToInfo(headStr,29);
                }
                else
                {
                    m_Re_str+=getDataToInfo(tr("检验报告单"),29);
                }
                m_Re_str+="\n"+tr("序号")+":"+QString::number(testInfo.Num);
                m_Re_str+="\n"+tr("姓名")+":"+testInfo.Name;
                switch (testInfo.Sex) {
                case 0:
                    m_Re_str+="\n"+tr("性别:男");
                    break;
                case 1:
                    m_Re_str+="\n"+tr("性别:女");
                    break;
                case 2:
                    m_Re_str+="\n"+tr("性别:其他");
                    break;
                default:
                    m_Re_str+="\n"+tr("性别:");
                    break;
                }

                QString ageStr="";
                if(testInfo.Age)
                {
                    ageStr=QString::number(testInfo.Age);
                }
                m_Re_str+="\n"+tr("年龄")+":"+ageStr;
                switch (testInfo.AgeType) {
                case 0:
                    m_Re_str+=tr("岁");
                    break;
                case 1:
                    m_Re_str+=tr("月");
                    break;
                case 2:
                    m_Re_str+=tr("周");
                    break;
                case 3:
                    m_Re_str+=tr("日");
                    break;
                case 4:
                    m_Re_str+=tr("小时");
                    break;
                default:
                    break;
                }
                m_Re_str+="\n"+tr("样本ID")+":"+testInfo.SampleID;
                m_Re_str+="\n"+tr("打印时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_current_StrTime();
                m_Re_str+="\n-----------------------------";
                m_Re_str+="\n";
                m_Re_str+=getDataToInfo(tr("项目"),10);
                m_Re_str+="|";
                m_Re_str+=getDataToInfo(tr("结果"),10);
                m_Re_str+="|";
                m_Re_str+=getDataToInfo(tr("单位"),7);
            }


            while (testInfo.resultList.size()) {
                st_TestResult resultInfo= testInfo.resultList.dequeue();
                referList<<resultInfo;
                m_Re_str+="\n";
                m_Re_str+=getDataToInfo(resultInfo.Project,10);
                m_Re_str+=getDataToInfo(resultInfo.Result+resultInfo.Hint,12);
                m_Re_str+=getDataToInfo(resultInfo.Unit,7);
            }
        }

        m_Re_str+="\n-----------------------------\n";
        if(Comom::CGlobal::getInstance()->getPrintData().report_Range)//参考范围
        {
            m_Re_str+=getDataToInfo(tr("参考范围"),29);
            m_Re_str+="\n-----------------------------";
            m_Re_str+="\n"+getDataToInfo(tr("项目"),10);
            m_Re_str+="|";
            m_Re_str+=getDataToInfo(tr("参考范围"),10);
            m_Re_str+="|";
            m_Re_str+=getDataToInfo(tr("单位"),7);
            QStringList  projectList;
            while (referList.size())
            {
                st_TestResult referInfo=referList.dequeue();
                if(!projectList.contains(referInfo.Project))
                {
                    m_Re_str+="\n";
                    m_Re_str+=getDataToInfo(referInfo.Project,10);
                    m_Re_str+=getDataToInfo(referInfo.Refer,12);
                    m_Re_str+=getDataToInfo(referInfo.Unit,7);
                    projectList<<referInfo.Project;
                }

            }
            m_Re_str+="\n-----------------------------";

        }
        m_Re_str+="\r\n*"+tr("声明:结果仅供临床参考")+"*\r\n\r\n\r\n";
        qDebug()<<"m_Re_str"<<m_Re_str;
        return m_Re_str;
    }





    /*
    QString CPrintManager::Printer_A4(st_Test nTest)
    {

        int head_line=0;
        int end_line=0;
        QString n_sHtml;

        st_Test printTest;
        //流水号
        printTest.Num<<nTest.Num.dequeue();
        //样本ID
        printTest.SampleID<<nTest.SampleID.dequeue();
        //原始值
        printTest.OriginalValue<<nTest.OriginalValue.dequeue();
        //校正值
        printTest.Result<<nTest.Result.dequeue();
        //姓名
        printTest.Name<<nTest.Name.dequeue();
        //性别
        printTest.Sex<<nTest.Sex.dequeue();
        //样本类型
        printTest.SampleType<<nTest.SampleType.dequeue();
        //样本状态
        printTest.SampleState<<nTest.SampleState.dequeue();
        //年龄
        printTest.Age<<nTest.Age.dequeue();
        //年龄
        printTest.AgeType<<nTest.AgeType.dequeue();
        //送检科室
        printTest.SubmittedDept<<nTest.SubmittedDept.dequeue();
        //送检医生
        printTest.SubmittedBy<<nTest.SubmittedBy.dequeue();
        //审核医生
        printTest.ReviewedBy<<nTest.ReviewedBy.dequeue();
        //检验医生
        printTest.TestedBy<<nTest.TestedBy.dequeue();
        //送检日期
        printTest.Submitted<<nTest.Submitted.dequeue();
        //检验日期
        printTest.Tested<<nTest.Tested.dequeue();
        //报告日期
        printTest.Reported<<nTest.Reported.dequeue();
        //参考范围
        printTest.Refer<<nTest.Refer.dequeue();
        //单位
        printTest.Unit<<nTest.Unit.dequeue();
        //项目
        printTest.Project<<nTest.Project.dequeue();
        //床号
        printTest.BedNum<<nTest.BedNum.dequeue();
        //电话
        printTest.Phone<<nTest.Phone.dequeue();
        //备注
        printTest.Note<<nTest.Note.dequeue();
        //病例号
        printTest.CaseNum<<nTest.CaseNum.dequeue();
        //患者编码
        printTest.PatientsNum<<nTest.PatientsNum.dequeue();
        //提示
        printTest.Hint<<nTest.Hint.dequeue();
        //性别
        QString sexStr;
        switch (printTest.Sex.head())
        {
        case 0:
            sexStr +=tr("男");
            break;
        case 1:
            sexStr +=tr("女");
            break;
        case 2:
            sexStr +=tr("其他");
            break;
        default:
            break;
        }

        QString ageStr="";//年龄
        if(printTest.Age.head()>0)
        {
            ageStr=QString::number(printTest.Age.head());
        }
        switch (printTest.AgeType.head())//年龄类型
        {
        case 0:
            ageStr +=tr("岁");
            break;
        case 1:
            ageStr +=tr("月");
            break;
        case 2:
            ageStr +=tr("周");
            break;
        case 3:
            ageStr +=tr("日");
            break;
        case 4:
            ageStr +=tr("小时");
            break;
        default:
            break;
        }
        //样本类型
        QString sampleTypeStr;
        switch (printTest.SampleType.head())
        {
        case 0:
            sampleTypeStr=tr("其他");
            break;
        case 1:
            sampleTypeStr=tr("全血");
            break;
        case 2:
            sampleTypeStr=tr("血清");
            break;
        case 3:
            sampleTypeStr=tr("血浆");
            break;
        case 4:
            sampleTypeStr=tr("尿液");
            break;
        default:
            sampleTypeStr=tr("其他");
            break;
        }
        //样本状态
        QString sampleStateStr;
        switch (printTest.SampleState.head())
        {
        case 0:
            sampleStateStr=tr("正常");
            break;
        case 1:
            sampleStateStr=tr("溶血");
            break;
        case 2:
            sampleStateStr=tr("黄疸");
            break;
        case 3:
            sampleStateStr=tr("脂血");
            break;
        case 4:
            sampleStateStr=tr("其他");
            break;
        default:
            sampleStateStr=tr("正常");
            break;
        }

        {
            //height=\"50\"1754×1240分辨率
             n_sHtml +=
             "<table align=\"center\" width=\"1040\" border=\"0\" cellspacing=\"2\" cellpadding=\"1\"  style=\"width: 100%; height: 100%;\">"
             "<tr>"
             "</tr>"
             "<tr>"
             "<td colspan=\"4\" style=\"font-size:30px;text-align:center\">"+
                     Comom::CGlobal::getInstance()->getPrintData().report_Head+//表头
             "</td>"
             "</tr>"
             "<tr>"
             "</tr>"
             "<tr>"
             "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
             tr("姓名")+":"+printTest.Name.head()+
             "</td>"
             "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
             tr("性别")+":"+sexStr+
             "</td>"
             "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
             tr("年龄")+":"+ageStr+
             "</td>";

             if(Comom::CGlobal::getInstance()->getPrintData().report_Type)//样本类型:
             {
                 n_sHtml += "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                         tr("样本类型")+":"+sampleTypeStr+
                         "</td>";
                 head_line=4;
             }
             else
             {
                 head_line=3;
             }
             if(head_line==4)
             {
                 head_line=0;
                 n_sHtml +="</tr>""<tr>";
                 head_line++;
                 n_sHtml += "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                         tr("ID号")+":"+printTest.SampleID.head()+
                         "</td>";
             }
             else
             {
                 head_line++;
                 n_sHtml += "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                         tr("ID号")+":"+printTest.SampleID.head()+
                         "</td>";
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_Dept)//科室
             {
                 if(head_line==4)
                 {
                     head_line=0;
                     n_sHtml +="</tr>""<tr>";
                 }
                 head_line++;
                 n_sHtml += "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                         tr("科室")+":"+printTest.SubmittedDept.head()+
                         "</td>";
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_Doctor)//申请医生
             {
                 if(head_line==4)
                 {
                     head_line=0;
                     n_sHtml +="</tr>""<tr>";
                 }
                 head_line++;
                 n_sHtml += "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                         tr("医生")+":"+printTest.ReviewedBy.head()+
                         "</td>";
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_State)//样本状态:
             {
                 if(head_line==4)
                 {
                     head_line=0;
                     n_sHtml +="</tr>""<tr>";
                 }
                 head_line++;
                 n_sHtml +="<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                         tr("样本状态")+":"+sampleStateStr+
                         "</td>";
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_Reserve1)//床号
             {
                 if(head_line==4)
                 {
                     head_line=0;
                     n_sHtml +="</tr>""<tr>";
                 }
                 head_line++;
                  n_sHtml +="<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                          Comom::CGlobal::getInstance()->getPrintData().report_reserve1Str+":"+printTest.BedNum.head()+
                          "</td>";
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_Reserve2)//电话
             {
                 if(head_line==4)
                 {
                     head_line=0;
                     n_sHtml +="</tr>""<tr>";
                 }
                 head_line++;
                  n_sHtml +="<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                          Comom::CGlobal::getInstance()->getPrintData().report_reserve2Str+":"+printTest.Phone.head()+
                          "</td>";
             }
             if(head_line==4)
             {
                 head_line=0;
                 n_sHtml +="</tr>""<tr>";
             }
             head_line++;
             n_sHtml +="<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                     tr("病例号")+":"+printTest.CaseNum.head()+
                     "</td>";
             if(head_line==4)
             {
                 head_line=0;
                 n_sHtml +="</tr>""<tr>";
             }
             head_line++;
             n_sHtml +="<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                     tr("患者编码")+":"+printTest.PatientsNum.head()+
                     "</td>";
             for(int i=head_line;i<4;i++)
             {
                 n_sHtml +="<td colspan=\"1\" style=\"font-size:20px\"></td>";
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_Reserve3)//提示
             {
                n_sHtml +="</tr>""<tr>";
                n_sHtml +="<td colspan=\"4\" style=\"font-size:20px\">"+
                        Comom::CGlobal::getInstance()->getPrintData().report_reserve3Str+":"+printTest.Note.head()+"</td>";
             }
             n_sHtml +="</tr>""</table>";
             n_sHtml += "<br><hr width=\"95%\" style=\"height:0.5px\">";
             n_sHtml += "<table align=\"center\" width=\"1040\" height=\"1100\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\"  style=\"width: 100%; height: 100%;\">";
             n_sHtml += "<tr>"
                        "<td width=\"230\" style=\"font-size:20px;font-weight:600;text-align:center;\">"+tr("项目名称")+"</td>"
                        "<td width=\"240\" style=\"font-size:20px;font-weight:600;text-align:center;\">"+tr("检验结果")+"</td>"
                        "<td width=\"150\" style=\"font-size:20px;font-weight:600;text-align:center;\">"+tr("结果提示")+"</td>";
             if(Comom::CGlobal::getInstance()->getPrintData().report_Range)//参考范围
             {
                 n_sHtml +="<td width=\"400\" style=\"font-size:20px;font-weight:600;text-align:center;\">"+
                         tr("参考范围")+"</td>";
             }
             else
             {
                 n_sHtml +="<td width=\"400\" style=\"font-size:20px;font-weight:600;text-align:center;\"></td>"  ;
             }
             n_sHtml += "</tr>";
             n_sHtml += "<tr>";
             //项目名称
             n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + printTest.Project.head() + "</td>";
             //检验项目
             if(printTest.Result.head()=="NULL"||printTest.Result.head()=="nan")
             {
                 n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + printTest.Result.head()+ "</td>";
             }
             else
             {
                 n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + printTest.Result.head()+ printTest.Unit.head() + "</td>";
             }
             //结果提示
             n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + printTest.Hint.head()  + "</td>";
             //参考范围
             if(Comom::CGlobal::getInstance()->getPrintData().report_Range)//参考范围
             {
                 n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + printTest.Refer.head()+ printTest.Unit.head() + "</td>";
             }
             else
             {
                 n_sHtml += "<td style=\"font-size:20px;text-align:center;\"> </td>";
             }
             n_sHtml += "</tr>";
             if(Comom::CGlobal::getInstance()->getPrintData().report_Way)//临床意义
             {
                 n_sHtml += "<tr><td colspan=\"5\" style=\"font-size:20px;text-align:left;padding-left:17px;\">"+
                         tr("临床意义")+":"+
                         "</td></tr> ";

                 n_sHtml += "<tr><td colspan=\"5\" style=\"font-size:20px;text-align:left;padding-left:17px;\">"+
                         printTest.Project.head()+":"+Comom::CGlobal::getInstance()->getClinicalStr(printTest.Project.head())
                         +"</td></tr> ";
             }
             n_sHtml +="</table>";
             n_sHtml += "<br><hr width=\"95%\" style=\"height:0.5px\">";

             n_sHtml += "<table align=\"center\" width=\"1020\" border=\"0\" cellspacing=\"1\" cellpadding=\"3\" style=\"width:100% height:100%\">"
                     "<tr>";
             if(Comom::CGlobal::getInstance()->getPrintData().report_TSample)//采血
             {
                n_sHtml +="<td width=\"380\" colspan=\"2\" style=\"font-size:20px;text-align:left;\">"+
                        tr("采血时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_TimeStr(printTest.Submitted.head()-58) +
                        "</td>";
                end_line++;
                end_line++;
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_TSubmit)//送检
             {
                n_sHtml +="<td width=\"380\" colspan=\"2\" style=\"font-size:20px;text-align:left;\">"+
                        tr("送检时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_TimeStr(printTest.Submitted.head())+
                        "</td>";
                end_line++;
                end_line++;
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_TText)//检验
             {
                 n_sHtml +="<td width=\"380\" colspan=\"2\" style=\"font-size:20px;text-align:left;\">"+
                         tr("检验时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_TimeStr(printTest.Tested.head())+
                         "</td>";
                 end_line++;
                 end_line++;
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_TReport)//报告时间
             {
                 if(end_line==6)
                 {
                     end_line=0;
                     n_sHtml +="</tr>";
                     n_sHtml +="<tr>";
                 }
                 end_line++;
                 end_line++;
                 n_sHtml +="<td width=\"380\" colspan=\"2\" style=\"font-size:20px;text-align:left;\">"+
                         tr("报告时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_TimeStr(printTest.Reported.head())+
                         "</td>";

             }
             if(end_line==6)
             {
                 end_line=0;
                 n_sHtml +="</tr>";
                 n_sHtml +="<tr>";
             }
             end_line++;
             end_line++;
             n_sHtml +="<td width=\"380\" colspan=\"2\" style=\"font-size:20px;text-align:left;\">"+
                     tr("打印时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_current_StrTime()+
                     "</td>";
             if(Comom::CGlobal::getInstance()->getPrintData().report_TextBy)//检验医生
             {
                 if(end_line==6)
                 {
                     end_line=0;
                     n_sHtml +="</tr>";
                     n_sHtml +="<tr>";
                 }
                 end_line++;
                 end_line++;
                 n_sHtml += "<td width=\"380\"  colspan=\"2\" style=\"font-size:20px;text-align:left;\">"+
                         tr("检验医生")+":"+printTest.TestedBy.head()+
                         "</td>";
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_SubmitBy)//送检
             {
                 if(end_line==6)
                 {
                     end_line=0;
                     n_sHtml +="</tr>";
                     n_sHtml +="<tr>";
                 }
                 end_line++;
                 end_line++;
                 n_sHtml += "<td width=\"380\" colspan=\"2\" style=\"font-size:20px;text-align:left;\">"+
                         tr("送检医生")+":"+printTest.SubmittedBy.head()+
                         "</td>";
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_ReviewBy)//审核
             {
                 if(end_line==6)
                 {
                     end_line=0;
                     n_sHtml +="</tr>";
                     n_sHtml +="<tr>";
                 }
                 end_line++;
                 end_line++;
                 n_sHtml += "<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\">"+
                         tr("审核医生")+":"+
                         "</td>";
                 switch (Comom::CGlobal::getInstance()->getPrintData().signature_Num) {
                 case 0:
                     n_sHtml += "<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\">";
                     n_sHtml+="<img src='"+QCoreApplication::applicationDirPath()+"/Signature/Signature_1.jpg'"+"width=\"170\" height=\"48\" ></td>";
                     break;
                 case 1:
                     n_sHtml += "<td width=\"170\" colspan=\"1\"style=\"font-size:20px;text-align:left;\">";
                     n_sHtml+="<img src='"+QCoreApplication::applicationDirPath()+"/Signature/Signature_2.jpg'"+"width=\"170\" height=\"48\" ></td>";
                     break;
                 case 2:
                     n_sHtml += "<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\">";
                     n_sHtml+="<img src='"+QCoreApplication::applicationDirPath()+"/Signature/Signature_3.jpg'"+"width=\"170\" height=\"48\" ></td>";
                     break;
                 default:
                     n_sHtml += "<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\"></td>";
                     break;
                 }
             }

             for(int i=end_line;i<6;i++)//补列
             {
                 n_sHtml +="<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\"></td>";
             }
               n_sHtml +="</tr>"
                     "</table><br><br>"
                     "<table align=\"center\" width=\"1000\" border=\"0\" cellspacing=\"5\" cellpadding=\"5\" style=\"width:100% height:100%\">"
                     "<tr>"
                     "<td style=\"font-size:14px;text-align:right;\">*"+
                       tr("本报告仅对所测样本负责，结果仅供临床参考")+
                       "*</td>"
                     "</tr>"
                     "</table>";
            //   n_sHtml +=" <img src="" width="165" height="60" />


        }
       // qDebug()<<"m_sHtml"<<n_sHtml;
        return n_sHtml;

    }

    QString CPrintManager::Printer_A5(st_Test nTest)
    {

        int head_line=0;
        int end_line=0;
        QString n_sHtml;

        st_Test printTest;
        //流水号
        printTest.Num<<nTest.Num.dequeue();
        //样本ID
        printTest.SampleID<<nTest.SampleID.dequeue();
        //原始值
        printTest.OriginalValue<<nTest.OriginalValue.dequeue();
        //校正值
        printTest.Result<<nTest.Result.dequeue();
        //姓名
        printTest.Name<<nTest.Name.dequeue();
        //性别
        printTest.Sex<<nTest.Sex.dequeue();
        //样本类型
        printTest.SampleType<<nTest.SampleType.dequeue();
        //样本状态
        printTest.SampleState<<nTest.SampleState.dequeue();
        //年龄
        printTest.Age<<nTest.Age.dequeue();
        //年龄
        printTest.AgeType<<nTest.AgeType.dequeue();
        //送检科室
        printTest.SubmittedDept<<nTest.SubmittedDept.dequeue();
        //送检医生
        printTest.SubmittedBy<<nTest.SubmittedBy.dequeue();
        //审核医生
        printTest.ReviewedBy<<nTest.ReviewedBy.dequeue();
        //检验医生
        printTest.TestedBy<<nTest.TestedBy.dequeue();
        //送检日期
        printTest.Submitted<<nTest.Submitted.dequeue();
        //检验日期
        printTest.Tested<<nTest.Tested.dequeue();
        //报告日期
        printTest.Reported<<nTest.Reported.dequeue();
        //参考范围
        printTest.Refer<<nTest.Refer.dequeue();
        //单位
        printTest.Unit<<nTest.Unit.dequeue();
        //项目
        printTest.Project<<nTest.Project.dequeue();
        //床号
        printTest.BedNum<<nTest.BedNum.dequeue();
        //电话
        printTest.Phone<<nTest.Phone.dequeue();
        //备注
        printTest.Note<<nTest.Note.dequeue();
        //病例号
        printTest.CaseNum<<nTest.CaseNum.dequeue();
        //患者编码
        printTest.PatientsNum<<nTest.PatientsNum.dequeue();
        //提示
        printTest.Hint<<nTest.Hint.dequeue();
        //性别
        QString sexStr;
        switch (printTest.Sex.head())
        {
        case 0:
            sexStr +=tr("男");
            break;
        case 1:
            sexStr +=tr("女");
            break;
        case 2:
            sexStr +=tr("其他");
            break;
        default:
            break;
        }
        QString ageStr="";//年龄
        if(printTest.Age.head()>0)
        {
            ageStr=QString::number(printTest.Age.head());
        }
        switch (printTest.AgeType.head())//类型
        {
        case 0:
            ageStr +=tr("岁");
            break;
        case 1:
            ageStr +=tr("月");
            break;
        case 2:
            ageStr +=tr("周");
            break;
        case 3:
            ageStr +=tr("日");
            break;
        case 4:
            ageStr +=tr("小时");
            break;
        default:
            break;
        }
        //样本类型
        QString sampleTypeStr;
        switch (printTest.SampleType.head())
        {
        case 0:
            sampleTypeStr=tr("其他");
            break;
        case 1:
            sampleTypeStr=tr("全血");
            break;
        case 2:
            sampleTypeStr=tr("血清");
            break;
        case 3:
            sampleTypeStr=tr("血浆");
            break;
        case 4:
            sampleTypeStr=tr("尿液");
            break;
        default:
            sampleTypeStr=tr("其他");
            break;
        }
        //样本状态
        QString sampleStateStr;
        switch (printTest.SampleState.head())
        {
        case 0:
            sampleStateStr=tr("正常");
            break;
        case 1:
            sampleStateStr=tr("溶血");
            break;
        case 2:
            sampleStateStr=tr("黄疸");
            break;
        case 3:
            sampleStateStr=tr("脂血");
            break;
        case 4:
            sampleStateStr=tr("其他");
            break;
        default:
            sampleStateStr=tr("正常");
            break;
        }

        {
            //height=\"50\"1754×1240分辨率
             n_sHtml +=
             "<table align=\"center\" width=\"1040\" border=\"0\" cellspacing=\"2\" cellpadding=\"1\"  style=\"width: 100%; height: 100%;\">"
             "<tr>"
             "</tr>"
             "<tr>"
             "<td colspan=\"4\" style=\"font-size:30px;text-align:center\">"+
                     Comom::CGlobal::getInstance()->getPrintData().report_Head+//表头
             "</td>"
             "</tr>"
             "<tr>"
             "</tr>"
             "<tr>"
             "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
             tr("姓名")+":"+printTest.Name.head()+
             "</td>"
             "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
             tr("性别")+":"+sexStr+
             "</td>"
             "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
             tr("年龄")+":"+ageStr+
             "</td>";

             if(Comom::CGlobal::getInstance()->getPrintData().report_Type)//样本类型:
             {
                 n_sHtml += "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                         tr("样本类型")+":"+sampleTypeStr+
                         "</td>";
                 head_line=4;
             }
             else
             {
                 head_line=3;
             }
             if(head_line==4)
             {
                 head_line=0;
                 n_sHtml +="</tr>""<tr>";
                 head_line++;
                 n_sHtml += "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                         tr("ID号")+":"+printTest.SampleID.head()+
                         "</td>";
             }
             else
             {
                 head_line++;
                 n_sHtml += "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                         tr("ID号")+":"+printTest.SampleID.head()+
                         "</td>";
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_Dept)//科室
             {
                 if(head_line==4)
                 {
                     head_line=0;
                     n_sHtml +="</tr>""<tr>";
                 }
                 head_line++;
                 n_sHtml += "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                         tr("科室")+":"+printTest.SubmittedDept.head()+
                         "</td>";
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_Doctor)//申请医生
             {
                 if(head_line==4)
                 {
                     head_line=0;
                     n_sHtml +="</tr>""<tr>";
                 }
                 head_line++;
                 n_sHtml += "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                         tr("医生")+":"+printTest.ReviewedBy.head()+
                         "</td>";
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_State)//样本状态:
             {
                 if(head_line==4)
                 {
                     head_line=0;
                     n_sHtml +="</tr>""<tr>";
                 }
                 head_line++;
                 n_sHtml +="<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                         tr("样本状态")+":"+sampleStateStr+
                         "</td>";
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_Reserve1)//床号
             {
                 if(head_line==4)
                 {
                     head_line=0;
                     n_sHtml +="</tr>""<tr>";
                 }
                 head_line++;
                  n_sHtml +="<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                          Comom::CGlobal::getInstance()->getPrintData().report_reserve1Str+":"+printTest.BedNum.head()+
                          "</td>";
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_Reserve2)//电话
             {
                 if(head_line==4)
                 {
                     head_line=0;
                     n_sHtml +="</tr>""<tr>";
                 }
                 head_line++;
                  n_sHtml +="<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                          Comom::CGlobal::getInstance()->getPrintData().report_reserve2Str+":"+printTest.Phone.head()+
                          "</td>";
             }
             if(head_line==4)
             {
                 head_line=0;
                 n_sHtml +="</tr>""<tr>";
             }
             head_line++;
             n_sHtml +="<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                     tr("病例号")+":"+printTest.CaseNum.head()+
                     "</td>";
             if(head_line==4)
             {
                 head_line=0;
                 n_sHtml +="</tr>""<tr>";
             }
             head_line++;
             n_sHtml +="<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                     tr("患者编码")+":"+printTest.PatientsNum.head()+
                     "</td>";
             for(int i=head_line;i<4;i++)
             {
                 n_sHtml +="<td colspan=\"1\" style=\"font-size:20px\"></td>";
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_Reserve3)//提示
             {
                n_sHtml +="</tr>""<tr>";
                n_sHtml +="<td colspan=\"4\" style=\"font-size:20px\">"+
                        Comom::CGlobal::getInstance()->getPrintData().report_reserve3Str+":"+printTest.Note.head()+"</td>";
             }
             n_sHtml +="</tr>""</table>";
             n_sHtml += "<br><hr width=\"95%\" style=\"height:0.5px\">";
             n_sHtml += "<table align=\"center\" width=\"1040\" height=\"300\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\"  style=\"width: 100%; height: 100%;\">";
             n_sHtml += "<tr>"
                        "<td width=\"230\" style=\"font-size:20px;font-weight:600;text-align:center;\">"+tr("项目名称")+"</td>"
                        "<td width=\"240\" style=\"font-size:20px;font-weight:600;text-align:center;\">"+tr("检验结果")+"</td>"
                        "<td width=\"150\" style=\"font-size:20px;font-weight:600;text-align:center;\">"+tr("结果提示")+"</td>";
             if(Comom::CGlobal::getInstance()->getPrintData().report_Range)//参考范围
             {
                 n_sHtml +="<td width=\"400\" style=\"font-size:20px;font-weight:600;text-align:center;\">"+
                         tr("参考范围")+"</td>";
             }
             else
             {
                 n_sHtml +="<td width=\"400\" style=\"font-size:20px;font-weight:600;text-align:center;\"></td>"  ;
             }
             n_sHtml += "</tr>";
             n_sHtml += "<tr>";
             //项目名称
             n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + printTest.Project.head() + "</td>";
             //检验项目
             if(printTest.Result.head()=="NULL"||printTest.Result.head()=="nan")
             {
                 n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + printTest.Result.head() + "</td>";
             }
             else
             {
                 n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + printTest.Result.head()+printTest.Unit.head()  + "</td>";
             }
             //结果提示
             n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + printTest.Hint.head()  + "</td>";
             //参考范围
             if(Comom::CGlobal::getInstance()->getPrintData().report_Range)//参考范围
             {
                 n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + printTest.Refer.head()+printTest.Unit.head() + "</td>";
             }
             else
             {
                 n_sHtml += "<td style=\"font-size:20px;text-align:center;\"> </td>";
             }
             n_sHtml += "</tr>";
             if(Comom::CGlobal::getInstance()->getPrintData().report_Way)//临床意义
             {
                 n_sHtml += "<tr><td colspan=\"5\" style=\"font-size:20px;text-align:left;padding-left:17px;\">"+
                         tr("临床意义")+":"+
                         "</td></tr> ";

                 n_sHtml += "<tr><td colspan=\"5\" style=\"font-size:20px;text-align:left;padding-left:17px;\">"+
                         printTest.Project.head()+":"+Comom::CGlobal::getInstance()->getClinicalStr(printTest.Project.head())
                         +"</td></tr> ";
             }
             n_sHtml +="</table>";
             n_sHtml += "<br><hr width=\"95%\" style=\"height:0.5px\">";

             n_sHtml += "<table align=\"center\" width=\"1020\" border=\"0\" cellspacing=\"1\" cellpadding=\"3\" style=\"width:100% height:100%\">"
                     "<tr>";
             if(Comom::CGlobal::getInstance()->getPrintData().report_TSample)//采血
             {
                n_sHtml +="<td width=\"380\" colspan=\"2\" style=\"font-size:20px;text-align:left;\">"+
                        tr("采血时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_TimeStr(printTest.Submitted.head()-58) +
                        "</td>";
                end_line++;
                end_line++;
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_TSubmit)//送检
             {
                n_sHtml +="<td width=\"380\" colspan=\"2\" style=\"font-size:20px;text-align:left;\">"+
                        tr("送检时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_TimeStr(printTest.Submitted.head())+
                        "</td>";
                end_line++;
                end_line++;
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_TText)//检验
             {
                 n_sHtml +="<td width=\"380\" colspan=\"2\" style=\"font-size:20px;text-align:left;\">"+
                         tr("检验时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_TimeStr(printTest.Tested.head())+
                         "</td>";
                 end_line++;
                 end_line++;
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_TReport)//报告时间
             {
                 if(end_line==6)
                 {
                     end_line=0;
                     n_sHtml +="</tr>";
                     n_sHtml +="<tr>";
                 }
                 end_line++;
                 end_line++;
                 n_sHtml +="<td width=\"380\" colspan=\"2\" style=\"font-size:20px;text-align:left;\">"+
                         tr("报告时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_TimeStr(printTest.Reported.head())+
                         "</td>";

             }
             if(end_line==6)
             {
                 end_line=0;
                 n_sHtml +="</tr>";
                 n_sHtml +="<tr>";
             }
             end_line++;
             end_line++;
             n_sHtml +="<td width=\"380\" colspan=\"2\" style=\"font-size:20px;text-align:left;\">"+
                     tr("打印时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_current_StrTime()+
                     "</td>";
             if(Comom::CGlobal::getInstance()->getPrintData().report_TextBy)//检验医生
             {
                 if(end_line==6)
                 {
                     end_line=0;
                     n_sHtml +="</tr>";
                     n_sHtml +="<tr>";
                 }
                 end_line++;
                 end_line++;
                 n_sHtml += "<td width=\"380\"  colspan=\"2\" style=\"font-size:20px;text-align:left;\">"+
                         tr("检验医生")+":"+printTest.TestedBy.head()+
                         "</td>";
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_SubmitBy)//送检
             {
                 if(end_line==6)
                 {
                     end_line=0;
                     n_sHtml +="</tr>";
                     n_sHtml +="<tr>";
                 }
                 end_line++;
                 end_line++;
                 n_sHtml += "<td width=\"380\" colspan=\"2\" style=\"font-size:20px;text-align:left;\">"+
                         tr("送检医生")+":"+printTest.SubmittedBy.head()+
                         "</td>";
             }
             if(Comom::CGlobal::getInstance()->getPrintData().report_ReviewBy)//审核
             {
                 if(end_line==6)
                 {
                     end_line=0;
                     n_sHtml +="</tr>";
                     n_sHtml +="<tr>";
                 }
                 end_line++;
                 end_line++;
                 n_sHtml += "<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\">"+
                         tr("审核医生")+":"+
                         "</td>";
                 switch (Comom::CGlobal::getInstance()->getPrintData().signature_Num) {
                 case 0:
                     n_sHtml += "<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\">";
                     n_sHtml+="<img src='"+QCoreApplication::applicationDirPath()+"/Signature/Signature_1.jpg'"+"width=\"170\" height=\"48\" ></td>";
                     break;
                 case 1:
                     n_sHtml += "<td width=\"170\" colspan=\"1\"style=\"font-size:20px;text-align:left;\">";
                     n_sHtml+="<img src='"+QCoreApplication::applicationDirPath()+"/Signature/Signature_2.jpg'"+"width=\"170\" height=\"48\" ></td>";
                     break;
                 case 2:
                     n_sHtml += "<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\">";
                     n_sHtml+="<img src='"+QCoreApplication::applicationDirPath()+"/Signature/Signature_3.jpg'"+"width=\"170\" height=\"48\" ></td>";
                     break;
                 default:
                     n_sHtml += "<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\"></td>";
                     break;
                 }
             }

             for(int i=end_line;i<6;i++)//补列
             {
                 n_sHtml +="<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\"></td>";
             }
               n_sHtml +="</tr>"
                     "</table>"
                     "<table align=\"center\" width=\"1000\" border=\"0\" cellspacing=\"5\" cellpadding=\"5\" style=\"width:100% height:100%\">"
                     "<tr>"
                     "<td style=\"font-size:14px;text-align:right;\">*"+
                       tr("本报告仅对所测样本负责，结果仅供临床参考")+
                       "*</td>"
                     "</tr>"
                     "</table>";
            //   n_sHtml +=" <img src="" width="165" height="60" />


        }
        //qDebug()<<"m_sHtml"<<n_sHtml;
        return n_sHtml;
    }

    void CPrintManager::Printer_QC(st_QC nQCInfo, st_Sample nQCSample ,QPixmap *pix)
    {
        QVector<double> xVector;
        QVector<double> yVector;
        QString monthStr=Comom::CGlobal::getInstance()->getTools()->get_TimeStr(nQCInfo.Time.head()).mid(0,7);
        int monthTime=Comom::CGlobal::getInstance()->getTools()->get_monthtamp(monthStr);
        double maxResult=nQCSample.TargetValue.head()+(nQCSample.SD.head()*2);
        double minResult=nQCSample.TargetValue.head()-(nQCSample.SD.head()*2);

        for (int timeVal = 0; timeVal < nQCInfo.Time.size(); ++timeVal)
        {
            yVector<<nQCInfo.Value.at(timeVal);
            xVector<<nQCInfo.Time.at(timeVal);

        }
        QImage customImage =QCInfoToImage(xVector,yVector,nQCSample.TargetValue.head(),minResult,maxResult,monthTime);
        QImage signatureImage;
        switch (Comom::CGlobal::getInstance()->getPrintData().signature_Num) {
        case 0:
            signatureImage.load(QCoreApplication::applicationDirPath()+"/Signature/Signature_1.jpg");
            break;
        case 1:
            signatureImage.load(QCoreApplication::applicationDirPath()+"/Signature/Signature_2.jpg");
            break;
        case 2:
            signatureImage.load(QCoreApplication::applicationDirPath()+"/Signature/Signature_3.jpg");
            break;
        default:
            signatureImage.load(QCoreApplication::applicationDirPath()+"/Signature/Signature_1.jpg");
            break;
        }

        QPainter nPrinterSet;
        nPrinterSet.begin(pix);
        nPrinterSet.setRenderHint(QPainter::Antialiasing, true);
        // 设置画笔颜色、宽度
        nPrinterSet.setPen(QPen(QColor(255, 255, 255), 2));
        // 设置画刷颜色
        nPrinterSet.setBrush(QColor(255,255,255));
        QRect rect(0,0,2479,3508);
        //整张图设置画刷白底
        nPrinterSet.fillRect(rect,QColor(255, 255, 255));
        nPrinterSet.drawRect(rect);
        //画数据部分的线条
        nPrinterSet.setPen(QPen(QColor(0, 0, 0), 1));
         QFont font;
        font.setPointSize(48);
        nPrinterSet.setFont(font);

        nPrinterSet.setPen(QPen(QColor(0, 0, 0), 1));
        nPrinterSet.drawText(200,200,2079,200,Qt::AlignCenter,tr("临床化学质量报告"));//单位名称
        font.setPointSize(26);
        nPrinterSet.setFont(font);

        int nRow=0;
        int nLine=0;
        nPrinterSet.drawText(QPoint(200+693*nRow,450+80*nLine),tr("项目")+":"+nQCSample.Project.head());
        nRow++;
        nPrinterSet.drawText(QPoint(200+693*nRow,450+80*nLine),tr("批号")+":"+nQCSample.Batch.head());
        nRow++;
        nPrinterSet.drawText(QPoint(200+693*nRow,450+80*nLine),tr("日期")+":"+monthStr);

        nRow=0;
        nLine++;
        nPrinterSet.drawText(QPoint(200+693*nRow,450+80*nLine),tr("方法:均相化学发光免疫分析技术"));
        nRow++;
        nPrinterSet.drawText(QPoint(200+693*nRow,450+80*nLine),tr("仪器")+":"+Comom::CGlobal::getInstance()->getConfigData().m_High_Info.split("|").at(0));

        nRow++;
        nRow=0;
        nLine++;
        nPrinterSet.drawText(QPoint(200+693*nRow,450+80*nLine),tr("水平")+":"+QString::number(nQCSample.Level.head()));
        nRow++;
        nPrinterSet.drawText(QPoint(200+693*nRow,450+80*nLine),tr("靶值")+":"+QString::number(nQCSample.TargetValue.head()));
        nRow++;
        nPrinterSet.drawText(QPoint(200+693*nRow,450+80*nLine),tr("SD值")+":"+QString::number(nQCSample.SD.head()));

        nRow=0;
        nLine++;
        nPrinterSet.drawText(QPoint(200+693*nRow,2400+80*9),tr("质控时间")+":"+monthStr);
        nRow++;
        nPrinterSet.drawText(QPoint(200+693*nRow,2400+80*9),tr("打印时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_current_StrTime());
        nRow++;
        nPrinterSet.drawText(QPoint(200+693*nRow,2400+80*9),tr("审核者:"));//+Control::CLoginManager::getInstances()->getUserName()

        signatureImage=signatureImage.scaled(signatureImage.width()/2,signatureImage.height()/2,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);


        nPrinterSet.drawPixmap(350+693*nRow,2410+80*9,signatureImage.width(),signatureImage.height(),QPixmap::fromImage(signatureImage));


        nLine++;
        nPrinterSet.drawText(QPoint(1082,2400+80*12),("*本报告仅对所测样本负责，结果仅供临床参考*"));



        customImage=customImage.scaled(customImage.width(),customImage.height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        nPrinterSet.translate(200,880); //将（100，100）设为坐标原点
        nPrinterSet.drawPixmap(0,0,customImage.width(),customImage.height(),QPixmap::fromImage(customImage));

    }

    //病程监测记录分析报告
    void CPrintManager::Printer_Course(st_Test nTest, QString project, int monthTime, QPixmap *pix)
    {
        QVector<double> xVector;
        QVector<double> yVector;
        QString monthStr=Comom::CGlobal::getInstance()->getTools()->get_TimeStr(monthTime).mid(0,7);


        double maxResult=1;
        double minResult=-1;
        QString sexStr;
        switch (nTest.Sex.head())
        {
        case 0:
            sexStr +=tr("男");
            break;
        case 1:
            sexStr +=tr("女");
            break;
        case 2:
            sexStr +=tr("其他");
            break;
        default:
            break;
        }

        QString ageStr="";//年龄
        if(nTest.Age.head()>0)
        {
            ageStr=QString::number(nTest.Age.head());
        }
        switch (nTest.AgeType.head())//类型
        {
        case 0:
            ageStr +=tr("岁");
            break;
        case 1:
            ageStr +=tr("月");
            break;
        case 2:
            ageStr +=tr("周");
            break;
        case 3:
            ageStr +=tr("日");
            break;
        case 4:
            ageStr +=tr("小时");
            break;
        default:
            break;
        }

        while (nTest.Project.size())
        {
            QString nProjectStr=nTest.Project.dequeue();
            int reported=nTest.Reported.head();
            if((nProjectStr==project)&&(reported>monthTime)&&(reported<(monthTime+2678400)))
            {
                if(maxResult<nTest.Result.head().toDouble())
                {
                    maxResult=nTest.Result.head().toDouble();
                }
                if(minResult>nTest.Result.head().toDouble())
                {
                    minResult=nTest.Result.head().toDouble();
                }
                xVector<<nTest.Reported.dequeue();
                yVector<<nTest.Result.dequeue().toDouble();
            }
            else
            {
                nTest.Reported.dequeue();
                nTest.Result.dequeue();
            }
        }
        QImage customImage =CourseInfoToImage(xVector,yVector ,minResult,maxResult,monthTime);
        QImage signatureImage;
        switch (Comom::CGlobal::getInstance()->getPrintData().signature_Num) {
        case 0:
            signatureImage.load(QCoreApplication::applicationDirPath()+"/Signature/Signature_1.jpg");
            break;
        case 1:
            signatureImage.load(QCoreApplication::applicationDirPath()+"/Signature/Signature_2.jpg");
            break;
        case 2:
            signatureImage.load(QCoreApplication::applicationDirPath()+"/Signature/Signature_3.jpg");
            break;
        default:
            signatureImage.load(QCoreApplication::applicationDirPath()+"/Signature/Signature_1.jpg");
            break;
        }

        QPainter nPrinterSet;
        nPrinterSet.begin(pix);
        nPrinterSet.setRenderHint(QPainter::Antialiasing, true);
        // 设置画笔颜色、宽度
        nPrinterSet.setPen(QPen(QColor(255, 255, 255), 2));
        // 设置画刷颜色
        nPrinterSet.setBrush(QColor(255,255,255));
        QRect rect(0,0,2479,3508);
        //整张图设置画刷白底
        nPrinterSet.fillRect(rect,QColor(255, 255, 255));
        nPrinterSet.drawRect(rect);
        //画数据部分的线条
        nPrinterSet.setPen(QPen(QColor(0, 0, 0), 1));
         QFont font;
        font.setPointSize(48);
        nPrinterSet.setFont(font);

        nPrinterSet.setPen(QPen(QColor(0, 0, 0), 1));
        nPrinterSet.drawText(200,200,2079,200,Qt::AlignCenter,tr("病程监测记录分析报告"));//单位名称
        font.setPointSize(26);
        nPrinterSet.setFont(font);


        int nRow=0;
        int nLine=0;
        nPrinterSet.drawText(QPoint(200+693*nRow,450+80*nLine),tr("姓名")+":"+nTest.Name.head());
        nRow++;
        nPrinterSet.drawText(QPoint(200+693*nRow,450+80*nLine),tr("性别")+":"+sexStr);
        nRow++;
        nPrinterSet.drawText(QPoint(200+693*nRow,450+80*nLine),tr("年龄")+":"+ageStr);

        nRow=0;
        nLine++;
        nPrinterSet.drawText(QPoint(200+693*nRow,450+80*nLine),tr("ID号")+":"+nTest.SampleID.head());
        nRow++;
        nPrinterSet.drawText(QPoint(200+693*nRow,450+80*nLine),tr("项目")+":"+project);
        nRow++;
        nPrinterSet.drawText(QPoint(200+693*nRow,450+80*nLine),tr("日期")+":"+monthStr);

        nRow=0;
        nLine++;
//        nPrinterSet.drawText(QPoint(200+693*nRow,2400+80*9),tr("时间")+":"+monthStr);
//        nRow++;
        nPrinterSet.drawText(QPoint(200+693*nRow,2400+80*9),tr("打印时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_current_StrTime());
        nRow++;
        nPrinterSet.drawText(QPoint(200+693*nRow,2400+80*9),tr("审核医生:"));//+Control::CLoginManager::getInstances()->getUserName()

        signatureImage=signatureImage.scaled(signatureImage.width()/2,signatureImage.height()/2,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);


        nPrinterSet.drawPixmap(350+693*nRow,2410+80*9,signatureImage.width(),signatureImage.height(),QPixmap::fromImage(signatureImage));


        nLine++;
        nPrinterSet.drawText(QPoint(1082,2400+80*12),tr("*本报告仅对所测样本负责，结果仅供临床参考*"));



        customImage=customImage.scaled(customImage.width(),customImage.height(),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        nPrinterSet.translate(200,880); //将（100，100）设为坐标原点
        nPrinterSet.drawPixmap(0,0,customImage.width(),customImage.height(),QPixmap::fromImage(customImage));


    }

    QImage CPrintManager::QCInfoToImage(QVector<double> xVector, QVector<double> yVector, double x, double Low, double High, int monthTime)
    {
        QVector<double> xLine;
        QVector<double> yLine;
        xLine.append(monthTime);
        xLine.append(monthTime+24*3600*31);

        QFont legendFont;
        legendFont.setPointSize(28);
        QCustomPlot custom_Print_qc;
        custom_Print_qc.setMinimumSize(2000,1800);
        custom_Print_qc.setBackground(Qt::white);
        //设置字体大小
        custom_Print_qc.legend->setFont(legendFont);
        custom_Print_qc.xAxis->setTickLabelFont(legendFont);
        custom_Print_qc.yAxis->setTickLabelFont(legendFont);


        //设置坐标轴标签
        custom_Print_qc.xAxis->setLabelFont(legendFont);
        custom_Print_qc.xAxis->setLabel(tr("临床化学质量控制图"));

        QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
        dateTicker->setDateTimeFormat("MM-dd");//日期格式(可参考QDateTime::fromString()函数)
        custom_Print_qc.xAxis->setTicker(dateTicker);//设置X轴为时间轴
        dateTicker->setTickCount(31);//设置大刻度个数 有可能计算出来的刻度数不完全等于设置的刻度个数，取决于刻度生成策略
        custom_Print_qc.xAxis->setTickLabelRotation(35);//设置x坐标 旋转35° 横着显示可能显示不全

        custom_Print_qc.clearPlottables();
        QPen color_pen;
        color_pen.setWidth(3);
        color_pen.setBrush(Qt::red);
        yLine.append(Low);
        yLine.append(Low);
        custom_Print_qc.addGraph();
        custom_Print_qc.graph(0)->setPen(color_pen);
        custom_Print_qc.graph(0)->setLineStyle(QCPGraph::lsLine);
        qDebug()<<"xLine"<<xLine;
        qDebug()<<"yLine"<<yLine;
        custom_Print_qc.graph(0)->setData(xLine,yLine);
        yLine.clear();
        yLine.append(High);
        yLine.append(High);
        custom_Print_qc.addGraph();
        custom_Print_qc.graph(1)->setPen(color_pen);
        custom_Print_qc.graph(1)->setLineStyle(QCPGraph::lsLine);
        qDebug()<<"xLine"<<xLine;
        qDebug()<<"yLine"<<yLine;
        custom_Print_qc.graph(1)->setData(xLine,yLine);
        yLine.clear();
        yLine.append(x);
        yLine.append(x);
        color_pen.setBrush(Qt::black);
        custom_Print_qc.addGraph();
        custom_Print_qc.graph(2)->setPen(color_pen);
        custom_Print_qc.graph(2)->setLineStyle(QCPGraph::lsLine);
        qDebug()<<"xLine"<<xLine;
        qDebug()<<"yLine"<<yLine;
        custom_Print_qc.graph(2)->setData(xLine,yLine);
        custom_Print_qc.addGraph();
        color_pen.setBrush(Qt::blue);
        custom_Print_qc.graph(3)->setPen(color_pen);
        custom_Print_qc.graph(3)->setLineStyle(QCPGraph::lsLine);
        custom_Print_qc.graph(3)->setData(xVector,yVector);
        custom_Print_qc.xAxis->setRange(monthTime,monthTime+24*3600*31);
        custom_Print_qc.yAxis->setRange(Low-((High-Low)/3),High+((High-Low)/3));
        custom_Print_qc.replot();

        return custom_Print_qc.toPixmap().toImage();
    }

    QImage CPrintManager::CourseInfoToImage(QVector<double> xVector, QVector<double> yVector , double minResult, double maxResult, int monthTime)
    {



        QFont legendFont;
        legendFont.setPointSize(28);
        QCustomPlot custom_Print_Course;
        custom_Print_Course.setMinimumSize(2000,1800);
        custom_Print_Course.setBackground(Qt::white);
        //设置字体大小
        custom_Print_Course.legend->setFont(legendFont);
        custom_Print_Course.xAxis->setTickLabelFont(legendFont);
        custom_Print_Course.yAxis->setTickLabelFont(legendFont);
        //设置坐标轴标签
        custom_Print_Course.xAxis->setLabelFont(legendFont);
        custom_Print_Course.xAxis->setLabel(Comom::CGlobal::getInstance()->getTools()->get_TimeStr(monthTime).mid(0,7));

        QSharedPointer<QCPAxisTickerDateTime> dateTicker(new QCPAxisTickerDateTime);//日期做X轴
        dateTicker->setDateTimeFormat("MM-dd");//日期格式(可参考QDateTime::fromString()函数)
        custom_Print_Course.xAxis->setTicker(dateTicker);//设置X轴为时间轴
        dateTicker->setTickCount(31);//设置大刻度个数 有可能计算出来的刻度数不完全等于设置的刻度个数，取决于刻度生成策略
        custom_Print_Course.xAxis->setTickLabelRotation(35);//设置x坐标 旋转35° 横着显示可能显示不全
        QPen nPen;
        nPen.setWidth(3);
        nPen.setBrush(Qt::blue);
        custom_Print_Course.addGraph();
        custom_Print_Course.graph(0)->setPen(nPen);
        custom_Print_Course.graph(0)->setLineStyle(QCPGraph::lsLine);
        custom_Print_Course.graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
        custom_Print_Course.graph(0)->setData(xVector,yVector);
        custom_Print_Course.yAxis->setRange(minResult-abs(minResult/6),maxResult+abs(maxResult/6));
        custom_Print_Course.xAxis->setRange(monthTime,monthTime+24*3600*31);
        custom_Print_Course.replot();
        return custom_Print_Course.toPixmap().toImage();


    }

    QString CPrintManager::Printer_merge_A5(st_Test nTest)
    {
        QStringList htmlProject;//项目名称
        QString n_sHtml;
        //性别
        QString sexStr;
        switch (nTest.Sex.head())
        {
        case 0:
            sexStr +=tr("男");
            break;
        case 1:
            sexStr +=tr("女");
            break;
        case 2:
            sexStr +=tr("其他");
            break;
        default:
            break;
        }

        QString ageStr="";//年龄
        if(nTest.Age.head()>0)
        {
            ageStr=QString::number(nTest.Age.head());
        }
        switch (nTest.AgeType.head())//年龄类型
        {
        case 0:
            ageStr +=tr("岁");
            break;
        case 1:
            ageStr +=tr("月");
            break;
        case 2:
            ageStr +=tr("周");
            break;
        case 3:
            ageStr +=tr("日");
            break;
        case 4:
            ageStr +=tr("小时");
            break;
        default:
            break;
        }


        {
            //height=\"50\"1754×1240分辨率
             n_sHtml +=
             "<table align=\"center\" width=\"1040\" border=\"0\" cellspacing=\"2\" cellpadding=\"1\"  style=\"width: 100%; height: 100%;\">"

             "<tr>"
             "</tr>"
             "<tr>"
             "<td colspan=\"4\" style=\"font-size:30px;text-align:center\">"+
                     Comom::CGlobal::getInstance()->getPrintData().report_Head+//表头
             "</td>";

             if(m_mergePage==1)
             {
                 n_sHtml +=
                         "</tr>"
                         "<tr>"
                         "</tr>"
                         "<tr>"
                 "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                 tr("姓名")+":"+nTest.Name.head()+
                 "</td>"
                 "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                 tr("ID号")+":"+nTest.SampleID.head()+
                 "</td>"
                 "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                 tr("性别")+":"+sexStr+
                 "</td>"
                 "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                 tr("年龄")+":"+ageStr+
                 "</td>";
                 if(Comom::CGlobal::getInstance()->getPrintData().report_Reserve3)//提示
                 {
                    n_sHtml +="</tr>""<tr>";
                    n_sHtml +="<td colspan=\"4\" style=\"font-size:20px\">"+
                            Comom::CGlobal::getInstance()->getPrintData().report_reserve3Str+":"+nTest.Note.head()+"</td>";
                 }

             }
             else
             {

             }

             n_sHtml +="</tr>""</table>";
             n_sHtml += "<br><hr width=\"95%\" style=\"height:0.5px\">";
             int htmlHeight=500;
             if(m_mergePage==1)
             {
                 htmlHeight=440;
             }
             n_sHtml += "<table align=\"center\" width=\"1040\" height=\""+QString::number(htmlHeight)+"\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\"  style=\"width: 100%; height: 100%;\">";
             n_sHtml += "<tr>"
                        "<td width=\"230\" style=\"font-size:20px;font-weight:600;text-align:center;\">"+tr("项目名称")+"</td>"
                        "<td width=\"240\" style=\"font-size:20px;font-weight:600;text-align:center;\">"+tr("检验结果")+"</td>"
                        "<td width=\"150\" style=\"font-size:20px;font-weight:600;text-align:center;\">"+tr("结果提示")+"</td>";
             if(Comom::CGlobal::getInstance()->getPrintData().report_Range)//参考范围
             {
                 n_sHtml +="<td width=\"400\" style=\"font-size:20px;font-weight:600;text-align:center;\">"+
                         tr("参考范围")+"</td>";
             }
             else
             {
                 n_sHtml +="<td width=\"400\" style=\"font-size:20px;font-weight:600;text-align:center;\"></td>"  ;
             }
             n_sHtml += "</tr>";

             int projectSize=0;
             while(nTest.Project.size()&&(projectSize+(htmlProject.size()*2))<10)
             {
                 htmlProject<<nTest.Project.head();
                 htmlProject = htmlProject.toSet().toList();

                 QString unitStr=nTest.Unit.dequeue();

                 n_sHtml += "<tr>";
                 //项目名称
                 n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + nTest.Project.dequeue() + "</td>";
                 //检验项目
                 if(nTest.Result.head()=="NULL"||nTest.Result.head()=="nan")
                 {
                     n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + nTest.Result.dequeue() + "</td>";
                 }
                 else
                 {
                     n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + nTest.Result.dequeue()+unitStr  + "</td>";
                 }
                 //结果提示
                 n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + nTest.Hint.dequeue()  + "</td>";
                 //参考范围
                 if(Comom::CGlobal::getInstance()->getPrintData().report_Range)//参考范围
                 {
                     n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + nTest.Refer.dequeue()+unitStr + "</td>";
                 }
                 else
                 {
                     n_sHtml += "<td style=\"font-size:20px;text-align:center;\"> </td>";
                 }
                 n_sHtml += "</tr>";
                 projectSize++;
             }
             //去除重复项
             qDebug()<<"htmlProject"<<htmlProject;
             if(Comom::CGlobal::getInstance()->getPrintData().report_Way)//临床意义
             {
                 n_sHtml += "<tr><td colspan=\"5\" style=\"font-size:20px;text-align:left;padding-left:17px;\">"+
                         tr("临床意义")+":"+
                         "</td></tr> ";
                 while (htmlProject.size())
                 {
                     QString projectStr=htmlProject.takeFirst();
                     n_sHtml += "<tr><td colspan=\"5\" style=\"font-size:20px;text-align:left;padding-left:17px;\">"+
                             projectStr+":"+Comom::CGlobal::getInstance()->getClinicalStr(projectStr)
                             +"</td></tr> ";
                 }

             }
             n_sHtml +="</table><br>";
             n_sHtml += "<hr width=\"95%\" style=\"height:0.5px\">";


             n_sHtml += "<table align=\"center\" width=\"1020\" border=\"0\" cellspacing=\"1\" cellpadding=\"3\" style=\"width:100% height:100%\">"
                     "<tr>";
             if(nTest.Project.size()==0)
             {
                 n_sHtml +="<td width=\"380\" colspan=\"2\" style=\"font-size:20px;text-align:left;\">"+
                         tr("打印时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_current_StrTime()+
                         "</td>";
                 if(Comom::CGlobal::getInstance()->getPrintData().report_ReviewBy)//审核
                 {
                     n_sHtml += "<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\">"+
                             tr("审核医生")+":"+
                             "</td>";
                     switch (Comom::CGlobal::getInstance()->getPrintData().signature_Num) {
                     case 0:
                         n_sHtml += "<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\">";
                         n_sHtml+="<img src='"+QCoreApplication::applicationDirPath()+"/Signature/Signature_1.jpg'"+"width=\"170\" height=\"48\" ></td>";
                         break;
                     case 1:
                         n_sHtml += "<td width=\"170\" colspan=\"1\"style=\"font-size:20px;text-align:left;\">";
                         n_sHtml+="<img src='"+QCoreApplication::applicationDirPath()+"/Signature/Signature_2.jpg'"+"width=\"170\" height=\"48\" ></td>";
                         break;
                     case 2:
                         n_sHtml += "<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\">";
                         n_sHtml+="<img src='"+QCoreApplication::applicationDirPath()+"/Signature/Signature_3.jpg'"+"width=\"170\" height=\"48\" ></td>";
                         break;
                     default:
                         n_sHtml += "<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\"></td>";
                         break;
                     }
                 }
             }


             for(int i=4;i<6;i++)//补列
             {
                 n_sHtml +="<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\"></td>";
             }
               n_sHtml +="</tr>"
                         "</table><br><br>"
                         "<table align=\"center\" width=\"1000\" border=\"0\" cellspacing=\"5\" cellpadding=\"5\" style=\"width:100% height:100%\">"
                         "<tr>"

                         "<td width=\"10\" colspan=\"1\" style=\"font-size:14px;text-align:left;\">"+
                         QString::number(m_mergePage)+
                         "</td>"
                         "<td width=\"990\" colspan=\"1\" style=\"font-size:14px;text-align:right;\">*"+
                         tr("本报告仅对所测样本负责，结果仅供临床参考")+
                         "*</td>"


                         "</tr>"
                         "</table>";
            //   n_sHtml +=" <img src="" width="165" height="60" />


        }
        //qDebug()<<"m_sHtml"<<n_sHtml;
        if(nTest.Project.size()==0)
        {
            m_mergePage=1;
            m_mergeFlag=false;
        }
        else
        {
            m_mergePage++;
        }
        return n_sHtml;
    }

    QString CPrintManager::Printer_merge_A4(st_Test nTest)
    {
        QStringList htmlProject;//项目名称
        QString n_sHtml;
        //性别
        QString sexStr;
        switch (nTest.Sex.head())
        {
        case 0:
            sexStr +=tr("男");
            break;
        case 1:
            sexStr +=tr("女");
            break;
        case 2:
            sexStr +=tr("其他");
            break;
        default:
            break;
        }
        QString ageStr="";//年龄
        if(nTest.Age.head()>0)
        {
            ageStr=QString::number(nTest.Age.head());
        }
        switch (nTest.AgeType.head())//年龄类型
        {
        case 0:
            ageStr +=tr("岁");
            break;
        case 1:
            ageStr +=tr("月");
            break;
        case 2:
            ageStr +=tr("周");
            break;
        case 3:
            ageStr +=tr("日");
            break;
        case 4:
            ageStr +=tr("小时");
            break;
        default:
            break;
        }

        {
            //height=\"50\"1754×1240分辨率
             n_sHtml +=
             "<table align=\"center\" width=\"1040\" border=\"0\" cellspacing=\"2\" cellpadding=\"1\"  style=\"width: 100%; height: 100%;\">"

             "<tr>"
             "</tr>"
             "<tr>"
             "<td colspan=\"4\" style=\"font-size:30px;text-align:center\">"+
                     Comom::CGlobal::getInstance()->getPrintData().report_Head+//表头
             "</td>";

             if(m_mergePage==1)
             {
                 n_sHtml +=
                         "</tr>"
                         "<tr>"
                         "</tr>"
                         "<tr>"
                 "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                 tr("姓名")+":"+nTest.Name.head()+
                 "</td>"
                 "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                 tr("ID号")+":"+nTest.SampleID.head()+
                 "</td>"
                 "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                 tr("性别")+":"+sexStr+
                 "</td>"
                 "<td width=\"280\" colspan=\"1\" style=\"font-size:20px\">"+
                 tr("年龄")+":"+ageStr+
                 "</td>";
                 if(Comom::CGlobal::getInstance()->getPrintData().report_Reserve3)//提示
                 {
                    n_sHtml +="</tr>""<tr>";
                    n_sHtml +="<td colspan=\"4\" style=\"font-size:20px\">"+
                            Comom::CGlobal::getInstance()->getPrintData().report_reserve3Str+":"+nTest.Note.head()+"</td>";
                 }

             }
             else
             {

             }

             n_sHtml +="</tr>""</table>";
             n_sHtml += "<br><hr width=\"95%\" style=\"height:0.5px\">";
             n_sHtml += "<table align=\"center\" width=\"1040\" height=\"1300\" border=\"0\" cellspacing=\"2\" cellpadding=\"2\"  style=\"width: 100%; height: 100%;\">";
             n_sHtml += "<tr>"
                        "<td width=\"230\" style=\"font-size:20px;font-weight:600;text-align:center;\">"+tr("项目名称")+"</td>"
                        "<td width=\"240\" style=\"font-size:20px;font-weight:600;text-align:center;\">"+tr("检验结果")+"</td>"
                        "<td width=\"150\" style=\"font-size:20px;font-weight:600;text-align:center;\">"+tr("结果提示")+"</td>";
             if(Comom::CGlobal::getInstance()->getPrintData().report_Range)//参考范围
             {
                 n_sHtml +="<td width=\"400\" style=\"font-size:20px;font-weight:600;text-align:center;\">"+
                         tr("参考范围")+"</td>";
             }
             else
             {
                 n_sHtml +="<td width=\"400\" style=\"font-size:20px;font-weight:600;text-align:center;\"></td>"  ;
             }
             n_sHtml += "</tr>";

             int projectSize=0;
             while(nTest.Project.size()&&(projectSize+(htmlProject.size()*2))<36)
             {

                 QString unitStr=nTest.Unit.dequeue();
                 htmlProject<<nTest.Project.head();
                 //去除重复项
                 htmlProject = htmlProject.toSet().toList();
                 n_sHtml += "<tr>";
                 //项目名称
                 n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + nTest.Project.dequeue() + "</td>";
                 //检验项目
                 if(nTest.Result.head()=="NULL"||nTest.Result.head()=="nan")
                 {
                     n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + nTest.Result.dequeue() + "</td>";
                 }
                 else
                 {
                     n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + nTest.Result.dequeue()+unitStr  + "</td>";
                 }
                 //结果提示
                 n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + nTest.Hint.dequeue()  + "</td>";
                 //参考范围
                 if(Comom::CGlobal::getInstance()->getPrintData().report_Range)//参考范围
                 {
                     n_sHtml += "<td style=\"font-size:20px;text-align:center;\">" + nTest.Refer.dequeue()+unitStr + "</td>";
                 }
                 else
                 {
                     n_sHtml += "<td style=\"font-size:20px;text-align:center;\"> </td>";
                 }
                 n_sHtml += "</tr>";
                 projectSize++;
             }
             qDebug()<<"htmlProject"<<htmlProject;
             if(Comom::CGlobal::getInstance()->getPrintData().report_Way)//临床意义
             {
                 n_sHtml += "<tr><td colspan=\"5\" style=\"font-size:20px;text-align:left;padding-left:17px;\">"+
                         tr("临床意义")+":"+
                         "</td></tr> ";
                 while (htmlProject.size())
                 {
                     QString projectStr= htmlProject.takeFirst();
                     n_sHtml += "<tr><td colspan=\"5\" style=\"font-size:20px;text-align:left;padding-left:17px;\">"+
                             projectStr+":"+Comom::CGlobal::getInstance()->getClinicalStr(projectStr)
                            +"</td></tr> ";
                 }

             }
             n_sHtml +="</table><br>";
             n_sHtml += "<hr width=\"95%\" style=\"height:0.5px\">";


             n_sHtml += "<table align=\"center\" width=\"1020\" border=\"0\" cellspacing=\"1\" cellpadding=\"3\" style=\"width:100% height:100%\">"
                     "<tr>";
             if(nTest.Project.size()==0)
             {
                 n_sHtml +="<td width=\"380\" colspan=\"2\" style=\"font-size:20px;text-align:left;\">"+
                         tr("打印时间")+":"+Comom::CGlobal::getInstance()->getTools()->get_current_StrTime()+
                         "</td>";
                 if(Comom::CGlobal::getInstance()->getPrintData().report_ReviewBy)//审核
                 {
                     n_sHtml += "<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\">"+
                             tr("审核医生")+":"+
                             "</td>";
                     switch (Comom::CGlobal::getInstance()->getPrintData().signature_Num) {
                     case 0:
                         n_sHtml += "<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\">";
                         n_sHtml+="<img src='"+QCoreApplication::applicationDirPath()+"/Signature/Signature_1.jpg'"+"width=\"170\" height=\"48\" ></td>";
                         break;
                     case 1:
                         n_sHtml += "<td width=\"170\" colspan=\"1\"style=\"font-size:20px;text-align:left;\">";
                         n_sHtml+="<img src='"+QCoreApplication::applicationDirPath()+"/Signature/Signature_2.jpg'"+"width=\"170\" height=\"48\" ></td>";
                         break;
                     case 2:
                         n_sHtml += "<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\">";
                         n_sHtml+="<img src='"+QCoreApplication::applicationDirPath()+"/Signature/Signature_3.jpg'"+"width=\"170\" height=\"48\" ></td>";
                         break;
                     default:
                         n_sHtml += "<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\"></td>";
                         break;
                     }
                 }
             }


             for(int i=4;i<6;i++)//补列
             {
                 n_sHtml +="<td width=\"170\" colspan=\"1\" style=\"font-size:20px;text-align:left;\"></td>";
             }
               n_sHtml +="</tr>"
                         "</table><br><br>"
                         "<table align=\"center\" width=\"1000\" border=\"0\" cellspacing=\"5\" cellpadding=\"5\" style=\"width:100% height:100%\">"
                         "<tr>"

                         "<td width=\"10\" colspan=\"1\" style=\"font-size:14px;text-align:left;\">"+
                         QString::number(m_mergePage)+
                         "</td>"
                         "<td width=\"990\" colspan=\"1\" style=\"font-size:14px;text-align:right;\">*"+
                         tr("本报告仅对所测样本负责，结果仅供临床参考")+
                         "*</td>"


                         "</tr>"
                         "</table>";
            //   n_sHtml +=" <img src="" width="165" height="60" />


        }
        //qDebug()<<"m_sHtml"<<n_sHtml;
        if(nTest.Project.size()==0)
        {
            m_mergePage=1;
            m_mergeFlag=false;
        }
        else
        {
            m_mergePage++;
        }
        return n_sHtml;

    }

    bool CPrintManager::setQCPrintInfo(st_QC nQCInfo, st_Sample nQCSample)
    {
        //打印机状态非自动打印热敏0，外置2-A4，4-A5 //自动打印热敏1，外置3-A4，5-A5

        bool printFlag=false;
        if((Comom::CGlobal::getInstance()->getConfigData().m_PrintType==2||
            Comom::CGlobal::getInstance()->getConfigData().m_PrintType==3 )
                &&nQCSample.Num.size()>0)
        {
            QPrinter printerPixmap;
            QPixmap pix = QPixmap(2479,3508);
            Printer_QC(nQCInfo,nQCSample,&pix);
            printerPixmap.setOrientation(QPrinter::Portrait); //纵向：Portrait 横向：Landscape
            printerPixmap.setPageSize(QPrinter::A4);//设置纸张大小
            printerPixmap.setResolution(300);//设置像素
            QPainter painterPixmap;
            //选取打印机，特别重要
            //开始打印
            painterPixmap.begin(&printerPixmap);
            //设置图像在A4中的开始坐标是什么
            painterPixmap.drawPixmap(0,0,pix);
            painterPixmap.end();
            printFlag=true;
        }
        return printFlag;
    }

    //病程监测记录分析报告
    bool CPrintManager::setCoursePrintData(st_Test nTest, QString project, int monthTime)
    {
        bool printFlag=false;
        if((Comom::CGlobal::getInstance()->getConfigData().m_PrintType==2||
            Comom::CGlobal::getInstance()->getConfigData().m_PrintType==3 )
                &&nTest.Num.size()>0)
        {
            QPrinter printerPixmap;
            QPixmap pix = QPixmap(2479,3508);
            Printer_Course(nTest,project,monthTime,&pix);
            printerPixmap.setOrientation(QPrinter::Portrait); //纵向：Portrait 横向：Landscape
            printerPixmap.setPageSize(QPrinter::A4);//设置纸张大小
            printerPixmap.setResolution(300);//设置像素
            QPainter painterPixmap;
            //选取打印机，特别重要
            //开始打印
            painterPixmap.begin(&printerPixmap);
            //设置图像在A4中的开始坐标是什么
            painterPixmap.drawPixmap(0,0,pix);
            painterPixmap.end();
            printFlag=true;
        }
        return printFlag;
    }
*/

    QString CPrintManager::BinToHex(QString strBin)
    {
        QString strout;
        QString strH,strL;
        QString stroutH,stroutL;
        strH=strBin.mid(0,4);
        strL=strBin.mid(4,4);

        if(strH=="1111")
        {
            stroutH="F";
        }
        else if(strH=="1110")
        {
            stroutH="E";
        }
        else if(strH=="1101")
        {
            stroutH="D";
        }
        else if(strH=="1100")
        {
            stroutH="C";
        }
        else if(strH=="1011")
        {
            stroutH="B";
        }
        else if(strH=="1010")
        {
            stroutH="A";
        }
        else if(strH=="1001")
        {
            stroutH="9";
        }
        else if(strH=="1000")
        {
            stroutH="8";
        }
        else if(strH=="0111")
        {
            stroutH="7";
        }
        else if(strH=="0110")
        {
            stroutH="6";
        }
        else if(strH=="0101")
        {
            stroutH="5";
        }
        else if(strH=="0100")
        {
            stroutH="4";
        }
        else if(strH=="0011")
        {
            stroutH="3";
        }
        else if(strH=="0010")
        {
            stroutH="2";
        }
        else if(strH=="0001")
        {
            stroutH="1";
        }
        else if(strH=="0000")
        {
            stroutH="0";
        }

        if(strL=="1111")
        {
            stroutL="F";
        }
        else if(strL=="1110")
        {
            stroutL="E";
        }
        else if(strL=="1101")
        {
            stroutL="D";
        }
        else if(strL=="1100")
        {
            stroutL="C";
        }
        else if(strL=="1011")
        {
            stroutL="B";
        }
        else if(strL=="1010")
        {
            stroutL="A";
        }
        else if(strL=="1001")
        {
            stroutL="9";
        }
        else if(strL=="1000")
        {
            stroutL="8";
        }
        else if(strL=="0111")
        {
            stroutL="7";
        }
        else if(strL=="0110")
        {
            stroutL="6";
        }
        else if(strL=="0101")
        {
            stroutL="5";
        }
        else if(strL=="0100")
        {
            stroutL="4";
        }
        else if(strL=="0011")
        {
            stroutL="3";
        }
        else if(strL=="0010")
        {
            stroutL="2";
        }
        else if(strL=="0001")
        {
            stroutL="1";
        }
        else if(strL=="0000")
        {
            stroutL="0";
        }
        strout=stroutH+stroutL;
        return strout;
    }

    //16进制Str转16进制byt
    QByteArray CPrintManager::HexStrToByt(QString HexString)
    {
        bool ok;
        QByteArray ret;
        HexString = HexString.trimmed();
        HexString = HexString.simplified();
        QStringList sl;
        for(int i=0;i<HexString.length();i++)
        {
            sl.append(HexString.mid(i*2,2));
        }

        foreach (QString s, sl)
        {
            if(!s.isEmpty())
            {
                char c = s.toInt(&ok,16)&0xFF;
                if(ok)
                {
                    ret.append(c);
                }
                else
                {
                   // QMessageBox::warning(0,tr("错误："),QString("非法的16进制字符: \"%1\"").arg(s));
                }
            }
        }
        return ret;
    }

    QByteArray CPrintManager::ImageToStrHex(QImage image)
    {

        int image_height;
        image_height=image.height()*384/image.width();
        image=image.scaled(384,image_height,Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
        int yL=image_height%256;
        int yH=image_height/256;

        QString yLTohex = QString("%1").arg(yL, 2, 16, QLatin1Char('0'));
        QString yHTohex = QString("%1").arg(yH, 2, 16, QLatin1Char('0'));
        QString hexStr = "1D7630303000"+yLTohex+yHTohex;

        unsigned char *data = image.bits();                         // 指向当前图像第一个像素
        int width = image.width ();                                 // 图像宽度
        int height = image.height ();                               // 图像高度
        unsigned char Blue = 0;                                     // 蓝色分量
        QString byt_str;
        for (int i = 0; i < height; i++)                            // 遍历每一行
        {
            QString Blue_str;
            for ( int j = 0; j < width; j++ )                       // 遍历每一列
            {
                Blue = *(data);                                     // 获取当前像素点蓝色分量
                int Blue_int=(int)Blue;
                if(Blue_int==163)
                {
                    if((i+j)%5==0)
                    {
                        Blue_str+="1";
                    }
                    else
                    {
                        Blue_str+="0";
                    }
                }
                else if(Blue_int==255)
                {
                    Blue_str+="0";
                }else
                {
                    Blue_str+="1";
                }
                data += 4;// 更新至下一像素点
            }
            for(int i=0;i<(Blue_str.length()/8);i++)
            {
                byt_str+=BinToHex(Blue_str.mid(i*8,8));
            }
        }
        hexStr+=byt_str;
        return HexStrToByt(hexStr);
    }

    QString CPrintManager::getDataToInfo(QString nData, int nWidth)//字符，所占空位
    {
        QString kStr;
        int number=0;
        int nCount = nData.count();
        for(int i = 0; i < nCount; i++)
        {
            QChar schar = nData.at(i);
            ushort uNum =schar.unicode();
            if(uNum >= 0x4E00 && uNum <= 0x9FA5)
            {
                number=number+2;
            }
            else
            {
                number++;
            }
        }
        if(number<nWidth)
        {
            number=nWidth-number;
        }
        if(number>1)
        {
            for(int i=0;i<number/2;i++)
            {
                kStr+=" ";
            }
            kStr+=nData;

            for(int i=0;i<(number-number/2);i++)
            {
                kStr+=" ";
            }
        }
        else
        {
            kStr+=nData+" ";
        }
        return kStr;
    }

}
