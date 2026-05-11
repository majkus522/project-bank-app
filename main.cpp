#include "MainWindow.h"
#include "Database.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(true);
    MainWindow window;
    window.show();

    QFile f(":/style/accountWidget.qss");
    f.open(QFile::ReadOnly);
    app.setStyleSheet(f.readAll());

    return app.exec();
}