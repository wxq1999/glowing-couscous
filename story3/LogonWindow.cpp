#include <QMessageBox>
#include "LogonWindow.h"
#include "ui_LogonWindow.h"
#include "../Common/Const.h"
#include "../Common/Result.h"

/**
 * 构造方法。
 * @param parent    父窗口
 */
LogonWindow::LogonWindow(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::LogonWindow)
{
    ui->setupUi(this);
}

/**
 * 析构方法。
 */
LogonWindow::~LogonWindow()
{
    delete ui;
}

/**
 * 获取用户名。
 * @return 用户名
 */
const QString& LogonWindow::getUserName()
{
    return m_userName;
}

/**
 * 获取密码。
 * @return 密码
 */
const QString& LogonWindow::getPassword()
{
    return m_password;
}

/**
 * “确定”按钮的单击响应方法。
 */
void LogonWindow::on_buttonOK_clicked()
{
    // 检查用户名
    const QString userName(ui->editUserName->text());

    // 用户名为空
    if (userName.isEmpty())
    {
        QMessageBox::critical(this, NULL, Result::getMessage(Result::USER_NAME_EMPTY));
        ui->editUserName->setFocus();
        return;
    }

    // 用户名太长
    if (userName.length() > Const::USERNAME_LEN)
    {
        QMessageBox::critical(this, NULL, Result::getMessage(Result::USER_NAME_TOO_LONG));
        ui->editUserName->setFocus();
        return;
    }

    // 用户名包含非法字符
    if (userName.contains(Const::SPLIT_FLAT))
    {
        QMessageBox::critical(this, NULL, Result::getMessage(Result::USER_NAME_INVALID));
        ui->editUserName->setFocus();
        return;
    }

    // 检查密码
    // 密码为空
    const QString password(ui->editPassword->text());
    if (password.isEmpty())
    {
        QMessageBox::critical(this, NULL, Result::getMessage(Result::PASSWORD_EMPTY));
        ui->editPassword->setFocus();
        return;
    }

    // 密码太长
    if (password.length() > Const::USERNAME_LEN)
    {
        QMessageBox::critical(this, NULL, Result::getMessage(Result::PASSWORD_TOO_LONG));
        ui->editPassword->setFocus();
        return;
    }

    // 保存以上内容到成员变量中
    m_userName = userName;
    m_password = password;

    QDialog::accept();
}

/**
 * “取消”按钮的单击响应方法。
 */
void LogonWindow::on_buttonCancel_clicked()
{
    QDialog::reject();
}
