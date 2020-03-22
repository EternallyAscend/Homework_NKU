#ifndef PLAYERPIXMAP_H
#define PLAYERPIXMAP_H

#include "head.h"
#include <QObject>

class PlayerObject;
class PlayerPixmap : public QGraphicsPixmapItem
{
public:
    PlayerPixmap(QString url=":/res/1.jpg",QGraphicsScene *scene=nullptr,QString name="Player");
    PlayerObject *playerObject;
    ~PlayerPixmap();
    double xP;
    double yP;

    int direction;
    bool lock;
    bool touchHall;

    int ele;

    int width;
    int height;

    QString playerName;
    QString classname;
    QGraphicsScene *sweapon;
};

#endif // PLAYERPIXMAP_H
//2019.07.04 20:21
