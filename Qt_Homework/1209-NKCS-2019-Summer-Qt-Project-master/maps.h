#ifndef WIDGET_H
#define WIDGET_H
#include "head.h"
#include "begindialog.h"
#include <QWidget>
#include "playerobject.h"
#include "playerpixmap.h"
#include "weaponobject.h"
#include "weaponpixmap.h"
#include "monsterobject.h"
#include "monsterpixmap.h"
#include "hall.h"
//

//namespace Ui {
//class Maps;
//}
class MainWindow;
class Maps : public QWidget
{
    Q_OBJECT

public:
    explicit Maps(QWidget *parent = nullptr);
    ~Maps();
    int maxvalue;
    int value;
    bool selected;
    bool easy;
    bool difficult;
    bool w,a,s,d,q,e,space;
    const int width;
    const int height;
    bool rush;
    double rushbox;
    double rushLength;
    int keyLock;
    bool defence;
//    QTimer *rushRecover;
    QTimer *createPlayer;
    QTimer *checkLifeTimer;
    QTimer *keyLockTimer;
    QTimer *valueTimer;
    QTimer *monsterTimer;
//    QTimer *rushRecoverTimer;
    PlayerObject *playerObject;
    PlayerPixmap *playerPixmap;
    WeaponObject *playerWeaponObject;
    WeaponPixmap *playerWeaponPixmap;
    MonsterObject *monsterObject;
    MonsterPixmap *monsterPixmap;
    Hall *hall;

//    MainWindow *windows;
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsRectItem *lifebox;
    QGraphicsRectItem *life;
    QGraphicsTextItem *textLife;
    QGraphicsRectItem *rushBox;
    QGraphicsRectItem *rushLevel;
    QGraphicsTextItem *textRush;
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
signals:
    void die();
public slots:
    void createHall();
    void createMonster();
    void exit();
    void setNoDifficulty();
    void setNormal();
    void setHard();
    void startCreatePlayer();
    void checkLife();
    void rewrite();
private:
    BeginDialog *st;

private:
};

#endif // WIDGET_H
//2019.07.05 12：31
