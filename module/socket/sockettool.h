#ifndef SOCKETTOOL_H
#define SOCKETTOOL_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QtNetwork/QNetworkInterface>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
class SocketTool: public QObject
{
    Q_OBJECT
public:
    explicit SocketTool(QObject *parent = nullptr);
    ~SocketTool();
public:
    bool set_Socket_Connect(QString nIPStr, int nPort);//连接Socket IP端口
    bool set_Socket_Disconnect();//断开
    bool set_Write_Data(QByteArray nDatabyt);//写数据
    bool m_TcpFlag=false;//连接标志位
    QString m_ErrorStr;//错误信息
    QByteArray m_TcpReq;

private:

    QTcpSocket *m_Socket;
public slots:
    void slt_connected();
    void slt_Read_Data();//发送data
signals:


};


#endif // SOCKETTOOL_H
