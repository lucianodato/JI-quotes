#include "src/mainwindow.h"
#include "src/dbmanager.h"
#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    application.setApplicationName("JI-quotes");

    // Initialize the database:
    DbManager *database = new DbManager();
    if(database->IsDatabaseOpen())
    {
        database->CreateDatabase();
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
    else
    {
        return 1;
    }

}
