#ifndef WEAPON_H
#define WEAPON_H

#include "head.h"
#include <QObject>

class Weapon : public QWidget
{
    Q_OBJECT
public:
    Weapon(QWidget *parent = nullptr,int xx=0,int yy=0,int toX=0,int toY=0,int wspeed=1,QGraphicsScene *scene=nullptr);
    int x;
    int y;
    int speed;
    int xTo;
    int yTo;
    int typeNum;//武器号码
    bool attackType;//攻击类型
    int xxx;
    int yyy;
    QTimer* attacktime;
    QTimer* deleteattack;
    QGraphicsPixmapItem *pixmap;
signals:
    void touchHall();
public slots:
    void moveTo();
    void destroy();
};

#endif // WEAPON_H
