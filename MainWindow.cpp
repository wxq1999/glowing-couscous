#include <QMessageBox>
#include "MainWindow.h"
#include "ui_MainWindow.h"

/**
 * 构造方法。
 * @param parent    父窗口
 */
MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

/**
 * 析构方法。
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * "开始"按钮的单击响应方法。
 */
void MainWindow::on_buttonBegin_clicked()
{
    m_server.begin();
    ui->buttonBegin->setEnabled(false);
    ui->buttonStop->setEnabled(true);
    QString serverAddr;
    serverAddr.sprintf("IP地址：%s\n端口号：%u", m_server.getAddress().toStdString().c_str(), m_server.getPort());
    ui->editServerAddr->setText(serverAddr);
}

/**
 * "结束"按钮的单击响应方法。
 */
void MainWindow::on_buttonStop_clicked()
{
    m_server.stop();
    ui->buttonBegin->setEnabled(true);
    ui->buttonStop->setEnabled(false);
    ui->editServerAddr->setText("IP地址：\n端口号：");
}
