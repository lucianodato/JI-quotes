#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Model Init
    SetupModels();

    //View Init
    ui->tableView->setModel(proxyModel);
    ui->tableView->hideColumn(DbManager::quotes::quoteId);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->horizontalHeader()->setSectionResizeMode(DbManager::quotes::content, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(DbManager::quotes::author, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(DbManager::quotes::created, QHeaderView::ResizeToContents);
    ui->tableView->horizontalHeader()->setSectionResizeMode(DbManager::quotes::topicIndex, QHeaderView::ResizeToContents);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    ui->tableView->setItemDelegateForColumn(DbManager::quotes::created, this->dateDelegate);

    //Child dialogs
    this->topicsDialog = new TopicsDialog(this, topicModel);
    this->quoteDialog = new QuoteDialog(this, quotesModel, mapper);
    this->exportDialog = new ExportDialog(this, quotesModel);
    this->configurationDialog = new ConfigurationDialog(this);

    //Signal and Slot connections
    ConnectSignalAndSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::SetupModels()
{
    quotesModel = new QSqlRelationalTableModel();
    quotesModel->setTable(quoteTableEnum.name());
    quotesModel->setHeaderData(DbManager::quotes::quoteId, Qt::Horizontal,
                               tr("quoteId"));
    quotesModel->setHeaderData(DbManager::quotes::content, Qt::Horizontal,
                               tr("Quote"));
    quotesModel->setHeaderData(DbManager::quotes::author, Qt::Horizontal,
                               tr("Author"));
    quotesModel->setHeaderData(DbManager::quotes::created, Qt::Horizontal,
                               tr("Creation Date"));
    quotesModel->setHeaderData(DbManager::quotes::topicIndex, Qt::Horizontal,
                               tr("Topic"));
    quotesModel->setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);
    quotesModel->setRelation(quotesModel->fieldIndex(quoteTableEnum.key(DbManager::quotes::topicIndex)),
                             QSqlRelation(topicTableEnum.name(),
                                          topicTableEnum.key(DbManager::topics::topicId),
                                          topicTableEnum.key(DbManager::topics::name)));

    proxyModel = new CustomSortFilterProxyModel();
    proxyModel->setSourceModel(quotesModel);

    topicModel = new QSqlTableModel();
    topicModel->setTable(topicTableEnum.name());
    topicModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    topicModel->setHeaderData(DbManager::topics::topicId, Qt::Horizontal,
                              tr("topicId"));
    topicModel->setHeaderData(DbManager::topics::name, Qt::Horizontal,
                              tr("Name"));

    //Populate models
    if (!quotesModel->select() || !topicModel->select()) {
        QMessageBox::critical(this, tr("Data Error"),
                              tr("Error loading database data into applications"),
                              QMessageBox::Ok, QMessageBox::Ok);
        return false;
    }
    fetch_data();

    //Mapper init
    mapper = new QDataWidgetMapper();
    mapper->setModel(quotesModel);

    this->dateDelegate = new DateDelegate();

    return true;
}

void MainWindow::ConnectSignalAndSlots()
{

    connect(ui->tableView->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),
            mapper,
            SLOT(setCurrentModelIndex(QModelIndex)));

    // Main table

    // Data fetch
    connect(this->quotesModel,
            SIGNAL(rowsInserted(QModelIndex,int,int)),
            this,
            SLOT(fetch_data()));

    connect(this->quotesModel,
            SIGNAL(rowsRemoved(QModelIndex,int,int)),
            this,
            SLOT(fetch_data()));

    connect(this->quotesModel,
            SIGNAL(dataChanged(QModelIndex,QModelIndex,QVector<int>)),
            this,
            SLOT(fetch_data()));

    // Scrolling
    connect(this->quotesModel,
            SIGNAL(rowsInserted(QModelIndex,int,int)),
            ui->tableView,
            SLOT(scrollToBottom()));

    connect(this->quoteDialog,
            SIGNAL(accepted()),
            ui->tableView,
            SLOT(scrollToBottom()));
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
    QModelIndex index = quotesModel->index(newRowIndex, DbManager::quotes::quoteId);
    this->mapper->setCurrentIndex(index.row());
    ui->lineEdit->clear();
    quoteDialog->open();
}

void MainWindow::on_actionEdit_triggered()
{
    if (ui->tableView->selectionModel()->hasSelection())
    {
        QModelIndex currentIndex = ui->tableView->selectionModel()->currentIndex();
        this->mapper->setCurrentIndex(proxyModel->mapToSource(currentIndex).row());
        quoteDialog->open();
    }
    else
    {
        QMessageBox::warning(this, tr("Edit quote"),
                              tr("Please select a quote first"),
                              QMessageBox::Ok, QMessageBox::Ok);
    }
}

void MainWindow::on_actionRemove_triggered()
{
    if (ui->tableView->selectionModel()->hasSelection())
    {
        QModelIndex currentIndex = ui->tableView->selectionModel()->currentIndex();
        int ret = QMessageBox::warning(this, tr("Remove quote"),
                                       tr("Are you sure you want to delete this quote?"),
                                       QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok);
        if (ret == QMessageBox::Ok)
        {
            quotesModel->removeRow(proxyModel->mapToSource(currentIndex).row());
            quotesModel->submitAll();
        }
        ui->lineEdit->clear();
        ui->tableView->scrollToTop();
    }
    else
    {
        QMessageBox::warning(this, tr("Remove quote"),
                              tr("Please select a quote first"),
                              QMessageBox::Ok, QMessageBox::Ok);
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    proxyModel->setFilterRegularExpression(QRegularExpression(arg1, QRegularExpression::CaseInsensitiveOption | QRegularExpression::NoPatternOption));
}

void MainWindow::on_tableView_doubleClicked(const QModelIndex &index)
{
    this->mapper->setCurrentIndex(this->proxyModel->mapToSource(index).row());
    quoteDialog->open();
}

void MainWindow::on_actionConfiguration_triggered()
{
    this->configurationDialog->open();
}

void MainWindow::fetch_data()
{
    while (quotesModel->canFetchMore())quotesModel->fetchMore();
}

void MainWindow::on_actionCopy_Quote_triggered()
{
    if (ui->tableView->selectionModel()->hasSelection())
    {
        QClipboard *clipboard = QApplication::clipboard();

        int currentRow = ui->tableView->selectionModel()->currentIndex().row();

        QString textToCopy = this->proxyModel->index(currentRow, DbManager::quotes::content).data().toString() +
                " - " + this->proxyModel->index(currentRow, DbManager::quotes::author).data().toString();

        clipboard->setText(textToCopy);

        QMessageBox::information(this, tr("Copy quote"),
                              tr("Quote copied"),
                              QMessageBox::Ok, QMessageBox::Ok);
    }
    else
    {
        QMessageBox::warning(this, tr("Copy quote"),
                              tr("Please select a quote first"),
                              QMessageBox::Ok, QMessageBox::Ok);
    }
}
