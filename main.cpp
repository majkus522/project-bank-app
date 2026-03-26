#include "mainwindow.h"
#include "Database.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    Database database(&a);

    w.show();
    return a.exec();
}