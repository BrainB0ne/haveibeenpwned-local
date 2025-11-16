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
#include "resulttabledialog.h"
#include "pwnedresult.h"
#include "convertdialog.h"

#include <QCryptographicHash>
#include <QStringEncoder>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCloseEvent>
#include <QMessageBox>

#define LINE_SEPARATOR "----------------------------------------------------------------------"
#define APP_TITLE "HaveIBeenPwned Local"

#ifdef WIN32
    #define DEFAULT_DB "pwned_indexed.sqlite"
#else
    #define DEFAULT_DB "~/pwned_indexed.sqlite"
#endif

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mSettings = nullptr;
    mConversionProcess = nullptr;
    mConvertInputFile = QString();
    mConvertOutputFile = QString();
}

MainWindow::~MainWindow()
{
    if (ui) delete ui;
    if (mSettings) delete mSettings;
    if (mConversionProcess) delete mConversionProcess;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    saveSettings();

    if (mConversionProcess && mConversionProcess->state() == QProcess::Running)
    {
        event->ignore();
        QMessageBox::warning(this, APP_TITLE, "Warning: Can't exit application now, database conversion process still running!");
        return;
    }

    QMainWindow::closeEvent(event);
}

void MainWindow::loadSettings()
{
    mSettings = new QSettings(QSettings::IniFormat, QSettings::UserScope, QApplication::applicationName(), "settings", this);

    if (mSettings)
    {
        mSQLiteDatabase = mSettings->value("Settings/SQLiteDatabase", DEFAULT_DB).toString();
        ui->dbLineEdit->setText(mSQLiteDatabase);

        QString strPasswordsListFile = mSettings->value("Settings/PasswordsListFile", QString()).toString();
        ui->fileLineEdit->setText(strPasswordsListFile);

        mConvertInputFile = mSettings->value("Settings/ConvertInputFile", QString()).toString();
        mConvertOutputFile = mSettings->value("Settings/ConvertOutputFile", QString()).toString();
    }

    updateHash(ui->passwordLineEdit->text());
}

void MainWindow::saveSettings()
{
    if (mSettings)
    {
        mSettings->setValue("Settings/SQLiteDatabase", ui->dbLineEdit->text());
        mSettings->setValue("Settings/PasswordsListFile", ui->fileLineEdit->text());
        mSettings->setValue("Settings/ConvertInputFile", mConvertInputFile);
        mSettings->setValue("Settings/ConvertOutputFile", mConvertOutputFile);
    }
}

void MainWindow::on_actionExit_triggered()
{
    close();
}

void MainWindow::on_checkButton_clicked()
{
    QString connectionName = QString();

    if (!mSQLiteDatabase.isEmpty() && QFile::exists(mSQLiteDatabase))
    {
        updateHash(ui->passwordLineEdit->text());

        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(mSQLiteDatabase);
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
                qDeleteAll(mResults);
                mResults.clear();

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

                        file.close();

                        ui->outputTextEdit->append(LINE_SEPARATOR);

                        ResultTableDialog* resTableDialog = new ResultTableDialog(this);
                        if (resTableDialog)
                        {
                            resTableDialog->setResults(mResults);
                            resTableDialog->exec();

                            qDeleteAll(mResults);
                            mResults.clear();

                            resTableDialog->deleteLater();
                        }
                        else
                        {
                            QMessageBox::critical(this, APP_TITLE, "Failed to create ResultTableDialog!");
                        }
                    }
                }
            }

            db.close();
        }
    }
    else
    {
        ui->outputTextEdit->append("<font color='red'>Error: No SQLite database found!</font>");
    }

    if (!mSQLiteDatabase.isEmpty() && QFile::exists(mSQLiteDatabase))
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

        PwnedResult* result = new PwnedResult(this);
        if (result)
        {
            result->setPassword(line);
            result->setNTLMHash(strNTLMHash);
            result->setResult("Pwned!");
            result->setPrevalence(prevalence);

            mResults.append(result);
        }
    }
    else
    {
        ui->outputTextEdit->append(QString("Not pwned! Password: %1 | NTLM: %2")
                                              .arg(line)
                                              .arg(strNTLMHash));

        PwnedResult* result = new PwnedResult(this);
        if (result)
        {
            result->setPassword(line);
            result->setNTLMHash(strNTLMHash);
            result->setResult("Not pwned!");
            result->setPrevalence("0");

            mResults.append(result);
        }
    }
}

void MainWindow::on_passwordLineEdit_returnPressed()
{
    on_checkButton_clicked();
}

void MainWindow::on_actionLoad_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(
                this,
                tr("Select SQLite Database"),
                ui->dbLineEdit->text(),
                tr("SQLite Database Files (*.sqlite)"));

    if (!fileName.isEmpty())
    {
        mSQLiteDatabase = QDir::toNativeSeparators(fileName);
        ui->dbLineEdit->setText(mSQLiteDatabase);
    }
}

void MainWindow::on_actionConvert_triggered()
{
    QString appDirPath = QApplication::applicationDirPath();
#ifdef WIN32
    QString convertToolLocation = QString("%1\\hibp2sqlite.exe").arg(appDirPath);
#else
    QString convertToolLocation = QString("%1/hibp2sqlite").arg(appDirPath);
#endif

    if (!QFile::exists(convertToolLocation))
    {
        QMessageBox::critical(this, APP_TITLE, QString("Error: Unable to start conversion, %1 does not exist!").arg(convertToolLocation));
        return;
    }

    if (mConversionProcess && mConversionProcess->state() == QProcess::Running)
    {
        QMessageBox::warning(this, APP_TITLE, "Error: Unable to start conversion now, another database conversion process is still running!");
        return;
    }

    ConvertDialog* convertDialog = new ConvertDialog(this);

    if (convertDialog)
    {
        convertDialog->initialize(mConvertInputFile, mConvertOutputFile);

        if (convertDialog->exec() == QDialog::Accepted)
        {
            mConvertInputFile = convertDialog->getInputFile();
            mConvertOutputFile = convertDialog->getOutputFile();

            if (!QFile::exists(mConvertInputFile))
            {
                convertDialog->deleteLater();
                QMessageBox::critical(this, APP_TITLE, "Error: Unable to start conversion, input file does not exist!");
                return;
            }

            if (QFile::exists(mConvertOutputFile))
            {
                int retCode = QMessageBox::question(this, APP_TITLE, "Attention: Output file already exists!\nAre you sure you want to continue and remove/overwrite it?");

                if (retCode == QMessageBox::Yes)
                {
                    bool removeOK = QFile::remove(mConvertOutputFile);

                    if (!removeOK)
                    {
                        convertDialog->deleteLater();
                        QMessageBox::critical(this, APP_TITLE, "Error: Unable to start conversion, failed to remove output file!");
                        return;
                    }
                }
                else
                {
                    convertDialog->deleteLater();
                    return;
                }
            }
        }
        else
        {
            convertDialog->deleteLater();
            return;
        }

        convertDialog->deleteLater();
    }
    else
    {
        QMessageBox::critical(this, APP_TITLE, "Error: Failed to create ConvertDialog!");
        return;
    }

    if (!mConversionProcess)
    {
        mConversionProcess = new QProcess(this);
    }

    QStringList arguments;
    arguments << mConvertInputFile;
    arguments << mConvertOutputFile;

    mConversionProcess->start(convertToolLocation, arguments);

    connect(mConversionProcess, SIGNAL(readyReadStandardOutput()),
            this, SLOT(readConversionOutput()));
    connect(mConversionProcess, SIGNAL(finished(int, QProcess::ExitStatus)),
            this, SLOT(conversionFinished(int, QProcess::ExitStatus)));
}

void MainWindow::readConversionOutput()
{
    QString line = QString();

    while (mConversionProcess->canReadLine())
    {
        line = mConversionProcess->readLine();
        ui->outputTextEdit->append(line.remove("\r").remove("\n"));
    }
}

void MainWindow::conversionFinished(int exitCode, QProcess::ExitStatus exitStatus)
{
    ui->outputTextEdit->append(LINE_SEPARATOR);

    if (exitStatus == QProcess::NormalExit)
    {
        ui->outputTextEdit->append(QString("SQLite database conversion process exited with exitcode: %1").arg(exitCode));

        if (exitCode == 0)
        {
            int retCode = QMessageBox::question(this, APP_TITLE, "Do you want to load the created SQLite database?");

            if (retCode == QMessageBox::Yes)
            {
                mSQLiteDatabase = QDir::toNativeSeparators(mConvertOutputFile);
                ui->dbLineEdit->setText(mSQLiteDatabase);
            }
        }
    }
    else
    {
        ui->outputTextEdit->append(QString("Error: SQLite database conversion process exited abnormally with exitcode: %1").arg(exitCode));
    }

    ui->outputTextEdit->append(LINE_SEPARATOR);

    if (mConversionProcess->state() == QProcess::NotRunning)
    {
        delete mConversionProcess;
        mConversionProcess = nullptr;
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
    {
        aboutDialog->exec();
    }
    else
    {
        QMessageBox::critical(this, APP_TITLE, "Error: Failed to create AboutDialog!");
        return;
    }
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
