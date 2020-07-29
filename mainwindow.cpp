#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->topicsDialog = new TopicsDialog(this);
    this->quoteDialog = new QuoteDialog(this);
    this->exportDialog = new ExportDialog(this);

    //Model Init
    quotesModel = new QSqlTableModel();
    quotesModel->setTable(tableEnum.name());
    quotesModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    quotesModel->select();
    quotesModel->setHeaderData(quotes::quoteId, Qt::Horizontal,
                              tr(tableEnum.key(quotes::quoteId)));
    quotesModel->setHeaderData(quotes::content, Qt::Horizontal,
                              tr(tableEnum.key(quotes::content)));
    quotesModel->setHeaderData(quotes::author, Qt::Horizontal,
                              tr(tableEnum.key(quotes::author)));
    quotesModel->setHeaderData(quotes::quoteTopic, Qt::Horizontal,
                              tr(tableEnum.key(quotes::quoteTopic)));

    //View Init
    ui->tableView->setModel(quotesModel);
    ui->tableView->hideColumn(quotes::quoteId);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->horizontalHeader()->setSectionResizeMode(quotes::content, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(quotes::author, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(quotes::quoteTopic, QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
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
    quoteDialog->open();
}

void MainWindow::on_actionEdit_triggered()
{
    quoteDialog->open();
}
