#ifndef MONSTERS_H
#define MONSTERS_H

#include "monsterobject.h"

class Gunner:public MonsterObject{

    Q_OBJECT

public:
    Gunner(MonsterPixmap *pixmap,int number,double xx,double yy,Maps* field);
    ~Gunner();

signals:

public slots:
    virtual void move();
    virtual void changeDirection();
    virtual void attackPlayer();
    virtual void setTimer();
};

//class Sniper:public MonsterObject{

//    Q_OBJECT

//public:
//    Sniper(MonsterPixmap *pixmap,int number,double mspeed,double xx,double yy,double xT,double yT,Maps* field);
//    ~Sniper();

//signals:

//public slots:
//    virtual void move();
//    virtual void changeDirection();
//    virtual void attackPlayer();
//    virtual void setTimer();
//};

class MachineGunner:public MonsterObject{

    Q_OBJECT

public:
    MachineGunner(MonsterPixmap *pixmap,int number,double xx,double yy,Maps* field);
    ~MachineGunner();

signals:

public slots:
    virtual void move();
    virtual void changeDirection();
    virtual void attackPlayer();
    virtual void setTimer();
};

class Shotgun:public MonsterObject{

    Q_OBJECT

public:
    Shotgun(MonsterPixmap *pixmap,int number,double xx,double yy,Maps* field);
    ~Shotgun();
    QTimer *atkTimer;
signals:

public slots:
    virtual void move();
    virtual void changeDirection();
    virtual void attackPlayer();
    virtual void setTimer();
};

class Scatter:public MonsterObject{

    Q_OBJECT

public:
    Scatter(MonsterPixmap *pixmap,int number,double xx,double yy,Maps* field);
    ~Scatter();

signals:

public slots:
    virtual void move();
    virtual void changeDirection();
    virtual void attackPlayer();
    virtual void setTimer();
};

class Annihilater:public MonsterObject{

    Q_OBJECT

public:
    Annihilater(MonsterPixmap *pixmap,int number,double xx,double yy,Maps* field);
    ~Annihilater();
    double dir;
signals:

public slots:
    virtual void move();
    virtual void changeDirection();
    virtual void attackPlayer();
    virtual void setTimer();
};

#endif // MONSTERS_H
