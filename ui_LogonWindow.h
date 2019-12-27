/********************************************************************************
** Form generated from reading UI file 'LogonWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGONWINDOW_H
#define UI_LOGONWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LogonWindow
{
public:
    QLabel *labelUserName;
    QLabel *labelPassword;
    QLineEdit *editUserName;
    QLineEdit *editPassword;
    QPushButton *buttonOK;
    QPushButton *buttonCancel;

    void setupUi(QDialog *LogonWindow)
    {
        if (LogonWindow->objectName().isEmpty())
            LogonWindow->setObjectName(QStringLiteral("LogonWindow"));
        LogonWindow->resize(243, 113);
        LogonWindow->setMinimumSize(QSize(243, 113));
        LogonWindow->setMaximumSize(QSize(243, 113));
        labelUserName = new QLabel(LogonWindow);
        labelUserName->setObjectName(QStringLiteral("labelUserName"));
        labelUserName->setGeometry(QRect(10, 10, 51, 16));
        labelPassword = new QLabel(LogonWindow);
        labelPassword->setObjectName(QStringLiteral("labelPassword"));
        labelPassword->setGeometry(QRect(10, 40, 51, 16));
        editUserName = new QLineEdit(LogonWindow);
        editUserName->setObjectName(QStringLiteral("editUserName"));
        editUserName->setGeometry(QRect(70, 10, 161, 20));
        editPassword = new QLineEdit(LogonWindow);
        editPassword->setObjectName(QStringLiteral("editPassword"));
        editPassword->setGeometry(QRect(70, 40, 161, 20));
        editPassword->setEchoMode(QLineEdit::Password);
        buttonOK = new QPushButton(LogonWindow);
        buttonOK->setObjectName(QStringLiteral("buttonOK"));
        buttonOK->setGeometry(QRect(20, 70, 91, 31));
        buttonCancel = new QPushButton(LogonWindow);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
        buttonCancel->setGeometry(QRect(130, 70, 91, 31));
        QWidget::setTabOrder(editUserName, editPassword);

        retranslateUi(LogonWindow);

        QMetaObject::connectSlotsByName(LogonWindow);
    } // setupUi

    void retranslateUi(QDialog *LogonWindow)
    {
        LogonWindow->setWindowTitle(QApplication::translate("LogonWindow", "IDS_LOGON_WINDOW", 0));
        labelUserName->setText(QApplication::translate("LogonWindow", "IDS_LABEL_USERNAME", 0));
        labelPassword->setText(QApplication::translate("LogonWindow", "IDS_LABEL_PASSWORD", 0));
        buttonOK->setText(QApplication::translate("LogonWindow", "IDS_BUTTON_OK", 0));
        buttonCancel->setText(QApplication::translate("LogonWindow", "IDS_BUTTON_CANCEL", 0));
    } // retranslateUi

};

namespace Ui {
    class LogonWindow: public Ui_LogonWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGONWINDOW_H
