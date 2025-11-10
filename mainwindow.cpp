#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCryptographicHash>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateHash(ui->passwordLineEdit->text());
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
    updateHash(ui->passwordLineEdit->text());

    ui->logPlainTextEdit->appendPlainText(
                QString("Checking Password: %1 | Hash (NTLM): %2")
                .arg(ui->passwordLineEdit->text())
                .arg(ui->hashLineEdit->text()));

    if (!m_strSQLiteDatabase.isEmpty())
    {

    }
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
