#include "configurationdialog.h"
#include "ui_configurationdialog.h"

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);

    //Settings Init
    configurations = new QSettings("JI-quotes",tr("JI-quotes"));

    //View Init
    ui->lineEdit_2->setText(configurations->value("document/DocumentTitle").toString());
    ui->plainTextEdit->setPlainText(configurations->value("document/DocumentIntroduction").toString());
    ui->lineEdit->setText(configurations->value("document/DocumentAuthor").toString());
}

ConfigurationDialog::~ConfigurationDialog()
{
    delete ui;
}

void ConfigurationDialog::on_pushButton_clicked()
{
    configurations->setValue("document/DocumentTitle", ui->lineEdit_2->text());
    configurations->setValue("document/DocumentIntroduction", ui->plainTextEdit->toPlainText());
    configurations->setValue("document/DocumentAuthor", ui->lineEdit->text());
    this->close();
}
