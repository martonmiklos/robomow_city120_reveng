#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("MM");
    QCoreApplication::setApplicationName("Robomow reveng tool");
    QCoreApplication::setApplicationVersion("1.0");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
