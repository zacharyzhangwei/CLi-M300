#ifndef CPRINTMANAGER_H
#define CPRINTMANAGER_H
/////////////////////////////////////////
/// \brief The CDBManager class
/// 打印机相关的控制
///
#include <QObject>
#include "print/cpmodule.h"
#include "print/psession.h"
#include "data/cdbsession.h"
#include "common/cglobal.h"
#include <QTextCodec>
#include "IPModule.h"
#include "control/chlcpeakmanager.h"
#include <QPixmap>
#include <QImage>
#include "qcustomplot.h"

namespace Control
{
class CPrintManager: public QObject, public IPModuleCB
{
    Q_OBJECT
public:
    static CPrintManager * getInstance()
    {
        static CPrintManager m_print(nullptr);
        return &m_print;
    }
    bool Init(int port,int rate);
    bool setPrintData(QQueue<st_TestInfo> testInfo, bool mergeFlag);
public:
     virtual void comstatus(int status);
private:
    CPrintManager(QObject *parent);
    CPModule m_printmodule;
    bool m_mergeFlag=true;//合并打印标志位
    int m_mergePage=1;

    QByteArray ImageToStrHex(QImage image);
    QString BinToHex(QString strBin);

    QByteArray HexStrToByt(QString HexString);//16进制Str转16进制byt
        QString getDataToInfo(QString nData, int nWidth=8);//字符，所占空位

    QString Printer_In_Str(st_TestInfo testInfo);
    QString Printer_merge_In_Str(QQueue<st_TestInfo> testList);

    /*
    QString Printer_A4(st_Test nTest);
    QString Printer_A5(st_Test nTest);

    QString Printer_merge_A4(st_Test nTest);
    QString Printer_merge_A5(st_Test nTest);

    void Printer_QC(st_QC nQCInfo, st_Sample nQCSample, QPixmap *pix);
    void Printer_Course(st_Test nTest, QString project, int monthTime, QPixmap *pix);

    QImage QCInfoToImage(QVector<double> xVector, QVector<double> yVector, double x, double Low, double High, int monthTime);
    QImage CourseInfoToImage(QVector<double> xVector, QVector<double> yVector, double minResult, double maxResult, int monthTime);

    bool setQCPrintInfo(st_QC nQCInfo, st_Sample nQCSample);
    bool setCoursePrintData(st_Test nTest, QString project, int monthTime);
*/


public:
};
}
#endif // CPRINTMANAGER_H



/*bool CPrintManager::setPrintData(st_Test nTest,bool mergeFlag)
    {
        //m_stTest
        qDebug()<<"mergeFlag"<<mergeFlag;
        bool printFlag=false;
        //合并打印
        if(mergeFlag)
        {
            //打印机状态非自动打印热敏0，外置2-A4，4-A5 //自动打印热敏1，外置3-A4，5-A5
            switch (Comom::CGlobal::getInstance()->getConfigData().m_PrintType) {
            case 0:
            {
                QQueue<ISession *> *ssqueue=new QQueue<ISession *>;
                PSession *sess=new PSession();
                QString LineStr="\n\n\n";
                QByteArray SetByt=Printer_merge_In_Str(nTest).toLocal8Bit();
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
                QByteArray SetByt=Printer_merge_In_Str(nTest).toLocal8Bit();
                SetByt.append(LineStr.toLocal8Bit());
                sess->setdata(SetByt);
                ssqueue->enqueue(sess);
                printFlag= m_printmodule.sends(ssqueue);
            }
                break;
            case 2:
            {
                while (m_mergeFlag)
                {
                    QPrinter printer;
                    printer.setOrientation(QPrinter::Portrait);
                    printer.setPageSize(QPrinter::A4);
                    printer.setResolution(150);//设置像素
                    QTextDocument textDocument;
                    textDocument.setHtml(Printer_merge_A4(nTest));
                    textDocument.setPageSize(printer.pageRect().size());
                    textDocument.print(&printer);
                    textDocument.clear();
                }
                printFlag= 1;
            }
                break;
            case 3:
            {
                QPrinter printer;
                printer.setOrientation(QPrinter::Portrait);
                printer.setPageSize(QPrinter::A4);
                printer.setResolution(150);//设置像素
                QTextDocument textDocument;
                textDocument.setHtml(Printer_merge_A4(nTest));
                textDocument.setPageSize(printer.pageRect().size());
                textDocument.print(&printer);
                textDocument.clear();
                printFlag= 1;
            }
                break;
            case 4:
            {
                QPrinter printer;
                printer.setOrientation(QPrinter::Landscape);
                printer.setPageSize(QPrinter::A5);
                printer.setResolution(150);//设置像素
                QTextDocument textDocument;
                textDocument.setHtml(Printer_merge_A5(nTest));
                textDocument.setPageSize(printer.pageRect().size());
                textDocument.print(&printer);
                textDocument.clear();
                printFlag= 1;
            }
                break;
            case 5:
            {
                qDebug()<<"A5";
                QPrinter printer;
                printer.setOrientation(QPrinter::Landscape);
                printer.setPageSize(QPrinter::A5);
                printer.setResolution(150);//设置像素
                QTextDocument textDocument;
                textDocument.setHtml(Printer_merge_A5(nTest));
                textDocument.setPageSize(printer.pageRect().size());
                textDocument.print(&printer);
                textDocument.clear();
                printFlag= 1;
            }
                break;
            default:
                return 1;
                break;
            }
        }
        else
        {
            while(nTest.Num.size())
            {
                qDebug()<<nTest.Num.size()<<"setPrintData"<<nTest.Num.head();
                st_Test setTest;
                setTest.Num<<nTest.Num.dequeue();//流水号
                setTest.SampleID<<nTest.SampleID.dequeue();//样本ID
                setTest.OriginalValue<<nTest.OriginalValue.dequeue();//原始值
                setTest.Result<<nTest.Result.dequeue();//校正值
                setTest.Name<<nTest.Name.dequeue();//姓名
                setTest.Sex<<nTest.Sex.dequeue();//姓名
                setTest.SampleType<<nTest.SampleType.dequeue();//样本类型
                setTest.SampleState<<nTest.SampleState.dequeue(); //样本状态
                setTest.Age<<nTest.Age.dequeue();//年龄
                setTest.AgeType<<nTest.AgeType.dequeue();//年龄
                setTest.SubmittedDept<<nTest.SubmittedDept.dequeue();//送检科室
                setTest.SubmittedBy<<nTest.SubmittedBy.dequeue();//送检医生
                setTest.ReviewedBy<<nTest.ReviewedBy.dequeue();//审核医生
                setTest.TestedBy<<nTest.TestedBy.dequeue();//检验医生
                setTest.Submitted<<nTest.Submitted.dequeue();//送检日期
                setTest.Tested<<nTest.Tested.dequeue();//检验日期
                setTest.Reported<<nTest.Reported.dequeue();//报告日期
                setTest.Refer<<nTest.Refer.dequeue();//参考范围
                setTest.Unit<<nTest.Unit.dequeue();//单位
                setTest.Project<<nTest.Project.dequeue();//项目
                setTest.BedNum<<nTest.BedNum.dequeue();//床号
                setTest.Phone<<nTest.Phone.dequeue();//电话
                setTest.Note<<nTest.Note.dequeue();//备注
                setTest.CaseNum<<nTest.CaseNum.dequeue();//病例号
                setTest.PatientsNum<<nTest.PatientsNum.dequeue();//患者编码
                setTest.Hint<<nTest.Hint.dequeue();//提示
                //            setTest.CalibrationTableID<<nTest.CalibrationTableID.dequeue();//校正表ID
                //            setTest.BitNum<<nTest.BitNum.dequeue();//位号

                //判断打印纸张
                //打印机状态非自动打印热敏0，外置2-A4，4-A5 //自动打印热敏1，外置3-A4，5-A5

                switch (Comom::CGlobal::getInstance()->getConfigData().m_PrintType) {
                case 0:
                {
                    QQueue<ISession *> *ssqueue=new QQueue<ISession *>;
                    PSession *sess=new PSession();
                    QString LineStr="\n\n\n";
                    qDebug()<<"Printer_In_Str(setTest)"<<Printer_In_Str(setTest);
                    QByteArray SetByt=Printer_In_Str(setTest).toLocal8Bit();
                    //SetByt.append(ImageToStrHex(DataToImage(setTest.CurveData.dequeue()).scaled(384,384,Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
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
                    QByteArray SetByt=Printer_In_Str(setTest).toLocal8Bit();
                    //SetByt.append(ImageToStrHex(DataToImage(setTest.CurveData.dequeue()).scaled(384,384,Qt::IgnoreAspectRatio, Qt::SmoothTransformation)));
                    SetByt.append(LineStr.toLocal8Bit());
                    sess->setdata(SetByt);
                    ssqueue->enqueue(sess);
                    printFlag= m_printmodule.sends(ssqueue);
                }
                    break;
                case 2:
                {
    //                qDebug()<<"A4";
    //                QPrinter printerPixmap;
    //                QPixmap pix = QPixmap(2479,3508);
    //                QString printStr=;
    //                printerPixmap.setOrientation(QPrinter::Portrait); //纵向：Portrait 横向：Landscape
    //                printerPixmap.setPageSize(QPrinter::A4);//设置纸张大小
    //                printerPixmap.setResolution(300);//设置像素
    //                QPainter painterPixmap;
    //                //选取打印机，特别重要
    //                //开始打印
    //                painterPixmap.begin(&printerPixmap);
    //                //设置图像在A4中的开始坐标是什么
    //                painterPixmap.drawPixmap(0,0,pix);
    //                painterPixmap.end();
    //                printFlag= 1;


                    QPrinter printer;
                    printer.setOrientation(QPrinter::Portrait);
                    printer.setPageSize(QPrinter::A4);
                    printer.setResolution(150);//设置像素
                    QTextDocument textDocument;
                    textDocument.setHtml(Printer_A4(setTest));
                    textDocument.setPageSize(printer.pageRect().size());
                    textDocument.print(&printer);
                    textDocument.clear();
                    printFlag= 1;



                }
                    break;
                case 3:
                {
                    QPrinter printer;
                    printer.setOrientation(QPrinter::Portrait);
                    printer.setPageSize(QPrinter::A4);
                    printer.setResolution(150);//设置像素
                    QTextDocument textDocument;
                    textDocument.setHtml(Printer_A4(setTest));
                    textDocument.setPageSize(printer.pageRect().size());
                    textDocument.print(&printer);
                    textDocument.clear();
                    printFlag= 1;
                }
                    break;
                case 4:
                {


                    QPrinter printer;
                    printer.setOrientation(QPrinter::Landscape);
                    printer.setPageSize(QPrinter::A5);
                    printer.setResolution(150);//设置像素
                    QTextDocument textDocument;
                    textDocument.setHtml(Printer_A5(setTest));
                    textDocument.setPageSize(printer.pageRect().size());
                    textDocument.print(&printer);
                    textDocument.clear();


    //                qDebug()<<"A5";
    //                QPrinter printerPixmap;
    //                QPixmap pix = QPixmap(2479,1750);
    //                Printer_A5(setTest,&pix);
    //                printerPixmap.setOrientation(QPrinter::Landscape); //纵向：Portrait 横向：Landscape
    //                printerPixmap.setPageSize(QPrinter::A5);//设置纸张大小
    //                printerPixmap.setResolution(300);//设置像素
    //                QPainter painterPixmap;
    //                //选取打印机，特别重要
    //                //开始打印
    //                painterPixmap.begin(&printerPixmap);
    //                //设置图像在A5中的开始坐标是什么
    //                painterPixmap.drawPixmap(0,0,pix);
    //                painterPixmap.end();
                    printFlag= 1;
                }
                    break;
                case 5:
                {
                    qDebug()<<"A5";
                    QPrinter printer;
                    printer.setOrientation(QPrinter::Landscape);
                    printer.setPageSize(QPrinter::A5);
                    printer.setResolution(150);//设置像素
                    QTextDocument textDocument;
                    textDocument.setHtml(Printer_A5(setTest));
                    textDocument.setPageSize(printer.pageRect().size());
                    textDocument.print(&printer);
                    textDocument.clear();
                    printFlag= 1;
                }
                    break;
                default:
                    return 1;
                    break;
                }
            }

        }
        return printFlag;
    }
*/










