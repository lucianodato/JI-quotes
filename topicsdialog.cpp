#include "topicsdialog.h"
#include "ui_topicsdialog.h"

TopicsDialog::TopicsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TopicsDialog)
{
    ui->setupUi(this);
}

TopicsDialog::~TopicsDialog()
{
    delete ui;
}

void TopicsDialog::on_CancelButton_clicked()
{
    TopicsDialog::close();
}
