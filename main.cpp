#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setWindowFlag(Qt::FramelessWindowHint);
    w.setWindowState(Qt::WindowFullScreen);
//    QDesktopWidget* p_desktop = QApplication::desktop();
//    const QRect sizeDesktop = p_desktop->screenGeometry();
//    w.setGeometry(0,0,sizeDesktop.width(),sizeDesktop.height());//установка левого верхнего угла окна приложения относительно
                                           //рабочего стола и его размеров

    w.show();

    return a.exec();
}
