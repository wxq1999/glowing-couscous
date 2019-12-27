#include <QMessageBox>
#include "RegWindow.h"
#include "ui_RegWindow.h"
#include "../Common/Config.h"
#include "../Common/Const.h"
#include "../Common/Result.h"

/**
 * 构造方法。
 * @param parent    父窗口
 */
RegWindow::RegWindow(QWidget* parent) :
    QDialog(parent),
    ui(new Ui::RegWindow)
{
    ui->setupUi(this);
    for (int i = 0; i < Const::ICON_COUNT; i++)
    {
        QString iconFilePath = QString(Const::ICON_FILE_NAME).arg(i, 2, 10, QLatin1Char('0'));
        QIcon icon(iconFilePath);
        QListWidgetItem* item = new QListWidgetItem(icon, NULL);
        ui->listUserIcon->addItem(item);
    }
}

/**
 * 析构方法。
 */
RegWindow::~RegWindow()
{
    // 删除图标列表中的所有列表项
    const int count = ui->listUserIcon->count();
    for (int i = count - 1; i >= 0; i--)
    {
        delete ui->listUserIcon->item(i);
    }

    delete ui;
}

/**
 * 获取用户名。
 * @return 用户名
 */
const QString& RegWindow::getUserName()
{
    return m_userName;
}

/**
 * 获取密码。
 * @return 密码
 */
const QString& RegWindow::getPassword()
{
    return m_password;
}

/**
 * 获取头像索引。
 * @return 头像索引
 */
int RegWindow::getIconIndex()
{
    return m_iconIndex;
}

/**
 * “确定”按钮的单击响应方法。
 */
void RegWindow::on_buttonOK_clicked()
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
    if (userName.contains(Const::SPLIT_FLAT) || userName == Const::MULTI_CHAT)
    {
        QMessageBox::critical(this, NULL, Result::getMessage(Result::USER_NAME_INVALID));
        ui->editUserName->setFocus();
        return;
    }

    // 检查密码
    const QString password(ui->editPassword->text());

    // 密码为空
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

    // 两次密码不一致
    QString repassword(ui->editRePassword->text());
    if (password != repassword)
    {
        QMessageBox::critical(this, NULL, Result::getMessage(Result::PASSWORD_NOT_EQUAL));
        ui->editRePassword->setFocus();
        return;
    }

    // 检查图标文件名
    QListWidgetItem* item = ui->listUserIcon->currentItem();
    if (item == NULL)
    {
        QMessageBox::critical(this, NULL, Result::getMessage(Result::ICON_NOT_SELECT));
        ui->listUserIcon->setFocus();
        return;
    }

    // 保存以上内容到成员变量中
    m_userName = userName;
    m_password = password;
    m_iconIndex = ui->listUserIcon->currentRow();

    QDialog::accept();
}

/**
 * “取消”按钮的单击响应方法。
 */
void RegWindow::on_buttonCancel_clicked()
{
    QDialog::reject();
}
