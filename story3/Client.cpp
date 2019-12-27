#include <QHostAddress>
#include <QDateTime>
#include <QMessageBox>
#include "LogonWindow.h"
#include "RegWindow.h"
#include "ChatWindow.h"
#include "../Common/Const.h"
#include "Client.h"

QString Client::s_name; // 用户名

/**
 * 构造方法。
 */
Client::Client() :
    m_friendCount(0)
{
    // 连接服务器 (Tcp) 或绑定端口 (Udp)
    Config config(Const::CONFIG_FILE_NAME);
    m_isTcp = config.isTcp();
    if (m_isTcp)
    {
        // 连接信号和槽
        QObject::connect(&m_tcpSocket, SIGNAL(readyRead()), SLOT(onReceive()));

        // 连接服务器
        QHostAddress serverAddr = config.getServerAddr();
        quint16 serverPort = config.getServerPort();
        m_tcpSocket.connectToHost(serverAddr, serverPort);
    }
    else
    {
        // 连接信号和槽
        QObject::connect(&m_udpSocket, SIGNAL(readyRead()), SLOT(onReceive()));

        // 获取服务器 IP 地址和端口号
        m_serverAddr = config.getServerAddr();
        m_serverPort = config.getServerPort();

        // 绑定客户端端口
        quint16 port = Const::CLIENT_PORT;
        while (!m_udpSocket.bind(port))
        {
            port++;
        }
    }
}

/**
 * 析构方法。
 */
Client::~Client()
{
    if (m_isTcp)
    {
        // 断开连接
        m_tcpSocket.disconnect();

        // 关闭 socket
        m_tcpSocket.close();
    }
    else
    {
        // 关闭 socket
        m_udpSocket.close();
    }
}

/**
 * 登录。
 * @return 结果
 */
Result::Code Client::logon()
{
    // 显示登录窗口
    LogonWindow logonWindow;
    int clickedButton = logonWindow.exec();
    if (clickedButton == QDialog::Rejected)
    {
        return Result::LOGON_SUCCESS;
    }

    // 获取用户输入的用户名和密码
    const QString& userName = logonWindow.getUserName();
    const QString& password = logonWindow.getPassword();

    // 发送登录请求
    LogonRequest request(userName, password);
    qint64 result = this->sendData(&request, sizeof(LogonRequest));
    if (result == -1)
    {
        return Result::NETWORK_WRONG;
    }

    s_name = userName;

    return Result::LOGON_SUCCESS;
}

/**
 * 注册。
 * @return 结果
 */
Result::Code Client::reg()
{
    // 显示注册窗口
    RegWindow regWindow;
    int clickedButton = regWindow.exec();
    if (clickedButton == QDialog::Rejected)
    {
        return Result::REG_SUCCESS;
    }

    // 获取用户名、密码和头像图标文件名
    const QString& userName = regWindow.getUserName();
    const QString& password = regWindow.getPassword();
    int iconIndex = regWindow.getIconIndex();

    // 发送注册请求
    RegRequest request(userName, password, iconIndex);
    qint64 result = this->sendData(&request, sizeof(RegRequest));
    if (result == -1)
    {
        return Result::NETWORK_WRONG;
    }

    // 保存用户名和头像索引
    s_name = userName;
    m_iconIndex = iconIndex;

    return Result::REG_SUCCESS;
}

/**
 * 聊天。
 * @param chat  聊天信息
 * @return 结果
 */
Result::Code Client::chat(const ChatInfo* chat)
{
    // 发送聊天信息
    qint64 result = this->sendData(chat, sizeof(ChatInfo));
    if (result == -1)
    {
        return Result::NETWORK_WRONG;
    }

    return Result::SUCCESS;
}

/**
 * 添加好友。
 * @param friendName    好友名字
 * @return 结果
 */
Result::Code Client::addFriend(const QString& friendName)
{
    // 检查是否超过好友上限
    if (m_friendCount > Const::MAX_USER_COUNT)
    {
        return Result::TOO_MANY_FRIENDS;
    }

    // 检查好友名
    if (friendName.isEmpty())
    {
        return Result::USER_NAME_EMPTY;
    }
    if (friendName.contains(Const::SPLIT_FLAT))
    {
        return Result::USER_NAME_INVALID;
    }
    if (friendName.length() > Const::USERNAME_LEN)
    {
        return Result::USER_NAME_TOO_LONG;
    }
    if (friendName == s_name)
    {
        return Result::FRIENDNAME_EQUAL_SELFNAME;
    }

    // 发送添加好友请求
    AddFriendRequest request(s_name, friendName, m_iconIndex);
    qint64 result = this->sendData(&request, sizeof(AddFriendRequest));
    if (result == -1)
    {
        return Result::NETWORK_WRONG;
    }

    return Result::SUCCESS;
}

/**
 * 离线。
 * @return 结果
 */
Result::Code Client::logoff()
{
    LogoffRequest request(s_name);
    qint64 result = this->sendData(&request, sizeof(LogoffRequest));
    s_name.clear();
    if (result == -1)
    {
        return Result::NETWORK_WRONG;
    }

    return Result::SUCCESS;
}

/**
 * 获取好友数。
 * @return 好友数
 */
int Client::getFriendCount()
{
    return m_friendCount;
}

/**
 * 获取自己的名字。
 * @return 自己的名字
 */
const QString& Client::getName()
{
    return s_name;
}

/**
 * 接收到服务器数据的响应方法。
 */
void Client::onReceive()
{
    if (m_isTcp)
    {
        this->onReceive_Tcp();
    }
    else
    {
        this->onReceive_Udp();
    }
}

/**
 * 接收到服务器数据的响应方法(Tcp)。
 */
void Client::onReceive_Tcp()
{
    // 接收数据大小
    qint64 size = 0;
    qint64 read = m_tcpSocket.read((char*)&size, sizeof(size));
    if (read <= 0)
    {
        return;
    }

    // 接收数据
    char* buffer = new char[size];
    read = m_tcpSocket.read(buffer, size);
    if (read <= 0)
    {
        delete[] buffer;
        return;
    }

    // 处理协议
    this->onGetMessageFromServer((const Protocol*)buffer);

    // 释放缓存
    delete[] buffer;
}

/**
 * 接收到服务器数据的响应方法(Udp)。
 */
void Client::onReceive_Udp()
{
    QByteArray datagram;
    Protocol* protocol = NULL;
    QHostAddress serverAddr;
    quint16 serverPort;

    while (m_udpSocket.hasPendingDatagrams())
    {
        // 设置数据包的大小
        datagram.resize(m_udpSocket.pendingDatagramSize());

        // 接收数据
        m_udpSocket.readDatagram(datagram.data(), datagram.size(), &serverAddr, &serverPort);

        // 将数据转换成协议
        protocol = (Protocol*)datagram.data();

        // 处理协议
        this->onGetMessageFromServer(protocol);
    }
}

/**
 * 发送数据。
 * @param data      数据
 * @param dataSize  数据长度
 * @return 实际发送的数据长度
 */
qint64 Client::sendData(const Protocol* data, qint64 dataSize)
{
    qint64 ret = 0;
    if (m_isTcp)
    {
        // 发送数据大小
        ret = m_tcpSocket.write((const char*)&dataSize, sizeof(dataSize));
        if (ret <= 0)
        {
            return ret;
        }

        // 发送数据
        ret = m_tcpSocket.write((const char*)data, dataSize);
        if (ret <= 0)
        {
            return ret;
        }
        m_tcpSocket.flush();
    }
    else
    {
        // 发送数据
        ret = m_udpSocket.writeDatagram((const char*)data, dataSize, m_serverAddr, m_serverPort);
    }
    return ret;
}

/**
 * 处理服务器发送来的数据。
 * @param protocol  协议
 */
void Client::onGetMessageFromServer(const Protocol* protocol)
{
    switch (protocol->getType())
    {
    case Protocol::Logon:
        this->handleLogonResult((LogonResult*)protocol);
        break;
    case Protocol::Reg:
        this->handleRegResult((RegResult*)protocol);
        break;
    case Protocol::Chat:
        this->handleChat((ChatInfo*)protocol);
        break;
    case Protocol::AddFriendRequest:
        this->handleAddFriendRequest((AddFriendRequest*)protocol);
        break;
    case Protocol::AddFriendResult:
        this->handleAddFriendResult((AddFriendResult*)protocol);
        break;
    case Protocol::Logoff:
        this->handleFriendLogoff((LogoffRequest*)protocol);
        break;
    case Protocol::FriendLogon:
        this->handleFriendLogon((FriendLogon*)protocol);
        break;
    default:
        break;
    }
}

/**
 * 处理登录结果。
 * @param result    登录结果
 */
void Client::handleLogonResult(const LogonResult* result)
{
    emit UM_GET_LOGON_RESULT(result);
    Result::Code resultCode = result->getResultCode();
    if (resultCode == Result::LOGON_SUCCESS)
    {
        m_iconIndex = result->getIconIndex();
        m_friendCount = result->getFriendCount();
    }
    else
    {
        s_name.clear();
        this->logon();
    }
}

/**
 * 处理注册结果。
 * @param result    注册结果
 */
void Client::handleRegResult(const RegResult* result)
{
    emit UM_GET_REG_RESULT(result);
    if (result->getResultCode() != Result::REG_SUCCESS)
    {
        s_name.clear();
        this->reg();
    }
}

/**
 * 处理聊天。
 * @param chat  聊天信息
 */
void Client::handleChat(const ChatInfo* chat)
{
    emit UM_CHAT_S2C(chat);
}

/**
 * 处理添加好友请求。
 * @param request   添加好友请求
 */
void Client::handleAddFriendRequest(const AddFriendRequest* request)
{
    const QString srcUserName(request->getSrcUserName());
    const QString dstUserName(request->getDstUserName());

    QString message(srcUserName);
    message += tr("IDS_CONFIRM_ADD_FRIEND");

    int clickedButton = QMessageBox::question(NULL, NULL, message);
    if (clickedButton == QMessageBox::Yes)  // 同意
    {
        // 向服务器发送结果
        AddFriendResult result(Result::ADD_FRIEND_ALLOW, srcUserName, dstUserName, m_iconIndex);
        this->sendData(&result, sizeof(AddFriendResult));
        m_friendCount++;

        // 将对方加为好友
        emit UM_GET_ADD_FRIEND_REQUEST(request);
    }
    else                                    // 不同意
    {
        // 向服务器发送结果
        AddFriendResult result(Result::ADD_FRIEND_NOT_ALLOW, srcUserName, dstUserName, 0);
        this->sendData(&result, sizeof(AddFriendResult));
    }
}

/**
 * 处理添加好友结果。
 * @param result    添加好友结果
 */
void Client::handleAddFriendResult(const AddFriendResult* result)
{
    if (result->getResultCode() == Result::ADD_FRIEND_ALLOW && result->getIconIndex() != -1)
    {
        m_friendCount++;
    }
    emit UM_GET_ADD_FRIEND_RESULT(result);
}

/**
 * 处理其他用户的离线请求。
 * @param request   其他用户的离线请求
 */
void Client::handleFriendLogoff(const LogoffRequest* request)
{
    emit UM_FRIEND_LOGOFF(request);
}

/**
 * 处理其他用户的登录消息。
 * @param friendLogon   其他用户的登录消息
 */
void Client::handleFriendLogon(const FriendLogon* friendLogon)
{
    emit UM_FRIEND_LOGON(friendLogon);
}
