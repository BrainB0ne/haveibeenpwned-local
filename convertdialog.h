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

#ifndef CONVERTDIALOG_H
#define CONVERTDIALOG_H

#include <QDialog>

namespace Ui {
class ConvertDialog;
}

class ConvertDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConvertDialog(QWidget *parent = nullptr);
    ~ConvertDialog();

    void initialize(const QString& inputFile, const QString& outputFile);

    QString getInputFile();
    QString getOutputFile();

private slots:
    void on_inputBrowseButton_clicked();
    void on_outputBrowseButton_clicked();

private:
    Ui::ConvertDialog *ui;
};

#endif // CONVERTDIALOG_H
