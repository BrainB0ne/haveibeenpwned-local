#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QDialog>

#define COLOR_GREEN 0
#define COLOR_RED   1

namespace Ui {
class ResultDialog;
}

class ResultDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultDialog(QWidget *parent = nullptr);
    ~ResultDialog();

    void setLabelColor(int color);
    void setLabelText(const QString& text);

private:
    Ui::ResultDialog *ui;
};

#endif // RESULTDIALOG_H
