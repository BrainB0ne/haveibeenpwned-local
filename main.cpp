#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setApplicationName("HaveIBeenPwned Local");
    QApplication::setApplicationVersion("0.1.0");

    MainWindow w;
    w.show();
    return a.exec();
}
