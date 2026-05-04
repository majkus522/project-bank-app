#include "LoginWindow.h"
#include "./ui_LoginWindow.h"
#include <QObject>
#include <libpq-fe.h>
#include <iostream>
#include "Database.h"
#include "main.h"

LoginWindow::LoginWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::addDatabase(Database *db)
{
    this->db = db;
}

void LoginWindow::on_pushButton_clicked()
{
    const char* paramValues[2];
    paramValues[0] = "test";
    paramValues[1] = "test";
    PGresult *res = PQexecParams(db->connection(), "SELECT * FROM users WHERE name = $1 AND password = $2",
        2, nullptr, paramValues, nullptr, nullptr, 0);
    if (PQntuples(res) > 0)
        this->close();
    PQclear(res);
}
