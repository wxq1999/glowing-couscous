#include <QDateTime>
#include <QMessageBox>
#include <QScrollBar>
#include "ChatWindow.h"
#include "ui_ChatWindow.h"
#include "Client.h"

/**
 * 构造方法。
 * @param friendName    好友名
 * @param parent        父窗口
 */
ChatWindow::ChatWindow(const QString& friendName, QWidget* parent) :
    QDialog(parent),
    ui(new Ui::ChatWindow),
    m_friendName(friendName)
{
    ui->setupUi(this);
    this->setWindowTitle(friendName);
}

/**
 * 析构方法。
 */
ChatWindow::~ChatWindow()
{
    delete ui;
}

/**
 * 设置聊天内容。
 * @param chat  聊天信息
 */
void ChatWindow::setContent(const ChatInfo* chat)
{
    // 获取好友名、发送时间、聊天内容
    const QString friendName(chat->getSrcUserName());  // 好友名
    const QString time(chat->getTime());               // 发送时间
    const QString content(chat->getContent());         // 内容

    // 显示聊天相关信息
    QString show(friendName + "  [" + time + "]\n" + content + "\n\n");
    m_content += show;
    ui->editHistory->setText(m_content);
}

/**
 * “发送”按钮的单击响应方法。
 */
void ChatWindow::on_buttonSend_clicked()
{
    // 焦点切换到输入框
    ui->editInput->setFocus();

    // 获取并查检用户输入的聊天内容
    const QString content(ui->editInput->toPlainText());
    if (content.length() > Const::CONTENT_LEN)
    {
        QString text(Result::getMessage(Result::CONTENT_IS_TOO_LONG));
        QMessageBox::critical(this, NULL, text);
        return;
    }

    // 获取当前时间
    const QString time(QDateTime::currentDateTime().toString(Const::DATE_TIME_FORMAT));

    // 显示聊天内容
    QString show(Client::getName() + "  [" + time + "]\n" + content + "\n\n");
    m_content += show;
    ui->editHistory->setText(m_content);

    // 滚动条滚动到最下面一行
    QScrollBar* scrollBar = ui->editHistory->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());

    // 清空输入框
    ui->editInput->clear();

    // 发送聊天内容
    ChatInfo chat(Client::getName(), m_friendName, content, time);
    emit UM_CHAT_C2S(&chat);
}
