#pragma once

#include <QMainWindow>

#include "Database.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class LoginWindow;
}
QT_END_NAMESPACE

class LoginWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::LoginWindow *ui;
        Database * db;

    public:
        explicit LoginWindow(QWidget *parent = nullptr);
        ~LoginWindow() override;
        void addDatabase(Database * db);

    private slots:
        void on_pushButton_clicked();
};