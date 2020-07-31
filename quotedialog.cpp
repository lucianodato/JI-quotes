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

    //Mapper Init
    this->mapper = mapper;
    this->mapper->setItemDelegate(new QSqlRelationalDelegate());
    this->mapper->addMapping(ui->plainTextEdit, DbManager::quotes::content);
    this->mapper->addMapping(ui->lineEdit, DbManager::quotes::author);
    this->mapper->addMapping(ui->comboBox, DbManager::quotes::topicIndex);

    //View Init
    ui->comboBox->setModel(this->quoteModel->relationModel(
                               DbManager::quotes::topicIndex));
    ui->comboBox->setModelColumn(DbManager::topics::name);
    ui->comboBox->setCurrentIndex(0);
}

QuoteDialog::~QuoteDialog()
{
    delete ui;
}

void QuoteDialog::on_SaveButton_clicked()
{
    if (ui->comboBox->currentIndex() == 0)
    {
        quoteModel->index(mapper->currentIndex(),
                          DbManager::quotes::topicIndex).data() = 1;
    }

    if (quoteModel->index(mapper->currentIndex(), DbManager::quotes::created).data().isNull())
    {
        quoteModel->setData(this->quoteModel->index(mapper->currentIndex(),
                          DbManager::quotes::created), QDate::currentDate().toString("yyyy-MM-dd"));
    }

    //Reset UI state
    ui->comboBox->setCurrentIndex(0);

    quoteModel->submitAll();
    this->accept();
}

void QuoteDialog::on_QuoteDialog_rejected()
{
    //Reset UI state
    ui->comboBox->setCurrentIndex(0);

    this->quoteModel->revertAll();
}
