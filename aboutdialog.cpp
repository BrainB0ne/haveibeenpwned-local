#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    ui->buildDateLabel->setText(tr("Build Date: %1 - %2").arg(__DATE__).arg(__TIME__));
    ui->versionLabel->setText(tr("Version: %1").arg(QApplication::applicationVersion()));
}

AboutDialog::~AboutDialog()
{
    if (ui) delete ui;
}

void AboutDialog::on_licenseButton_clicked()
{
    QApplication::aboutQt();
}
