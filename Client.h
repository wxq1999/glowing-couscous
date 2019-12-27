#pragma once

#include <QTcpSocket>
#include <QHostAddress>

class Server;

class Client : public QObject
{
    Q_OBJECT

public:
    Client(QTcpSocket*, Server*);
    Client(const QHostAddress&, quint16);
    ~Client();
    const QHostAddress& getIP();
    quint16 getPort();
    qint64 sendData(const char*, qint64);

private slots:
    void onReceive();

private:
    QTcpSocket* m_socket;   // 套接字
    Server* m_server;       // 服务器
    QHostAddress m_ip;      // 客户端 IP 地址
    quint16 m_port;         // 客户端端口号
};
