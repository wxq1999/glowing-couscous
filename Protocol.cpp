#include <string.h>
#include "Protocol.h"

using namespace std;

/********** 协议基类 **********/
/**
 * 构造方法。
 * @param type  协议类型
 */
Protocol::Protocol(Type type) : m_type(type)
{
}

/**
 * 获取协议类型。
 * @return 协议类型
 */
Protocol::Type Protocol::getType() const
{
    return m_type;
}

/********** 登录请求 **********/
/**
 * 构造方法。
 * @param userName  用户名
 * @param password  密码
 */
LogonRequest::LogonRequest(const QString& userName, const QString& password) :
    Protocol(Protocol::Logon)
{
    strcpy(m_userName, userName.toStdString().c_str());
    strcpy(m_password, password.toStdString().c_str());
}

/**
 * 获取用户名。
 * @return 用户名
 */
const char* LogonRequest::getUserName() const
{
    return m_userName;
}

/**
 * 获取密码。
 * @return 密码
 */
const char* LogonRequest::getPassword() const
{
    return m_password;
}

/********** 登录结果 **********/
/**
 * 构造方法。
 */
LogonResult::LogonResult() :
    Protocol(Protocol::Logon),
    m_friendCount(0)
{
    memset(m_friendIconIndexs, 0, sizeof(m_friendIconIndexs));
    memset(m_friendNames, 0, sizeof(m_friendNames));
}

/**
 * 获取登录结果。
 * @return 登录结果
 */
Result::Code LogonResult::getResultCode() const
{
    return m_resultCode;
}

/**
 * 获取头像索引。
 * @return 头像索引
 */
int LogonResult::getIconIndex() const
{
    return m_iconIndex;
}

/**
 * 获取好友数。
 * @return 好友数
 */
int LogonResult::getFriendCount() const
{
    return m_friendCount;
}

/**
 * 获取好友名列表。
 * @param friendNames   好友名列表
 */
void LogonResult::getFriendNames(QStringList& friendNames) const
{
    QByteArray byteArray(m_friendNames, sizeof(m_friendNames));
    QList<QByteArray> friendsNames = byteArray.split(Const::SPLIT_FLAT);

    int count = friendsNames.count();
    for (int i = 0; i < count; i++)
    {
        friendNames.append(QString(friendsNames[i]));
    }
}

/**
 * 获取好友头像索引列表。
 * @return 好友头像索引列表
 */
const int* LogonResult::getFriendIconIndexs() const
{
    return m_friendIconIndexs;
}

/**
 * 获取某个好友是否在线。
 * @param index 好友索引
 * @return true 表示在线，false 表示不在线
 */
bool LogonResult::isFriendOnline(int index) const
{
    return m_friendsOnline[index];
}

/**
 * 设置登录结果。
 * @param resultCode    登录结果
 */
void LogonResult::setResultCode(Result::Code resultCode)
{
    m_resultCode = resultCode;
}

/**
 * 设置头像索引。
 * @param iconIndex    头像索引
 */
void LogonResult::setIconIndex(int iconIndex)
{
    m_iconIndex = iconIndex;
}

/**
 * 设置好友数。
 * @param friendCount   好友数
 */
void LogonResult::setFriendCount(int friendCount)
{
    m_friendCount = friendCount;
}

/**
 * 设置好友名列表。
 * @param friendNames   好友名列表
 */
void LogonResult::setFriendNames(const QString& friendNames)
{
    strcpy(m_friendNames, friendNames.toStdString().c_str());
}

/**
 * 设置好友头像索引列表。
 * @param iconIndexs    头像索引列表
 * @param count         列表中的元素个数
 */
void LogonResult::setFriendIconIndexs(const int* iconIndexs, int count)
{
    memcpy(m_friendIconIndexs, iconIndexs, count * sizeof(int));
}

/**
 * 设置某个好友的在线状态。
 * @param index     好友索引
 * @param isOnline  true 表示在线，false 表示不在线
 */
void LogonResult::setFriendsOnline(int index, bool isOnline)
{
    m_friendsOnline[index] = isOnline;
}

/********** 注册请求 **********/
/**
 * 构造方法。
 * @param userName  用户名
 * @param password  密码
 * @param iconIndex 头像索引
 */
RegRequest::RegRequest(const QString& userName, const QString& password, int iconIndex) :
    Protocol(Protocol::Reg),
    m_iconIndex(iconIndex)
{
    strcpy(m_userName, userName.toStdString().c_str());
    strcpy(m_password, password.toStdString().c_str());
}

/**
 * 获取用户名。
 * @return 用户名
 */
const char* RegRequest::getUserName() const
{
    return m_userName;
}

/**
 * 获取密码。
 * @return 密码
 */
const char* RegRequest::getPassword() const
{
    return m_password;
}

/**
 * 获取头像索引。
 * @return 头像索引
 */
int RegRequest::getIconIndex() const
{
    return m_iconIndex;
}

/********** 注册结果 **********/
/**
 * 构造方法。
 */
RegResult::RegResult() : Protocol(Protocol::Reg)
{
}

/**
 * 获取结果。
 * @return 结果
 */
Result::Code RegResult::getResultCode() const
{
    return m_resultCode;
}

/**
 * 设置结果。
 * @param resultCode    结果
 */
void RegResult::setResultCode(Result::Code resultCode)
{
    m_resultCode = resultCode;
}

/********** 添加好友请求 **********/
/**
 * 构造方法。
 */
AddFriendRequest::AddFriendRequest() : Protocol(Protocol::AddFriendRequest)
{
}

/**
 * 构造方法。
 * @param srcUserName   源用户名
 * @param dstUserName   目标用户名
 * @param iconIndex     源用户的头像索引
 */
AddFriendRequest::AddFriendRequest(const QString& srcUserName, const QString& dstUserName, int iconIndex) :
    Protocol(Protocol::AddFriendRequest),
    m_iconIndex(iconIndex)
{
    strcpy(m_srcUserName, srcUserName.toStdString().c_str());
    strcpy(m_dstUserName, dstUserName.toStdString().c_str());
}

/**
 * 获取源用户名。
 * @return 源用户名
 */
const char* AddFriendRequest::getSrcUserName() const
{
    return m_srcUserName;
}

/**
 * 获取目标用户名。
 * @return 目标用户名
 */
const char* AddFriendRequest::getDstUserName() const
{
    return m_dstUserName;
}

/**
 * 获取源用户头像索引。
 * @return 源用户头像索引
 */
int AddFriendRequest::getIconIndex() const
{
    return m_iconIndex;
}

/********** 添加好友结果 **********/
/**
 * 构造方法。
 */
AddFriendResult::AddFriendResult() : Protocol(Protocol::AddFriendResult)
{
}

/**
 * 构造方法。
 * @param resultCode    结果
 * @param srcUserName   源用户名
 * @param dstUserName   目标用户名
 * @param iconIndex     目标用户头像索引
 */
AddFriendResult::AddFriendResult(Result::Code resultCode,
    const QString& srcUserName, const QString& dstUserName, int iconIndex) :
    Protocol(Protocol::AddFriendResult),
    m_resultCode(resultCode),
    m_dstUserIconIndex(iconIndex)
{
    if (!srcUserName.isEmpty())
    {
        strcpy(m_srcUserName, srcUserName.toStdString().c_str());
    }
    else
    {
        memset(m_srcUserName, 0, sizeof(m_srcUserName));
    }

    if (!dstUserName.isEmpty())
    {
        strcpy(m_dstUserName, dstUserName.toStdString().c_str());
    }
    else
    {
        memset(m_dstUserName, 0, sizeof(m_dstUserName));
    }
}

/**
 * 获取结果。
 * @return 结果
 */
Result::Code AddFriendResult::getResultCode() const
{
    return m_resultCode;
}

/**
 * 获取源用户名。
 * @return 源用户名
 */
const char* AddFriendResult::getSrcUserName() const
{
    return m_srcUserName;
}

/**
 * 获取目标用户名。
 * @return 目标用户名
 */
const char* AddFriendResult::getDstUserName() const
{
    return m_dstUserName;
}

/**
 * 获取目标用户头像索引。
 * @return 目标用户头像索引
 */
int AddFriendResult::getIconIndex() const
{
    return m_dstUserIconIndex;
}

/********** 聊天信息 **********/
/**
 * 构造方法。
 */
ChatInfo::ChatInfo() : Protocol(Protocol::Chat)
{
}

/**
 * 构造方法。
 * @param srcUserName   源用户名
 * @param dstUserName   目标用户名
 * @param content       聊天内容
 * @param time          时间
 */
ChatInfo::ChatInfo(const QString& srcUserName, const QString& dstUserName,
    const QString& content, const QString& time) :
    Protocol(Protocol::Chat)
{
    strcpy(m_srcUserName, srcUserName.toStdString().c_str());
    strcpy(m_dstUserName, dstUserName.toStdString().c_str());
    strcpy(m_content, content.toStdString().c_str());
    strcpy(m_time, time.toStdString().c_str());
}

/**
 * 获取源用户名。
 * @return 源用户名
 */
const char* ChatInfo::getSrcUserName() const
{
    return m_srcUserName;
}

/**
 * 获取目标用户名。
 * @return 目标用户名
 */
const char* ChatInfo::getDstUserName() const
{
    return m_dstUserName;
}

/**
 * 获取聊天内容。
 * @return 聊天内容
 */
const char* ChatInfo::getContent() const
{
    return m_content;
}

/**
 * 获取时间。
 * @return 时间
 */
const char* ChatInfo::getTime() const
{
    return m_time;
}

/********** 离线请求 **********/
/**
 * 构造方法。
 */
LogoffRequest::LogoffRequest() : Protocol(Protocol::Logoff)
{
}

/**
 * 构造方法。
 * @param userName  用户名
 */
LogoffRequest::LogoffRequest(const QString& userName) :
    Protocol(Protocol::Logoff)
{
    strcpy(m_userName, userName.toStdString().c_str());
}

/**
 * 获取用户名。
 * @return 用户名
 */
const char* LogoffRequest::getUserName() const
{
    return m_userName;
}

/********** 好友上线通知 **********/
/**
 * 构造方法。
 */
FriendLogon::FriendLogon() : Protocol(Protocol::FriendLogon)
{
}

/**
 * 构造方法。
 * @param userName  用户名
 */
FriendLogon::FriendLogon(const char* userName) :
    Protocol(Protocol::FriendLogon)
{
    strcpy(m_userName, userName);
}

/**
 * 获取用户名。
 * @return 用户名
 */
const char* FriendLogon::getUserName() const
{
    return m_userName;
}
