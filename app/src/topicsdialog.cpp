#include "topicsdialog.h"
#include "ui_topicsdialog.h"

TopicsDialog::TopicsDialog(QWidget *parent,
                           QSqlTableModel *topicModel) :
    QDialog(parent),
    ui(new Ui::TopicsDialog)
{
    ui->setupUi(this);

    //Model Init
    this->topicModel = topicModel;
    this->orderedModel = new QSortFilterProxyModel();
    this->orderedModel->setSourceModel(this->topicModel);
    this->orderedModel->setSortCaseSensitivity(Qt::CaseInsensitive);
    this->orderedModel->sort(DbManager::topics::name);

    //View Init
    ui->listView->setModel(this->orderedModel);
    ui->listView->setModelColumn(DbManager::topics::name);
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->listView->setSelectionMode(QAbstractItemView::SingleSelection);
}

TopicsDialog::~TopicsDialog()
{
    delete ui;
}

void TopicsDialog::on_AddTopic_clicked()
{
    QSqlRecord newTopic;
    newTopic.setValue(topicTableEnum.key(DbManager::topics::name), QString());
    topicModel->insertRecord(orderedModel->rowCount(), newTopic);
    QModelIndex index = this->orderedModel->index(0, DbManager::topics::name);
    ui->listView->selectionModel()->clear();
    ui->listView->edit(index);
}

void TopicsDialog::on_RemoveTopic_clicked()
{
    if (ui->listView->selectionModel()->currentIndex().isValid())
    {
        int ret = QMessageBox::warning(this, tr("Remove topic"),
                                       tr("Are you sure you want to delete this topic? "
                                          "This will remove all quotes related"),
                                       QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
        if (ret == QMessageBox::Ok)
        {
            orderedModel->removeRow(ui->listView->selectionModel()->currentIndex().row());
            topicModel->submitAll();
        }
    }
    else
    {
        QMessageBox::warning(this, tr("Remove topic"),
                             tr("Please select a topic first"),
                             QMessageBox::Ok, QMessageBox::Ok);
    }
}

void TopicsDialog::on_TopicsDialog_rejected()
{
    //Remove empty topics
    QModelIndex index;
    for(int i = 0; i < this->topicModel->rowCount(); i++)
    {
        index = this->topicModel->index(i, DbManager::topics::name);
        if (index.data().toString() == QString())
        {
            topicModel->removeRow(index.row());
        }
    }

    topicModel->submitAll();
}
