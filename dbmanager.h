#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QObject>
#include <QMetaEnum>
#include <QStandardPaths>
#include <QDir>
#include <QMessageBox>
#include <QCoreApplication>

class DbManager : QObject
{
    Q_OBJECT
public:
    const QString databaseName = "database.db";
    const QString quotesTableDefinition = "CREATE TABLE IF NOT EXISTS quotes "
                                          "(quoteId	INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT UNIQUE,"
                                          " content TEXT NOT NULL, author TEXT,"
                                          " created	TEXT NOT NULL, topicIndex INTEGER NOT NULL,"
                                          " FOREIGN KEY(topicIndex) REFERENCES topics(topicId))";
    const QString topicsTableDefinition = "CREATE TABLE IF NOT EXISTS topics ("
                                          "topicId INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, "
                                          "name TEXT NOT NULL)";
    const QString indexQuotesCreation = "CREATE UNIQUE INDEX IF NOT EXISTS quote_Id ON quotes(quoteId)";
    const QString indexTopicsCreation = "CREATE UNIQUE INDEX IF NOT EXISTS topic_Id ON topics(topicId)";

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

    DbManager();
    ~DbManager();
    void CreateDatabase();
    bool IsDatabaseOpen();

private:
    QSqlDatabase database;
    QSqlQuery query;
};

#endif // DB_MANAGER_H
