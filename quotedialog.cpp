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
