#include "monsterpixmap.h"

MonsterPixmap::MonsterPixmap(QString url,QGraphicsScene *scene,QString name,double xx,double yy,int mwidth,int mheight):QGraphicsPixmapItem (url)
{
    x=xx;
    y=yy;
    width=mwidth;
    height=mheight;
    this->moveBy(x,y);
    scene->addItem(this);
    monsterScene=scene;
    classname=name;
}
MonsterPixmap::~MonsterPixmap(){

}
