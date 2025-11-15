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

#include "convertdialog.h"
#include "ui_convertdialog.h"

#include <QFileDialog>

ConvertDialog::ConvertDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConvertDialog)
{
    ui->setupUi(this);
}

ConvertDialog::~ConvertDialog()
{
    delete ui;
}

void ConvertDialog::initialize(const QString& inputFile, const QString& outputFile)
{
    ui->inputLineEdit->setText(inputFile);
    ui->outputLineEdit->setText(outputFile);
}

QString ConvertDialog::getInputFile()
{
    return ui->inputLineEdit->text();
}

QString ConvertDialog::getOutputFile()
{
    return ui->outputLineEdit->text();
}

void ConvertDialog::on_inputBrowseButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Select Input File"),
                ui->inputLineEdit->text(),
                tr("Text Files (*.txt)"));

    if (!fileName.isEmpty())
    {
        ui->inputLineEdit->setText(QDir::toNativeSeparators(fileName));
    }
}

void ConvertDialog::on_outputBrowseButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(
                this,
                tr("Select Output File"),
                ui->outputLineEdit->text(),
                tr("SQLite Database Files (*.sqlite)"));

    if (!fileName.isEmpty())
    {
        ui->outputLineEdit->setText(QDir::toNativeSeparators(fileName));
    }
}
