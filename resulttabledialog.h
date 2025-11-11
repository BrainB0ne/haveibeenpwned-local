#ifndef RESULTTABLEDIALOG_H
#define RESULTTABLEDIALOG_H

#include <QDialog>
#include "pwnedresult.h"

namespace Ui {
class ResultTableDialog;
}

class ResultTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ResultTableDialog(QWidget *parent = nullptr);
    ~ResultTableDialog();

    void setResults(const QList<PwnedResult*> results);

private slots:
    void on_okButtonBox_accepted();

private:
    Ui::ResultTableDialog *ui;
};

#endif // RESULTTABLEDIALOG_H
