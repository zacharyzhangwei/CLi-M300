#ifndef CRECORDMANGER_H
#define CRECORDMANGER_H
/////////////////////////////////////////
/// \brief The CDBManager class
/// 历史记录的相关逻辑
///
#include <QObject>
#include "cdbmanager.h"
#include "data/cdbsession.h"
#include <QVector>
namespace Control
{
class CRecordManger: public QObject
{
    Q_OBJECT
public:
    static CRecordManger * getInstances()
    {
        static CRecordManger s_msgRouter;
        return &s_msgRouter;
    }
private:
    CRecordManger();
public:
    bool getRecordInit();
public:
};
}
#endif // CRECORDMANGER_H
