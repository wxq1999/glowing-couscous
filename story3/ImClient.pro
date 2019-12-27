#-------------------------------------------------
#
# Project created by QtCreator 2015-02-23T16:50:29
#
#-------------------------------------------------

QT       += core gui
QT       += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Client
TEMPLATE = app


SOURCES += \
    Main.cpp \
    Client.cpp \
    ChatManager.cpp \
    ChatWindow.cpp \
    UserListWidget.cpp \
    LogonWindow.cpp \
    RegWindow.cpp \
    MainWindow.cpp \
    ../Common/Config.cpp \
    ../Common/Const.cpp \
    ../Common/Protocol.cpp \
    ../Common/Result.cpp

HEADERS += \
    Client.h \
    ChatManager.h \
    ChatWindow.h \
    UserListWidget.h \
    LogonWindow.h \
    RegWindow.h \
    MainWindow.h \
    ../Common/Config.h \
    ../Common/Const.h \
    ../Common/Protocol.h \
    ../Common/Result.h

FORMS    += \
    ChatWindow.ui \
    LogonWindow.ui \
    RegWindow.ui \
    MainWindow.ui

RESOURCES += \
    Resource.qrc

TRANSLATIONS += Language_zh_CN.ts
