#ifndef ISQLSESSION_H
#define ISQLSESSION_H
enum enum_db_cmd
{
    em_User_get_Null,
    em_User_get_List,//获取用户列表
    em_User_get_ID,//获取对应ID用户信息
    em_user_get_Add,//新增账户
    em_user_get_IDName,//获取所有账户信息
};
namespace  Data
{
    class IDBSession
    {
    public:
        virtual void setcmd(enum_db_cmd cmd) = 0;
        virtual enum_db_cmd  getcmd() = 0;
    };
}

#endif // ISQLSESSION_H
