#include "Config.h"
#include "Const.h"

/**
 * 构造方法。
 * @param fileName  配置文件的路径
 */
Config::Config(const char* fileName) : m_settings(fileName, QSettings::IniFormat)
{
}

/**
 * 获取服务器 IP 地址。
 * @return 服务器 IP 地址
 */
QHostAddress Config::getServerAddr()
{
    return QHostAddress(m_settings.value(Const::CONFIG_SERVER_IP).toString());
}

/**
 * 获取服务器端口号。
 * @return 服务器端口号
 */
quint16 Config::getServerPort()
{
    return (quint16)(m_settings.value(Const::CONFIG_SERVER_PORT).toUInt());
}

/**
 * 获取 Tcp、Udp 标志。
 * @return 为 true 表示使用 Tcp 协议，为 false 表示使用 Udp 协议
 */
bool Config::isTcp()
{
    return m_settings.value(Const::CONFIG_IS_TCP).toBool();
}
