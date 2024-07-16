#include "cdbsqllite.h"
#include "common/cglobal.h"

#include <QApplication>
namespace  Data
{
    CSQLLite::CSQLLite()
    {

    }

    void CSQLLite::init()
    {
        QFileInfo file(QCoreApplication::applicationDirPath()+"/CLi-M300.db");
        if(file.exists()==false)
        {
            qDebug()<<"数据库丢失自建设";
            BTLOG->print(e_debug,"%s,%d","dbErorr",230420);
            m_db=QSqlDatabase::addDatabase("QSQLITE");
            m_db.setDatabaseName("CLi-M300.db");
            m_db.open();
            m_db.lastError();
            setEstablishDB();
        }
        else
        {
            m_db = QSqlDatabase::addDatabase("QSQLITE");
            m_db.setDatabaseName("CLi-M300.db");
            if(!m_db.open())
            {
               PRINT_LOG_ERROR("%s","sqllite连接失败");
            }
            m_db.lastError();
           // addTableList("TestTable","UploadState");
        }


    }
    CSQLLite::~CSQLLite()
    {
        m_db.close();
    }

    QSqlQuery CSQLLite::sql_query(QString sql)
    {
        qDebug()<<"sql"<<sql;
        QSqlQuery sql_query;
        if(sql_query.exec(sql))
        {
            return sql_query;
        }
    }

    bool CSQLLite::sql_execute(QString sql)
    {
        QSqlQuery sql_query;
        if(sql_query.exec(sql))
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void CSQLLite::setEstablishDB()
    {
        QSqlQuery sqlSql;
        QSqlQuery estabSql;
        QString selStr=QString("SELECT COUNT(*) FROM sqlite_master");


        QString calibStr="CREATE TABLE [CalibrationTable]("
                "[Num] INTEGER PRIMARY KEY AUTOINCREMENT,"
                "[Batch] CHAR,"
                "[aValue] DOUBLE,"
                "[bVlaue] DOUBLE,"
                "[aData1] CHAR,"
                "[aData2] CHAR,"
                "[bData1] CHAR,"
                "[bData2] CHAR,"
                "[Time] CHAR);";

         QString itemStr="CREATE TABLE [ItemTable]("
                "[ProjectName] CHAR,"
                "[ChName] CHAR,"
                "[MinValue] CHAR,"
                "[MaxValue] CHAR,"
                "[PrintRefer] CHAR,"
                "[CrisisValue] CHAR,"
                "[Clinical] CHAR,"
                "[TestTime] CHAR,"
                "[Unit] CHAR,"
                "[Ratio] CHAR,"
                "[NewUnit] CHAR,"
                "[Language] CHAR,"
                "[Lot] CHAR,"
                "[SampleType] CHAR);";

        QString qcSampleStr="CREATE TABLE [QCSampleTable]("
                "[Num] INTEGER PRIMARY KEY AUTOINCREMENT,"
                "[Project] CHAR,"
                "[Batch] CHAR,"
                "[Level] CHAR,"
                "[TargetValue] CHAR,"
                "[SD] CHAR,"
                "[Unit] CHAR);";

        QString qcStr="CREATE TABLE [QCTable]("
                "[QCSampleNum] CHAR,"
                "[Time] CHAR,"
                "[BitNum] CHAR,"
                "[State] CHAR,"
                "[Value] CHAR,"
                "[TestBy] CHAR,"
                "[ExamineBy] CHAR,"
                "[SampleType] CHAR);";



        QString testStr="CREATE TABLE [TestTable]("
                "[Num] INTEGER PRIMARY KEY AUTOINCREMENT,"
                "[SampleID] CHAR,"
                "[CalibrationTableID] CHAR,"
                "[Name] CHAR,"
                "[Sex] CHAR,"
                "[Age] CHAR,"
                "[AgeType] CHAR,"
                "[SubmittedDept] CHAR,"
                "[SampleType] CHAR,"
                "[SampleState] CHAR,"
                "[SubmittedBy] CHAR,"
                "[ReviewedBy] CHAR,"
                "[TestedBy] CHAR,"
                "[CaseNum] CHAR,"
                "[PatientsNum] CHAR,"
                "[Phone] CHAR,"
                "[BedNum] CHAR,"
                "[Note] CHAR,"
                "[Batch] CHAR,"
                "[Project] CHAR,"
                "[OriginalValue] CHAR,"
                "[Result] CHAR,"
                "[Unit] CHAR,"
                "[Hint] CHAR,"
                "[Refer] CHAR,"
                "[Submitted] CHAR,"
                "[Tested] CHAR,"
                "[Reported] CHAR,"
                "[UploadState] CHAR);";

        QString userStr="CREATE TABLE [UserTable]("
                "[ID] CHAR,"
                "[Password] CHAR,"
                "[Permissions] INT,"
                "[Dept] CHAR,"
                "[Contact] CHAR,"
                "[Name] CHAR);";

        QString addUserStr=QString("insert into UserTable values('admin','1','511','宝太生物','400-0532-711','管理员')");
        if(sqlSql.exec(selStr))
        {
            qDebug()<<"selStr"<<selStr;
            if(estabSql.exec(calibStr))
            {
                qDebug()<<"calibStr"<<calibStr;
                if(estabSql.exec(itemStr))
                {
                    qDebug()<<"itemStr"<<itemStr;
                    if(estabSql.exec(qcSampleStr))
                    {
                        qDebug()<<"qcSampleStr"<<qcSampleStr;
                        if(estabSql.exec(qcStr))
                        {
                            qDebug()<<"qcStr"<<qcStr;
                            if(estabSql.exec(testStr))
                            {
                                qDebug()<<"testStr"<<testStr;
                                if(estabSql.exec(userStr))
                                {
                                    qDebug()<<"userStr"<<userStr;
                                    if(estabSql.exec(addUserStr))
                                    {
                                        qDebug()<<"addUserStr"<<addUserStr;
                                        BTLOG->print(e_debug,"%s,%d","dbAddOver",230420);

                                        QString btcPath = DEFAULT_BTC_PATH;
                                        QDir btcDir(btcPath);
                                        if(btcDir.exists())
                                        {
                                            QStringList filters;
                                            filters<<QString("*.btc");
                                            btcDir.setFilter(QDir::Files | QDir::NoSymLinks); //设置类型过滤器，只为文件格式
                                            btcDir.setNameFilters(filters);  //设置文件名称过滤器，只为filters格式
                                            //统计log格式的文件个数
                                            int dirCount = btcDir.count();
                                            if(dirCount > 0)
                                            {
                                                //存储文件名称
                                                for(int i=0; i<dirCount; i++)
                                                {
                                                    QString file_name = btcDir[i];  //文件名称
                                                    QFile::remove(btcPath+"/"+file_name);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    void CSQLLite::addTableList(QString tableName, QString columnName)
    {
        QStringList columnList;
        QSqlQuery sql_NameColumnQuery;
        QString sql_ColumnNameStr=QString("PRAGMA table_info("+tableName+")");
        if(sql_NameColumnQuery.exec(sql_ColumnNameStr))
        {
            while(sql_NameColumnQuery.next())
            {
                columnList<<sql_NameColumnQuery.value(1).toString();
            }
        }
        qDebug()<<"columnList"<<columnList;
        if((!columnList.contains(columnName))&&columnList.size())
        {
            qDebug()<<"columnName"<<columnName;
            QSqlQuery sql_ColumnQuery;
            QString sql_AddcoulumnStr="alter table "+tableName+" add column "+columnName+" CHAR";
            if(sql_ColumnQuery.exec(sql_AddcoulumnStr))
            {
                QSqlQuery sql_State;
                QString sqlStr_State="update "+tableName+" set "+columnName+"=0";
                if(sql_State.exec(sqlStr_State))
                {
                    qDebug()<<"addColumnName";
                }
            }
        }
    }
}
