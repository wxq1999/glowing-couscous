#pragma once

#include <QMainWindow>
#include <QListWidgetItem>
#include <QLabel>
#include "Client.h"
#include "ChatManager.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

private:
    void addOneFriend(const QString&, int, bool isOnline = true);
    void addAllFriends(const LogonResult*);

private slots:
    void on_buttonLogon_triggered();
    void on_buttonReg_triggered();
    void on_buttonAddFriend_triggered();
    void on_buttonMChat_triggered();
    void on_buttonLogoff_triggered();
    void onItemDoubleClicked(QListWidgetItem*);
    void onGetLogonResult(const LogonResult*);
    void onGetRegResult(const RegResult*);
    void onChatC2S(const ChatInfo*);
    void onChatS2C(const ChatInfo*);
    void onGetAddFriendRequest(const AddFriendRequest*);
    void onGetAddFriendResult(const AddFriendResult*);
    void onFriendLogoff(const LogoffRequest*);
    void onFriendLogon(const FriendLogon*);

private:
    Ui::MainWindow* ui;         // 界面
    QLabel m_labelStatus;       // 状态标签
    QLabel m_labelFriendCount;  // 好友数标签
    Client m_client;            // 客户端
    ChatManager m_chatManager;  // 聊天管理者
};
