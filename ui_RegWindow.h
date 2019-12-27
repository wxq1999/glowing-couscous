/********************************************************************************
** Form generated from reading UI file 'RegWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGWINDOW_H
#define UI_REGWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_RegWindow
{
public:
    QLabel *labelUserName;
    QLineEdit *editUserName;
    QLabel *labelPassword;
    QLineEdit *editPassword;
    QListWidget *listUserIcon;
    QLineEdit *editRePassword;
    QLabel *labelRePassword;
    QLabel *labelRePassword_2;
    QPushButton *buttonOK;
    QPushButton *buttonCancel;

    void setupUi(QDialog *RegWindow)
    {
        if (RegWindow->objectName().isEmpty())
            RegWindow->setObjectName(QStringLiteral("RegWindow"));
        RegWindow->resize(254, 330);
        RegWindow->setMinimumSize(QSize(254, 330));
        RegWindow->setMaximumSize(QSize(254, 330));
        labelUserName = new QLabel(RegWindow);
        labelUserName->setObjectName(QStringLiteral("labelUserName"));
        labelUserName->setGeometry(QRect(10, 10, 51, 16));
        editUserName = new QLineEdit(RegWindow);
        editUserName->setObjectName(QStringLiteral("editUserName"));
        editUserName->setGeometry(QRect(90, 10, 153, 20));
        labelPassword = new QLabel(RegWindow);
        labelPassword->setObjectName(QStringLiteral("labelPassword"));
        labelPassword->setGeometry(QRect(10, 40, 72, 15));
        editPassword = new QLineEdit(RegWindow);
        editPassword->setObjectName(QStringLiteral("editPassword"));
        editPassword->setGeometry(QRect(90, 40, 153, 20));
        editPassword->setEchoMode(QLineEdit::Password);
        listUserIcon = new QListWidget(RegWindow);
        listUserIcon->setObjectName(QStringLiteral("listUserIcon"));
        listUserIcon->setGeometry(QRect(10, 120, 233, 148));
        listUserIcon->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listUserIcon->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        listUserIcon->setAutoScroll(false);
        listUserIcon->setDragDropMode(QAbstractItemView::DragDrop);
        listUserIcon->setIconSize(QSize(32, 32));
        listUserIcon->setViewMode(QListView::IconMode);
        editRePassword = new QLineEdit(RegWindow);
        editRePassword->setObjectName(QStringLiteral("editRePassword"));
        editRePassword->setGeometry(QRect(90, 70, 153, 20));
        editRePassword->setEchoMode(QLineEdit::Password);
        labelRePassword = new QLabel(RegWindow);
        labelRePassword->setObjectName(QStringLiteral("labelRePassword"));
        labelRePassword->setGeometry(QRect(10, 70, 72, 15));
        labelRePassword_2 = new QLabel(RegWindow);
        labelRePassword_2->setObjectName(QStringLiteral("labelRePassword_2"));
        labelRePassword_2->setGeometry(QRect(10, 100, 72, 15));
        buttonOK = new QPushButton(RegWindow);
        buttonOK->setObjectName(QStringLiteral("buttonOK"));
        buttonOK->setGeometry(QRect(20, 280, 101, 31));
        buttonCancel = new QPushButton(RegWindow);
        buttonCancel->setObjectName(QStringLiteral("buttonCancel"));
        buttonCancel->setGeometry(QRect(130, 280, 101, 31));
        QWidget::setTabOrder(editUserName, editPassword);
        QWidget::setTabOrder(editPassword, editRePassword);
        QWidget::setTabOrder(editRePassword, listUserIcon);

        retranslateUi(RegWindow);

        QMetaObject::connectSlotsByName(RegWindow);
    } // setupUi

    void retranslateUi(QDialog *RegWindow)
    {
        RegWindow->setWindowTitle(QApplication::translate("RegWindow", "IDS_REG_WINDOW", 0));
        labelUserName->setText(QApplication::translate("RegWindow", "IDS_LABEL_USERNAME", 0));
        labelPassword->setText(QApplication::translate("RegWindow", "IDS_LABEL_PASSWORD", 0));
        labelRePassword->setText(QApplication::translate("RegWindow", "IDS_LABEL_REPASSWORD", 0));
        labelRePassword_2->setText(QApplication::translate("RegWindow", "IDS_LABEL_USERICON", 0));
        buttonOK->setText(QApplication::translate("RegWindow", "IDS_BUTTON_OK", 0));
        buttonCancel->setText(QApplication::translate("RegWindow", "IDS_BUTTON_CANCEL", 0));
    } // retranslateUi

};

namespace Ui {
    class RegWindow: public Ui_RegWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGWINDOW_H
