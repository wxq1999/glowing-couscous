#pragma once

#include <QMap>
#include "ChatWindow.h"

typedef QMap<QString, ChatWindow*> Chats;

class ChatManager : public QObject
{
    Q_OBJECT

public:
    explicit ChatManager(QWidget*);
    ~ChatManager();
    void clear();
    ChatWindow* getChatWindow(const QString&);

private:
    Chats m_chats;          // 聊天窗口集合
    QWidget* m_mainWindow;  // 主窗口
};
