#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("auditControl - v0.9.8");
    a.setWindowIcon(QIcon(":/icons/img/appicon.ico"));
    w.show();

    return a.exec();
}
