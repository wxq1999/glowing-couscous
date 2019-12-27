#include <QApplication>
#include <QTranslator>
#include "MainWindow.h"

int main(int argc, char* argv[])
{
    QTranslator translator;
    translator.load(":/qm/Language_zh_CN.qm");

    QApplication a(argc, argv);
    a.installTranslator(&translator);

    MainWindow w;
    w.show();

    return a.exec();
}
