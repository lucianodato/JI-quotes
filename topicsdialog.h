#ifndef TOPICS_H
#define TOPICS_H

#include <QDialog>
#include <QSqlTableModel>
#include <QMetaEnum>

namespace Ui {
class TopicsDialog;
}

class TopicsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TopicsDialog(QWidget *parent = nullptr);
    ~TopicsDialog();

    enum topics {
        topicId,
        Name
    };
    Q_ENUM(topics)

private slots:
    void on_AddTopic_clicked();

    void on_RemoveTopic_clicked();

    void on_TopicsDialog_rejected();

private:
    Ui::TopicsDialog *ui;
    QSqlTableModel *topicModel;
    QMetaEnum tableEnum = QMetaEnum::fromType<topics>();
};

#endif // TOPICS_H
