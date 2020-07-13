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

private:
    Ui::QuoteDialog *ui;
};

#endif // QUOTEDIALOG_H
