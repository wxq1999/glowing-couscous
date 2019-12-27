#pragma once

#include <QTcpSocket>
#include <QUdpSocket>
#include "../Common/Protocol.h"
#include "../Common/Result.h"
#include "../Common/Config.h"

class Client : public QObject
{
    Q_OBJECT

public:
    explicit Client();
    ~Client();
    Result::Code logon();
    Result::Code reg();
    Result::Code chat(const ChatInfo*);
    Result::Code addFriend(const QString&);
    Result::Code logoff();
    int getFriendCount();
    static const QString& getName();

signals:
    void UM_GET_LOGON_RESULT(const LogonResult*);               // 获取到登录结果事件
    void UM_GET_REG_RESULT(const RegResult*);                   // 获取到注册结果事件
    void UM_GET_ADD_FRIEND_REQUEST(const AddFriendRequest*);    // 获取到添加好友请求事件
    void UM_GET_ADD_FRIEND_RESULT(const AddFriendResult*);      // 获取到添加好友结果事件
    void UM_CHAT_S2C(const ChatInfo*);                          // 接收到来自服务器的聊天信息的事件
    void UM_FRIEND_LOGOFF(const LogoffRequest*);                // 好友离线事件
    void UM_FRIEND_LOGON(const FriendLogon*);                   // 好友登录事件

private slots:
    void onReceive();

private:
    void onReceive_Tcp();
    void onReceive_Udp();
    qint64 sendData(const Protocol*, qint64);
    void onGetMessageFromServer(const Protocol*);
    void handleLogonResult(const LogonResult*);
    void handleRegResult(const RegResult*);
    void handleChat(const ChatInfo*);
    void handleAddFriendRequest(const AddFriendRequest*);
    void handleAddFriendResult(const AddFriendResult*);
    void handleFriendLogoff(const LogoffRequest*);
    void handleFriendLogon(const FriendLogon*);

private:
    QTcpSocket m_tcpSocket;     // Tcp 套接字
    QUdpSocket m_udpSocket;     // Udp 套接字
    QHostAddress m_serverAddr;  // 服务器地址
    qint16 m_serverPort;        // 服务器端口号
    static QString s_name;      // 用户名
    int m_iconIndex;            // 头像头像索引
    int m_friendCount;          // 好友数
    bool m_isTcp;               // Tcp、Udp 协议标志
};
