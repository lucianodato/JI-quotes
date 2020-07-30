#include "quotedialog.h"
#include "ui_quotedialog.h"

QuoteDialog::QuoteDialog(QWidget *parent,
                         QSqlRelationalTableModel *quoteModel,
                         QDataWidgetMapper *mapper) :
    QDialog(parent),
    ui(new Ui::QuoteDialog)
{
    ui->setupUi(this);

    //Model Init
    this->quoteModel = quoteModel;

    //View Init
    ui->comboBox->setModel(this->quoteModel->relationModel(DbManager::quotes::topicIndex));
    ui->comboBox->setModelColumn(DbManager::topics::name);
    ui->comboBox->setCurrentIndex(0);

    //Mapper Init
    this->mapper = mapper;
    this->mapper->setItemDelegate(new QSqlRelationalDelegate());
    this->mapper->addMapping(ui->plainTextEdit, DbManager::quotes::content);
    this->mapper->addMapping(ui->lineEdit, DbManager::quotes::author);
    this->mapper->addMapping(ui->comboBox, DbManager::quotes::topicIndex);
    this->mapper->toFirst();
}

QuoteDialog::~QuoteDialog()
{
    delete ui;
}

void QuoteDialog::on_SaveButton_clicked()
{
    quoteModel->submitAll();
    this->close();
}

void QuoteDialog::on_QuoteDialog_rejected()
{
}
