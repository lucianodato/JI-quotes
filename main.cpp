#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QTranslator translator;
    translator.load(QLocale::system(), QStringLiteral("JI-quotes_"));
    application.installTranslator(&translator);

    MainWindow windows;
    windows.show();
    return application.exec();
}
