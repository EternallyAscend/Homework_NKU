#ifndef MONSTERPIXMAP_H
#define MONSTERPIXMAP_H

#include "head.h"

class MonsterObject;
class MonsterPixmap : public QGraphicsPixmapItem
{
public:
    MonsterPixmap(QString url,QGraphicsScene *scene,QString name,double xx,double yy,int mwidth,int mheight);
    ~MonsterPixmap();
    MonsterObject *monsterObject;
    QGraphicsScene *monsterScene;
    QString classname;
    double x;
    double y;
    int width;
    int height;
};

#endif // MONSTERPIXMAP_H
//2019.07.05 08:43
