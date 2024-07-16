#include "ctools.h"
#include <QApplication>
namespace Comom
{
    CTools::CTools()
    {
    }

    int CTools::get_Timestamp(QString time_str)//Str转时间戳
    {
        QDateTime time;
        time = QDateTime::fromString(time_str, "yyyy/MM/dd hh:mm:ss");
        int ntime_t=time.toTime_t();
        return ntime_t;
    }

    int CTools::get_monthtamp(QString time_str)
    {
        QDateTime time;
        time = QDateTime::fromString(time_str, "yyyy/MM");
        int ntime_t=time.toTime_t();
        return ntime_t;
    }

    QString CTools::get_TimeStr(int time_t)//时间戳转str
    {
        QString nTimeStr;
        QDateTime nDatetime = QDateTime::fromTime_t(time_t);
        nTimeStr = nDatetime.toString("yyyy/MM/dd hh:mm:ss");
        return nTimeStr;
    }
    QString CTools::get_current_StrTime()//获取当前时间Str
    {
        QDateTime current_DateTime =QDateTime::currentDateTime();
        QString current_StrTime =current_DateTime.toString("yyyy/MM/dd hh:mm:ss");
        return current_StrTime;
    }

    void CTools::setTimeZone()
    {
        QDateTime currentTime = QDateTime::currentDateTime();//当前时区的当前时间
        QTimeZone currentZone = currentTime.timeZone();
        QString currentZoneId = currentZone.id();//当前时间的当前时区
    }

    QString CTools::fromGBKtoUtf8(QByteArray arry)
    {
        QTextCodec *gbk = QTextCodec::codecForName("gbk");
        QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
        QString unicode=gbk->toUnicode(arry);
        return QString(utf8->fromUnicode(unicode));
    }

    QByteArray CTools::fromUtf8toGBK(QString str)
    {
        QTextCodec *gbk = QTextCodec::codecForName("gbk");
        QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");
        QString unicode=utf8->toUnicode(str.toLocal8Bit());
        return gbk->fromUnicode(unicode);
    }

    QString CTools::HexToIEEE(QString nStr)//将16进制数值转为10进制IEEE
    {
        int hex = nStr.toUInt(0,16);
        float nIEEE = *(float*)&hex;
        QString nIEEEStr=QString::number(nIEEE,'f',6);
        if(nIEEEStr.toDouble()>10000)
        {
            nIEEEStr=QString::number(listIeee);
        }
        else if(nIEEEStr.toDouble()<-10000)
        {
            qDebug()<<"nIEEEStr"<<nIEEEStr;
            nIEEEStr=QString::number(listIeee);
        }
        else
        {
            listIeee=nIEEEStr.toDouble();
        }
        return nIEEEStr;
        //新转换方式
//        const QByteArray ba = QByteArray::fromHex(nStr.toLatin1());
//        if (ba.size() != 4){
//            return 0;
//        }
//        quint32 word = quint32((quint8(ba.at(0)) << 24) |
//                               (quint8(ba.at(1)) << 16) |
//                               (quint8(ba.at(2)) <<  8) |
//                               (quint8(ba.at(3)) <<  0));
//        const float *f = reinterpret_cast<const float *>(&word);
//        return QString::number(*f);


    }

    QString CTools::StrtoHex(QString Str)
    {
        return QString("%1").arg(Str.toInt(), 4, 16, QLatin1Char('0'));
    }

    QByteArray CTools::HexStrToByteArray(QString str)
    {
        QByteArray senddata;  //发送数据
        int hexdata,lowhexdata;
        int hexdatalen = 0;
        int len = str.length();  //求出发送字符传长度
        senddata.resize(len/2); //两个字符分割
        char lstr,hstr;
        for(int i=0; i<len; ) {
            hstr=str[i].toLatin1(); //本地字符
            if(hstr == ' ') {
                i++;
                continue;
            }
            i++;
            if(i >= len)
                break;
            lstr = str[i].toLatin1();
            hexdata = ConvertHexChar(hstr);
            lowhexdata = ConvertHexChar(lstr);
            if((hexdata == 16) || (lowhexdata == 16))
                break;
            else
                hexdata = hexdata*16+lowhexdata;
            i++;
            senddata[hexdatalen] = (char)hexdata;
            hexdatalen++;
        }
        senddata.resize(hexdatalen);
        qDebug()<<"senddata"<<senddata;
        return senddata;
    }
    char CTools::ConvertHexChar(char ch) //将16进制转换字符型
    {
        if((ch >= '0') && (ch <= '9'))
            return ch-0x30;
        else if((ch >= 'A') && (ch <= 'F'))
            return ch-'A'+10;
        else if((ch >= 'a') && (ch <= 'f'))
            return ch-'a'+10;
        else return (-1);
    }


    QString CTools::getDisk()
    {
        QFileInfoList list =  QDir::drives();  //获取当前系统的盘符
        qDebug()<<"驱动器数量： "<<list.count();
        for(int i=0;i<list.count();++i)
        {
            UINT driver_type = GetDriveType((WCHAR *) list[i].filePath().utf16());
            switch (driver_type) {
            case 0:
                qDebug()<<list[i].filePath()<<" "<<driver_type<<" 驱动类型不能确定";
                break;
            case 1:
                qDebug()<<list[i].filePath()<<" "<<driver_type<<" 根路径无效";
                break;
            case 2:
                qDebug()<<list[i].filePath()<<" "<<driver_type<<" 可移动驱动器：软盘驱动器，拇指驱动器或闪存卡读取器";
                return list[i].filePath();
                break;
            case 3:
                qDebug()<<list[i].filePath()<<" "<<driver_type<<" 固定驱动器：硬盘驱动器或闪存驱动器";
                break;
            case 4:
                qDebug()<<list[i].filePath()<<" "<<driver_type<<" 远程（网络）驱动器";
                break;
            case 5:
                qDebug()<<list[i].filePath()<<" "<<driver_type<<" CD-ROM驱动器";
                break;
            case 6:
                qDebug()<<list[i].filePath()<<" "<<driver_type<<" RAM磁盘";
                break;
            default:
                break;
            }
        }
        return "NODisk";
    }

    int CTools::setPathData(QString newFile, QString oldFile)//将文件拷贝至新文件
    {
        qDebug()<<"newFile"<<newFile;
        qDebug()<<"oldFile"<<oldFile;
        int nState=-1;
        //判断目标文件是否存在
        if (!QFile::exists(oldFile))
        {
            //文件不存在
            nState=0;
        }
        else
        {
            //判断是否有同名文件是否存在
            if (!QFile::exists(newFile))
            {
                //无->文件导入成功
                if(QFile::copy(oldFile, newFile))
                {
                    nState=1;
                }
                else
                {
                    nState=-2;
                }
            }
            else
            {
                //有->文件覆盖成功
                //执行删除
                if(QFile::remove(newFile))
                {
                    if(QFile::copy(oldFile, newFile))
                    {
                        nState=2;
                    }
                }
                else
                {
                    if(QFile::copy(oldFile, newFile))
                    {
                        nState=2;
                    }
                    else
                    {
                        nState=-3;
                    }
                }
            }
        }
        qDebug()<<"nState"<<nState;
        return nState;
    }

    bool CTools::setCSVFile(QString nFileStr, QString nCSVStr)
    {
        bool nState;
        QFile data(nFileStr);
        if(data.open(QIODevice::Text|QFile::WriteOnly|QIODevice::Truncate))
        {
            nState=true;
            QTextStream out(&data);
            out<<nCSVStr;
        }
        else
        {
            nState=false;
        }
        data.flush();
        data.close();
        return nState;
    }

    //函数计算平均值。
    double CTools::cal_mean(double arr[], int size)
    {
        double sum = 0;
        for (int i = 0; i < size; i++)
        sum = sum + arr[i];
        return sum / size;
    }

    //计算标准偏差的功能
    double CTools::StandardDeviation(double arr[], int size)
    {
       double sum = 0;
       for (int i = 0; i < size; i++)
       sum = sum + (arr[i] - cal_mean(arr, size)) * (arr[i] - cal_mean(arr, size));
       return sqrt(sum / (size - 1));
    }
    //函数来计算变异系数。
    double CTools::CoefficientOfVariation(double arr[], int size)
    {
        return StandardDeviation(arr, size) / cal_mean(arr, size);
    }

    void CTools::setdelaymTime(int msec) //毫秒级延时
    {
        QTime dieTime = QTime::currentTime().addMSecs(msec);
        while( QTime::currentTime() < dieTime )
        {
            QCoreApplication::processEvents(QEventLoop::AllEvents);
        }
    }
    //发送Windows关机命令
    void CTools::setWinShutdown()
    {
        qDebug()<<"发送Windows关机命令";
//        system("shutdown -s -t 00");//立马关机
        QApplication::quit();
    }

}
