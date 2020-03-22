#ifndef MONSTER_H
#define MONSTER_H

#include <QObject>
#include "head.h"

class Monster : public QWidget
{
    Q_OBJECT
public:
    explicit Monster(int xx=0,int yy=0,int xT=1024,int yT=768,int movespeed=2,bool veryeasy=true,bool veryhard=false,QGraphicsScene *scene=nullptr);
    ~Monster();
    int num;//Number of monster
    int life;
    int atk;
    int speed;
    int x;
    int y;
    int xTo;
    int yTo;
    bool easy;
    bool difficult;
    QGraphicsScene *sweapon;
    QGraphicsPixmapItem *pixmap;
    QGraphicsPixmapItem *weapon;
    QTimer *moveTimer;
signals:
    void create();
    void touchHall();
    void died();
public slots:
    void attackPlayer();
    void getAttack(int hurt,float percent);

    void changeDirection(int x,int y);
    void move(int xT,int yT);

    void destory();
};

#endif // MONSTER_H
