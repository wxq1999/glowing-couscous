#pragma once

#include <QDialog>

namespace Ui
{
    class LogonWindow;
}

class LogonWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LogonWindow(QWidget* parent = 0);
    ~LogonWindow();
    const QString& getUserName();
    const QString& getPassword();

private slots:
    void on_buttonOK_clicked();
    void on_buttonCancel_clicked();

private:
    Ui::LogonWindow* ui;    // 界面
    QString m_userName;     // 用户名
    QString m_password;     // 密码
};
