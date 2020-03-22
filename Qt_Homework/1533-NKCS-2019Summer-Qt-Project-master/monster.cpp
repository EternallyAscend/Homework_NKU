#include "monster.h"

Monster::Monster(int xx,int yy,int xT,int yT,int movespeed,bool veryeasy,bool veryhard,QGraphicsScene *scene)
{
    sweapon=scene;
    pixmap=new QGraphicsPixmapItem(QPixmap(":/res/weapon50.png"));
    pixmap->moveBy(xx,yy);
    sweapon->addItem(pixmap);
    emit create();
}

void Monster::attackPlayer(){

}
void Monster::getAttack(int hurt,float precent){
    life-=hurt*precent;
    if(life<=0){
        destory();
    }
}
void Monster::changeDirection(int x,int y){

}
void Monster::move(int xT,int yT){

}
void Monster::destory(){

}
Monster::~Monster(){

}
