#ifndef ISQLMGR_H
#define ISQLMGR_H
#include "IDBSession.h"

namespace  Data
{
    class IDBModule_CB
    {
      public:
        virtual void recv(Data::IDBSession *sess) = 0;
    };
}

#endif // ISQLMGR_H
