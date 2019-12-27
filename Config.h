#pragma once

#include <QSettings>
#include <QHostAddress>

class Config
{
public:
    Config(const char*);
    QHostAddress getServerAddr();
    quint16 getServerPort();
    bool isTcp();

private:
    QSettings m_settings;   // 配置文件读取者
};
