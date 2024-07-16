#ifndef CTOOLS_H
#define CTOOLS_H

#include <QObject>
#include <QDateTime>
#include <QTimeZone>
#include <QDebug>
#include <QImage>
#include <QTextCodec>
#include <QBitmap>
#include <QPainter>
#include <QFile>
#include <QDir>
#include <QStorageInfo>
#include <QCoreApplication>
#include <windows.h>
#include <thread>
#include <QtCore/qmath.h>

#pragma execution_character_set("utf-8")
namespace Comom
{
    class CTools: public QObject
    {
        Q_OBJECT
    public:
        CTools();
        int get_Timestamp(QString time_str);//str转时间戳
        int get_monthtamp(QString time_str);//str转时间戳月份
        QString get_TimeStr(int time_t);//时间戳转str
        QString get_current_StrTime();//获取当前时间Str
        void setTimeZone();
        QString  fromGBKtoUtf8(QByteArray arry);
        QByteArray fromUtf8toGBK(QString str);
        QString HexToIEEE(QString nStr);
        QString StrtoHex(QString Str);
        static QByteArray HexStrToByteArray(QString str); //16进制字符串转字节数组
        static char ConvertHexChar(char ch); //将16进制转换字符型

        QString getDisk();//获取盘符
        int setPathData(QString newFile, QString oldFile);//拷贝至目标文件夹
        bool setCSVFile(QString nFileStr,QString nCSVStr);//保存CSV文件
        double listIeee;

        //函数计算平均值。
        double cal_mean(double arr[], int size);
        //计算标准偏差的功能
        double StandardDeviation(double arr[], int size) ;
        //函数来计算变异系数。
        double CoefficientOfVariation(double arr[], int size);
        //延时函数，用于非阻塞延时
        void setdelaymTime(int msec);
        //发送Windows关机命令
        void setWinShutdown();



    };

}
#endif // CTOOLS_H
