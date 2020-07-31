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

    //View Init
    ui->listView->setModel(topicModel);
    ui->listView->setModelColumn(topicModel->fieldIndex(
                                     topicTableEnum.key(DbManager::topics::name)));
    ui->listView->setEditTriggers(QAbstractItemView::DoubleClicked);
    ui->listView->setSelectionMode(QAbstractItemView::SingleSelection);
}

TopicsDialog::~TopicsDialog()
{
    delete ui;
}

void TopicsDialog::on_AddTopic_clicked()
{
    int newRowIndex = topicModel->rowCount();
    topicModel->insertRow(newRowIndex);
    QModelIndex index = topicModel->index(newRowIndex,
                                          topicModel->fieldIndex(
                                              topicTableEnum.key(DbManager::topics::name)));
    ui->listView->edit(index);
}

void TopicsDialog::on_RemoveTopic_clicked()
{
    topicModel->removeRow(ui->listView->currentIndex().row());
    topicModel->submitAll();
}

void TopicsDialog::on_TopicsDialog_rejected()
{
    topicModel->submitAll();
}
