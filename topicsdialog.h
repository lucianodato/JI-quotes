#ifndef TOPICS_H
#define TOPICS_H

#include <QDialog>
#include <QSqlRelationalTableModel>

#include "dbmanager.h"

namespace Ui {
class TopicsDialog;
}

class TopicsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TopicsDialog(QWidget *parent = nullptr,
                          QSqlTableModel *topicModel = nullptr);
    ~TopicsDialog();

private slots:
    void on_AddTopic_clicked();

    void on_RemoveTopic_clicked();

    void on_TopicsDialog_rejected();

private:
    Ui::TopicsDialog *ui;

    QSqlTableModel *topicModel;

    QMetaEnum topicTableEnum = QMetaEnum::fromType<DbManager::topics>();
};

#endif // TOPICS_H
