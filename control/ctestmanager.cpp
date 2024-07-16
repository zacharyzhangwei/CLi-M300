#include "ctestmanager.h"
namespace Control
{
    CTestManager::CTestManager()
    {

    }

    void CTestManager::setPatient1(st_Patient nPatientInfo)
    {
        plate_1=nPatientInfo;
    }

    st_Patient CTestManager::getPatient1()
    {
        return plate_1;
    }

//    int CTestManager::getNumPatient()
//    {

//    }


    int CTestManager::get_value(QString dataHigh, QString dataLow)
    {
        int data=dataHigh.toInt()<<16;
        data=data+dataLow.toInt();
        return data;
    }


}

