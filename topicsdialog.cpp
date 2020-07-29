#include "topicsdialog.h"
#include "ui_topicsdialog.h"

TopicsDialog::TopicsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TopicsDialog)
{
    ui->setupUi(this);

    //Model Init
    topicModel = new QSqlTableModel();
    topicModel->setTable(tableEnum.name());
    topicModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    topicModel->select();
    topicModel->setHeaderData(topics::topicId, Qt::Horizontal,
                              tr(tableEnum.key(topics::topicId)));
    topicModel->setHeaderData(topics::Name, Qt::Horizontal,
                              tr(tableEnum.key(topics::Name)));

    //View Init
    ui->listView->setModel(topicModel);
    ui->listView->setModelColumn(topicModel->fieldIndex(tableEnum.key(topics::Name)));
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
                                          topicModel->fieldIndex(tableEnum.key(topics::Name)));
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
