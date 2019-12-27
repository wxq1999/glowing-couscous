#pragma once

#include <QString>

class Const
{
public:
    // 数据长度
    static const int USERNAME_LEN = 11;                     // 最大用户名长度
    static const int PASSWORD_LEN = 12;                     // 最大密码长度
    static const int CONTENT_LEN = 1023;                    // 一次发送的最大聊天内容长度
    static const int MAX_USER_COUNT = 100;                  // 最大用户数
    static const int FRIEND_NAMES_LEN =
        (USERNAME_LEN + 1) * MAX_USER_COUNT;                // 所有好友名字加在一起的最大长度
    static const int TIME_LEN = 19;                         // 时间长度

    // 可配置内容
    static const char* CONFIG_FILE_NAME;                    // 配置文件的文件名
    static const char* CONFIG_SERVER_IP;                    // 服务器 IP 地址
    static const char* CONFIG_SERVER_PORT;                  // 服务器端口号
    static const char* CONFIG_IS_TCP;                       // Tcp、Udp 协议标志

    // 数据库
    static const char* DB_DRIVER;                           // 数据库驱动名
    static const char* DB_NAME;                             // 数据库名

    // 数据库 - 用户表
    static const char* TABLE_USERS;                         // 用户表名
    static const char* FIELD_NAME;                          // "姓名"字段
    static const char* FIELD_PASSWORD;                      // "密码"字段
    static const char* FIELD_ICON_INDEX;                    // "头像索引"字段

    // 数据库 - 好友表
    static const char* TABLE_FRIENDS;                       // 好友表名
    static const char* FIELD_OWNER;                         // 好友的拥有者
    static const char* FIELD_FRIEND_NAME;                   // 好友名

    // 数据库 - 离线聊天表
    static const char* TABLE_OFFLINE_CHAT;                  // 离线聊天表
    static const char* FIELD_SRC_USER;                      // 源用户
    static const char* FIELD_DST_USER;                      // 目标用户
    static const char* FIELD_CONTENT;                       // 聊天内容
    static const char* FIELD_TIME;                          // 时间

    // 数据库 - 离线添加好友请求表
    static const char* TABLE_OFFLINE_ADD_FRIEND_REQUEST;    // 离线添加好友请求表

    // 数据库 - 离线添加好友结果表
    static const char* TABLE_OFFLINE_ADD_FRIEND_RESULT;     // 离线添加好友结果表
    static const char* FIELD_ADD_FRIEND_RESULT;             // 结果

    // 其它
    static const char* DATE_TIME_FORMAT;                    // 时间格式，格式例：2015-01-01 12:00:00
    static const QString MULTI_CHAT;                        // 群聊标志
    static const quint16 CLIENT_PORT = 10000;               // 客户端端口号
    static const char* ICON_FILE_NAME;                      // 客户端图标文件名
    static const int ICON_COUNT = 24;                       // 客户端图标文件数
    static const char SPLIT_FLAT = '*';                     // 好友名列表中，每个元素之间的分隔符
    static const int STATUSBAR_PART_COUNT = 2;              // 状态栏格数
};
