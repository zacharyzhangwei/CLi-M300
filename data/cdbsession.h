#ifndef CSQLSESSION_H
#define CSQLSESSION_H

#include <QObject>
#include <QDebug>
#include <QQueue>
#include "data/IDBSession.h"

//UserTable 用户表
typedef struct UserTable{
    QString ID;//用户名
    QString Password;//密码
    int Permissions;//权限
    QString Dept;//科室
    QString Contact;//联系方式
    QString Name;//姓名
} st_User;

//QCSampleTable 质控品表
typedef struct QCSampleTable{
    int Num;//流水号
    QString Project;//项目名称
    QString Batch;//质控批号
    QString Source;//来源
    int Level;//水平
    double Value;//靶值
    double SD;//SD
    QString Unit;//单位
    int Type;//类型（设备OR试剂）
} st_QCSample;

//QCResultTable 质控表
typedef struct QCTable{
    QString QCSampleNum;//质控品流水号
    int Time;//质控时间
    int BitNum;//位号
    int State;//在控状态 未质控=0 脱靶未审核=1 在控未审核=2 脱靶已审核=3 在控已审核=4 过期=5
    double Value;//检测值
    QString TestBy;//操作医生
    QString ExamineBy;//审核医生
} st_QCResult;

//ItemTable 项目表
typedef struct ItemTable{
    QString ProjectName;//项目名称
    QString ChName;//中文名
    double MinValue;//最小值
    double MaxValue;//最大值
    QString PrintRefer;//打印参考范围
    double CrisisValue;//危急值
    QString Clinical;//临床意义
    int TestTime;//测试时间(s)
    QString Unit;//单位
    double Ratio;//比率
    QString NewUnit;//新单位
    int Language;//语言
} st_Item;

//BatchTable批次表
typedef struct BatchTable{
    QString Batch;//批号
    QString Project;//项目
    double Ratio;//数量
} st_Batch;

//TestResultTable 测试结果表
typedef struct TestResult{
    int TestNum;//测试列表流水号
    QString Project;//项目名称
    QString Result;//结果
    QString Refer;//参考范围
    QString Unit;//单位
    QString Hint;//结果提示（箭头）
    int CardIndex;//联卡号
} st_TestResult;

//TestInfoTable 测试信息表
typedef struct TestInfo{
    int Num;//流水号
    QString SampleID;//样本ID
    QString Name;//姓名
    int Sex;//性别
    int Age;//年龄
    int AgeType;//年龄类型
    QString SubmittedDept;//送检科室
    int SampleType;//样本类型
    int SampleState;//样本状态
    QString SubmittedBy;//送检医生
    QString ReviewedBy;//审核医生
    QString TestedBy;//检验医生
    QString CaseNum;//病例号
    QString PatientsNum;//患者编码
    QString Phone;//电话
    QString BedNum;//床号
    QString Note;//备注
    int Submitted;//送检日期
    int Tested;//检验日期
    int Reported;//报告日期
    int CardNumber;//联卡数
    QString Batch;//批号
    QString CurveData;//曲线数据
    QQueue<st_TestResult> resultList;//结果列表
} st_TestInfo;


Q_DECLARE_METATYPE(st_User)
Q_DECLARE_METATYPE(st_QCSample)
Q_DECLARE_METATYPE(st_QCResult)
Q_DECLARE_METATYPE(st_Item)
Q_DECLARE_METATYPE(st_Batch)
Q_DECLARE_METATYPE(st_TestInfo)
Q_DECLARE_METATYPE(st_TestResult)





namespace  Data
{
    class CDBSession : public QObject,public IDBSession
    {
        Q_OBJECT
    public:
        explicit CDBSession(QObject *parent = nullptr);
        virtual ~CDBSession()override{};
    public:
        virtual void setcmd(enum_db_cmd cmd);
        virtual enum_db_cmd  getcmd();
    private:
        enum_db_cmd  m_cmd;     //请求命令
    //用户信息
    public:
        QQueue<st_User> getUserList();
        void setUserList(QQueue<st_User> userList);
        QString getPasswd();//密码
        void setPasswd(QString sPasswd);
        int getPermissions();//权限
        void setPermissions(int sPermissions);
        QString getDept();//科室
        void setDept(QString sDept);
        QString getContact();//联系方式
        void setContact(QString sContact);
        QString getUserID();
        void setUserID(QString id);
        void setUseradd(st_User user_Add);
        void setUserName(QString sName);
        QString getUserName();//姓名
        st_User getUserInfo();
        st_User getUserAdd();
        void set_allUser(QQueue<st_User> alluserList);
        QQueue<st_User> get_allUser();
        void setUserInfo(st_User userInfo);



    private:
        QQueue<st_User> m_UserList;
        st_User mCDB_User;
        QString m_ID;
        st_User m_UserInfo;
        int m_maxTestNum;
        st_User madd_User;
        QQueue<st_User> m_allUser;



    };


//    class CDBSessionUser:public CDBSession//用户信息操作
//    {
//    public:
//        CDBSessionUser(){};
//        virtual ~CDBSessionUser()override{};
//        QQueue<st_User> getUserList();//ID
//        void setUserList(QQueue<st_User> userList);
//    private:

//        QQueue<st_User> m_UserList;
//    };



}

#endif // CSQLSESSION_H
