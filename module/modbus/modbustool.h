#ifndef MODBUSTOOL_H
#define MODBUSTOOL_H

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QDateTime>
#include <QQueue>
#include "lib/libmodbus/modbus.h"
#include <QSerialPort>
#include <QSerialPortInfo>


#pragma execution_character_set("utf-8")

class ModbusTool : public QObject
{
    Q_OBJECT
public:
    explicit ModbusTool(QObject *parent = nullptr);
    ~ModbusTool();
signals:
    void data_out(QStringList data_list);
public:

    bool disconnected=false;//判断断线状态
    static QStringList getPortNameList();//获取所有可用的串口列表
    bool Modbus_connect(int nCom, int nBaud);//连接串口
    bool disconnect_modbus();//关闭串口
    bool reconnect_modbus();//重连串口
    int Write_Client(unsigned int regStartAddr, unsigned int data);//上位机向下位机的某个寄存器写入数据
    int Write_Bit_Client(unsigned int regStartAddr, unsigned int data);//上位机向下位机的某个线圈写入数据
    bool Read_Client(unsigned int startAddress, int data);//从指定下位机寄存器处读取数据
    void Read_Bit_Client(unsigned int startAddress, int data);//从指定下位机寄存器处读取数据

    int m_Com;
    int m_Baud;
    int LastBit=0;//上一个操作命令
    int NowBit=0;//上一个操作命令
    uint16_t req16[125];
    uint8_t req8[100];
    int regs;//判断读取成功没有-1失败
private:
    modbus_t *ctx;//Modbus对象



private slots:



};

#endif // MODBUSTOOL_H
