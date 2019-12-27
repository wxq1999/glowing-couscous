#pragma once

#include <QDialog>

namespace Ui
{
    class RegWindow;
}

class RegWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegWindow(QWidget* parent = 0);
    ~RegWindow();
    const QString& getUserName();
    const QString& getPassword();
    int getIconIndex();

private slots:
    void on_buttonOK_clicked();
    void on_buttonCancel_clicked();

private:
    Ui::RegWindow* ui;  // 界面
    QString m_userName; // 用户名
    QString m_password; // 密码
    int m_iconIndex;    // 头像索引
};
