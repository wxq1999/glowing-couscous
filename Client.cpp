#include "Client.h"
#include "Server.h"

/**
 * 构造方法。
 * @param socket  客户端套接字
 * @param server  服务器
 */
Client::Client(QTcpSocket* socket, Server* server) :
    m_socket(socket),
    m_server(server)
{
    if (socket != NULL)
    {
        QObject::connect(socket, SIGNAL(readyRead()), SLOT(onReceive()));
    }
}

/**
 * 构造方法。
 * @param ip    客户端 IP 地址
 * @param port  客户端端口号
 */
Client::Client(const QHostAddress& ip, quint16 port) :
    m_socket(NULL),
    m_server(NULL),
    m_ip(ip),
    m_port(port)
{
}

/**
 * 析构方法。
 */
Client::~Client()
{
    if (m_socket)
    {
        delete m_socket;
    }
}

/**
 * 获取客户端 IP 地址。
 * @return 客户端 IP 地址
 */
const QHostAddress& Client::getIP()
{
    return m_ip;
}

/**
 * 获取端口号。
 * @return 客户端端口号
 */
quint16 Client::getPort()
{
    return m_port;
}

/**
 * 发送数据。
 * @param data      数据
 * @param dataSize  数据长度
 * @return 实际发送的数据长度
 */
qint64 Client::sendData(const char* data, qint64 dataSize)
{
    quint64 ret = 0;
    if (m_socket)
    {
        // 发送数据大小
        ret = m_socket->write((const char*)&dataSize, sizeof(dataSize));
        if (ret <= 0)
        {
            return ret;
        }

        // 发送数据
        ret = m_socket->write(data, dataSize);
        m_socket->flush();
    }
    return ret;
}

/**
 * 接收到客户端数据的响应方法(Tcp)。
 */
void Client::onReceive()
{
    // 接收数据大小
    qint64 size = 0;
    qint64 read = m_socket->read((char*)&size, sizeof(size));
    if (read <= 0)
    {
        return;
    }

    // 接收数据
    char* buffer = new char[size];
    read = m_socket->read(buffer, size);
    if (read <= 0)
    {
        delete[] buffer;
        return;
    }

    // 处理协议
    m_server->onGetMessageFromClient((const Protocol*)buffer, this);

    // 释放缓存
    delete[] buffer;
}
