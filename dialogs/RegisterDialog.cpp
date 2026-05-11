#include <QObject>
#include <libpq-fe.h>
#include <iostream>
#include "../Database.h"
#include "../MainWindow.h"
#include "./RegisterDialog.h"
#include "ui_RegisterDialog.h"

using namespace std;

RegisterDialog::RegisterDialog(QWidget *parent) : QDialog(parent), ui(new Ui::RegisterDialog)
{
    ui->setupUi(this);
}

RegisterDialog::~RegisterDialog()
{
    delete ui;
}

void RegisterDialog::on_pushButton_clicked()
{
    const char* paramValues[3];
    paramValues[0] = ui->editLogin->text().toStdString().c_str();
    paramValues[1] = ui->editEmail->text().toStdString().c_str();
    paramValues[2] = ui->editPassword->text().toStdString().c_str();
    // TODO: walidacja danych
    PGresult *res = PQexecParams(Database::getInstance().connection(), "INSERT INTO users (name, email, password) VALUES ($1, $2, $3) RETURNING id",
        3, nullptr, paramValues, nullptr, nullptr, 0);
    int user = atoi(PQgetvalue(res, 0, 0));
    paramValues[0] = std::to_string(user).c_str();
    res = PQexecParams(Database::getInstance().connection(), "INSERT INTO accounts (owner) VALUES ($1)",
        1, nullptr, paramValues, nullptr, nullptr, 0);
    PQclear(res);
    this->done(user);
}