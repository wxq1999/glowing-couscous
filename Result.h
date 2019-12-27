#pragma once

#include <QString>

class Result
{
public:
    enum Code
    {
        SUCCESS,                        // ""
        NETWORK_WRONG,                  // "网络无响应，请检查网络是否接通。"
        LOGON_SUCCESS,                  // "登录成功。"
        REG_SUCCESS,                    // "注册成功。"
        USER_NAME_EMPTY,                // "用户名是空的。"
        USER_NAME_TOO_LONG,             // "用户名太长了。"
        USER_NAME_INVALID,              // "用户名中包含非法字符。"
        PASSWORD_EMPTY,                 // "密码是空的。"
        PASSWORD_TOO_LONG,              // "密码太长了。"
        PASSWORD_NOT_EQUAL,             // "两次输入的密码不同。"
        ICON_NOT_SELECT,                // "未选择头像。"
        USER_NOT_FOUND,                 // "该用户尚未注册。"
        USER_ALREADY_LOGON,             // "该用户已经登录了。"
        PASSWORD_WRONG,                 // "密码不正确。"
        USER_EXISTS,                    // "该用户名已经被注册了。"
        ADD_FRIEND_ALLOW,               // "同意你添加他为好友。你们已经是好友了。"
        ADD_FRIEND_NOT_ALLOW,           // "拒绝你添加他为好友。"
        FRIENDNAME_EQUAL_SELFNAME,      // "好友名字与自己名字相同。"
        ALREADY_BE_FRIENDS,             // "已经是你的好友了。"
        CONTENT_IS_TOO_LONG,            // "内容太长了，无法发送。"
        TOO_MANY_FRIENDS                // "朋友太多了，不能再继续添加了。"
    };

    static QString getMessage(Code);
};
