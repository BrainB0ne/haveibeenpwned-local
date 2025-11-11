#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString calcHash(const QString& password);
    void updateHash(const QString& password);
    void processLine(const QString& line);

private slots:
    void on_checkButton_clicked();
    void on_actionExit_triggered();
    void on_actionOpen_triggered();
    void on_actionAbout_triggered();
    void on_passwordLineEdit_textChanged(const QString &arg1);
    void on_browseButton_clicked();
    void on_clearButton_clicked();

private:
    Ui::MainWindow *ui;
    QString m_strSQLiteDatabase;

};
#endif // MAINWINDOW_H
