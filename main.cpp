#include "mainwindow.h"

#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap("");
    QSplashScreen splash(pixmap, Qt::FramelessWindowHint);
    splash.show();

    MainWindow w;
    w.show();
    return a.exec();
}
