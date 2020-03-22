#include "hall.h"

Hall::Hall(QString url,int x,int y,int width,int height,QGraphicsScene *scene,QString name) : QGraphicsPixmapItem (url)
{
    hallWidth=width;
    hallHeight=height;
    this->moveBy(x,y);
    Name=name;
    hallscene=scene;
    scene->addItem(this);
}
Hall::~Hall(){

}
//2019.07.05 08:19
