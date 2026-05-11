#ifndef ACCOUNTWIDGET_H
#define ACCOUNTWIDGET_H

#include <QWidget>
#include "../Database.h"

namespace Ui
{
    class AccountWidget;
}

class AccountWidget : public QWidget
{
    Q_OBJECT

    private:
        Ui::AccountWidget *ui;
        const int accountId;

    public:
        explicit AccountWidget(QWidget *parent = nullptr, int accountId = -1);
        ~AccountWidget();

    private slots:
        void on_accountButton_clicked();
};

#endif // ACCOUNTWIDGET_H
