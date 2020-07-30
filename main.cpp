#include "mainwindow.h"
#include "dbmanager.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    // Initialize the database:
    DbManager database;
    database.CreateSchema();

    // Load spanish translation
    QTranslator translator;
    if (translator.load(":/translations/JI-quotes_es_AR.qm"))
    {
        application.installTranslator(&translator);
    }

    MainWindow windows;
    windows.show();

    return application.exec();
}
