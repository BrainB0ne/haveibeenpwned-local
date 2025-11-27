/*
 * HaveIBeenPwned Local
 * Copyleft 2025
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "resulttabledialog.h"
#include "ui_resulttabledialog.h"

#include <QMenu>
#include <QClipboard>

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

void ResultTableDialog::on_resultTableWidget_customContextMenuRequested(const QPoint &pos)
{
    int row = ui->resultTableWidget->rowAt(pos.y());
    int col = ui->resultTableWidget->columnAt(pos.x());

    if (row < 0 || col < 0)
        return;

    QMenu* contextMenu = new QMenu(this);

    if (contextMenu)
    {
        QAction* copyPassword = contextMenu->addAction(QIcon(":/images/tabler/password.png"), tr("Copy Password"));
        QAction* copyHash = contextMenu->addAction(QIcon(":/images/tabler/hash.png"), tr("Copy Hash"));

        QAction* act = contextMenu->exec(QCursor::pos());

        if (act == copyPassword)
        {
            QString password = ui->resultTableWidget->item(row, 0)->text();
            QClipboard *clipboard = QGuiApplication::clipboard();
            clipboard->setText(password);
        }
        else if (act == copyHash)
        {
            QString hash = ui->resultTableWidget->item(row, 1)->text();
            QClipboard *clipboard = QGuiApplication::clipboard();
            clipboard->setText(hash);
        }

        contextMenu->deleteLater();
    }
}

