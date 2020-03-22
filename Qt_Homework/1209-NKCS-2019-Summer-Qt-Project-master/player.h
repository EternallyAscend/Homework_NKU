#ifndef PLAYER_H
#define PLAYER_H

#include "head.h"
#include "weapon.h"

class Player : public QWidget
{
    Q_OBJECT
public:
    explicit Player(QWidget *parent,QGraphicsScene *scene = nullptr);
    ~Player();
    int life;
    int atk;//attack
    int speed;
    int weapon;
    int xP;
    int yP;
    bool pause;
    int direction;
    bool lock;
    bool touchHall;

    int ele;

    int width;
    int height;
    QPainter *picture;
    QPalette *background;
    bool w,a,s,d,q,e,space;
    QLabel *btn;
    QPixmap pic;
    QTimer *moveTimer;
    QTimer *rushTimer;
    QTimer *rushInterval;
    Weapon *att;
    QGraphicsScene *sweapon;
    QGraphicsPixmapItem *pixmap;
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *evnet);
    void keyReleaseEvent(QKeyEvent *event);
//    void paintEvent(QPaintEvent *event);
signals:
    void changePosition();
    void createFarAttack();
    void died();
public slots:
    void attack(int x,int y);
    void getHurt(int hurt,int percent);
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
//    bool touchHall();
    void destory();
};

#endif // PLAYER_H
