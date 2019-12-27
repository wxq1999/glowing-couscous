#pragma once

#include <QMainWindow>
#include "Server.h"

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

private slots:
    void on_buttonBegin_clicked();
    void on_buttonStop_clicked();

private:
    Ui::MainWindow* ui; // 界面
    Server m_server;    // 服务
};
