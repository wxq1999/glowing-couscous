/********************************************************************************
** Form generated from reading UI file 'ChatWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHATWINDOW_H
#define UI_CHATWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>

QT_BEGIN_NAMESPACE

class Ui_ChatWindow
{
public:
    QTextEdit *editInput;
    QPushButton *buttonSend;
    QTextEdit *editHistory;

    void setupUi(QDialog *ChatWindow)
    {
        if (ChatWindow->objectName().isEmpty())
            ChatWindow->setObjectName(QStringLiteral("ChatWindow"));
        ChatWindow->resize(402, 300);
        ChatWindow->setMinimumSize(QSize(402, 300));
        ChatWindow->setMaximumSize(QSize(402, 300));
        editInput = new QTextEdit(ChatWindow);
        editInput->setObjectName(QStringLiteral("editInput"));
        editInput->setGeometry(QRect(10, 190, 381, 61));
        buttonSend = new QPushButton(ChatWindow);
        buttonSend->setObjectName(QStringLiteral("buttonSend"));
        buttonSend->setGeometry(QRect(10, 260, 381, 31));
        editHistory = new QTextEdit(ChatWindow);
        editHistory->setObjectName(QStringLiteral("editHistory"));
        editHistory->setGeometry(QRect(10, 10, 381, 181));
        editHistory->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        editHistory->setReadOnly(true);

        retranslateUi(ChatWindow);

        QMetaObject::connectSlotsByName(ChatWindow);
    } // setupUi

    void retranslateUi(QDialog *ChatWindow)
    {
        ChatWindow->setWindowTitle(QString());
        editInput->setHtml(QApplication::translate("ChatWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", 0));
        buttonSend->setText(QApplication::translate("ChatWindow", "IDS_BUTTON_SEND", 0));
    } // retranslateUi

};

namespace Ui {
    class ChatWindow: public Ui_ChatWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHATWINDOW_H
