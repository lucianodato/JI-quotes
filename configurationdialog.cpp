#include "configurationdialog.h"
#include "ui_configurationdialog.h"

ConfigurationDialog::ConfigurationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationDialog)
{
    ui->setupUi(this);

    //Settings Init
    configurations = new QSettings();

    //View Init
    ui->plainTextEdit->setPlainText(configurations->value("document/RecopilationIntroduction").toString());
    ui->lineEdit->setText(configurations->value("document/RecopilationAuthor").toString());
}

ConfigurationDialog::~ConfigurationDialog()
{
    delete ui;
}

void ConfigurationDialog::on_pushButton_clicked()
{
    configurations->setValue("document/RecopilationIntroduction", ui->plainTextEdit->toPlainText());
    configurations->setValue("document/RecopilationAuthor", ui->lineEdit->text());
    this->close();
}
