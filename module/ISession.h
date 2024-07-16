#ifndef ISESSION_H
#define ISESSION_H
#include <QByteArray>
class ISession
{
public:
    virtual void settype(char type) = 0;
    virtual char  gettype() = 0;
    virtual void setcmd(char cmd) = 0;
    virtual char  getcmd() = 0;
    virtual QByteArray tostring() = 0;
    virtual void setdata(QByteArray data) = 0;
    virtual QByteArray getdata() = 0;
};

/*modbus需要*/
/* 读取：
 * 1、寄存器起始地址
 * 2、寄存器数量
 * 写入地址：
 * 1、寄存器去写入地址
 * 2、写入值
 * 写入线圈：
 * 1、写入地址
 * 2、写入线圈值
 */



#endif // ISESSION_H
