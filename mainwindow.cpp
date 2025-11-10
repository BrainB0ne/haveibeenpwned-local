#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QCryptographicHash>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_checkButton_clicked()
{
    QString strPassword = ui->passwordLineEdit->text();

    QStringEncoder toUtf16 = QStringEncoder(QStringEncoder::Utf16LE);
    QByteArray encodedUtf16String = toUtf16(strPassword);

    QByteArray ba = QCryptographicHash::hash(encodedUtf16String, QCryptographicHash::Md4);

    QString strHash = QString(ba.toHex().toUpper());

    ui->hashLineEdit->setText(strHash);

    ui->logPlainTextEdit->appendPlainText(
                QString("Checking Password: %1 | Hash (NTLM): %2")
                .arg(strPassword)
                .arg(strHash));
}

