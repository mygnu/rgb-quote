#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationDisplayName("RGB-Quote");
    MainWindow w;
    w.show();

    return a.exec();
}
