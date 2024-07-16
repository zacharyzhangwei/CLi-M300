#include "modbustool.h"
#include <QThread>
ModbusTool::ModbusTool(QObject *parent) : QObject(parent)
{
    ctx =nullptr;

    req16[125] = {0};
    req8[100] = {0};
    regs = 0;

}

ModbusTool::~ModbusTool()
{

}

QStringList ModbusTool::getPortNameList()
{
    QStringList m_serialPortName;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        m_serialPortName << info.portName();
    }
    return m_serialPortName;
}

/*
 * @FuncName   函数名:modbus连接函数
 * @Function   功能：连接modbus串口
 * @param Com_str 串口号0
 * Baud_str 波特率
 * @return 成功返回true
 */
bool ModbusTool::Modbus_connect(int nCom,int nBaud)
{
    qDebug()<<"ctx"<<nCom;
    //qDebug()<<"Com_str"<<Com_str<<"nBaud"<<nBaud;


    QString Com_str;
    if(nCom>9)
    {
        Com_str="\\\\.\\";
    }
    Com_str+="COM"+QString::number(nCom);
    if(ctx == nullptr)
    {
        ctx = modbus_new_rtu(Com_str.toStdString().c_str(), nBaud, 'N', 8, 1);
        modbus_set_slave(ctx,1); //设置modbus从机地址
    }
    else
    {
        qDebug()<<"modbus不为空开启";
        return true;
    }
    if (modbus_connect(ctx) == -1)//开启失败
    {
        qDebug()<<"modbus开启失败";
        modbus_free(ctx);
        ctx = nullptr;
        return false;
    }
    else
    {
        modbus_set_response_timeout(ctx, 0, 3000000);//modbus超时时间为3000毫秒
        qDebug()<<"modbus开启成功";
        m_Com=nCom;
        m_Baud=nBaud;
        return true;
    }
}

bool ModbusTool::reconnect_modbus()
{
    if(disconnect_modbus()) {
           return Modbus_connect(m_Com,m_Baud);
       }
       return false;
}
/*
 * @FuncName   函数名:modbus断连函数
 * @return 返回值无
 */
bool ModbusTool::disconnect_modbus()
{
    if(ctx == nullptr) {
        return true;
    }
    modbus_close(ctx);
    modbus_free(ctx);
    ctx = nullptr;
    return true;
}

/*
 * @FuncName   函数名:上位机向下位机的某个寄存器写入数据
 * @Function   功能：上位机向下位机的某个寄存器写入数据
 * @param 参数regStartAddr 下位机寄存器起始地址
 * data 写入数据
 * @return 返回值无
 */

int ModbusTool::Write_Client(unsigned int regStartAddr, unsigned int data)
{
    uint16_t _data = data;
    int writeFlag=modbus_write_register(ctx, regStartAddr, _data);
    //qDebug()<<"Write_Client"<<writeFlag;
    return writeFlag;

}

/*
 * @FuncName   函数名:上位机向下位机的某个线圈写入数据
 * @Function   功能：05模式向下位机的某个线圈写入数据
 * @param 参数regStartAddr 下位机寄存器起始地址
 * number 写入数据
 * @return 返回值无
 */

int ModbusTool::Write_Bit_Client(unsigned int regStartAddr, unsigned int data)
{
    int writeFlag=modbus_write_bit(ctx, regStartAddr, data);
    //qDebug()<<"Write_Bit_Client"<<writeFlag;
    return writeFlag;
    //modbus_write_bits(ctx, regStartAddr, cnt, data);//cnt
}

/*
 * @FuncName   函数名:从指定下位机寄存器处读取数据
 * @Function   功能：0x03读模式，读取下位机数据
 * @param startAddress 下位机寄存器起始地址
 * @param endAddress 数据量
 * @return 返回值无
 */

bool ModbusTool::Read_Client(unsigned int startAddress, int data)
{
    memset(req16, 0, sizeof(req16));
    regs = modbus_read_registers(ctx, startAddress, data, req16);
    //qDebug()<<"Read_Client"<<regs;
    if (regs == -1)
    {
        qDebug()<<"Read_Client"<<regs;
        return false;
    }
    return true;
}

/*
* @FuncName   函数名:从指定下位机线圈处读取数据
* @Function   功能：0x03读模式，读取下位机线圈数据
* @param startAddress 下位机寄存器起始地址
* @param endAddress 数据量
* @return 返回值无
*/

void ModbusTool::Read_Bit_Client(unsigned int startAddress, int data)
{
    memset(req8, 0, sizeof(req8));
    regs = modbus_read_bits(ctx, startAddress, data, req8);
    //qDebug()<<"Read_Bit_Client"<<regs;
    if (regs == -1)
    {
        return;
    }
    return;
}
