#ifndef CCONFIGURE_H
#define CCONFIGURE_H
#include <QSettings>
#include <QObject>
#include <QVariant>
#include "globals.h"
#include <QQueue>
#include <QMutex>
#include <QTimer>
#include <QMetaEnum>

#pragma execution_character_set("utf-8")
namespace Comom
{
class CConfigure: public QObject
{
    Q_OBJECT
public:
    CConfigure();
    void init(QString strPath);
    void setParam(EM_SETTINGS_IDX idx, QVariant val);
    QVariant getParam(EM_SETTINGS_IDX idx);
 //   bool contains(EM_SETTINGS_IDX idx);
    void setParamList(QQueue <EM_SETTINGS_IDX> idxList, QQueue <QVariant> valList );
     QQueue <QVariant> getParamList();

private:
    QSettings  *m_settings;

};

}
#endif // CCONFIGURE_H

