#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "topicsdialog.h"
#include "quotedialog.h"
#include "exportdialog.h"

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
    void on_actionTopics_triggered();

    void on_actionExport_triggered();

    void on_actionAdd_triggered();

    void on_actionEdit_triggered();

    void on_actionQuit_triggered();

private:
    Ui::MainWindow *ui;
    TopicsDialog *topicsDialog;
    QuoteDialog *quoteDialog;
    ExportDialog *exportDialog;
};
#endif // MAINWINDOW_H
