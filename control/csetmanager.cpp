#include "csetmanager.h"
namespace Control
{
    CSetManager::CSetManager()
    {

    }

    void CSetManager::set_order(ST_Order d_order)
    {
        Comom::CGlobal::getInstance()->set_order(d_order);
    }

    ST_Order CSetManager::get_order()
    {
        return Comom::CGlobal::getInstance()->get_order();
    }




}
