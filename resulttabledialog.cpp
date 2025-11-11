#include "resulttabledialog.h"
#include "ui_resulttabledialog.h"

ResultTableDialog::ResultTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultTableDialog)
{
    ui->setupUi(this);
}

ResultTableDialog::~ResultTableDialog()
{
    delete ui;
}

void ResultTableDialog::on_okButtonBox_accepted()
{
    close();
}

void ResultTableDialog::setResults(const QList<PwnedResult*> results)
{
    ui->resultTableWidget->setRowCount(results.count());

    int iRow = 0;

    foreach (PwnedResult* res, results)
    {
        ui->resultTableWidget->setItem(iRow, 0, new QTableWidgetItem(res->getPassword()));
        ui->resultTableWidget->setItem(iRow, 1, new QTableWidgetItem(res->getNTLMHash()));
        ui->resultTableWidget->setItem(iRow, 2, new QTableWidgetItem(res->getPrevalence()));
        ui->resultTableWidget->setItem(iRow, 3, new QTableWidgetItem(res->getResult()));

        if (res->getResult() == "Pwned!")
        {
            ui->resultTableWidget->item(iRow, 3)->setData(Qt::BackgroundRole, QColor(Qt::red));
            ui->resultTableWidget->item(iRow, 3)->setData(Qt::ForegroundRole, QColor(Qt::white));
        }
        else if (res->getResult() == "Not pwned!")
        {
            ui->resultTableWidget->item(iRow, 3)->setData(Qt::BackgroundRole, QColor(Qt::green));
        }

        iRow++;
    }

    ui->resultTableWidget->resizeColumnsToContents();
}
