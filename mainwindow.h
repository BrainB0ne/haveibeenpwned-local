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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class PwnedResult;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void loadSettings();
    void saveSettings();

    QString calcHash(const QString& password);
    void updateHash(const QString& password);
    void processLine(const QString& line);

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void on_checkButton_clicked();
    void on_actionExit_triggered();
    void on_actionLoad_triggered();
    void on_actionConvert_triggered();
    void on_actionAbout_triggered();
    void on_passwordLineEdit_textChanged(const QString &arg1);
    void on_browseButton_clicked();
    void on_clearButton_clicked();
    void on_passwordLineEdit_returnPressed();

private:
    Ui::MainWindow *ui;
    QString mSQLiteDatabase;
    QList<PwnedResult*> mResults;
    QSettings *mSettings;
};
#endif // MAINWINDOW_H
