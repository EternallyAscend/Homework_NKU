#include "monsterobject.h"
#include "playerobject.h"
#include "maps.h"
#include "bullet.h"
#include "bulletpixmap.h"
MonsterObject::MonsterObject(MonsterPixmap *pixmap,int number,double mspeed,double xx,double yy,double xT,double yT,Maps *field,int hp,int Atk)
{
    life=hp;
    atk=Atk;
    monsterPixmap=pixmap;
    monsterPixmap->monsterObject=this;
    num=number;
    speed=mspeed;
    x=xx;
    y=yy;
    xTo=xT;
    yTo=yT;
    maps=field;
    alivePlayer=true;


    inMaps=false;

    lifeRect=new QGraphicsRectItem(x+10,y+10,life/5,5);

    if(life>=70){
        QBrush lifeGreen(Qt::green);
       this->lifeRect->setBrush(lifeGreen);
    }
    if(life>40&&life<70){
        QBrush lifeYellow(Qt::yellow);
        this->lifeRect->setBrush(lifeYellow);
    }
    if(life<=40&&life>20){
        QBrush lifeOrange(QColor(225,158,53));
        this->lifeRect->setBrush(lifeOrange);
    }
    if(life<=20){
        QBrush lifeRed(Qt::red);
        this->lifeRect->setBrush(lifeRed);
    }

    monsterPixmap->monsterScene->addItem(lifeRect);
    ////qDebug()<<"value:"<<maps->value<<" maxvalue:"<<maps->maxvalue;
}
void MonsterObject::setTimer()
{
    moveTimer=new QTimer(this);
    moveTimer->start(10);
    attackTimer=new QTimer(this);
    attackTimer->start(1000);
    lifeTimer=new QTimer(this);
    lifeTimer->start(10);
    dirTimer=new QTimer(this);
    dirTimer->start(1000);
    connect(dirTimer,SIGNAL(timeout()),this,SLOT(changeDirection()));
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    connect(maps,SIGNAL(die()),this,SLOT(destroy()));
    connect(dirTimer,SIGNAL(timeout()),this,SLOT(attackPlayer()));
    connect(lifeTimer,SIGNAL(timeout()),this,SLOT(checkLife()));
}
void MonsterObject::attackPlayer(){
    Bullet *blt;
    BulletPixmap *bltpix;
    bltpix=new BulletPixmap(":/res/weapon.png",maps->scene,"Bullet",x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,10,10);
    blt=new Bullet(bltpix,x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,maps->playerPixmap->xP,maps->playerPixmap->yP,2,maps);
}
void MonsterObject::getAttack(int hurt,float precent){
    life-=hurt*precent;
    if(life<=0){
        if(alivePlayer){
            if(lifeRect!=nullptr){
                maps->scene->removeItem(lifeRect);
                delete lifeRect;
            }
        }
        destroy();
        if(monsterPixmap!=nullptr){

            maps->scene->removeItem(monsterPixmap);
                    delete monsterPixmap;

        }

        if(alivePlayer){
            moveTimer->stop();
            attackTimer->stop();
            lifeTimer->stop();
            dirTimer->stop();
            this->deleteLater();
        }
    }
}
void MonsterObject::changeDirection(){
    xTo=maps->playerPixmap->xP;
    yTo=maps->playerPixmap->yP;
}
void MonsterObject::move(){
        double dx=xTo-x;
        double dy=yTo-y;
        double cache=speed;
        double length=sqrt(dx*dx+dy*dy);
        double ddx=speed*dx/length;
        double ddy=speed*dy/length;
        if(length<speed){
            speed=length;
        }
        if(length<speed*2){

            ddx=0;
            ddy=0;
        }
        if(10<x&&x<1024&&10<y&&y<768){
            inMaps=true;
        }

        if(length&&inMaps){
            if(monsterPixmap->x-ddx<0){
                x=0;
                monsterPixmap->x=0;
                emit touchHall();
            }
            else if(monsterPixmap->x+ddx>1024){
                x=1024;
                monsterPixmap->x=1024;
                emit touchHall();
            }
            else{
                x+=ddx;
                monsterPixmap->x+=ddx;
                lifeRect->moveBy(ddx,0);
                monsterPixmap->moveBy(ddx,0);

            }
            if(monsterPixmap->y-ddy<0){
                y=0;
                monsterPixmap->y=0;
                emit touchHall();
            }
            else if(monsterPixmap->y+ddy<0){
                y=1024;
                monsterPixmap->y=1024;
                emit touchHall();
            }
            else{
                y+=ddy;
                monsterPixmap->y+=ddy;
                lifeRect->moveBy(0,ddy);
                monsterPixmap->moveBy(0,ddy);

            }
        }
        if(!inMaps){
            x+=ddx;
            monsterPixmap->x+=ddx;
            lifeRect->moveBy((ddx),0);
            monsterPixmap->moveBy((ddx),0);

            y+=ddy;
            monsterPixmap->y+=ddy;
            lifeRect->moveBy(0,ddy);
            monsterPixmap->moveBy(0,ddy);

        }
        speed=cache;

}

void MonsterObject::destroy(){



}
MonsterObject::~MonsterObject(){
    maps->value-=value;

}

void MonsterObject::checkLife(){

    lifeRect->setRect(x,y,life/5,5);

    if(life>=70){
        QBrush lifeGreen(Qt::green);
       lifeRect->setBrush(lifeGreen);
    }
    if(life>40&&life<70){
        QBrush lifeYellow(Qt::yellow);
        lifeRect->setBrush(lifeYellow);
    }
    if(life<=40&&life>20){
        QBrush lifeOrange(QColor(225,158,53));
        lifeRect->setBrush(lifeOrange);
    }
    if(life<=20){
        QBrush lifeRed(Qt::red);
        lifeRect->setBrush(lifeRed);
    }
//    monsterPixmap->monsterScene->addItem(lifeRect);
//    //////qDebug()<<"MonsterLife= "<<life;
//    //////qDebug()<<monsterPixmap->x<<" "<<monsterPixmap->y<<" "<<lifeRect->x()<<" "<<lifeRect->y();
}
//2019.07.05 10:29
