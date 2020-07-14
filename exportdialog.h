#ifndef PRINTDIALOG_H
#define PRINTDIALOG_H

#include <QDialog>

namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = nullptr);
    ~ExportDialog();

private slots:
    void on_ExportQuotes_clicked();

private:
    Ui::ExportDialog *ui;
};

#endif // PRINTDIALOG_H
