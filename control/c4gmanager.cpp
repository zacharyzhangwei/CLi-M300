#include "c4gmanager.h"

namespace Control
{
    C4gManager::C4gManager()
    {

    }

    bool C4gManager::get_C4gRecordEnd()
    {
        return m_recordEnd;
    }

    void C4gManager::set_C4gRecordEnd(bool state)
    {
        m_recordEnd=state;
    }

    bool C4gManager::get_update()
    {
        QString dirName = QDir::currentPath();
        QString dirUpdateName = dirName+ "/upadteApk";
        QDir dir(dirUpdateName);
        // 判断此目录文件是否存在
        if (dir.exists())
        {
            QFileInfoList fileInfoList = dir.entryInfoList();
            int file_count = fileInfoList.count();
            qDebug()<<"file_count"<<QString::number(file_count);

            //判断文件夹中数据是否未空
            if (file_count <= 0)
            {
                //升级文件不存在,说明无需更新
                return false;
            }
            else
            {
                bool countFlag=false;
                for (int i = 0; i < fileInfoList.count(); i++)
                {
                    QString fileName = fileInfoList[i].fileName();
                    if (fileName != "." && fileName != "..")
                    {
                        countFlag=true;
                    }
                }
                if(!countFlag)
                {
                    return false;
                }
                else
                {
                    return true;
                }
            }
        }
        else
        {
            return false;
        }
    }

    void C4gManager::init()
    {
        // 开启socket
        m_4g_cache = new C4gCache(nullptr);
        m_4g_cache->init();
        // 开启接收任务线程并传递给socket
        m_4g_module = new C4gModule();
        QObject::connect(m_4g_module, &C4gModule::signal_session, m_4g_cache,
                         &C4gCache::sltSession);

        QObject::connect(m_4g_cache, &C4gCache::signal_upload_finish, this,
                         &C4gManager::slt_upload_finish);
        QObject::connect(m_4g_cache, &C4gCache::sgn_C4g_State, this,
                         &C4gManager::slt_C4g_State);



        qDebug()<<"开启socket";
    }

    void C4gManager::get4GTime()
    {
        QJsonObject cmd;
        cmd.insert("dtype", (int)EM_4G_DTYPE::e_get_info);
        cmd.insert("cmd", (int)EM_4G_CMD_TYPE::e_time);
        m_4g_module->setSession(cmd);
    }

    void C4gManager::sendErrorMsg(QString faultcode)
    {
        QString msgStr="FLI-1200设备运行故障，故障码"+faultcode;
        QJsonObject cmd;
        cmd.insert("dtype", (int)EM_4G_DTYPE::e_error);
        cmd.insert("faultcode", faultcode);
        cmd.insert("msg", msgStr);
        m_4g_module->setSession(cmd);
    }

    bool C4gManager::getC4gState()
    {
        if(m_4g_cache->m_4g_registered && m_4g_cache->m_4g_logined)
        {
            return true;
        }
        else
        {
            return false;
        }

    }

    void C4gManager::sendTestData(QString curvStr,st_Test_Data testData ,bool testOrRecord)
    {
        qDebug()<<"上传数据"<<testData.resourceId;
        if(getC4gState())
        {
            QString isRealTime="yes";
            if(!testOrRecord)
            {
                //历史数据
                isRealTime = "no";
            }
//            QString lineData;//曲线赋值
//            lineData=curvStr;
//            QStringList listData = lineData.split("|");
//            qDebug()<<"listData"<<listData;
            qDebug()<<"curvStr"<<curvStr;
            if(!curvStr.isEmpty())
            {
//                QString     curvedata;
//                for (int i = 0; i < 1500; i++)
//                {
//                    QString curve = listData[i] + "|";
//                    curvedata.append(curve);
//                }
//                curvedata = curvedata.left(curvedata.size() - 1);

                //参数赋值testData
                QString projectName = testData.projectName;
                QString sampleId=testData.sampleId;
                QString resourceId=testData.resourceId;
                QString name = testData.name;
                int sex = testData.sex;
                QString age = testData.age;
                QString detectTime = testData.detectTime;
                int     cardType = testData.cardType;
                QString batch = testData.batch;
                int     sampleType = testData.sampleType;

                QQueue <st_Item_Data> itemDataList=testData.itemData;

                QJsonArray arr;

                qDebug()<<"itemDataList"<<itemDataList.size();
                while (itemDataList.size())
                {
                    st_Item_Data itemInfo=itemDataList.dequeue();
                    QJsonObject o1;
                    o1["itemName"] = itemInfo.itemName;
                    o1["detectRange"] = itemInfo.detectRange;
                    o1["referRange"] = itemInfo.referRange;
                    o1["result"] = itemInfo.result;
                    o1["resultUnit"] = itemInfo.resultUnit;
                    arr.append(o1);
                }

                QJsonObject cmd0;
                cmd0.insert("dtype", (int)EM_4G_DTYPE::e_result);
                cmd0.insert("sn", Comom::CGlobal::getInstance()->get_snStr());
                cmd0.insert("projectName", projectName.replace(",", "|"));
                cmd0.insert("patientName", name);
                cmd0.insert("sex", sex);
                cmd0.insert("age", age);
                cmd0.insert("detectTime", detectTime);
                cmd0.insert("cardType", cardType);
                cmd0.insert("batch", batch);
                cmd0.insert("curve", curvStr);
                cmd0.insert("shardNum", 0);
                cmd0.insert("resourceId", resourceId);
                cmd0.insert("sampleId", sampleId);
                cmd0.insert("sampleType", sampleType);
                cmd0.insert("listResItem", arr);
                cmd0.insert("isRealTime", isRealTime);;
                if(Comom::CGlobal::getInstance()->get_isqcFlag())
                {
                    cmd0.insert("isCustomer", 0);
                }
                else
                {
                    cmd0.insert("isCustomer", 1);
                }
                qDebug()<<"cmd0"<<cmd0;
                m_4g_module->setSession(cmd0);
                m_resuleState=false;
            }
        }
    }

    bool C4gManager::getResultState()
    {
        return m_resuleState;
    }

    void C4gManager::setResultState(bool state)
    {
        m_resuleState=state;
        if(m_resuleState)
        {
            m_4g_cache->m_shard_num.clear();
            m_4g_cache->m_last_resource_id="";
        }
    }

    //打包设备信息
    void C4gManager::setComputerInfo()
    {
        if (m_4g_cache->m_4g_registered && m_4g_cache->m_4g_logined)
        {
            MEMORYSTATUSEX statusex;
            statusex.dwLength=sizeof(statusex);
            GlobalMemoryStatusEx(&statusex);
            QString memory=QString::number(statusex.dwMemoryLoad);

            //获取c盘磁盘信息
            LPCWSTR lpcwstrDriver=(LPCWSTR)QString("C:/").utf16();
            ULARGE_INTEGER liFreeBytesAvailable, liTotalBytes, liTotalFreeBytes;
            GetDiskFreeSpaceEx( lpcwstrDriver, &liFreeBytesAvailable, &liTotalBytes, &liTotalFreeBytes);
            QString diskSizeStr=QString::number((quint64) liTotalFreeBytes.QuadPart/1024/1024);

            // 上报cpu使用率及内存信息
            QString cpuStr=QString::number(getCpuUsage());

            QJsonObject cmd;
            cmd.insert("sn", Comom::CGlobal::getInstance()->get_snStr()); //设备编号
            cmd.insert("dtype", (int)EM_4G_DTYPE::e_status);//消息类型 2
            cmd.insert("softVersion", DEFAULT_WEVERSION);//软件版本号
            cmd.insert("cpu", cpuStr);//cpu使用率
            cmd.insert("diskRemain", diskSizeStr);//硬盘可用空间
            cmd.insert("memory", memory);//内存使用率
            cmd.insert("requstTime", QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"));//请求时间
            m_4g_module->setSession(cmd);
        }
    }

    double C4gManager::getCpuUsage()
    {
    #ifdef Q_OS_WIN
        static FILETIME s_preIdleTime = { 0, 0 };
        static FILETIME s_preKernelTime = { 0, 0 };
        static FILETIME s_preUserTime = { 0, 0 };
        static bool isFirst = true;

        FILETIME idleTime;
        FILETIME kernelTime;
        FILETIME userTime;

        int idleCost = 0;
        int kernelCost = 0;
        int userCost = 0;

        double rate = 0.0;

        GetSystemTimes(&idleTime, &kernelTime, &userTime);

        idleCost = CompareFileTime(&s_preIdleTime, &idleTime);
        kernelCost = CompareFileTime(&s_preKernelTime, &kernelTime);
        userCost = CompareFileTime(&s_preUserTime, &userTime);

        s_preIdleTime = idleTime;
        s_preKernelTime = kernelTime;
        s_preUserTime = userTime;

        if (kernelCost + userCost == 0) {
            return -1;
        } else if (isFirst) {
            isFirst = false;
            return 0.0;
        } else {
            rate = (double)(kernelCost + userCost - idleCost) * 100 / (kernelCost + userCost);
            return rate;
        }
#endif
    }

    st_Test_Data C4gManager::stTestToC4TestData(st_TestInfo stTestInfo)
    {

        st_Test_Data testData;
        QQueue<st_TestResult> stResultList=stTestInfo.resultList;
        QQueue <st_Item_Data> itemList;
        if(stResultList.size()>1)
        {
            testData.projectName=QString::number(stResultList.size())+"合1";//项目名称
            while (stResultList.size())
            {
                st_TestResult resultInfo=stResultList.dequeue();
                st_Item_Data itemData;
                itemData.itemName =resultInfo.Project;      //项目名称
                itemData.detectRange=resultInfo.Refer.replace("-", "|");   //检测范围 用|划分开 如0.0|22.0|
                itemData.referRange=resultInfo.Refer.replace("-", "|");    //参考范围 如上
                itemData.result=resultInfo.Result;        //检测结果
                itemData.resultUnit=resultInfo.Unit;    //单位
                itemList<<itemData;
            }
        }
        else
        {
            while (stResultList.size())
            {
                st_TestResult resultInfo=stResultList.dequeue();
                st_Item_Data itemData;
                testData.projectName=resultInfo.Project;    //项目名称
                itemData.itemName =resultInfo.Project;      //项目名称
                itemData.detectRange=resultInfo.Refer.replace("-", "|");   //检测范围 用|划分开 如0.0|22.0|
                itemData.referRange=resultInfo.Refer.replace("-", "|");    //参考范围 如上
                itemData.result=resultInfo.Result;        //检测结果
                itemData.resultUnit=resultInfo.Unit;    //单位
                itemList<<itemData;
            }
        }
        testData.sampleId=stTestInfo.SampleID;   //样本ID
        testData.resourceId=QString::number(stTestInfo.Num); //测试流水号
        testData. name=stTestInfo.Name;      //患者姓名
        //性别  0 男 1 女 2 其他 ?空
        switch (stTestInfo.Sex) {
        case 0:
            //性别   1 男 2 女 3 其他
            testData.sex=1 ;
            break;
        case 1:
            //性别   1 男 2 女 3 其他
            testData.sex=2;
            break;
        case 2:
            //性别   1 男 2 女 3 其他
            testData.sex=3;
            break;
        default:
            //性别   1 男 2 女 3 其他
            testData.sex=0;
            break;
        }
        //年龄
        if(stTestInfo.AgeType<5)
        {
            //年龄 xx|x  (年xx|1,月xx|2,周xx|3,日xx|4,小时xx|5)
            testData.age=QString::number(stTestInfo.Age)+"|"+QString::number(stTestInfo.AgeType+1);
        }
        testData.detectTime=Comom::CGlobal::getInstance()->getTools()->get_TimeStr(stTestInfo.Tested); //检测时间 时间格式 xxxx/xx/xx xx:xx:xx
        testData.cardType=1;       //试剂卡类型 1单卡 2二联卡 3三联卡
        testData.batch=stTestInfo.Batch;      //试剂批次
         //样本类型
        //样本类型0其他 1全血 2血清 3血浆 4尿液 5默认
        switch (stTestInfo.SampleType) {
        case 0:
            testData.sampleType=1009;//其他
            break;
        case 1:
            testData.sampleType=1001;//全血
            break;
        case 2:
            testData.sampleType=1002; //血清
            break;
        case 3:
            testData.sampleType=1003;//血浆
            break;
        case 4:
            testData.sampleType=1004;//尿液l
            break;
        case 5:
            testData.sampleType=1009;//其他
            break;
        default:
            testData.sampleType=1009;//其他
            break;
        }
        testData.itemData=itemList;


        return testData;
    }


    //操作数据库将反馈流水号修改标志位
    void C4gManager::slt_upload_finish(int resourceId)
    {
        qDebug()<<"resourceId"<<resourceId;
        if(!m_resuleState)
        {
           // CDBManager::getInstance()->getC4gNumState(resourceId);
        }
    }

    void C4gManager::slt_C4g_State(bool state)
    {
        emit sgn_CacheC4g_State(state);
    }

}
