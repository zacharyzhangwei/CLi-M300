#include "chismanager.h"

namespace Control
{
    CHISManager::CHISManager(QObject *parent): QObject(parent)
    {

    }
    bool CHISManager::Init()
    {
        m_HISmodule.init();
        m_HISmodule.setprintOrHis(false);
        m_HISmodule.setcb((this));
        return true;
    }

    bool CHISManager::setHISOpen(int port, int rate)
    {
        m_comState=m_HISmodule.open(port,rate);
        return m_comState;
    }

    bool CHISManager::getHISState()
    {
        return m_comState;
    }

    bool CHISManager::setHISClose()
    {
        if(m_comState)
        {
            m_HISmodule.close();
        }
        m_comState =false;
        return m_comState;
    }

    bool CHISManager::setHISData(QQueue<st_TestInfo> testList)
    {
        if(m_comState)
        {
            QQueue<ISession *> *ssqueue=new QQueue<ISession *>;
            while (testList.size())
            {

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



                PSession *sess=new PSession();
                QByteArray SetByt=hl7->encode().toLocal8Bit();
                sess->setdata(SetByt);
                ssqueue->enqueue(sess);
            }
            if(ssqueue->size()>0)
            {
                return m_HISmodule.sends(ssqueue);
            }
        }
        else
        {
            return 0;
        }

    }


    void CHISManager::comstatus(int status)
    {
        int i=0;
        i++;
        //串口i连接状态
        if(!status)
        {
            //打开失败
        }
    }

}
