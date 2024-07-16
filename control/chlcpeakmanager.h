#ifndef CHLCPEAKMANAGER_H
#define CHLCPEAKMANAGER_H
/////////////////////////////////////////
/// \brief The CDBManager class
/// 寻峰算法的使用
///
#include <QObject>
#include <QCoreApplication>
#include "cconfgmanager.h"



typedef struct Value{
    QString CalibrationID;//校正品ID
    QString OriginalValue;//原始值
    QString CalibrationValue;//校正值
    float alcArea;
    float allArea;
    QVector<double> xVector;
    QVector<double> yVector;
    QVector<double> gyVector;
    QVector<double> gxVector;
    QVector<double> m_xBaseV;
    QVector<double> m_yBaseV;
    QString PrintStr;
} st_Value;



namespace Control {

    class ChlcpeakManager : public QObject
    {
        Q_OBJECT
    public:
        static ChlcpeakManager * getInstance()
        {
            static ChlcpeakManager m_peakmgr(nullptr);
            return &m_peakmgr;
        }
        ~ChlcpeakManager()
        {
        }
    private:
        explicit ChlcpeakManager(QObject *parent = nullptr);
    public:
        void Init();
        static bool getBatchExist(QString batch);// 判断批号文件是否存在
        static QString getBarcodeToBatch (QString Barcode);//转换条码为批号
        static QString BarcodeToBatch (QString Barcode);//转换条码为批号
        QString getBtcInfoForPath(QString fileName);//从地址中获取Btc信息

    };

}


#endif // CHLCPEAKMANAGER_H
