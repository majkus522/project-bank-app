#include "MainWindow.h"

#include <iostream>
#include <libpq-fe.h>
#include <ostream>

#include "./ui_MainWindow.h"
#include "dialogs/LoginDialog.h"
#include "widgets/AccountWidget.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    LoginDialog *loginDialog = new LoginDialog(this);
    loginDialog->exec();

    int userId = loginDialog->result();
    std::cout << userId << std::endl;
    const char* paramValues[1];
    paramValues[0] = std::to_string(userId).c_str();
    PGresult *res = PQexecParams(Database::getInstance().connection(), "SELECT id FROM account_info WHERE owner = $1",
        1, nullptr, paramValues, nullptr, nullptr, 0);
    for (int index = 0; index < PQntuples(res); ++index)
    {
        auto *w = new AccountWidget(this, atoi(PQgetvalue(res, index, 0)));
        std::cout << w->objectName().toStdString() << std::endl;
        w->update();
        ui->horizontalLayout->addWidget(w);
    }
}

void MainWindow::addDatabase(Database *db)
{
    this->db = db;
}

MainWindow::~MainWindow()
{
    delete ui;
}
