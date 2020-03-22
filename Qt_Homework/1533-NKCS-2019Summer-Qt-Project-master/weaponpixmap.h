#ifndef WEAPONPIXMAP_H
#define WEAPONPIXMAP_H

#include "head.h"

class WeaponObject;
class WeaponPixmap : public QGraphicsPixmapItem
{
public:
    WeaponPixmap(QString url=":/res/weapon.png",QGraphicsScene *scene=nullptr,QString Name="Weapon",double xx=0,double yy=0,int wwidget=10,int wheight=10);
    ~WeaponPixmap();
    WeaponObject *weaponObject;
    double x;
    double y;
    int typeNum;//武器号码
    int width;
    int height;
    QGraphicsScene *wscene;
};

#endif // WEAPONPIXMAP_H
