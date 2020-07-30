#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>

#include "topicsdialog.h"
#include "quotedialog.h"
#include "exportdialog.h"
#include "dbmanager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionQuit_triggered();

    void on_actionExport_triggered();

    void on_actionTopics_triggered();

    void on_actionAdd_triggered();

    void on_actionEdit_triggered();

    void on_actionRemove_triggered();

    void on_tableView_doubleClicked();

private:
    Ui::MainWindow *ui;
    TopicsDialog *topicsDialog;
    QuoteDialog *quoteDialog;
    ExportDialog *exportDialog;

    QSqlRelationalTableModel *quotesModel;
    QDataWidgetMapper *mapper;
    QSqlTableModel *topicModel;

    QMetaEnum topicTableEnum = QMetaEnum::fromType<DbManager::topics>();
    QMetaEnum quoteTableEnum = QMetaEnum::fromType<DbManager::quotes>();
};
#endif // MAINWINDOW_H
