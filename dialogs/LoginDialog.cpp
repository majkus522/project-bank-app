#include "LoginDialog.h"
#include "ui_LoginDialog.h"
#include <QObject>
#include <libpq-fe.h>
#include <iostream>
#include "../Database.h"
#include "../MainWindow.h"
#include "./RegisterDialog.h"

LoginDialog::LoginDialog(QWidget *parent) : QDialog(parent), ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_pushButton_clicked()
{
    const char* paramValues[2];
    paramValues[0] = "test";
    paramValues[1] = "test";
    PGresult *res = PQexecParams(Database::getInstance().connection(), "SELECT id FROM users WHERE name = $1 AND password = $2",
        2, nullptr, paramValues, nullptr, nullptr, 0);
    if (PQntuples(res) > 0)
    {
        this->done(1);
    }
    else
    {
        ui->label->setText("Niepoprawny login lub hasło");
    }
    PQclear(res);
}