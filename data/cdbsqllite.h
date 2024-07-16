#ifndef CSQLLITE_H
#define CSQLLITE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>


namespace  Data
{
class CSQLLite: public QObject
{
    Q_OBJECT
public:
    CSQLLite();
    virtual ~CSQLLite();
public:
    void init();
    QSqlQuery sql_query(QString sql);
    bool sql_execute(QString sql);
    void setEstablishDB();//创建DB文件
    void addTableList(QString tableName,QString columnName);//修改列表，添加列
private:
    QSqlDatabase m_db;
};
}
#endif // CSQLLITE_H








