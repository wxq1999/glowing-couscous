#pragma once

#include <QTcpSocket>
#include <QTcpServer>
#include <QUdpSocket>
#include <QSqlDatabase>
#include "../Common/Protocol.h"
#include "Client.h"

typedef QMap<QString, Client*> OnlineUsers;

class Server : public QObject
{
    Q_OBJECT

    friend class Client;

public:
    explicit Server();
    ~Server();
    void begin();
    void stop();
    QString getAddress();
    quint16 getPort();
    void onGetMessageFromClient(const Protocol*, Client*);

private slots:
    void onAccept();
    void onReceive();

private:
    void createDatabase();
    qint64 sendData(Client*, const Protocol*, qint64);
    void handleLogon(const LogonRequest*, Client*);
    void handleReg(const RegRequest*, Client*);
    void handleChat(const ChatInfo*);
    void handleAddFriendRequest(const AddFriendRequest*, Client*);
    void handleAddFriendResult(const AddFriendResult*);
    void handleLogoff(const LogoffRequest*);

private:
    QTcpServer m_tcpServer;     // Tcp 服务器
    QUdpSocket m_udpServer;     // Udp 服务器
    QSqlDatabase m_database;    // 数据库
    OnlineUsers m_olineUsers;   // 在线用户列表
    bool m_isTcp;               // Tcp、Udp 协议标志
};
