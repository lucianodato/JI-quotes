#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    topicsDialog = new TopicsDialog(this);
    quoteDialog = new QuoteDialog(this);
    exportDialog = new ExportDialog(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionTopics_triggered()
{
    topicsDialog->exec();
}

void MainWindow::on_actionExport_triggered()
{
    exportDialog->exec();
}

void MainWindow::on_actionAdd_triggered()
{
    quoteDialog->exec();
}

void MainWindow::on_actionEdit_triggered()
{
    quoteDialog->exec();
}

void MainWindow::on_actionQuit_triggered()
{
    MainWindow::close();
}
