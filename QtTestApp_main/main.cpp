#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{

    LOG_DEBUG("%s", "---------- Main Function Start !! ----------");

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    //w.showFullScreen();

    return a.exec();
}
