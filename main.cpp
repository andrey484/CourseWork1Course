#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>
#include "startup.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartUp w;
    w.show();

    return a.exec();
}
