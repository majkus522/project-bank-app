#pragma once

#include <QMainWindow>
#include "Database.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::MainWindow *ui;
        Database * db;

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow() override;
        void addDatabase(Database * db);
};