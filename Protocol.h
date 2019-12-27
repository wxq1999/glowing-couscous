#pragma once

#include <QStringList>
#include "Const.h"
#include "Result.h"

class Protocol
{
public:
    enum Type
    {
        Logon,              // 登录
        Reg,                // 注册
        Chat,               // 聊天
        AddFriendRequest,   // 添加好友请求
        AddFriendResult,    // 添加好友结果
        Logoff,             // 离线请求
        FriendLogon         // 好友登录通知
    };

    Protocol(Type type);
    Type getType() const;

protected:
    Type m_type;    // 协议类型
};

class LogonRequest : public Protocol
{
public:
    LogonRequest(const QString&, const QString&);
    const char* getUserName() const;
    const char* getPassword() const;

private:
    char m_userName[Const::USERNAME_LEN + 1];  // 用户名
    char m_password[Const::PASSWORD_LEN + 1];       // 密码
};

class LogonResult : public Protocol
{
public:
    LogonResult();
    Result::Code getResultCode() const;
    int getIconIndex() const;
    int getFriendCount() const;
    void getFriendNames(QStringList&) const;
    const int* getFriendIconIndexs() const;
    bool isFriendOnline(int) const;
    void setResultCode(Result::Code);
    void setIconIndex(int);
    void setFriendCount(int);
    void setFriendNames(const QString&);
    void setFriendIconIndexs(const int*, int);
    void setFriendsOnline(int, bool);

private:
    Result::Code m_resultCode;                          // 登录结果
    int m_iconIndex;                                    // 头像索引
    int m_friendCount;                                  // 好友数
    char m_friendNames[Const::FRIEND_NAMES_LEN];        // 好友名列表
    int m_friendIconIndexs[Const::MAX_USER_COUNT];   // 好友头像索引列表
    bool m_friendsOnline[Const::MAX_USER_COUNT];     // 好友在线状态列表
};

class RegRequest : public Protocol
{
public:
    RegRequest(const QString&, const QString&, int);
    const char* getUserName() const;
    const char* getPassword() const;
    int getIconIndex() const;

private:
    char m_userName[Const::USERNAME_LEN + 1];  // 用户名
    char m_password[Const::PASSWORD_LEN + 1];       // 密码
    int m_iconIndex;                                // 头像索引
};

class RegResult : public Protocol
{
public:
    RegResult();
    Result::Code getResultCode() const;
    void setResultCode(Result::Code);

private:
    Result::Code m_resultCode;  // 结果
};

class AddFriendRequest : public Protocol
{
public:
    AddFriendRequest();
    AddFriendRequest(const QString&, const QString&, int);
    const char* getSrcUserName() const;
    const char* getDstUserName() const;
    int getIconIndex() const;

private:
    char m_srcUserName[Const::USERNAME_LEN + 1];   // 源用户名
    char m_dstUserName[Const::USERNAME_LEN + 1];   // 目标用户名
    int m_iconIndex;                                    // 源用户的头像索引
};

class AddFriendResult : public Protocol
{
public:
    AddFriendResult();
    AddFriendResult(Result::Code, const QString&, const QString&, int);
    Result::Code getResultCode() const;
    const char* getSrcUserName() const;
    const char* getDstUserName() const;
    int getIconIndex() const;

private:
    Result::Code m_resultCode;                          // 结果
    char m_srcUserName[Const::USERNAME_LEN + 1];   // 源用户名
    char m_dstUserName[Const::USERNAME_LEN + 1];   // 目标用户名
    int m_dstUserIconIndex;                              // 目标用户的头像索引
};

class ChatInfo : public Protocol
{
public:
    ChatInfo();
    ChatInfo(const QString&, const QString&, const QString&, const QString&);
    const char* getSrcUserName() const;
    const char* getDstUserName() const;
    const char* getContent() const;
    const char* getTime() const;

private:
    char m_srcUserName[Const::USERNAME_LEN + 1];   // 源用户名
    char m_dstUserName[Const::USERNAME_LEN + 1];   // 目标用户名
    char m_content[Const::CONTENT_LEN + 1];             // 内容
    char m_time[Const::TIME_LEN + 1];                   // 发送时间
};

class LogoffRequest : public Protocol
{
public:
    LogoffRequest();
    LogoffRequest(const QString&);
    const char* getUserName() const;

private:
    char m_userName[Const::USERNAME_LEN + 1];  // 用户名
};

class FriendLogon : public Protocol
{
public:
    FriendLogon();
    FriendLogon(const char*);
    const char* getUserName() const;

private:
    char m_userName[Const::USERNAME_LEN + 1];  // 用户名
};
