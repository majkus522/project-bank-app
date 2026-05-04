#include "mainwindow.h"
#include "Database.h"
#include <QApplication>
#include "LoginWindow.h"
#include "main.h"

static Database * database;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWindow loginWindow;

    database = new Database(&a);

    loginWindow.addDatabase(database);

    loginWindow.show();
    return a.exec();
}