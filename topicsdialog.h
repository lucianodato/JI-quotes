#ifndef TOPICS_H
#define TOPICS_H

#include <QDialog>

namespace Ui {
class TopicsDialog;
}

class TopicsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TopicsDialog(QWidget *parent = nullptr);
    ~TopicsDialog();

private slots:
    void on_CancelButton_clicked();

private:
    Ui::TopicsDialog *ui;
};

#endif // TOPICS_H
