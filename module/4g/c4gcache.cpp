#include "c4gcache.h"
#include <QAbstractSocket>
#include <QJsonDocument>
#include <QTextCodec>
#include <QThread>

C4gCache::C4gCache(QObject* parent) : QObject(parent)
{
    m_socket = new QTcpSocket(this);

    QString appName=QFileInfo(QCoreApplication::applicationFilePath()).fileName();
    appName=appName.mid(0,appName.length()-4);
    //设置更新项目名称
    QSettings settings("configServer.ini",QSettings::IniFormat);
    settings.beginGroup("BtServer");
    settings.setIniCodec(QTextCodec::codecForName("utf-8"));
    settings.setValue("appName",appName);
    settings.endGroup();
}

#define PORT_4G 8181
#define RETRY_COUNT 3

C4gCache::~C4gCache()
{
    m_socket->abort();
    m_socket->close();
    delete m_socket;
}

bool C4gCache::init()
{
    QObject::connect(m_socket, &QTcpSocket::connected, this,
                     &C4gCache::sltConnected);
    m_socket->connectToHost("127.0.0.1", PORT_4G);

    if (!m_socket->waitForConnected(300))  //连接失败
    {
        m_4g_connected = false;
    }
    else
    {
        m_4g_connected = true;
    }

    QSettings readtings("configServer.ini",QSettings::IniFormat);
    readtings.setIniCodec(QTextCodec::codecForName("utf-8"));
    QString registered_stateStr=readtings.value("BtServer/registered_state").toString();
    QString update_stateStr=readtings.value("BtServer/update_state").toString();
    m_softRetain=readtings.value("BtServer/softRetain").toString();
    if(registered_stateStr=="1")
    {
        m_4g_registered=true;
    }
    if(update_stateStr=="1")
    {
        m_4g_update=true;
    }
    qDebug()<<"m_4g_connected"<<m_4g_connected;
    connect(m_socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)),
            this, SLOT(sltStateChanged(QAbstractSocket::SocketState)),
            Qt::DirectConnection);
    return false;
}

void C4gCache::sltSession(QJsonObject obj)
{
    /// 如果断线状态,尝试重连
    if (m_4g_connected == false) {
        retryConnect();
    }
    ///连接状态下,发送数据
    if (m_4g_connected == true) {
        QTextCodec*   gbk = QTextCodec::codecForName("utf-8");
        QJsonDocument document;
        document.setObject(obj);
        QByteArray byte_array = document.toJson(QJsonDocument::Compact);
        QString    msg(byte_array);
        msg = msg + "\r\n";
        qDebug() << "write content is :" + msg;
        QByteArray setByt = gbk->fromUnicode(msg.toUtf8().data());

        qint64 writeCount = m_socket->write(setByt);
        bool   flushResult = m_socket->flush();
//        m_socket->waitForReadyRead();

        qDebug() << "writeCount:" << writeCount
                 << "writeResult:" << flushResult;
        if (flushResult == false) {
            ///发送不成功,尝试重连
            retryConnect();
            /// 连接成功后才发送
            if (m_4g_connected == true) {
                qint64 writeResult = m_socket->write(setByt);
                bool   flushResult = m_socket->flush();
//                m_socket->waitForReadyRead();

                qDebug() << "Reconnected to server;";
                qDebug() << "writeResult is:" << writeResult
                         << "flushResult is:" << flushResult;
            }
        }
    }
    return;
}

//保存sd升级文件
bool C4gCache::setBtcData(QString btcStr, QString dataStr)
{
    qDebug()<<"保存sd升级文件";
    qDebug()<<"btcStr"<<btcStr;
    qDebug()<<"dataStr"<<dataStr;
    QString fileName = DEFAULT_BTC_PATH;//BTC的默认路径
    QString batchStr;
    QString backupStr;
    bool reflag=true;
    if(btcStr.isEmpty()||dataStr.isEmpty())
    {
        reflag =false;
    }
    else
    {
        batchStr=fileName+"/"+btcStr+".btc";//文件所在位置及名称;
    }
    if(reflag)
    {
        //判断文件是否存在
        if (!QFile::exists(batchStr))//文件不存在
        {
            QFile filey(batchStr);
            if(!filey.open(QIODevice::WriteOnly))
            {
                reflag=false;
            }
            else
            {
                QByteArray bytes =QByteArray::fromBase64(dataStr.toUtf8());
                filey.flush();
                filey.write(bytes);
                filey.close();
            }
        }
        else//文件存在
        {
            if(!QFile::remove(batchStr))//执行删除
            {
                reflag=false;
            }
            else
            {
                QFile filey(batchStr);
                if(!filey.open(QIODevice::WriteOnly))
                {
                    reflag=false;
                }
                else
                {
                    QByteArray bytes =QByteArray::fromBase64(dataStr.toUtf8());
                    filey.flush();
                    filey.write(bytes);
                    filey.close();
                }
            }
        }
    }

    //备份btc操作
    if(reflag)
    {
        //判断文件是否存在
        if (!QFile::exists(backupStr))//文件不存在
        {
            QFile filey(backupStr);
            if(!filey.open(QIODevice::WriteOnly))
            {
                reflag=false;
            }
            else
            {
                QByteArray bytes =QByteArray::fromBase64(dataStr.toUtf8());
                filey.flush();
                filey.write(bytes);
                filey.close();
            }
        }
        else//文件存在
        {
            if(!QFile::remove(backupStr))//执行删除
            {
                reflag=false;
            }
            else
            {
                QFile filey(backupStr);
                if(!filey.open(QIODevice::WriteOnly))
                {
                    reflag=false;
                }
                else
                {
                    QByteArray bytes =QByteArray::fromBase64(dataStr.toUtf8());
                    filey.flush();
                    filey.write(bytes);
                    filey.close();
                }
            }
        }
    }
    qDebug()<<"reflag"<<reflag;
    return reflag;
}

//重连
void C4gCache::retryConnect()
{
    int retryCount = 0;
    while (retryCount < 1) {
        // 重连3次
        m_4g_connected = false;
        m_socket->connectToHost("127.0.0.1", PORT_4G);

        if (!m_socket->waitForConnected(300))  //连接失败
        {
            m_4g_connected = false;
        } else {
            m_4g_connected = true;
            break;
        }
        retryCount++;
    }
#ifndef QT_DEBUG
    qDebug() << "C4gCache::retryConnect  retryCount is:" << retryCount;
    qDebug() << "m_4g_connected is:" << m_4g_connected;
#endif
}

int C4gCache::getTimestamp(QString timeStr)
{
    QDateTime time;
    time = QDateTime::fromString(timeStr, "yyyy-MM-dd HH:mm:ss");
    int ntime_t = time.toTime_t();
    return ntime_t;
}

//安装包备份
void C4gCache::apkImport(QString newFile,QString oldFile)
{
    //判断目标文件是否存在
    if (!QFile::exists(oldFile))
    {
        qDebug()<<"文件不存在";
    }
    else
    {
        //判断是否有同名文件是否存在
        if (!QFile::exists(newFile))
        {
            qDebug()<<"文件导入成功";
            //无->文件导入成功
            if(QFile::copy(oldFile, newFile))
            {
                if(QFile::remove(oldFile))
                {
                    qDebug()<<"无->文件导入成功";
                }
            }
        }
        else
        {
            //有->文件覆盖成功
            //执行删除
            qDebug()<<"文件覆盖成功";
            if(QFile::remove(newFile))
            {
                if(QFile::copy(oldFile, newFile))
                {
                    if(QFile::remove(oldFile))
                    {
                        qDebug()<<"有->文件覆盖成功";
                    }
                }
            }
        }
    }
}

void C4gCache::sltStateChanged(QAbstractSocket::SocketState state)
{
#ifndef QT_DEBUG
    qDebug() << "TcpSocketState------" << state;
#endif
    switch (state) {
    case QAbstractSocket::ConnectedState:
    case QAbstractSocket::ConnectingState:
    case QAbstractSocket::ClosingState:
        m_4g_connected = true;
        break;
    case QAbstractSocket::UnconnectedState:
        m_4g_connected = false;
        break;
    default:
        break;
    }
}

void C4gCache::sltConnected()
{
#ifndef QT_DEBUG
    qDebug() << "sltConnected()";
#endif
    m_socket->setSocketOption(QAbstractSocket::KeepAliveOption, 1);
    QObject::connect(m_socket, &QTcpSocket::readyRead, this,
                     &C4gCache::sltReadData);
    QObject::connect(m_socket, &QTcpSocket::disconnected, this,
                     &C4gCache::sltDisconnect);
}

// 接收4g平台数据
void C4gCache::sltReadData()
{
    QByteArray data = m_socket->readAll();
#ifndef QT_DEBUG
    QString string = data;
    qDebug() << "receive 4g data:" << string;
#endif
    QJsonParseError jsonError;
    QJsonDocument   ret = QJsonDocument::fromJson(data, &jsonError);
    QJsonObject     obj;
    if (jsonError.error == QJsonParseError::NoError && ret.isObject()) {
        obj = ret.object();
        int dtype = obj.value("dtype").toInt();
        int status = obj.value("status").toInt();
        if (dtype == (int)EM_4G_DTYPE::e_get_info) {  //获取信息
            int cmd = obj.value("cmd").toInt();
            if (cmd == (int)EM_4G_CMD_TYPE::e_time) { //获取4g的时间
                QString stime = obj.value("stime").toString();
                qDebug() << "stime is:" << stime;
                int       time_t = getTimestamp(stime);
                QDateTime nDatetime = QDateTime::fromTime_t(time_t);

                QString timsStr=nDatetime.toString("yyyy-MM-dd hh:mm:ss");
                qDebug()<<"4g设置timsStr"<<timsStr;
                SYSTEMTIME st;
                GetLocalTime(&st);
                st.wYear=timsStr.mid(0,4).toInt();
                st.wMonth=timsStr.mid(5,2).toInt();
                st.wDay=timsStr.mid(8,2).toInt();
                st.wHour = timsStr.mid(11,2).toInt();
                st.wMinute = timsStr.mid(14,2).toInt();
                st.wSecond=timsStr.mid(17,2).toInt();
                SetLocalTime(&st);
                m_4g_time = nDatetime;
#ifndef QT_DEBUG
                qDebug() << "m_4g_time is:" << nDatetime;
#endif
                QJsonObject newObj;
                QString snStr=Comom::CGlobal::getInstance()->get_snStr();
                newObj.insert("sn",snStr);
                QThread::msleep(200);
                // 如果未注册4g，去注册盒子
                if (m_4g_registered == false) {
                    newObj.insert("dtype", (int)EM_4G_DTYPE::e_regist);
                    newObj.insert("bindTime", stime);
                    newObj.insert("softVersion", DEFAULT_WEVERSION);
                    newObj.insert("devName", "FLI-1200");
                    sltSession(newObj);

                }
                else
                {
                    //未登录,去登录盒子
                    if (m_4g_logined == false)
                    {
                        newObj.insert("dtype", (int)EM_4G_DTYPE::e_login);
                        newObj.insert("connTime", stime);
                        newObj.insert("login", 1);
                        sltSession(newObj);
                    }
                }
            }
            else if (cmd == (int)EM_4G_CMD_TYPE::e_soft_path)
            {
                if (m_4g_update)
                {
                    QString oldVersion = DEFAULT_OLDVERSION;
                    QString newVersion = DEFAULT_WEVERSION;
                    QString snStr=Comom::CGlobal::getInstance()->get_snStr();
                    QJsonObject newObj;
                    newObj.insert("sn",snStr);
                    newObj.insert("dtype", (int)EM_4G_DTYPE::e_soft);
                    newObj.insert("oldVersion", oldVersion);
                    newObj.insert("newVersion", newVersion);
                    newObj.insert("retain", m_softRetain);
                    newObj.insert("process", 100);
                    sltSession(newObj);
                    qDebug() << "反馈更新状态：1、旧版本号" << oldVersion
                             <<"2、新版本号："<<newVersion
                             <<"3、retain："<<m_softRetain;
                    QSettings settings("configServer.ini",QSettings::IniFormat);
                    settings.beginGroup("BtServer");
                    settings.setIniCodec(QTextCodec::codecForName("utf-8"));
                    settings.setValue("update_state","0");
                    settings.endGroup();
                }

            } else if (cmd == (int)EM_4G_CMD_TYPE::e_imei) {//获取imei
                QString simei = obj.value("simei").toString();
                qDebug() << "m_imei is:" << simei;
            }
        }
        else if (dtype == (int)EM_4G_DTYPE::e_regist)//注册
        {
            if (status == 1 || status == 0)
            {
                qDebug() << "4g注册成功";
                m_4g_registered = true;
                m_4g_logined = true;

                QSettings settings("configServer.ini",QSettings::IniFormat);
                settings.beginGroup("BtServer");
                settings.setIniCodec(QTextCodec::codecForName("utf-8"));
                settings.setValue("registered_state","1");
                settings.endGroup();

                qDebug() << "重新获取时间,去登录系统";
                QJsonObject cmd;
                cmd.insert("dtype", (int)EM_4G_DTYPE::e_get_info);
                cmd.insert("cmd", (int)EM_4G_CMD_TYPE::e_time);
                sltSession(cmd);
            }
            else
            {
                m_4g_registered = false;
            }
#ifndef QT_DEBUG
            qDebug() << "m_4g_registered is:" << m_4g_registered
                     << "m_4g_logined is:" << m_4g_logined;
#endif
        } else if (dtype == (int)EM_4G_DTYPE::e_login) {  //登录
            if (status == 1)
            {
                m_4g_logined = true;
                qDebug() << "4g登录成功";
                QString pathStr=QCoreApplication::applicationDirPath()+"/upadteApk/";
                QJsonObject newObj;
                newObj.insert("dtype", (int)EM_4G_DTYPE::e_get_info);
                newObj.insert("cmd", (int)EM_4G_CMD_TYPE::e_soft_path);
                newObj.insert("path",pathStr);
                sltSession(newObj);
                emit sgn_C4g_State(true);
            }
            else
            {
                m_4g_logined = false;
                qDebug() << "4g登录失败";
                QSettings settings("configServer.ini",QSettings::IniFormat);
                settings.beginGroup("BtServer");
                settings.setIniCodec(QTextCodec::codecForName("utf-8"));
                settings.setValue("registered_state","0");
                settings.endGroup();
                emit sgn_C4g_State(false);
            }

#ifndef QT_DEBUG
            qDebug() << "m_4g_registered is:" << m_4g_registered
                     << "m_4g_logined is:" << m_4g_logined;
#endif
        } else if (dtype == (int)EM_4G_DTYPE::e_logout) {  //登出
        } else if (dtype == (int)EM_4G_DTYPE::e_status) {  //设备状态上报
        } else if (dtype == (int)EM_4G_DTYPE::e_result) {
            //上报检测结果
            QString resourceId = obj.value("resourceId").toString();
            int     lsh = resourceId.toInt();
            int     shardNum = obj.value("shardNum").toInt();
            qDebug()<<"收到结果上传的回复:流水号:"<<lsh<<"分片号"<<shardNum<<"状态值"<<status;

            if(status==1)
            {
                 emit signal_upload_finish(resourceId.toInt());
            }

        } else if (dtype == (int)EM_4G_DTYPE::e_qc) {  //上报质控结果
        } else if (dtype ==(int)EM_4G_DTYPE::e_error) {  //故障码错误日志上报
        } else if (dtype == (int)EM_4G_DTYPE::e_sd)// sd升级
        {
            QString stimeStr = obj.value("stime").toString();
            QString retainStr= obj.value("retain").toString();
            QJsonArray btcArray= obj.value("btcarray").toArray();
            bool btcFlag=false;
            for(int i=0;i<btcArray.size();i++)
            {
                //Array中的每一项都是一个QJsonValue，可以用toT()方法把它转化为对应的类型
                //由于这里是K-V类型，所以要提取其中的K和V，只能先转化为QJsonObject
                QJsonObject jobj = btcArray[i].toObject();
                QString batchStr= jobj.value("batch").toString();
                QString dataStr= jobj.value("btcData").toString();
                btcFlag=setBtcData(batchStr,dataStr);
                if(!btcFlag)
                {
                    break;
                }
            }
            QJsonObject newObj;
            newObj.insert("dtype", (int)EM_4G_DTYPE::e_sd);
            //newObj.stime("imei", imei);//imei号 可以不填 守护进程会帮你填进去
            QString snStr=Comom::CGlobal::getInstance()->get_snStr();
            newObj.insert("sn",snStr);
            newObj.insert("stime", stimeStr);// 时间
            if(btcFlag)
            {
                newObj.insert("process", "100");//进度（float转为字符串）
            }
            else
            {
                newObj.insert("process", "-1");//进度（float转为字符串）
            }
            newObj.insert("retain", retainStr); //保留用与工单id/用户id传输
            sltSession(newObj);
        }
        else if (dtype == (int)EM_4G_DTYPE::e_soft)// 远程软件升级
        {
            QString     softRetain = obj.value("retain").toString();
            QSettings settings("configServer.ini",QSettings::IniFormat);
            settings.beginGroup("BtServer");
            settings.setIniCodec(QTextCodec::codecForName("utf-8"));
            settings.setValue("softRetain",softRetain);
            settings.endGroup();
        }
    } else {
#ifndef QT_DEBUG
        qDebug() << "接收4G守护进程的数据失败,无法解析";
#endif
        return;
    }
}

void C4gCache::sltDisconnect()
{
#ifndef QT_DEBUG
    qDebug() << "sltDisconnect()";
#endif
    m_socket->setSocketOption(QAbstractSocket::KeepAliveOption, 0);
    m_socket->close();
    m_4g_connected = false;
}
