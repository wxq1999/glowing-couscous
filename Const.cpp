#include "Const.h"

// 可配置内容
const char* Const::CONFIG_FILE_NAME = "../Config.ini";          // 配件文件的路径
const char* Const::CONFIG_SERVER_IP = "/Server/IP";             // 服务器IP地址
const char* Const::CONFIG_SERVER_PORT = "/Server/Port";         // 服务器端口号
const char* Const::CONFIG_IS_TCP = "/Server/IsTcp";             // Tcp、Udp 协议标志

// 数据库
const char* Const::DB_DRIVER = "QSQLITE";                       // 数据库驱动名
const char* Const::DB_NAME = "../Database/Server.db";           // 数据库名

// 数据库 - 用户表
const char* Const::TABLE_USERS = "Users";                       // 表名
const char* Const::FIELD_NAME = "Name";                         // "姓名"字段
const char* Const::FIELD_PASSWORD = "Password";                 // "密码"字段
const char* Const::FIELD_ICON_INDEX = "IconIndex";              // "头像索引"字段

// 数据库 - 好友表
const char* Const::TABLE_FRIENDS = "Friends";                   // 表名
const char* Const::FIELD_OWNER = "Owner";                       // 好友拥有者
const char* Const::FIELD_FRIEND_NAME = "FriendName";            // 好友名

// 数据库 - 离线聊天表
const char* Const::TABLE_OFFLINE_CHAT = "OfflineChat";          // 表名
const char* Const::FIELD_SRC_USER = "SrcUser";                  // 源用户
const char* Const::FIELD_DST_USER = "DstUser";                  // 目标用户
const char* Const::FIELD_CONTENT = "Content";                   // 聊天内容
const char* Const::FIELD_TIME = "Time";                         // 时间

// 数据库 - 离线添加好友请求表
const char* Const::TABLE_OFFLINE_ADD_FRIEND_REQUEST =
    "OfflineAddFriendRequest";                                  // 表名

// 数据库 - 离线添加好友结果表
const char* Const::TABLE_OFFLINE_ADD_FRIEND_RESULT =
    "OfflineAddFriendResult";                                   // 表名
const char* Const::FIELD_ADD_FRIEND_RESULT = "AddFriendResult"; // 结果

// 其它
const char* Const::DATE_TIME_FORMAT = "yyyy-MM-dd hh:mm:ss";    // 时间格式
const QString Const::MULTI_CHAT(QString::fromUtf8("群聊"));     // 群聊标志
const char* Const::ICON_FILE_NAME = ":/png/res/%1.png";         // 客户端图标文件名
