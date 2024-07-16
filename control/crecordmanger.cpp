#include "crecordmanger.h"
namespace Control
{
    CRecordManger::CRecordManger()
    {
    }

    bool CRecordManger::getRecordInit()
    {
        BTLOG->print(e_debug,"%d,%s",2,"getRecordInit");
//        return CDBManager::getInstance()->getRecordInit(m_Sequence);
        return true;
    }



}
