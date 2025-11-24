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

#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);
}

PreferencesDialog::~PreferencesDialog()
{
    delete ui;
}

void PreferencesDialog::setOutputHideCheckedPasswords(bool checked)
{
    ui->hideCheckedPasswordsCheckBox->setChecked(checked);
}

bool PreferencesDialog::getOutputHideCheckedPasswords()
{
    return ui->hideCheckedPasswordsCheckBox->isChecked();
}

void PreferencesDialog::setClearClipboardOnExit(bool checked)
{
    ui->clearClipboardOnExitCheckBox->setChecked(checked);
}

bool PreferencesDialog::getClearClipboardOnExit()
{
    return ui->clearClipboardOnExitCheckBox->isChecked();
}
