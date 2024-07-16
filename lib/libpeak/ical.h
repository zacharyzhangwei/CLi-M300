#ifndef ICAL_H
#define ICAL_H

#include <QtCore/qglobal.h>

#if defined(ANLYSISCAL_LIBRARY)
#  define ANLYSISCALSHARED_EXPORT Q_DECL_EXPORT
#else
#  define ANLYSISCALSHARED_EXPORT Q_DECL_IMPORT
#endif

#include <QVector>


enum code_err{
    em_successfull,
    em_findpeak_err, //寻峰错误
    em_guassfit_err,//高斯拟合失败
    em_lineAndGua_err//基线与高斯交叉位置查找失败
};
struct stu_peak
{
    int s;
    int e;
    int center;
};

class ICal
{
public:
    virtual code_err getlasterr() = 0;                                                  //获取错误码
    virtual bool    setData(float* data, int len) =0;                                   //设置数据
    virtual bool    getbaseline(int x1,int x2,float &y)= 0;                             //获取基线
    virtual bool    setsmooth(int wlen) =0;                                             //设置平滑的窗口
    virtual bool    setdistance(int st=42,int et=48,int all=150) =0;                    //st：起始，et结束地址  //初始设置出峰的范围
    virtual bool    findpeak(int ds =0,int h=0) =0;                                     //ds峰间距 h 峰的高度   //开始寻峰
    virtual bool    gethabA1cbyGause(QVector<float> &gy,int &x1,int &x2,float &alcArea,float &allArea) =0; //获取高斯阴影部分以及起始位置

    virtual bool    gethabA1cby2Gause(QVector<float> &gy,int &x1,int &x2,float &alcArea,float &allArea) =0; //获取通过两套高斯拟合的阴影部分面积

    virtual bool    setsolventds(int stime,int etime)=0;
    virtual bool    findsolventpeak(int &x1,int &x2,int &center,float &area,float val=0.5)=0;   //查找溶剂峰-1

    virtual bool    sethbf(int stime,int etime) =0;
    virtual bool    findhbf(int &x1,int &x2,int &center,float &area,float val=0.5) = 0;         //查找F峰-1

    virtual bool    setlhba1cds(int stime,int etime) = 0;
    virtual bool    findlhba1c(int &x1,int &x2,int &center,float &area,float val= 0.5) = 0;     //查找 不稳定的糖化蛋白峰
    virtual bool    findotherpeaks(int s,int e,QVector<stu_peak> &peasks)  = 0;
};

extern "C" ANLYSISCALSHARED_EXPORT ICal * CreateCal();
extern "C" ANLYSISCALSHARED_EXPORT void destroyCal(ICal * cal);
#endif // ICAL_H
