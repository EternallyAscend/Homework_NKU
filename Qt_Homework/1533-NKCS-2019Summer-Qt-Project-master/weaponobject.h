#ifndef WEAPONOBJECT_H
#define WEAPONOBJECT_H

#include "head.h"
#include <QObject>
#include "weaponpixmap.h"
class Maps;
class WeaponObject : public QObject
{
    Q_OBJECT
public:
    explicit WeaponObject(WeaponPixmap *pixmap, double xx,double yy,double toX,double toY,double wspeed,Maps *field);
    ~WeaponObject();
    WeaponPixmap *weaponPixmap;
    double speed;
    double xTo;
    double yTo;
    int typeNum;//武器号码
    int atk;
    bool attackType;//攻击类型
    double xxx;
    double yyy;
    QTimer* attacktime;
    QTimer* deleteattack;
    QGraphicsScene *weaponScene;
    Maps *wmaps;
signals:
    void touchHall();
public slots:
    void moveTo();
    void destroy();
};

#endif // WEAPONOBJECT_H
