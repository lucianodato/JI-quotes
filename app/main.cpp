#include "src/mainwindow.h"
#include "src/dbmanager.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    application.setApplicationName("JI-quotes");

    // Initialize the database:
    DbManager *database = new DbManager();
    if(database->IsDatabaseOpen())
    {
        database->CreateDatabase();

        // Load translation
        QTranslator translator;
        QLocale spanishArgentina(QLocale::Spanish, QLocale::Argentina);
        translator.load(spanishArgentina,
                QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        application.installTranslator(&translator);
        if (translator.load(":/translations/translations/JI-quotes_es_AR.qm"))
        {
            application.installTranslator(&translator);
        }

        MainWindow windows;
        windows.showMaximized();

        return application.exec();
    }
    else
    {
        return 1;
    }

}
