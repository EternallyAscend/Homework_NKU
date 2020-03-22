#include "playerpixmap.h"

PlayerPixmap::PlayerPixmap(QString url,QGraphicsScene *scene,QString name):QGraphicsPixmapItem (url)
{
    width=50;
    height=50;
    xP=(1024+width)/2;
    yP=(768+height)/2;
    direction=0;
    lock=false;
    touchHall=false;
    playerName=name;
    classname="player";
    this->moveBy(xP,yP);
    ele=0;
    scene->addItem(this);
}
PlayerPixmap::~PlayerPixmap(){

}
//2019.07.05 00:24
