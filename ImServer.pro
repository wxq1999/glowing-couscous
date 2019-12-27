#-------------------------------------------------
#
# Project created by QtCreator 2015-02-27T20:11:11
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Server
TEMPLATE = app


SOURCES += \
    Main.cpp \
    ../Common/Config.cpp \
    ../Common/Const.cpp \
    ../Common/Protocol.cpp \
    ../Common/Result.cpp \
    MainWindow.cpp \
    Server.cpp \
    Client.cpp

HEADERS += \
    ../Common/Config.h \
    ../Common/Const.h \
    ../Common/Protocol.h \
    ../Common/Result.h \
    Server.h \
    MainWindow.h \
    Client.h

FORMS    += \
    MainWindow.ui

RESOURCES += \
    Resource.qrc

TRANSLATIONS += Language_zh_CN.ts
