#include "gameover.h"

Gameover::Gameover(QWidget *parent) : QDialog(parent)
{
    this->setMaximumSize(1024,768);
    this->setMinimumSize(1024,768);
    closeTimer=new QTimer(this);
    closeTimer->start(2000);

    p=new QPalette();
    p->setBrush(QPalette::Window, QBrush(QPixmap(":/res/Gameover.png")));
    this->setPalette(*p);
    this->move(440,100);
    this->show();
    connect(closeTimer,SIGNAL(timeout()),this,SLOT(close()));
    connect(closeTimer,&QTimer::timeout,this,[=](){

        this->close();
    });
}
//2019.07.08 21:02
