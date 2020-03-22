#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    that=parent;
    w=new Maps(parent);
    w->setMinimumSize(1024,768);
    w->setMaximumSize(1024,768);
    w->move(440,100);
    w->setWindowTitle("Peace Game Pro  7");
    w->show();
    connect(w,SIGNAL(die()),this,SLOT(rewritew()));
}
void MainWindow::rewritew(){

//    m=new Maps(that);
////    gameover=new Gameover(this);

//    disconnect(w,SIGNAL(die()),this,SLOT(rewritew()));
//    m->setMinimumSize(1024,768);
//    m->setMaximumSize(1024,768);
//    m->move(440,100);
//    m->setWindowTitle("Peace Game Pro");
//    m->show();
//    connect(m,SIGNAL(die()),this,SLOT(rewritem()));

//    w->close();
    gameover=new Gameover(this);

}
void MainWindow::rewritem(){

//    w=new Maps(that);
////    gameover=new Gameover(this);

//    disconnect(m,SIGNAL(die()),this,SLOT(rewritem()));
//    w->setMinimumSize(1024,768);
//    w->setMaximumSize(1024,768);
//    w->move(440,100);
//    w->setWindowTitle("Peace Game Pro");
//    w->show();
//    connect(w,SIGNAL(die()),this,SLOT(rewritew()));

//    m->close();
    gameover=new Gameover(this);

}
//RePlay function is updating
//2019.07.08 11:31
