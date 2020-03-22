#include "weaponobject.h"
#include <QList>
#include <QGraphicsItem>
#include "monsterpixmap.cpp"
#include "monsterobject.h"
#include "maps.h"


WeaponObject::WeaponObject(WeaponPixmap *pixmap,double xx,double yy,double toX,double toY,double wspeed,Maps *field)
{
    weaponPixmap=pixmap;
    atk=50;
    xxx=xx;
    yyy=yy;
    xTo=toX;
    yTo=toY;
    speed=wspeed;
    wmaps=field;

    attacktime=new QTimer(this);
    attacktime->start(10);
    weaponPixmap->weaponObject=this;

    connect(attacktime,&QTimer::timeout,this,[=](){
        moveTo();

            QList<QGraphicsItem*> l=pixmap->collidingItems();
            if(!l.isEmpty())
            {
                for(int i=l.length()-1;i>=0;i--)
                {
                    MonsterPixmap* target=dynamic_cast<MonsterPixmap*>(l.at(i));
                    if(target==nullptr)continue;
                    else {
                        target->monsterObject->getAttack(atk,1);
                        if(alivePlayer){
                            if(weaponPixmap!=nullptr){
                                weaponPixmap->wscene->removeItem(weaponPixmap);

                                delete weaponPixmap;
                            }

                            this->deleteLater();

                        }
                        else{
    //
                            if(weaponPixmap!=nullptr){

                            }
                        }

                        break;
                    }
                }
//            }
        }

    });

    connect(this,&WeaponObject::touchHall,[=](){
        attacktime->stop();
            if(weaponPixmap!=nullptr){
                weaponPixmap->hide();
                weaponPixmap->wscene->removeItem(weaponPixmap);
//                delete weaponPixmap;

            }

            this->deleteLater();

    });


    connect(wmaps,&Maps::die,this,[=](){
        attacktime->stop();
        destroy();
    });
}
WeaponObject::~WeaponObject(){

}
//**********************************************************************************************
void WeaponObject::moveTo(){

    double dx=xTo-xxx;
    double dy=yTo-yyy;
    double cache=speed;
    double length=sqrt(dx*dx+dy*dy);
    if(length<speed){
        speed=length;
    }
    if(length&&weaponPixmap!=nullptr){


        if(weaponPixmap!=nullptr)
        {

            if(weaponPixmap->x-speed*dx/length<0){
                weaponPixmap->x=-10;
                emit touchHall();
            }
            else if(weaponPixmap->x+speed*dx/length>1024){
                weaponPixmap->x=1048;
                emit touchHall();
            }
            else{
                weaponPixmap->moveBy((speed*dx/length),0);
                weaponPixmap->x+=speed*dx/length;
            }
            if(weaponPixmap->y-speed*dy/length<0){
            weaponPixmap->y=-10;
            emit touchHall();
            }
            else if(weaponPixmap->y+speed*dy/length<0){
                weaponPixmap->y=1024;
                emit touchHall();
            }
            else{
                weaponPixmap->moveBy(0,speed*dy/length);
                weaponPixmap->y+=speed*dy/length;
            }
        }

    }
    speed=cache;

}//*********************************************************************************************
void WeaponObject::destroy(){

    if(alivePlayer){
        if(weaponPixmap!=nullptr){
            weaponPixmap->wscene->removeItem(weaponPixmap);
            delete weaponPixmap;
        }
        this->deleteLater();

    }


}
//2019.07.03 04:00
//2019.07.04 23:46
//2019.07.05 00:16
//2019/07/05 08:41
