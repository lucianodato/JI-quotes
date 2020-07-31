#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QMetaEnum>

class DbManager : QObject
{
    Q_OBJECT
public:
    DbManager();
    ~DbManager();

    const QString databasepath = "database.db";
    const QString quotesTableDefinition = "create table if not exists quotes"
                                          " (quoteId integer PRIMARY KEY ASC, content varchar(2000) NOT NULL,"
                                          " author varchar(100), created date NOT NULL, topicIndex int NOT NULL, "
                                          "FOREIGN KEY(topicIndex) REFERENCES topics(topicId))";
    const QString topicsTableDefinition = "create table if not exists topics "
                                          "(topicId integer PRIMARY KEY ASC, name varchar(50) NOT NULL)";

    enum topics {
        topicId,
        name
    };
    Q_ENUM(topics)

    enum quotes {
        quoteId,
        content,
        author,
        created,
        topicIndex
    };
    Q_ENUM(quotes)

    void CreateSchema();

private:
    QSqlDatabase database;
    QSqlQuery query;
};

#endif // DB_MANAGER_H
