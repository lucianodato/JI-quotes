#include "exportdialog.h"
#include "ui_exportdialog.h"

ExportDialog::ExportDialog(QWidget *parent, QSqlRelationalTableModel *quoteModel) :
    QDialog(parent),
    ui(new Ui::ExportDialog)
{
    ui->setupUi(this);

    //Model init
    this->quoteModel = quoteModel;
    this->configurations = new QSettings("JI-quotes",tr("JI-quotes"));

    //View Init
    ui->spinBox_2->setMaximum(quoteModel->rowCount());
    ui->spinBox->setMaximum(ui->spinBox_2->value());
}

ExportDialog::~ExportDialog()
{
    delete ui;
}

void ExportDialog::on_ExportQuotes_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save PDF location"), nullptr, tr("Pdf Files (*.pdf)"));
    fileName += " " + QDate::currentDate().toString(tr("M-d-yy")) + ".pdf";

    this->pdfExporter = new QPdfWriter(fileName);
    this->document = new QTextDocument();
    this->document->setHtml(CreateHtmlContent().toHtmlEscaped());
    this->document->setHtml(this->document->toPlainText());
    document->print(pdfExporter);

    this->accept();
}

void ExportDialog::on_spinBox_2_valueChanged(int arg1)
{
    ui->radioButton_2->setChecked(true);
    ui->spinBox->setMaximum(qMax(arg1 - 1, 0));
}

void ExportDialog::on_spinBox_valueChanged(int arg1)
{
    ui->radioButton_2->setChecked(true);
}

QString ExportDialog::CreateHtmlContent()
{
    QString title = "<h1 align=left>" +
            configurations->value("document/DocumentTitle").toString()
            + "</h1>";
    QString author = "<p align=left>" +
            configurations->value("document/DocumentAuthor").toString()
            + "</p>";
    QString introduction = "<p align=justify>" +
            configurations->value("document/DocumentIntroduction").toString()
            + "</p>";

    QString quotes = "<p align=justify>";
    if(ui->radioButton->isChecked())
    {
        quotes += "<ol>";
        for (int i = 0; i < quoteModel->rowCount(); i++)
        {
            quotes += "<li>" + quoteModel->index(i, DbManager::quotes::content).data().toString()
                    + " - " + quoteModel->index(i, DbManager::quotes::author).data().toString()
                    + "</li>";
        }

        quotes += "</ol></p>";
        return title + author + introduction + quotes;
    }
    else
    {
        quotes += QString("<ol start=\"%1\">").arg(QString::number(ui->spinBox->value()));
        for (int i = ui->spinBox->value(); i < ui->spinBox_2->value(); i++)
        {
            quotes += "<li>" + quoteModel->index(i, DbManager::quotes::content).data().toString()
                    + " - " + quoteModel->index(i, DbManager::quotes::author).data().toString()
                    + "</li>";
        }

        quotes += "</ol></p>";

        return title + quotes;
    }
}
