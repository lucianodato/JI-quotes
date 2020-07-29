#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

    enum quotes {
        quoteId,
        content,
        author,
        quoteTopic
    };
    Q_ENUM(quotes)

private slots:
    void on_actionQuit_triggered();

    void on_actionExport_triggered();

    void on_actionTopics_triggered();

    void on_actionAdd_triggered();

    void on_actionEdit_triggered();

private:
    Ui::MainWindow *ui;
    TopicsDialog *topicsDialog;
    QuoteDialog *quoteDialog;
    ExportDialog *exportDialog;

    QSqlTableModel *quotesModel;
    QMetaEnum tableEnum = QMetaEnum::fromType<quotes>();
};
#endif // MAINWINDOW_H
