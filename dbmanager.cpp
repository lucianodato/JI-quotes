#include "dbmanager.h"
#include <QDebug>

DbManager::DbManager()
{
    if (!QSqlDatabase::drivers().contains("QSQLITE")){
        qDebug() << "Database driver not found";
    }

    database = QSqlDatabase::addDatabase("QSQLITE");
    database.setDatabaseName(databasepath);
    database.open();

    if(database.isOpen())
    {
        query = QSqlQuery(database);
    }
    else
    {
        qDebug() << "There was an error creating or opening the database";
    }
}

DbManager::~DbManager()
{
    if(database.isOpen())
    {
        database.close();
    }
}

void DbManager::CreateSchema()
{
    if (!query.exec(topicsTableDefinition) || !query.exec(quotesTableDefinition))
    {
        qDebug() << "Error running query";
    }
}
