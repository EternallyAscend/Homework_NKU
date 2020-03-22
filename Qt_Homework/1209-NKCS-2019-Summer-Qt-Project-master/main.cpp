#include "mainwindow.h"
#include "begindialog.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow *mainWindow;
    mainWindow=new MainWindow();
    mainWindow->setMinimumSize(1024,768);
    mainWindow->setMaximumSize(1024,768);
    mainWindow->setFixedSize(1024,768);
    mainWindow->move(440,100);
    mainWindow->setWindowTitle("Peace Game Pro");

    return a.exec();
}
//2019.06.30 00:35
