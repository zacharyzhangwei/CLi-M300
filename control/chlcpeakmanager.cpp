#include "chlcpeakmanager.h"


namespace Control {

    ChlcpeakManager::ChlcpeakManager(QObject *parent) : QObject(parent)
    {
    }

    void ChlcpeakManager::Init()
    {
    }

    //从地址中获取Btc信息
    QString ChlcpeakManager::getBtcInfoForPath(QString fileName)
    {
        QByteArray line;
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            return "-1";
        }
        else
        {
            line = file.readAll();
        }
        file.close();
        QString BtcStr(line.toHex());
        return BtcStr;
    }


    //判断批号文件是否存在
    bool ChlcpeakManager::getBatchExist(QString batch)
    {
        QString BatchBtc = batch+".btc";
        if(QFile::exists(DEFAULT_BTC_PATH+"/"+BatchBtc))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //转换条码为批号
    QString ChlcpeakManager::getBarcodeToBatch(QString Barcode)
    {
        if (Barcode.indexOf("\r") != -1)
            Barcode = Barcode.replace("\r", "");
        if (Barcode.indexOf("\n") != -1)
            Barcode = Barcode.replace("\n", "");
        qDebug()<<"Barcode"<<Barcode;
        return  Barcode;
    }

    QString ChlcpeakManager::BarcodeToBatch(QString Barcode)
    {
        if (Barcode.indexOf("\r") != -1)
            Barcode = Barcode.replace("\r", "");
        if (Barcode.indexOf("\n") != -1)
            Barcode = Barcode.replace("\n", "");
        qDebug()<<"Barcode"<<Barcode;
        return  Barcode;
    }





}
