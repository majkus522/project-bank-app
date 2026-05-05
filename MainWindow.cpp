#include "MainWindow.h"

#include <QLabel>

#include "./ui_MainWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget * widget = new QWidget(this);
    QLabel * label = new QLabel("test", widget);
}

void MainWindow::setUserId(int userId)
{
    this->userId = userId;
}

MainWindow::~MainWindow()
{
    delete ui;
}
