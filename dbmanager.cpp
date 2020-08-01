#include "dbmanager.h"

DbManager::DbManager()
{
    //Create directory to put the database
    QString applicationDirectoryPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir applicationDirectory(applicationDirectoryPath);
    if (!applicationDirectory.exists())
    {
        applicationDirectory.mkpath(applicationDirectoryPath);
    }
    QString databasePath = applicationDirectoryPath + "/" + databaseName;

    if (!QSqlDatabase::drivers().contains("QSQLITE"))
    {
        QMessageBox::critical(nullptr, tr("Database Error"),
                              tr("Database driver not found"),
                              QMessageBox::Ok, QMessageBox::Ok);
        QCoreApplication::exit();
    }

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(databasePath);

    if(database.open())
    {
        query = QSqlQuery(database);
    }
    else
    {
        QMessageBox::critical(nullptr, tr("Database Error"),
                              tr("There was an error creating or opening the database"),
                              QMessageBox::Ok, QMessageBox::Ok);
        QCoreApplication::exit();
    }
}

DbManager::~DbManager()
{
    if(database.isOpen())
    {
        database.close();
    }
}

void DbManager::CreateDatabase()
{
    if (!query.exec(topicsTableDefinition) || !query.exec(quotesTableDefinition))
    {
        QMessageBox::critical(nullptr, tr("Database Error"),
                              tr("Error creating tables"),
                              QMessageBox::Ok, QMessageBox::Ok);
        QCoreApplication::exit();
    }

    if (!query.exec(indexQuotesCreation) || !query.exec(indexTopicsCreation))
    {
        QMessageBox::critical(nullptr, tr("Database Error"),
                              tr("Error creating indexes"),
                              QMessageBox::Ok, QMessageBox::Ok);
        QCoreApplication::exit();
    }
}

bool DbManager::IsDatabaseOpen()
{
    return database.isOpen();
}
