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

#include "resultdialog.h"
#include "ui_resultdialog.h"

ResultDialog::ResultDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ResultDialog)
{
    ui->setupUi(this);

    ui->labelResult->setAutoFillBackground(true);
}

ResultDialog::~ResultDialog()
{
    delete ui;
}

void ResultDialog::setLabelColor(int color)
{
    QPalette pallete = ui->labelResult->palette();

    if (color == COLOR_RED)
    {
        pallete.setColor(QPalette::Window, Qt::red);
    }
    else if (color == COLOR_GREEN)
    {
        pallete.setColor(QPalette::Window, Qt::green);
    }

    ui->labelResult->setPalette(pallete);
}

void ResultDialog::setLabelText(const QString& text)
{
    ui->labelResult->setText(text);
}

void ResultDialog::on_okButtonBox_accepted()
{
    close();
}

