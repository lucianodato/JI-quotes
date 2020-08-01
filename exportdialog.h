#ifndef PRINTDIALOG_H
#define PRINTDIALOG_H

#include "dbmanager.h"

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QTextDocument>
#include <QPdfWriter>
#include <QDate>
#include <QFileDialog>
#include <QSettings>

namespace Ui {
class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = nullptr, QSqlRelationalTableModel *quoteModel = nullptr);
    ~ExportDialog();

private slots:
    void on_ExportQuotes_clicked();

    void on_spinBox_2_valueChanged(int arg1);

    void on_spinBox_valueChanged(int arg1);

private:
    Ui::ExportDialog *ui;
    QSqlRelationalTableModel *quoteModel;
    QTextDocument *document;
    QPdfWriter *pdfExporter;
    QSettings *configurations;

    QString CreateHtmlContent();
};

#endif // PRINTDIALOG_H
