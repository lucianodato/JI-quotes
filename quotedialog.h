#ifndef QUOTEDIALOG_H
#define QUOTEDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QDataWidgetMapper>
#include <QItemSelectionModel>
#include <QSqlRelation>
#include <QSqlRelationalDelegate>

#include "dbmanager.h"

namespace Ui {
class QuoteDialog;
}

class QuoteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QuoteDialog(QWidget *parent = nullptr,
                         QSqlRelationalTableModel *quoteModel = nullptr,
                         QDataWidgetMapper *mapper = nullptr);
    ~QuoteDialog();

private slots:
    void on_SaveButton_clicked();

    void on_QuoteDialog_rejected();

private:
    Ui::QuoteDialog *ui;

    QSqlRelationalTableModel *quoteModel;
    QDataWidgetMapper *mapper;

    QMetaEnum quoteTableEnum = QMetaEnum::fromType<DbManager::quotes>();
};

#endif // QUOTEDIALOG_H
