#include <QMessageBox>
#include <QInputDialog>
#include "MainWindow.h"
#include "ui_MainWindow.h"

/**
 * 构造方法。
 * @param parent    父窗口
 */
MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_chatManager(this)
{
    ui->setupUi(this);

    // 设置状态栏
    m_labelStatus.setText(tr("IDS_LABEL_STATUS_LOGOFF"));
    m_labelFriendCount.setText(tr("IDS_LABEL_FRIEND_COUNT"));
    int labelWidth = this->width() / Const::STATUSBAR_PART_COUNT;
    ui->statusBar->addWidget(&m_labelStatus, labelWidth);
    ui->statusBar->addWidget(&m_labelFriendCount, labelWidth);

    // 连接信号与槽
    QObject::connect(ui->listFriends, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
        SLOT(onItemDoubleClicked(QListWidgetItem*)));

    QObject::connect(&m_client, SIGNAL(UM_GET_LOGON_RESULT(const LogonResult*)),
        SLOT(onGetLogonResult(const LogonResult*)));

    QObject::connect(&m_client, SIGNAL(UM_GET_REG_RESULT(const RegResult*)),
        SLOT(onGetRegResult(const RegResult*)));

    QObject::connect(&m_client, SIGNAL(UM_GET_ADD_FRIEND_REQUEST(const AddFriendRequest*)),
        SLOT(onGetAddFriendRequest(const AddFriendRequest*)));

    QObject::connect(&m_client, SIGNAL(UM_GET_ADD_FRIEND_RESULT(const AddFriendResult*)),
        SLOT(onGetAddFriendResult(const AddFriendResult*)));

    QObject::connect(&m_client, SIGNAL(UM_CHAT_S2C(const ChatInfo*)),
        SLOT(onChatS2C(const ChatInfo*)));

    QObject::connect(&m_client, SIGNAL(UM_FRIEND_LOGOFF(const LogoffRequest*)),
        SLOT(onFriendLogoff(const LogoffRequest*)));

    QObject::connect(&m_client, SIGNAL(UM_FRIEND_LOGON(const FriendLogon*)),
        SLOT(onFriendLogon(const FriendLogon*)));
}

/**
 * 析构方法。
 */
MainWindow::~MainWindow()
{
    // 清空好友列表控件
    ui->listFriends->clear();

    // 离线
    m_client.logoff();

    delete ui;
}

/**
 * 添加一个好友到好友列表控件中。
 * @param friendName    好友名
 * @param iconIndex     好友头像索引
 * @param isOnline      true 表示好友在线，false 表示好友不在线
 */
void MainWindow::addOneFriend(const QString& friendName, int iconIndex, bool isOnline)
{
    if (iconIndex < 0)
    {
        return;
    }
    QString iconFilePath = QString(Const::ICON_FILE_NAME).arg(iconIndex, 2, 10, QLatin1Char('0'));
    ui->listFriends->addItem(friendName, iconFilePath, isOnline);
    m_labelFriendCount.setText(tr("IDS_LABEL_FRIEND_COUNT") + QString::number(m_client.getFriendCount()));
}

/**
 * 添加所有好友到好友列表控件中。
 * @param result    登录结果
 */
void MainWindow::addAllFriends(const LogonResult* result)
{
    // 获取好友名列表、图标文件名列表、在线标志
    QStringList friendNames;
    result->getFriendNames(friendNames);
    const int* friendIconIndexs = result->getFriendIconIndexs();
    bool isOnline = false;
    QString iconFilePath;

    // 遍历好友名和图标文件夹名列表
    int count = result->getFriendCount();
    for (int i = 0; i < count; i++)
    {
        isOnline = result->isFriendOnline(i);
        iconFilePath = QString(Const::ICON_FILE_NAME).arg(friendIconIndexs[i], 2, 10, QLatin1Char('0'));
        ui->listFriends->addItem(friendNames[i], iconFilePath, isOnline);
    }
    m_labelFriendCount.setText(tr("IDS_LABEL_FRIEND_COUNT") + QString::number(result->getFriendCount()));
}

/**
 * “登录”按钮的单击响应方法。
 */
void MainWindow::on_buttonLogon_triggered()
{
    Result::Code resultCode = m_client.logon();
    if (resultCode != Result::LOGON_SUCCESS)
    {
        QMessageBox::critical(this, NULL, Result::getMessage(resultCode));
    }
}

/**
 * “注册”按钮的单击响应方法。
 */
void MainWindow::on_buttonReg_triggered()
{
    Result::Code resultCode = m_client.reg();
    if (resultCode != Result::REG_SUCCESS)
    {
        QMessageBox::critical(this, NULL, Result::getMessage(resultCode));
    }
}

/**
 * “添加好友”按钮的单击响应方法。
 */
void MainWindow::on_buttonAddFriend_triggered()
{
    // 弹出输入框，让用户输入好友名
    QInputDialog inputWindow(this);
    bool ok = false;
    QString defaultValue;

    QString userName = inputWindow.getText(this, NULL, tr("IDS_INUTBOX_TIPTEXT"), QLineEdit::Normal, defaultValue, &ok);
    if (!ok)    // ok 为 false 表示单击了输入框的取消按钮
    {
        return;
    }

    // 执行添加好友
    Result::Code resultCode = m_client.addFriend(userName);
    if (resultCode != Result::SUCCESS)
    {
        QMessageBox::critical(this, NULL, Result::getMessage(resultCode));
    }
}

/**
 * “群聊”按钮的单击响应方法。
 */
void MainWindow::on_buttonMChat_triggered()
{
    m_chatManager.getChatWindow(Const::MULTI_CHAT)->show();
}

/**
 * “离线”按钮的单击响应方法。
 */
void MainWindow::on_buttonLogoff_triggered()
{
    // 设置各种控件的状态
    m_labelStatus.setText(tr("IDS_LABEL_STATUS_LOGOFF"));
    m_labelFriendCount.setText(tr("IDS_LABEL_FRIEND_COUNT"));
    ui->buttonLogon->setEnabled(true);
    ui->buttonReg->setEnabled(true);
    ui->buttonAddFriend->setEnabled(false);
    ui->buttonMChat->setEnabled(false);
    ui->buttonLogoff->setEnabled(false);

    // 清空各种列表
    ui->listFriends->clear();
    m_chatManager.clear();

    // 发离线请求
    m_client.logoff();
}

/**
 * 双击好友列表中某个列表项的响应方法。
 * @param item  被双击的列表项
 */
void MainWindow::onItemDoubleClicked(QListWidgetItem* item)
{
    QString friendName(item->text());
    ChatWindow* chatWindow = m_chatManager.getChatWindow(friendName);
    chatWindow->show();
}

/**
 * 登录事件的响应方法。
 * @param result    登录结果
 */
void MainWindow::onGetLogonResult(const LogonResult* result)
{
    Result::Code resultCode = result->getResultCode();
    if (resultCode == Result::LOGON_SUCCESS)
    {
        m_labelStatus.setText(tr("IDS_LABEL_STATUS_LOGON"));
        ui->buttonLogon->setEnabled(false);
        ui->buttonReg->setEnabled(false);
        ui->buttonAddFriend->setEnabled(true);
        ui->buttonMChat->setEnabled(true);
        ui->buttonLogoff->setEnabled(true);
        this->addAllFriends(result);
    }
    else
    {
        QMessageBox::critical(this, NULL, Result::getMessage(resultCode));
    }
}

/**
 * 注册事件的响应方法。
 * @param result    注册结果
 */
void MainWindow::onGetRegResult(const RegResult* result)
{
    Result::Code resultCode = result->getResultCode();
    QMessageBox::information(this, NULL, Result::getMessage(resultCode));
    if (resultCode == Result::REG_SUCCESS)
    {
        m_labelStatus.setText(tr("IDS_LABEL_STATUS_LOGON"));
        m_labelFriendCount.setText(tr("IDS_LABEL_FRIEND_COUNT") + QString::number(0));
        ui->buttonLogon->setEnabled(false);
        ui->buttonReg->setEnabled(false);
        ui->buttonAddFriend->setEnabled(true);
        ui->buttonMChat->setEnabled(true);
        ui->buttonLogoff->setEnabled(true);
    }
}

/**
 * 聊天事件(客户端到服务器)的响应方法。
 * @param chat  聊天信息
 */
void MainWindow::onChatC2S(const ChatInfo* chat)
{
    m_client.chat(chat);
}

/**
 * 聊天事件(服务器到客户端)的响应方法。
 * @param chat  聊天信息
 */
void MainWindow::onChatS2C(const ChatInfo* chat)
{
    QString srcUserName(chat->getSrcUserName());
    QString dstUserName(chat->getDstUserName());
    ChatWindow* chatWindow = NULL;

    if (dstUserName == Const::MULTI_CHAT)
    {
        chatWindow = m_chatManager.getChatWindow(Const::MULTI_CHAT);
    }
    else
    {
        chatWindow = m_chatManager.getChatWindow(srcUserName);
    }
    chatWindow->setContent(chat);
    chatWindow->show();
}

/**
 * 添加好友事件的响应方法。
 * @param request   添加好友请求
 */
void MainWindow::onGetAddFriendRequest(const AddFriendRequest* request)
{
    this->addOneFriend(request->getSrcUserName(), request->getIconIndex());
}

/**
 * 得到添加好友结果事件的响应方法。
 * @param result    添加好友结果
 */
void MainWindow::onGetAddFriendResult(const AddFriendResult* result)
{
    Result::Code resultCode = result->getResultCode();
    QString message(Result::getMessage(resultCode));
    if (resultCode == Result::ADD_FRIEND_ALLOW)
    {
        message = result->getDstUserName() + message;
        this->addOneFriend(result->getDstUserName(), result->getIconIndex(), true);
    }
    else if (resultCode == Result::ALREADY_BE_FRIENDS || resultCode == Result::ADD_FRIEND_NOT_ALLOW)
    {
        message = result->getDstUserName() + message;
    }
    QMessageBox::information(this, NULL, message);
}

/**
 * 好友离线事件的响应方法。
 * @param request   离线请求
 */
void MainWindow::onFriendLogoff(const LogoffRequest* request)
{
    ui->listFriends->changeItemColor(request->getUserName(), false);
}

/**
 * 好友登录事件的响应方法。
 * @param friendLogon   好友登录信息
 */
void MainWindow::onFriendLogon(const FriendLogon* friendLogon)
{
    ui->listFriends->changeItemColor(friendLogon->getUserName(), true);
}
