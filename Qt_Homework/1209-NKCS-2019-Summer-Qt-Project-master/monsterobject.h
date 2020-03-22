#ifndef MONSTEROBJECT_H
#define MONSTEROBJECT_H

#include <QObject>
#include "head.h"
#include "monsterpixmap.h"

class Maps;
class MonsterObject : public QObject
{
    Q_OBJECT
public:
    explicit MonsterObject(MonsterPixmap *pixmap,int number,double mspeed,double xx,double yy,double xT,double yT,Maps *field,int hp=100,int atk=10);
    ~MonsterObject();
    MonsterPixmap *monsterPixmap;
    int value;
    int weight;
    int num;//Number of monster
    double life;
    int atk;
    double speed;
    double x;
    double y;
    double xTo;
    double yTo;
    bool easy;
    bool difficult;
    bool inMaps;
    Maps* maps;

    QTimer *moveTimer;
    QTimer *attackTimer;
    QTimer *lifeTimer;
    QTimer *dirTimer;
    QGraphicsRectItem *lifeRect;
    QGraphicsRectItem *lifeBackground;
signals:
    void create();
    void touchHall();
    void died();
public slots:
    virtual void attackPlayer();
    void getAttack(int hurt,float percent);

    virtual void changeDirection();
    virtual void move();
    virtual void setTimer();
    void checkLife();

    void destroy();
};

#endif // MONSTEROBJECT_H
//2019.07.05 08:45
