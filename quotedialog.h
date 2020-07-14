#ifndef QUOTEDIALOG_H
#define QUOTEDIALOG_H

#include <QDialog>

namespace Ui {
class QuoteDialog;
}

class QuoteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QuoteDialog(QWidget *parent = nullptr);
    ~QuoteDialog();

private slots:
    void on_CancelButton_clicked();

    void on_SaveButton_clicked();

private:
    Ui::QuoteDialog *ui;
};

#endif // QUOTEDIALOG_H
