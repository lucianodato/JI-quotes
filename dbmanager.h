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
    const QString quotesTableDefinition = "CREATE TABLE IF NOT EXISTS quotes"
                                          " (quoteId INTEGER PRIMARY KEY ASC, content VARCHAR(2000) NOT NULL,"
                                          " author VARCHAR(100), created DATE NOT NULL, topicIndex INTEGER NOT NULL, "
                                          "FOREIGN KEY(topicIndex) REFERENCES topics(topicId))";
    const QString topicsTableDefinition = "CREATE TABLE IF NOT EXISTS topics "
                                          "(topicId INTEGER PRIMARY KEY ASC, name VARCHAR(50) NOT NULL)";
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

    void CreateDatabase();

private:
    QSqlDatabase database;
    QSqlQuery query;
};

#endif // DB_MANAGER_H
