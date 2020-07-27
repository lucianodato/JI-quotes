#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    QTranslator translator;
    if (translator.load(":/translations/JI-quotes_es_AR.qm"))
    {
        application.installTranslator(&translator);
    }

    MainWindow windows;
    windows.show();
    return application.exec();
}
