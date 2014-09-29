#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("AUDIT CONTROLER - v0.9.7");
    a.setWindowIcon(QIcon(":/icons/img/appicon.ico"));
    w.show();

    return a.exec();
}
