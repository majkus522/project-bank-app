#include "AccountWidget.h"
#include "ui_AccountWidget.h"
#include <libpq-fe.h>
#include <QFile>
#include <iostream>

using namespace std;

AccountWidget::AccountWidget(QWidget *parent, int accountId) : QWidget(parent), ui(new Ui::AccountWidget), accountId(accountId)
{
    ui->setupUi(this);

    const char* paramValues[1];
    paramValues[0] = std::to_string(accountId).c_str();
    PGresult *res = PQexecParams(Database::getInstance().connection(), "SELECT * FROM account_info WHERE id = $1",
        1, nullptr, paramValues, nullptr, nullptr, 0);
    ui->accountButton->setText(QString::fromUtf8(PQgetvalue(res, 0, 1)) + "\n\n" + QString::fromUtf8(PQgetvalue(res, 0, 4)));
}

AccountWidget::~AccountWidget()
{
    delete ui;
}

void AccountWidget::on_accountButton_clicked()
{
    cout << accountId << endl;
}