#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include "head.h"
#include "bulletpixmap.h"
class Maps;
class Bullet:public QObject
{
    Q_OBJECT

public:
    Bullet(BulletPixmap *pixmap, double xx,double yy,double toX,double toY,double wspeed,double attack,Maps *field);
    Bullet(BulletPixmap *pixmap, double xx,double yy,double dir,double wspeed,double attack,Maps *field);
    ~Bullet();
    BulletPixmap* pix;
    double speed;
    double xTo;
    double yTo;
    double dir;
    double atk;
    double xxx;
    double yyy;
    bool inMaps;
    Maps *map;
    QTimer* attacktime;
    QTimer* deleteattack;
    QGraphicsScene *weaponScene;
signals:
    void touchHall();
public slots:
    void moveTo();
    void destroy();
};

#endif // BULLET_H
