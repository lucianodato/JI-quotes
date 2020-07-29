#include "quotedialog.h"
#include "ui_quotedialog.h"

QuoteDialog::QuoteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuoteDialog)
{
    ui->setupUi(this);
}

QuoteDialog::~QuoteDialog()
{
    delete ui;
}

void QuoteDialog::on_CancelButton_clicked()
{
    this->close();
}

void QuoteDialog::on_SaveButton_clicked()
{
    this->close();
}
