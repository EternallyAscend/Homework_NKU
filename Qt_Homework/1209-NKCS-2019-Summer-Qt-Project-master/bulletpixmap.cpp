#include "bulletpixmap.h"

BulletPixmap::BulletPixmap(QString url,QGraphicsScene *scene,QString Name,double xx,double yy,int wwidget,int wheight):QGraphicsPixmapItem (url)
{
    x=xx;
    y=yy;
    width=wwidget;
    height=wheight;
    this->moveBy(x,y);
    scene->addItem(this);
    bscene=scene;
}
BulletPixmap::~BulletPixmap()
{

}
//2019.07.08 11:14
