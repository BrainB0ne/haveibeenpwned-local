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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "aboutdialog.h"
#include "resultdialog.h"

#include <QCryptographicHash>
#include <QStringEncoder>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

#define LINE_SEPARATOR "-----------------------------------------------------------------"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateHash(ui->passwordLineEdit->text());

    m_strSQLiteDatabase = "pwned_indexed";
    ui->dbLineEdit->setText(m_strSQLiteDatabase);
}

MainWindow::~MainWindow()
{
    if (ui) delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_checkButton_clicked()
{
    QString connectionName;

    if (!m_strSQLiteDatabase.isEmpty() && QFile::exists(m_strSQLiteDatabase))
    {
        updateHash(ui->passwordLineEdit->text());

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(m_strSQLiteDatabase);
        connectionName = db.connectionName();

        if (db.open())
        {
            if (ui->tabWidget->currentIndex() == 0)
            {
                ui->outputTextEdit->append(
                            QString("Checking Password: %1 | Hash (NTLM): %2")
                            .arg(ui->passwordLineEdit->text())
                            .arg(ui->hashLineEdit->text()));

                QSqlQuery query;
                query.prepare("SELECT prevalence FROM passwords WHERE hash=?");
                query.bindValue(0, ui->hashLineEdit->text());
                query.exec();

                ResultDialog* resDialog = new ResultDialog(this);

                if (query.first())
                {
                    QString prevalence = query.value(0).toString();
                    ui->outputTextEdit->append(QString("<font color='red'>Pwned! This password has been seen %1 times.</font>").arg(prevalence));

                    if (resDialog)
                    {
                        resDialog->setLabelColor(COLOR_RED);
                        resDialog->setLabelText("Pwned!");

                        ui->outputTextEdit->append(LINE_SEPARATOR);

                        resDialog->exec();
                    }
                }
                else
                {
                    ui->outputTextEdit->append("Not pwned!");

                    if (resDialog)
                    {
                        resDialog->setLabelColor(COLOR_GREEN);
                        resDialog->setLabelText("Not pwned!");

                        ui->outputTextEdit->append(LINE_SEPARATOR);

                        resDialog->exec();
                    }
                }

                if (resDialog)
                    resDialog->deleteLater();
            }
            else if (ui->tabWidget->currentIndex() == 1)
            {
                QString strTxtFileName = ui->fileLineEdit->text();
                QFile file(strTxtFileName);

                if (!strTxtFileName.isEmpty() && file.exists())
                {
                    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
                    {
                        QTextStream in(&file);
                        QString line = in.readLine();
                        while (!line.isNull())
                        {
                            processLine(line);
                            line = in.readLine();
                        }

                        ui->outputTextEdit->append(LINE_SEPARATOR);
                    }
                }
            }

            db.close();
        }
    }
    else
    {
        ui->outputTextEdit->append("No SQLite database found!");
    }

    if (!m_strSQLiteDatabase.isEmpty() && QFile::exists(m_strSQLiteDatabase))
    {
        QSqlDatabase::removeDatabase(connectionName);
    }

    ui->outputTextEdit->ensureCursorVisible();
}

void MainWindow::processLine(const QString& line)
{
    if (line.trimmed().isEmpty())
        return;

    QString strNTLMHash = calcHash(line);

    QSqlQuery query;
    query.prepare("SELECT prevalence FROM passwords WHERE hash=?");
    query.bindValue(0, strNTLMHash);
    query.exec();

    if (query.first())
    {
        QString prevalence = query.value(0).toString();
        ui->outputTextEdit->append(QString("<font color='red'>Pwned! Password: %1 | NTLM: %2 | Seen %3 times.</font>")
                                              .arg(line)
                                              .arg(strNTLMHash)
                                              .arg(prevalence));
    }
    else
    {
        ui->outputTextEdit->append(QString("Not pwned! Password: %1 | NTLM: %2")
                                              .arg(line)
                                              .arg(strNTLMHash));
    }
}

void MainWindow::on_passwordLineEdit_returnPressed()
{
    on_checkButton_clicked();
}

void MainWindow::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Select SQLite Database"),
                ui->dbLineEdit->text(),
                tr("All Files (*.*)"));

    if (!fileName.isEmpty())
    {
        m_strSQLiteDatabase = QDir::toNativeSeparators(fileName);
        ui->dbLineEdit->setText(m_strSQLiteDatabase);
    }
}


void MainWindow::on_passwordLineEdit_textChanged(const QString &arg1)
{
    updateHash(arg1);
}

QString MainWindow::calcHash(const QString& password)
{
    QStringEncoder toUtf16LE = QStringEncoder(QStringEncoder::Utf16LE);
    QByteArray encodedUtf16LEString = toUtf16LE(password);

    QByteArray baNTLMHash = QCryptographicHash::hash(
                encodedUtf16LEString, QCryptographicHash::Md4);

    QString strNTLMHash = QString(baNTLMHash.toHex().toUpper());

    return strNTLMHash;
}

void MainWindow::updateHash(const QString& password)
{
    QString strNTLMHash = calcHash(password);

    ui->hashLineEdit->setText(strNTLMHash);
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog* aboutDialog = new AboutDialog(this);

    if (aboutDialog)
        aboutDialog->exec();
}

void MainWindow::on_browseButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Select Passwords File"),
                ui->fileLineEdit->text(),
                tr("Text Files (*.txt)"));

    if (!fileName.isEmpty())
    {
        ui->fileLineEdit->setText(QDir::toNativeSeparators(fileName));
    }
}

void MainWindow::on_clearButton_clicked()
{
    ui->outputTextEdit->clear();
}
