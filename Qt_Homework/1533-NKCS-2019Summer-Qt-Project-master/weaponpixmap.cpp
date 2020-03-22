#include "weaponpixmap.h"

WeaponPixmap::WeaponPixmap(QString url,QGraphicsScene *scene,QString Name,double xx,double yy,int wwidget,int wheight):QGraphicsPixmapItem (url)
{
    x=xx;
    y=yy;
    width=wwidget;
    height=wheight;
    this->moveBy(x,y);
    scene->addItem(this);
    wscene=scene;
}
WeaponPixmap::~WeaponPixmap(){

}
//2019.07.05 00:24
