#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "aboutdialog.h"

#include <QCryptographicHash>
#include <QFileDialog>
#include <QSqlDatabase>
#include <QSqlQuery>

#define LINE_SEPARATOR "----------------------------------------------------------------------"

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

        if ( db.open() )
        {
            ui->logPlainTextEdit->appendPlainText(LINE_SEPARATOR);
            //ui->logPlainTextEdit->appendPlainText("SQLite Database opened!");

            ui->logPlainTextEdit->appendPlainText(
                        QString("Checking Password: %1 | Hash (NTLM): %2")
                        .arg(ui->passwordLineEdit->text())
                        .arg(ui->hashLineEdit->text()));

            QSqlQuery query;
            query.prepare("SELECT prevalence FROM passwords WHERE hash=?");
            query.bindValue(0, ui->hashLineEdit->text());
            query.exec();

            if (query.first())
            {
                QString prevalence = query.value(0).toString();
                ui->logPlainTextEdit->appendPlainText(QString("Pwned! This password has been seen %1 times.").arg(prevalence));
            }
            else
            {
                ui->logPlainTextEdit->appendPlainText("Not pwned!");
            }

            db.close();

            //ui->logPlainTextEdit->appendPlainText("SQLite Database closed!");
            ui->logPlainTextEdit->appendPlainText(LINE_SEPARATOR);
        }
    }
    else
    {
        ui->logPlainTextEdit->appendPlainText("No SQLite database selected!");
    }

    if (!m_strSQLiteDatabase.isEmpty() && QFile::exists(m_strSQLiteDatabase))
    {
        QSqlDatabase::removeDatabase(connectionName);

        //ui->logPlainTextEdit->appendPlainText(QString("SQLite Database '%1' removed!").arg(connectionName));
    }

    ui->logPlainTextEdit->ensureCursorVisible();
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

void MainWindow::updateHash(const QString& password)
{
    QStringEncoder toUtf16LE = QStringEncoder(QStringEncoder::Utf16LE);
    QByteArray encodedUtf16LEString = toUtf16LE(password);

    QByteArray baNTLMHash = QCryptographicHash::hash(
                encodedUtf16LEString, QCryptographicHash::Md4);

    QString strNTLMHash = QString(baNTLMHash.toHex().toUpper());

    ui->hashLineEdit->setText(strNTLMHash);
}

void MainWindow::on_actionAbout_triggered()
{
    AboutDialog* aboutDialog = new AboutDialog(this);

    if (aboutDialog)
        aboutDialog->exec();
}
