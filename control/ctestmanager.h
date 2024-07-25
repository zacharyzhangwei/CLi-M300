#ifndef CTESTMANAGER_H
#define CTESTMANAGER_H
#include "control/imhelper.h"
#include <QObject>
#include "cdbsession.h"
#include "control/chlcpeakmanager.h"
#include <QQueue>


typedef struct Patient{
    int csNum;
    QString SampleID;//样本ID
    QString Name;//姓名
    int Sex;//性别
    int Age;//年龄
    int AgeType;//年龄类型
    int SampleType;//样本类型
    int SampleState;//样本状态
    QString SubmittedDept;//送检科室
    QString BilledBy;//开单医生
    QString SubmittedBy;//送检医生
    QString ReviewedBy;//审核医生
    QString TestedBy;//检验医生
    QString CaseNum;//病例号
    QString PatientsNum;//患者编码
    QString Phone;//电话
    QString BedNum;//床号
    QString Note;//备注
    QString Batch;//批号
    QString Project;//项目名称
    double OriginalValue;//原始值
    double Result;//结果
    QString Unit;//单位
    QString Hint;//提示
    QString Refer;//参考范围
    QString Submitted;//送检日期
    QString Tested;//检验日期
    QString Reported;//报告日期
} st_Patient;

enum enum_Test_Cmd
{
    enum_Test_Null,//空闲
    enum_Test_Self,//自检
    enum_Test_Init,//初始化
    enum_Test_RESET,//设备重置
    enum_Test_PushAir,//排液
    enum_Test_Scan,//扫码
    enum_Test_PreAction,//前处理（离心）
    enum_Test_DevTest,//分步法测试
    enum_Test_St,//一步法测试
};


namespace Control
{
    class CTestManager: public QObject
    {
        Q_OBJECT
    private:
        CTestManager();
    public:
        static CTestManager * getInstances()
        {
            static CTestManager s_msgRouter;
            return &s_msgRouter;
        }
        void setPatient1(st_Patient nPatientInfo);
        st_Patient getPatient1();
        int getNumPatient();
        enum_Test_Cmd m_Cmd=enum_Test_Null;//默认开机自检
        int get_value(QString dataHigh,QString dataLow);//采集点转换

    signals:


    private:
        st_Patient plate_1;
        st_Patient plate_2;
        st_Patient plate_3;
        int m_SerialNum;

    public slots:


    };

}
#endif // CTESTMANAGER_H
