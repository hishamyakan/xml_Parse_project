#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.titleChange();
    a.setWindowIcon(QIcon(":/resources_images/img/logo.png"));
    return a.exec();
}
