#include "RegisterDialog.h"
#include "ui_RegisterDialog.h"
#include <iostream>

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
    cout << ui->editLogin->text().toStdString() << ui->editEmail->text().toStdString() << endl;
}