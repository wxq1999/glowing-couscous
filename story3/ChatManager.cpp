#include "ChatManager.h"

/**
 * 构造方法。
 * @param mainWindow    主窗口
 */
ChatManager::ChatManager(QWidget* mainWindow) :
    QObject(mainWindow),
    m_mainWindow(mainWindow)
{
}

/**
 * 析构方法。
 */
ChatManager::~ChatManager()
{
    this->clear();
}

/**
 * 清除所有聊天窗口。
 */
void ChatManager::clear()
{
    Chats::iterator end = m_chats.end();
    for (Chats::iterator i = m_chats.begin(); i != end; i++)
    {
        delete i.value();
    }
    m_chats.clear();
}

/**
 * 获取指定好友名对应的聊天窗口。
 * @param friendName    好友名
 * @return 好友名对应的聊天窗口
 */
ChatWindow* ChatManager::getChatWindow(const QString& friendName)
{
    // 查找用户名对应的聊天窗口
    ChatWindow* window = NULL;
    Chats::iterator it = m_chats.find(friendName);

    if (it.key().isEmpty())
    {
        // 未找到，则新建一个
        window = new ChatWindow(friendName, m_mainWindow);
        QObject::connect(window, SIGNAL(UM_CHAT_C2S(const ChatInfo*)),
            m_mainWindow, SLOT(onChatC2S(const ChatInfo*)));
        m_chats.insert(friendName, window);
    }
    else
    {
        // 找到了
        window = it.value();
    }

    return window;
}
