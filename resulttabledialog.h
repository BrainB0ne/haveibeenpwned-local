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

#ifndef RESULTTABLEDIALOG_H
#define RESULTTABLEDIALOG_H

#include <QDialog>
#include "pwnedresult.h"

namespace Ui {
class ResultTableDialog;
}

class ResultTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultTableDialog(QWidget *parent = nullptr);
    ~ResultTableDialog();

    void setResults(const QList<PwnedResult*> results);

private slots:
    void on_okButtonBox_accepted();

private:
    Ui::ResultTableDialog *ui;
};

#endif // RESULTTABLEDIALOG_H
