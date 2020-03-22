#include "bullet.h"
#include "playerpixmap.h"
#include "playerobject.h"
#include "maps.h"
#include <QGraphicsItem>

double getdir(double x1,double y1,double x2,double y2);
Bullet::Bullet(BulletPixmap *pixmap, double xx,double yy,double toX,double toY,double wspeed,double attack,Maps *field)
{
    pix=pixmap;
    atk=attack;
    xxx=xx;
    yyy=yy;
    xTo=toX;
    yTo=toY;
    dir=getdir(xx,yy,toX,toY);
    speed=wspeed;
    attacktime=new QTimer(this);
    attacktime->start(10);
    map=field;
    inMaps=true;
    connect(attacktime,&QTimer::timeout,this,[=](){
        moveTo();
            if(pix!=nullptr&&map->playerPixmap&&map){
                if(pix->collidesWithItem(map->playerPixmap))
                {
                  map->playerObject->getHurt(atk,1);
                   attacktime->stop();
                  if(pix!=nullptr){
                      pix->bscene->removeItem(pix);
                      delete pix;
                        this->deleteLater();
                  }
                }

            }



    });

    connect(this,&Bullet::touchHall,[=](){
        attacktime->stop();

        if(pix!=nullptr){
            pix->bscene->removeItem(pix);
            delete pix;

        }
        this->deleteLater();
    });

    pix->obj=this;
}
Bullet::Bullet(BulletPixmap *pixmap, double xx,double yy,double direction,double wspeed,double attack,Maps *field)
{
    pix=pixmap;
    atk=10;
    xxx=xx;
    yyy=yy;
    dir=direction;
    speed=wspeed;
    attacktime=new QTimer(this);
    attacktime->start(10);

    map=field;
    inMaps=true;
    connect(attacktime,&QTimer::timeout,this,[=](){
        moveTo();
//        if(alivePlayer)
            if(pix!=nullptr&&map->playerPixmap&&map){
                if(pix->collidesWithItem(map->playerPixmap))
                {
                  map->playerObject->getHurt(atk,1);
                   attacktime->stop();
                  if(pix!=nullptr){
                      pix->bscene->removeItem(pix);
                      delete pix;
                        this->deleteLater();
                  }
                }
    //            this->deleteLater();
            }



    });

    connect(this,&Bullet::touchHall,[=](){
        attacktime->stop();

        if(pix!=nullptr){
            pix->bscene->removeItem(pix);
            delete pix;

        }
        this->deleteLater();
    });

    pix->obj=this;
}
void Bullet::moveTo(){
    double cache=speed;
    if(inMaps){
        if(pix!=nullptr){
            if(pix->x-speed*sin(dir)<0){
                pix->x=0;
                inMaps=false;
                destroy();

            }
            else if(pix->x-speed*sin(dir)>1024){
                pix->x=1024;
                inMaps=false;
                destroy();

            }
            else{
                pix->moveBy((speed*sin(dir)),0);
                pix->x+=speed*sin(dir);
            }
            if(pix!=nullptr)
            {
                if(pix!=nullptr&&pix->y-speed*cos(dir)<0){
                pix->y=0;
                inMaps=false;
                destroy();

            }
                else if(pix!=nullptr&&pix->y+speed*cos(dir)<0){
                pix->y=1024;
                inMaps=false;
                destroy();

            }
            else if(pix!=nullptr){
                pix->moveBy(0,speed*cos(dir));
                pix->y+=speed*cos(dir);
            }
        }
    }
    speed=cache;
    }
    else {
        if(alivePlayer){
            pix->bscene->removeItem(pix);
            delete pix;
            this->deleteLater();
        }

    }

}//*********************************************************************************************
void Bullet::destroy(){

    if(pix!=nullptr){
        pix->bscene->removeItem(pix);

        this->deleteLater();
    }
    if(attacktime!=nullptr){

    }
}
Bullet::~Bullet()
{
    if(alivePlayer){
        if(attacktime!=nullptr){
        }
        if(pix!=nullptr){
            pix->bscene->removeItem(pix);
            delete pix;
        }

        this->deleteLater();

    }
}
//2019.07.08 11:16
