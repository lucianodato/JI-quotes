#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class DbManager
{
public:
    const QString databasepath = "database.db";
    const QString quotesTableDefinition = "create table quotes (quoteId integer primary key, content varchar(2000), author varchar(100), quoteTopic varchar(50))";
    const QString topicsTableDefinition = "create table topics (topicId integer primary key, name varchar(50))";

    DbManager();
    ~DbManager();
    void CreateSchema();
private:
    QSqlDatabase database;
    QSqlQuery query;
};

#endif // DB_MANAGER_H
