#include <QFile>
#include <QSqlQuery>
#include <QMessageBox>
#include <QNetworkInterface>
#include <QHostInfo>
#include <QProcess>
#include <QThread>
#include <string.h>
#include "Server.h"
#include "../Common/Config.h"
#include "../Common/Result.h"

using namespace std;

/**
 * 构造方法。
 */
Server::Server() : m_database(QSqlDatabase::addDatabase(Const::DB_DRIVER))
{
    // 创建数据库
    this->createDatabase();

    // 连接信号和槽
    QObject::connect(&m_tcpServer, SIGNAL(newConnection()), SLOT(onAccept()));
    QObject::connect(&m_udpServer, SIGNAL(readyRead()), SLOT(onReceive()));
}

/**
 * 析构方法。
 */
Server::~Server()
{
    // 停止服务
    this->stop();

    // 关闭数据库
    m_database.close();
}

/**
 * 开启服务。
 */
void Server::begin()
{
    Config config(Const::CONFIG_FILE_NAME);
    QHostAddress ip = config.getServerAddr();   // IP
    quint16 port = config.getServerPort();      // 端口号
    m_isTcp = config.isTcp();

    if (m_isTcp)
    {
        // 侦听端口
        while (!m_tcpServer.listen(ip, port))
        {
            port++;
        }
    }
    else
    {
        // 绑定端口
        while (!m_udpServer.bind(ip, port))
        {
            port++;
        }
    }
}

/**
 * 关闭服务。
 */
void Server::stop()
{
    // 关闭服务
    m_tcpServer.close();
    m_udpServer.close();

    // 清空在线用户列表
    OnlineUsers::iterator end = m_olineUsers.end();
    for (OnlineUsers::iterator i = m_olineUsers.begin(); i != end; i++)
    {
        delete i.value();
    }
    m_olineUsers.clear();
}

/**
 * 获取服务器地址。
 * @return 服务器地址
 */
QString Server::getAddress()
{
    if (m_isTcp)
    {
        return m_tcpServer.serverAddress().toString();
    }
    return m_udpServer.localAddress().toString();
}

/**
 * 获取服务器端口号。
 * @return 服务器端口号
 */
quint16 Server::getPort()
{
    if (m_isTcp)
    {
        return m_tcpServer.serverPort();
    }
    return m_udpServer.localPort();
}

/**
 * 处理客户端发送来的数据。
 * @param protocol  协议
 * @param client    客户端
 */
void Server::onGetMessageFromClient(const Protocol* protocol, Client* client)
{
    switch (protocol->getType())
    {
    case Protocol::Logon:
        this->handleLogon((LogonRequest*)protocol, client);
        break;
    case Protocol::Reg:
        this->handleReg((RegRequest*)protocol, client);
        break;
    case Protocol::Chat:
        this->handleChat((ChatInfo*)protocol);
        break;
    case Protocol::AddFriendRequest:
        this->handleAddFriendRequest((AddFriendRequest*)protocol, client);
        break;
    case Protocol::AddFriendResult:
        this->handleAddFriendResult((AddFriendResult*)protocol);
        break;
    case Protocol::Logoff:
        this->handleLogoff((LogoffRequest*)protocol);
        break;
    default:
        break;
    }
}

/**
 * 客户端连接事件的响应方法。
 */
void Server::onAccept()
{
    QTcpSocket* clientSocket = m_tcpServer.nextPendingConnection();
    new Client(clientSocket, this);
}

/**
 * 接收到客户端数据的响应方法(Udp)。
 */
void Server::onReceive()
{
    QByteArray datagram;        // 客户端发来的数据
    QHostAddress clientIP;      // 客户端 IP 地址
    quint16 clientPort = 0;     // 客户端端口号
    Client* client = NULL;      // 客户端
    Protocol* protocol = NULL;  // 协议

    while (m_udpServer.hasPendingDatagrams())
    {
        datagram.resize(m_udpServer.pendingDatagramSize());
        m_udpServer.readDatagram(datagram.data(), datagram.size(), &clientIP, &clientPort);
        protocol = (Protocol*)datagram.data();
        client = new Client(clientIP, clientPort);
        this->onGetMessageFromClient(protocol, client);
    }
}

/**
 * 创建数据库。
 */
void Server::createDatabase()
{
    // 创建数据库
    m_database.setDatabaseName(Const::DB_NAME);
    m_database.open();

    // 创建表
    QSqlQuery query(m_database);
    QString sql;

    /* 用户表 */
    sql = QString("CREATE TABLE IF NOT EXISTS %1(%2 VARCHAR(%3) PRIMARY KEY,%4 VARCHAR(%5),%6 INTEGER)").
        arg(Const::TABLE_USERS).arg(Const::FIELD_NAME).arg(Const::USERNAME_LEN).
        arg(Const::FIELD_PASSWORD).arg(Const::PASSWORD_LEN).arg(Const::FIELD_ICON_INDEX);
    query.exec(sql);

    /* 好友表 */
    sql = QString("CREATE TABLE IF NOT EXISTS %1(%2 VARCHAR(%3),%4 VARCHAR(%5))").
        arg(Const::TABLE_FRIENDS).arg(Const::FIELD_OWNER).arg(Const::USERNAME_LEN).
        arg(Const::FIELD_FRIEND_NAME).arg(Const::USERNAME_LEN);
    query.exec(sql);

    /* 离线聊天表 */
    sql = QString("CREATE TABLE IF NOT EXISTS %1(%2 VARCHAR(%3),%4 VARCHAR(%5),%6 VARCHAR(%7),%8 VARCHAR(%9))").
        arg(Const::TABLE_OFFLINE_CHAT).arg(Const::FIELD_DST_USER).arg(Const::USERNAME_LEN).
        arg(Const::FIELD_SRC_USER).arg(Const::USERNAME_LEN).arg(Const::FIELD_CONTENT).
        arg(Const::CONTENT_LEN).arg(Const::FIELD_TIME).arg(Const::TIME_LEN);
    query.exec(sql);

    /* 离线添加好友请求表 */
    sql = QString("CREATE TABLE IF NOT EXISTS %1(%2 VARCHAR(%3),%4 VARCHAR(%5))").
        arg(Const::TABLE_OFFLINE_ADD_FRIEND_REQUEST).arg(Const::FIELD_DST_USER).
        arg(Const::USERNAME_LEN).arg(Const::FIELD_SRC_USER).arg(Const::USERNAME_LEN);
    query.exec(sql);

    /* 离线添加好友结果表 */
    sql = QString("CREATE TABLE IF NOT EXISTS %1(%2 VARCHAR(%3),%4 VARCHAR(%5),%6 INTEGER)").
        arg(Const::TABLE_OFFLINE_ADD_FRIEND_RESULT).arg(Const::FIELD_SRC_USER).
        arg(Const::USERNAME_LEN).arg(Const::FIELD_DST_USER).
        arg(Const::USERNAME_LEN).arg(Const::FIELD_ADD_FRIEND_RESULT);
    query.exec(sql);
}

/**
 * 发送数据。
 * @param client    客户端
 * @param data      数据
 * @param dataSize  数据长度
 * @return 实际发送的数据的长度
 */
qint64 Server::sendData(Client* client, const Protocol* data, qint64 dataSize)
{
    if (m_isTcp)
    {
        return client->sendData((const char*)data, dataSize);
    }
    return m_udpServer.writeDatagram((const char*)data, dataSize, client->getIP(), client->getPort());
}

/**
 * 处理登录请求。
 * @param request   请求
 * @param client    客户端
 */
void Server::handleLogon(const LogonRequest* request, Client* client)
{
    LogonResult logonResult;
    const char* userName = request->getUserName();
    const char* password = request->getPassword();
    QSqlQuery query(m_database);
    QString sql;

    // 检查该用户是否已经登录
    OnlineUsers::iterator it = m_olineUsers.find(userName);
    if (!it.key().isEmpty())
    {
        logonResult.setResultCode(Result::USER_ALREADY_LOGON);
        this->sendData(client, &logonResult, sizeof(LogonResult));
        return;
    }

    // 从数据库中查找该用户
    sql = QString("SELECT * FROM %1 WHERE %2='%3'").arg(Const::TABLE_USERS).arg(Const::FIELD_NAME).arg(userName);
    query.exec(sql);
    query.next();

    // 比对用户名
    const QString userNameInDB(query.value(Const::FIELD_NAME).toString());
    if (userNameInDB != userName)
    {
        logonResult.setResultCode(Result::USER_NOT_FOUND);
        this->sendData(client, &logonResult, sizeof(LogonResult));
        return;
    }

    // 比对密码
    const QString passwordInDB(query.value(Const::FIELD_PASSWORD).toString());
    if (passwordInDB != password)
    {
        logonResult.setResultCode(Result::PASSWORD_WRONG);
        this->sendData(client, &logonResult, sizeof(LogonResult));
        return;
    }

    // 登录成功，获取该用户的相关信息
    logonResult.setResultCode(Result::LOGON_SUCCESS);
    logonResult.setIconIndex(query.value(Const::FIELD_ICON_INDEX).toInt());

    // 获取该用户的好友列表
    sql = QString("SELECT * FROM %1 WHERE %2='%3'").arg(Const::TABLE_FRIENDS).arg(Const::FIELD_OWNER).arg(userName);
    query.exec(sql);

    QString oneFriendName;
    QString allFriendNames;
    int allFriendIconIndexs[Const::MAX_USER_COUNT];
    QSqlQuery query_temp(m_database);
    bool isOnline = false;
    int friendCount = 0;

    for (friendCount = 0; query.next(); friendCount++)
    {
        oneFriendName = query.value(Const::FIELD_FRIEND_NAME).toString();
        allFriendNames += oneFriendName + Const::SPLIT_FLAT;

        sql = QString("SELECT %1 FROM %2 WHERE %3='%4'").arg(Const::FIELD_ICON_INDEX).
            arg(Const::TABLE_USERS).arg(Const::FIELD_NAME).arg(oneFriendName);
        query_temp.exec(sql);
        query_temp.next();

        allFriendIconIndexs[friendCount] = query_temp.value(Const::FIELD_ICON_INDEX).toInt();
        OnlineUsers::iterator it = m_olineUsers.find(oneFriendName);
        isOnline = !it.key().isEmpty();
        logonResult.setFriendsOnline(friendCount, isOnline);

        // 如果好友在线，则通知他该用户已经登录了
        if (isOnline)
        {
            FriendLogon friendLogon(userName);
            this->sendData(it.value(), &friendLogon, sizeof(FriendLogon));
        }
    }

    if (!allFriendNames.isEmpty())
    {
        allFriendNames = allFriendNames.left(allFriendNames.length() - 1);
        logonResult.setFriendNames(allFriendNames);
    }
    if (friendCount > 0)
    {
        logonResult.setFriendIconIndexs(allFriendIconIndexs, friendCount);
        logonResult.setFriendCount(friendCount);
    }

    // 发送登录结果
    this->sendData(client, &logonResult, sizeof(LogonResult));
    QThread::msleep(10);

    // 查询是否有和该用户相关的离线添加好友请求，有则发送
    sql = QString("SELECT * FROM %1 WHERE %2='%3'").
        arg(Const::TABLE_OFFLINE_ADD_FRIEND_REQUEST).arg(Const::FIELD_DST_USER).arg(userName);
    query.exec(sql);
    const QString dstUserName(userName);
    while (query.next())
    {
        const QString srcUserName(query.value(Const::FIELD_SRC_USER).toString());
        sql = QString("SELECT %1 FROM %2 WHERE %3='%4'").arg(Const::FIELD_ICON_INDEX).
            arg(Const::TABLE_USERS).arg(Const::FIELD_NAME).arg(srcUserName);
        QSqlQuery query_temp(m_database);
        query_temp.exec(sql);
        query_temp.next();
        AddFriendRequest addFriendRequest(srcUserName, dstUserName, query_temp.value(Const::FIELD_ICON_INDEX).toInt());
        this->sendData(client, &addFriendRequest, sizeof(AddFriendRequest));
        QThread::msleep(10);
    }
    sql = QString("DELETE FROM %1 WHERE %2='%3'").
        arg(Const::TABLE_OFFLINE_ADD_FRIEND_REQUEST).arg(Const::FIELD_DST_USER).arg(userName);
    query.exec(sql);

    // 查询是否有和该用户相关的离线添加好友结果，有则发送
    sql = QString("SELECT * FROM %1 WHERE %2='%3'").
        arg(Const::TABLE_OFFLINE_ADD_FRIEND_RESULT).arg(Const::FIELD_SRC_USER).arg(userName);
    query.exec(sql);
    const QString srcUserName(userName);
    while (query.next())
    {
        const QString dstUserName(query.value(Const::FIELD_DST_USER).toString());
        Result::Code result = (Result::Code)query.value(Const::FIELD_ADD_FRIEND_RESULT).toInt();
        AddFriendResult addFriendResult(result, srcUserName, dstUserName, -1);
        this->sendData(client, &addFriendResult, sizeof(AddFriendResult));
        QThread::msleep(10);
    }
    sql = QString("DELETE FROM %1 WHERE %2='%3'").
        arg(Const::TABLE_OFFLINE_ADD_FRIEND_RESULT).arg(Const::FIELD_SRC_USER).arg(userName);
    query.exec(sql);

    // 查询是否有和该用户相关的离线聊天消息，有则发送
    sql = QString("SELECT * FROM %1 WHERE %2='%3'").arg(Const::TABLE_OFFLINE_CHAT).arg(Const::FIELD_DST_USER).arg(userName);
    query.exec(sql);
    while (query.next())
    {
        const QString srcUserName(query.value(Const::FIELD_SRC_USER).toString());
        const QString content(query.value(Const::FIELD_CONTENT).toString());
        const QString time(query.value(Const::FIELD_TIME).toString());
        ChatInfo chat(srcUserName, userName, content, time);
        this->sendData(client, &chat, sizeof(ChatInfo));
        QThread::msleep(10);
    }
    sql = QString("DELETE FROM %1 WHERE %2='%3'").arg(Const::TABLE_OFFLINE_CHAT).arg(Const::FIELD_DST_USER).arg(userName);
    query.exec(sql);

    // 将该用户加入在线列表
    m_olineUsers.insert(userName, client);
}

/**
 * 处理注册请求。
 * @param request   请求
 * @param client    客户端
 */
void Server::handleReg(const RegRequest* request, Client* client)
{
    RegResult regResult;
    const char* userName = request->getUserName();
    const char* password = request->getPassword();
    int iconIndex = request->getIconIndex();
    QSqlQuery query(m_database);
    QString sql;
    bool result = false;

    // 将该用户信息插入到数据库中
    sql = QString("INSERT INTO %1 VALUES('%2','%3','%4')").arg(Const::TABLE_USERS).arg(userName).arg(password).arg(iconIndex);
    result = query.exec(sql);
    if (!result)
    {
        regResult.setResultCode(Result::USER_EXISTS);
        this->sendData(client, &regResult, sizeof(RegResult));
        return;
    }

    // 发送结果
    regResult.setResultCode(Result::REG_SUCCESS);
    this->sendData(client, &regResult, sizeof(RegResult));

    // 将该用户加入到在线列表中
    m_olineUsers.insert(userName, client);
}

/**
 * 处理聊天。
 * @param chat  聊天信息
 */
void Server::handleChat(const ChatInfo* chat)
{
    const char* srcUserName = chat->getSrcUserName();
    QString dstUserName(chat->getDstUserName());
    QSqlQuery query(m_database);
    QString sql;

    // 处理群聊
    if (dstUserName == Const::MULTI_CHAT)
    {
        OnlineUsers::iterator end = m_olineUsers.end();
        for (OnlineUsers::iterator i = m_olineUsers.begin(); i != end; i++)
        {
            if (i.key() == srcUserName)
            {
                continue;
            }
            this->sendData(i.value(), chat, sizeof(ChatInfo));
        }
        return;
    }

    // 如果目标用户不在线，则将聊天信息插入到数据库中
    OnlineUsers::iterator it = m_olineUsers.find(dstUserName);
    if (it.key().isEmpty())
    {
        const char* content = chat->getContent();
        const char* time = chat->getTime();
        sql = QString("INSERT INTO %1 VALUES('%2','%3','%4','%5')").
            arg(Const::TABLE_OFFLINE_CHAT).arg(dstUserName).arg(srcUserName).arg(content).arg(time);
        query.exec(sql);
        return;
    }

    // 发送给目标用户
    this->sendData(it.value(), chat, sizeof(ChatInfo));
}

/**
 * 处理添加好友请求。
 * @param request   请求
 * @param client    客户端
 */
void Server::handleAddFriendRequest(const AddFriendRequest* request, Client* client)
{
    const char* srcUserName = request->getSrcUserName();
    const char* dstUserName = request->getDstUserName();
    QSqlQuery query(m_database);
    QString sql;

    // 检查目标用户是否存在
    sql = QString("SELECT * FROM %1 WHERE %2='%3'").arg(Const::TABLE_USERS).arg(Const::FIELD_NAME).arg(dstUserName);
    query.exec(sql);
    query.next();
    if (!query.isValid())
    {
        // 查无此人，通知源用户
        AddFriendResult result(Result::USER_NOT_FOUND, NULL, dstUserName, 0);
        this->sendData(client, &result, sizeof(AddFriendResult));
        return;
    }

    // 检查是否已经是好友了
    sql = QString("SELECT * FROM %1 WHERE %2='%3' AND %4='%5'").arg(Const::TABLE_FRIENDS).
        arg(Const::FIELD_OWNER).arg(srcUserName).arg(Const::FIELD_FRIEND_NAME).arg(dstUserName);
    query.exec(sql);
    query.next();
    if (query.isValid())
    {
        AddFriendResult result(Result::ALREADY_BE_FRIENDS, NULL, dstUserName, 0);
        this->sendData(client, &result, sizeof(AddFriendResult));
        return;
    }

    // 如果目标用户不在线，则将请求信息插入到数据库中
    OnlineUsers::iterator it = m_olineUsers.find(dstUserName);
    if (it.key().isEmpty())
    {
        sql = QString("INSERT INTO %1 VALUES('%2','%3')").
            arg(Const::TABLE_OFFLINE_ADD_FRIEND_REQUEST).arg(dstUserName).arg(srcUserName);
        query.exec(sql);
        return;
    }

    // 向目标用户发请求
    this->sendData(it.value(), request, sizeof(AddFriendRequest));
}

/**
 * 处理添加好友结果。
 * @param request   结果
 */
void Server::handleAddFriendResult(const AddFriendResult* result)
{
    const char* srcUserName = result->getSrcUserName();
    const char* dstUserName = result->getDstUserName();

    Result::Code resultCode = result->getResultCode();
    QSqlQuery query(m_database);
    QString sql;

    // 如果结果是同意，则将相关信息写到好友表中
    if (resultCode == Result::ADD_FRIEND_ALLOW)
    {
        sql = QString("INSERT INTO %1 VALUES('%2','%3')").arg(Const::TABLE_FRIENDS).arg(srcUserName).arg(dstUserName);
        query.exec(sql);

        sql = QString("INSERT INTO %1 VALUES('%2','%3')").arg(Const::TABLE_FRIENDS).arg(dstUserName).arg(srcUserName);
        query.exec(sql);
    }

    // 如果目标用户不在线，则将结果信息插入到数据库中
    OnlineUsers::iterator it = m_olineUsers.find(srcUserName);
    if (it.key().isEmpty())
    {
        sql = QString("INSERT INTO %1 VALUES('%2','%3','%4')").
            arg(Const::TABLE_OFFLINE_ADD_FRIEND_RESULT).arg(srcUserName).arg(dstUserName).arg(resultCode);
        query.exec(sql);
        return;
    }

    // 向目标用户发请求
    this->sendData(it.value(), result, sizeof(AddFriendResult));
}

/**
 * 处理离线请求。
 * @param request   离线请求
 */
void Server::handleLogoff(const LogoffRequest* request)
{
    // 广播该用户的离线请求
    OnlineUsers::iterator end = m_olineUsers.end();
    for (OnlineUsers::iterator it = m_olineUsers.begin(); it != end; it++)
    {
        // 跳过自己
        if (it.key() == request->getUserName())
        {
            continue;
        }
        this->sendData(it.value(), request, sizeof(LogoffRequest));
    }

    // 将该用户从在线列表移除
    const char* userName = request->getUserName();
    m_olineUsers.remove(userName);
}
