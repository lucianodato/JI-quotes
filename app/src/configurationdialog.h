#ifndef CONFIGURATIONDIALOG_H
#define CONFIGURATIONDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class ConfigurationDialog;
}

class ConfigurationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigurationDialog(QWidget *parent = nullptr);
    ~ConfigurationDialog();

private slots:
    void on_pushButton_clicked();

private:
    Ui::ConfigurationDialog *ui;
    QSettings *configurations;
};

#endif // CONFIGURATIONDIALOG_H
