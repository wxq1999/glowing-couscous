#pragma once

#include <QDialog>
#include "../Common/Protocol.h"

namespace Ui
{
    class ChatWindow;
}

/**
 * 聊天窗口。
 */
class ChatWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChatWindow(const QString&, QWidget*);
    ~ChatWindow();
    void setContent(const ChatInfo*);

signals:
    void UM_CHAT_C2S(const ChatInfo*);  // 向服务器发送聊天信息的事件

private slots:
    void on_buttonSend_clicked();

private:
    Ui::ChatWindow* ui;     // 界面
    QString m_friendName;   // 好友名
    QString m_content;      // 聊天内容
};
