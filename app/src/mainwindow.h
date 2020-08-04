#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSortFilterProxyModel>
#include <QDataWidgetMapper>
#include <QMessageBox>
#include <QClipboard>

#include "topicsdialog.h"
#include "quotedialog.h"
#include "exportdialog.h"
#include "configurationdialog.h"
#include "dbmanager.h"
#include "customsortfilterproxymodel.h"
#include "datedelegate.h"

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

    void on_lineEdit_textChanged(const QString &arg1);

    void on_tableView_doubleClicked(const QModelIndex &index);

    void on_actionConfiguration_triggered();

    void fetch_data();

    void on_actionCopy_Quote_triggered();

private:
    Ui::MainWindow *ui;
    TopicsDialog *topicsDialog;
    QuoteDialog *quoteDialog;
    ExportDialog *exportDialog;
    ConfigurationDialog *configurationDialog;
    QMenu *tableMenu;

    QSqlRelationalTableModel *quotesModel;
    CustomSortFilterProxyModel *proxyModel;
    QDataWidgetMapper *mapper;
    QSqlTableModel *topicModel;

    QMetaEnum topicTableEnum = QMetaEnum::fromType<DbManager::topics>();
    QMetaEnum quoteTableEnum = QMetaEnum::fromType<DbManager::quotes>();

    DateDelegate *dateDelegate;

    bool SetupModels();
    void ConnectSignalAndSlots();
};
#endif // MAINWINDOW_H
