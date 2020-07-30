#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDataWidgetMapper>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Model Init
    quotesModel = new QSqlRelationalTableModel();
    quotesModel->setTable(quoteTableEnum.name());
    quotesModel->setHeaderData(DbManager::quotes::quoteId, Qt::Horizontal,
                               tr("quoteId"));
    quotesModel->setHeaderData(DbManager::quotes::content, Qt::Horizontal,
                               tr("Quote"));
    quotesModel->setHeaderData(DbManager::quotes::author, Qt::Horizontal,
                               tr("Author"));
    quotesModel->setHeaderData(DbManager::quotes::topicIndex, Qt::Horizontal,
                               tr("Topic"));
    quotesModel->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    quotesModel->setRelation(quotesModel->fieldIndex(quoteTableEnum.key(DbManager::quotes::topicIndex)),
                             QSqlRelation(topicTableEnum.name(),
                                          topicTableEnum.key(DbManager::topics::topicId),
                                          topicTableEnum.key(DbManager::topics::name)));

    topicModel = new QSqlTableModel();
    topicModel->setTable(topicTableEnum.name());
    topicModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    topicModel->setHeaderData(DbManager::topics::topicId, Qt::Horizontal,
                              tr("topicId"));
    topicModel->setHeaderData(DbManager::topics::name, Qt::Horizontal,
                              tr("Name"));

    //Populate models
    if (!quotesModel->select() || !topicModel->select()) {
        qDebug() << "Error getting data from database";
        return;
    }

    //View Init
    ui->tableView->setModel(quotesModel);
    ui->tableView->hideColumn(DbManager::quotes::quoteId);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setSectionResizeMode(DbManager::quotes::content, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(DbManager::quotes::author, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(DbManager::quotes::topicIndex, QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    //Mapper init
    mapper = new QDataWidgetMapper();
    mapper->setModel(quotesModel);
    connect(ui->tableView->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            mapper,
            &QDataWidgetMapper::setCurrentModelIndex);

    //Child dialogs
    this->topicsDialog = new TopicsDialog(this, topicModel);
    this->quoteDialog = new QuoteDialog(this, quotesModel, mapper);
    this->exportDialog = new ExportDialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionQuit_triggered()
{
    this->close();
}

void MainWindow::on_actionExport_triggered()
{
    exportDialog->open();
}

void MainWindow::on_actionTopics_triggered()
{
    topicsDialog->open();
}

void MainWindow::on_actionAdd_triggered()
{
    int newRowIndex = quotesModel->rowCount();
    quotesModel->insertRow(newRowIndex);
    QModelIndex index = quotesModel->index(newRowIndex,
                                           quotesModel->fieldIndex(
                                               quoteTableEnum.key(DbManager::quotes::quoteId)));
    ui->tableView->setCurrentIndex(index);
    quoteDialog->open();
}

void MainWindow::on_actionEdit_triggered()
{
    quoteDialog->open();
}

void MainWindow::on_actionRemove_triggered()
{
    quotesModel->removeRow(ui->tableView->currentIndex().row());
    quotesModel->submitAll();
}

void MainWindow::on_tableView_doubleClicked()
{
    quoteDialog->open();
}
