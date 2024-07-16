#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QDir>
#include <QString>
#include <Windows.h>
#include <wingdi.h>
#include <WinUser.h>
#include <DbgHelp.h>
#include "module/4g/runguard.h"
//#include "vld.h"

/*
功能: 程序异常捕获接口
*/
LONG ExceptionCapture(EXCEPTION_POINTERS *pException)
{
    //当前时间串
    const int TIMESTRLEN = 32;
    WCHAR timeStr[TIMESTRLEN];
    SYSTEMTIME time;
    GetLocalTime(&time);
    swprintf_s(timeStr, TIMESTRLEN, L"%4d%02d%02d%02d%02d%02d", time.wYear, time.wMonth, time.wDay, time.wHour, time.wMinute, time.wSecond);
    WCHAR strname[MAX_PATH];
    swprintf_s(strname, MAX_PATH, L"application_%s.dmp", timeStr);

    //创建 Dump 文件
    HANDLE hDumpFile = CreateFile(strname, GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if( hDumpFile != INVALID_HANDLE_VALUE)
    {
        //Dump信息
        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ExceptionPointers = pException;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ClientPointers = TRUE;
        //写入Dump文件内容
        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, nullptr, nullptr);
    }

    //完成一些数据保存工作
    //.....

    //弹出错误对话框并退出程序
    QMessageBox::critical(nullptr,"错误提示",QString("当前程序遇到异常;\n请在关机后断电重启").arg(QString::fromWCharArray(strname)),QMessageBox::Ok,QMessageBox::Ok);
    return EXCEPTION_EXECUTE_HANDLER;
}

int main(int argc, char *argv[])
{

    //判断软件启动的唯一性
    RunGuard guard("FLI-1200");
    if (!guard.tryToRun()) {
        return 0;
    }

   // qDebug()<<"SetDllDirectoryA"<<SetDllDirectoryA("C:\\Windows\\SysWOW64\\version.dll");
    QApplication a(argc, argv);
    //注冊异常捕获函数
    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ExceptionCapture);

    //设置外置字体
    QDir::setCurrent(QCoreApplication::applicationDirPath());
    int fontID=QFontDatabase::addApplicationFont(":/font/font/Alibaba-PuHuiTi-Medium.otf");
    QString PingFangSC=QFontDatabase::applicationFontFamilies ( fontID ).at(0);
    QFont font(PingFangSC,10);
    a.setFont(font);
    //替换数据库
    QString newFileName = QCoreApplication::applicationDirPath()+"/FLI1200.db";//获取程序Btc文件目录
    QString oldFileName = QCoreApplication::applicationDirPath()+"/newFLI1200.db";//获取程序Btc文件目录
    if(Comom::CGlobal::getInstance()->getTools()->setPathData(newFileName,oldFileName)>0)
    {
        if(QFile::remove(oldFileName))
        {
            qDebug()<<"替换数据库";
        }
    }


    //日志文件夹
    QString pathLogStr=QCoreApplication::applicationDirPath()+"/Log";
    //旧文件备份文件夹
    QString patholdApkStr=QCoreApplication::applicationDirPath()+"/oldApk";
    //更新压缩包备份文件夹
    QString pathapkStr=QCoreApplication::applicationDirPath()+"/apk";
    //更新文件接收文件夹
    QString pathupadteApkStr=QCoreApplication::applicationDirPath()+"/upadteApk";
    //图片文件夹
    QString pathimagesStr=QCoreApplication::applicationDirPath()+"/images";
    //语言包文件夹
    QString pathLangStr=QCoreApplication::applicationDirPath()+"/Lang";
    //手写签名文件夹
    QString pathSignatureStr=QCoreApplication::applicationDirPath()+"/Signature";
    //btc文件夹
    QString pathBtcDataStr=QCoreApplication::applicationDirPath()+"/BtcData";

    // 判断此目录文件是否存在,不存在创建
    QDir dir(pathLogStr);
    if (!dir.exists(pathLogStr))
    {
        dir.mkdir(pathLogStr);
    }
    if (!dir.exists(patholdApkStr))
    {
        dir.mkdir(patholdApkStr);
    }
    if (!dir.exists(pathapkStr))
    {
        dir.mkdir(pathapkStr);
    }
    if (!dir.exists(pathupadteApkStr))
    {
        dir.mkdir(pathupadteApkStr);
    }
    if (!dir.exists(pathimagesStr))
    {
        dir.mkdir(pathimagesStr);
    }
    if (!dir.exists(pathLangStr))
    {
        dir.mkdir(pathLangStr);
    }
    if (!dir.exists(pathSignatureStr))
    {
        dir.mkdir(pathSignatureStr);
    }
    if (!dir.exists(pathBtcDataStr))
    {
        dir.mkdir(pathBtcDataStr);
    }




    Comom::CGlobal::getInstance()->m_lang = Control::CConfgManager::getInstance()->getLang();
    QTranslator *translator = new QTranslator();
    QString sPath = QDir::currentPath();
    QString strLangPath=sPath;
    strLangPath+="/Lang/gtsoft";
    switch (Comom::CGlobal::getInstance()->m_lang) {
    case LANG_BIO_ENGLISH:
         strLangPath+="_en.qm";
        break;
    case LANG_BIO_CHINESE:
        strLangPath+="_zh.qm";
        break;
    case LANG_BIO_CHINESE_C:
        strLangPath+="_ts.qm";
        break;
    default:
        strLangPath+="_zh";
        break;
    }
    translator->load(strLangPath);
    qApp->installTranslator(translator);

    MainWindow w;
    w.setWindowTitle("FLI-1200");
    if(Control::CConfgManager::getInstance()->getWindowInfo()==1)
        w.show();//showFullScreen
    else
        w.showFullScreen();//showFullScreen

    return a.exec();
}
