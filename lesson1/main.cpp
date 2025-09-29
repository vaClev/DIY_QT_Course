#include "mainwindow.h"

#include <QApplication>
#include <clocale>

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "");
    QString str = "Start";
    qDebug() << str;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    qDebug() << "window is running";
    return a.exec();
}
