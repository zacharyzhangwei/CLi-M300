#include "csocketmanager.h"

namespace Control
{
    CSocketManager::CSocketManager(QObject *parent): QObject(parent)
    {

    }

    CSocketManager::~CSocketManager()
    {

    }

    bool CSocketManager::Init()
    {
        m_Tcpmodule.init();
        m_Tcpmodule.setcb((this));
        return true;
    }

    bool CSocketManager::setSocketClose()
    {
        if(m_tcpState)
        {
            m_Tcpmodule.close();
        }
        m_tcpState =false;
        return m_tcpState;
    }

    bool CSocketManager::setSocketOpen(QString IP, int port)
    {
        qDebug()<<"IP"<<IP<<"port"<<QString::number(port);
        m_tcpState=m_Tcpmodule.open(IP,port);
        return m_tcpState;
    }

    bool CSocketManager::getSocketOpen()
    {
        return m_tcpState;
    }

    bool CSocketManager::setSocketData(QQueue<st_TestInfo> testList)
    {
        if(m_tcpState)
        {
            QQueue<ISession *> *ssqueue=new QQueue<ISession *>;
            while (testList.size()) {

                st_TestInfo testInfo=testList.dequeue();

                QString sexStr;
                //性别
                switch (testInfo.Sex)
                {
                case 0:
                    sexStr =tr("男");
                    break;
                case 1:
                    sexStr =tr("女");
                    break;
                case 2:
                    sexStr =tr("其他");
                    break;
                default:
                    sexStr =tr("男");
                    break;
                }


                Hl7_manage *hl7 = new Hl7_manage();
                hl7->ini();
                //流水号
                hl7->set_msh(QString::number(testInfo.Num));
                hl7->set_pid(testInfo.SampleID,testInfo.Name,"",sexStr);
                hl7->set_obr(Comom::CGlobal::getInstance()->getTools()->get_TimeStr(testInfo.Submitted));
                while (testInfo.resultList.size())
                {
                    st_TestResult testResult=testInfo.resultList.dequeue();
                    QStringList referList = testResult.Refer.split("-");
                    QString referHead=referList.at(0);
                    QString referEnd=referList.at(1);
                    hl7->set_obx("NM",
                                 testInfo.Batch,
                                 testResult.Project,
                                 testResult.Result,
                                 testResult.Unit,
                                 referHead.toFloat(),
                                 referEnd.toFloat());
                }

                SSession *sess=new SSession();
                QByteArray SetByt=hl7->encode().toLocal8Bit();
                sess->setdata(SetByt);
                ssqueue->enqueue(sess);
            }


            if(ssqueue->size()>0)
            {
                return m_Tcpmodule.sends(ssqueue);
            }
        }
        else
        {
            return 0;
        }
    }

}
