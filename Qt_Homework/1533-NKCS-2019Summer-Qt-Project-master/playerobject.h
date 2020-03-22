#ifndef PLAYEROBJECT_H
#define PLAYEROBJECT_H

#include "head.h"
#include <QObject>
#include "playerpixmap.h"

class PlayerObject : public QObject
{
    Q_OBJECT
public:
    explicit PlayerObject(PlayerPixmap *pixmap);
    PlayerPixmap *playerPixmap;
    ~PlayerObject();
    int life;
    int atk;//attack
    int weapon;
    double speed;
    bool pause;
    bool w,a,s,d,q,e,space;

    QTimer *moveTimer;
    QTimer *rushTimer;
    QTimer *rushInterval;

    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *evnet);
    void keyReleaseEvent(QKeyEvent *event);
signals:
    void changePosition();
    void createFarAttack();
    void died();
public slots:
    void attack(int x,int y);
    void getHurt(double hurt,double percent);
    void moveLeft();
    void moveRight();
    void moveTop();
    void moveBottom();
    void movePlayer();
    void changePosition(int x,int y);
    void rush();
    void speedNormal();
    void changeWeapon();
    void change_elements();
    void destory();
};

#endif // PLAYEROBJECT_H
//2019.07.04 20:21
