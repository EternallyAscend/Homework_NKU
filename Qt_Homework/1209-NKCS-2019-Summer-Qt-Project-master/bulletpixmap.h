#ifndef BULLETPIXMAP_H
#define BULLETPIXMAP_H

#include "head.h"
class Bullet;
class BulletPixmap : public QGraphicsPixmapItem
{
public:
    BulletPixmap(QString url=":/res/weapon.png",QGraphicsScene *scene=nullptr,QString Name="Weapon",double xx=0,double yy=0,int wwidget=10,int wheight=10);
    ~BulletPixmap();
    Bullet* obj;
    double x;
    double y;
    int width;
    int height;
    QGraphicsScene *bscene;
};

#endif // BULLETPIXMAP_H
