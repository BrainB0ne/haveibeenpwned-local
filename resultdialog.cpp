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
