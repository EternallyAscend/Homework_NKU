#include "monsters.h"
#include <QGraphicsPolygonItem>
#include <QPolygonF>
#include <QPolygon>
#include "maps.h"
#include <QList>
#include "hall.h"
#include <QDebug>
#include "bullet.h"
#include "bulletpixmap.h"

double getdir(double x1,double y1,double x2,double y2)
{
    double dx=x2-x1;
    double dy=y2-y1;
    if(-10e-3<dy&&dy<10e-3)
    {
        if(dx>=0)return 0;
        if(dx<0)return 3.1415926;
    }
    else {
        if(dy>=0)return atan(dx/dy);
        if(dy<0)return atan(dx/dy)+3.1415926;
    }

}
Gunner::Gunner(MonsterPixmap *pixmap,int number,double xx,double yy,Maps* field):MonsterObject (pixmap,number,1,xx,yy,512,384,field,150,20)
{
    setTimer();
    value=1;
    weight=45;
    maps->value+=value;
    //qDebug()<<"create Gunner";
}
Gunner::~Gunner()
{

}
void Gunner::setTimer()
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
void Gunner::changeDirection()
{
//    bool end=true;
//    qDebug()<<"changedirection";
    double xrand=0,yrand=0;
    while((20>xrand||xrand>1000||yrand>740||yrand<20)&&inMaps)
    {
//        end=true;
        double dir=qrand()%360;
        xrand=x+100*sin(dir);
        yrand=y+100*cos(dir);
//        QPolygon p;
//        qDebug()<<xTo<<" "<<yTo;
        if(xrand>20&&xrand<1000&&yrand>20&&yrand<740)
        {
            xTo=xrand;
            yTo=yrand;
            break;
        }
    }
}
void Gunner::attackPlayer(){
    if(inMaps){
        Bullet *blt;
        BulletPixmap *bltpix;
        bltpix=new BulletPixmap(":/res/bullet(5,5).png",maps->scene,"Bullet",x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,5,5);
        blt=new Bullet(bltpix,x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,maps->playerPixmap->xP,maps->playerPixmap->yP,5,atk,maps);
    }
}
void Gunner::move()
{
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
    if(20<x&&x<1000&&20<y&&y<740){
        inMaps=true;
    }
    else inMaps=false;
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
//            lifeRect->moveBy(ddx,0);
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
//            lifeRect->moveBy(0,ddy);
            monsterPixmap->moveBy(0,ddy);

        }
    }
    else if(!inMaps){
        x+=ddx;
        monsterPixmap->x+=ddx;
//        lifeRect->moveBy((ddx),0);
        monsterPixmap->moveBy((ddx),0);

        y+=ddy;
        monsterPixmap->y+=ddy;
//        lifeRect->moveBy(0,ddy);
        monsterPixmap->moveBy(0,ddy);

    }
    speed=cache;
}
/*------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
MachineGunner::MachineGunner(MonsterPixmap *pixmap,int number,double xx,double yy,Maps* field):MonsterObject (pixmap,number,1,xx,yy,512,384,field,500,10)
{
    setTimer();
    value=4;
    weight=15;
    qDebug()<<"create MachineGunner";
    maps->value+=value;
}
MachineGunner::~MachineGunner()
{

}
void MachineGunner::setTimer()
{
    moveTimer=new QTimer(this);
    moveTimer->start(10);
    attackTimer=new QTimer(this);
    attackTimer->start(1000);
    lifeTimer=new QTimer(this);
    lifeTimer->start(10);
    dirTimer=new QTimer(this);
    dirTimer->start(340);
//    connect(dirTimer,SIGNAL(timeout()),this,SLOT(changeDirection()));
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    connect(maps,SIGNAL(die()),this,SLOT(destroy()));
    connect(dirTimer,SIGNAL(timeout()),this,SLOT(attackPlayer()));
    connect(lifeTimer,SIGNAL(timeout()),this,SLOT(checkLife()));
}
void MachineGunner::changeDirection()
{
//    bool end=true;
//    qDebug()<<"changedirection";
    double xrand=0,yrand=0;
    while((20>xrand||xrand>1000||yrand>740||yrand<20)&&inMaps)
    {
//        end=true;
        double dir=qrand()%360;
        xrand=x+100*sin(dir);
        yrand=y+100*cos(dir);
//        QPolygon p;
//        qDebug()<<xTo<<" "<<yTo;
        if(xrand>20&&xrand<1000&&yrand>20&&yrand<740)
        {
            xTo=xrand;
            yTo=yrand;
            disconnect(dirTimer,SIGNAL(timeout()),this,SLOT(changeDirection()));
            disconnect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
            break;
        }
    }
}
void MachineGunner::attackPlayer(){
    if(inMaps){
        Bullet *blt;
        BulletPixmap *bltpix;
        bltpix=new BulletPixmap(":/res/bullet(5,5).png",maps->scene,"Bullet",x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,5,5);
        blt=new Bullet(bltpix,x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,maps->playerPixmap->xP,maps->playerPixmap->yP,2,atk,maps);
    }
}
void MachineGunner::move()
{
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
    if(20<x&&x<1000&&20<y&&y<740){
        inMaps=true;
        xTo=x;
        yTo=y;
    }
    else inMaps=false;

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
//            lifeRect->moveBy(ddx,0);
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
//            lifeRect->moveBy(0,ddy);
            monsterPixmap->moveBy(0,ddy);

        }
    }
    if(!inMaps){
        x+=ddx;
        monsterPixmap->x+=ddx;
//        lifeRect->moveBy((ddx),0);
        monsterPixmap->moveBy((ddx),0);

        y+=ddy;
        monsterPixmap->y+=ddy;
//        lifeRect->moveBy(0,ddy);
        monsterPixmap->moveBy(0,ddy);

    }
    speed=cache;
//        qDebug()<<"MonsterObject Move x="<<x<<" y="<<y;
//    qDebug()<<"ddx:"<<ddx<<" ddy:"<<ddy;
}
/*------------------------------------------------------------------------------------------------------------------------------------*/
Scatter::Scatter(MonsterPixmap *pixmap,int number,double xx,double yy,Maps* field):MonsterObject (pixmap,number,1,xx,yy,512,368,field,300,20)
{
    setTimer();
    value=2;
    weight=25;
    qDebug()<<"create Scatter";
    maps->value+=value;
}
Scatter::~Scatter()
{

}
void Scatter::setTimer()
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
void Scatter::changeDirection()
{
//    bool end=true;
//    qDebug()<<"changedirection";
    double xrand=0,yrand=0;
    while((20>xrand||xrand>1000||yrand>740||yrand<20)&&inMaps)
    {
//        end=true;
        double dir=qrand()%360;
        xrand=x+100*sin(dir);
        yrand=y+100*cos(dir);
//        QPolygon p;
        qDebug()<<xTo<<" "<<yTo;
        if(xrand>20&&xrand<1000&&yrand>20&&yrand<740)
        {
            xTo=xrand;
            yTo=yrand;
            break;
        }

    }
}
void Scatter::attackPlayer(){
    if(inMaps){
        Bullet *blt;
        BulletPixmap *bltpix;
        double dir=getdir(x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,maps->playerPixmap->xP,maps->playerPixmap->yP);
        bltpix=new BulletPixmap(":/res/bullet(5,5).png",maps->scene,"Bullet",x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,5,5);
        blt=new Bullet(bltpix,x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,dir,5,atk,maps);
        bltpix=new BulletPixmap(":/res/bullet(5,5).png",maps->scene,"Bullet",x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,5,5);
        blt=new Bullet(bltpix,x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,dir+0.09,5,atk,maps);
        bltpix=new BulletPixmap(":/res/bullet(5,5).png",maps->scene,"Bullet",x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,5,5);
        blt=new Bullet(bltpix,x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,dir-0.09,5,atk,maps);
    }
}
void Scatter::move()
{
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
    if(20<x&&x<1000&&10<y&&y<740){
        inMaps=true;
    }
    else inMaps=false;

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
//            lifeRect->moveBy(ddx,0);
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
//            lifeRect->moveBy(0,ddy);
            monsterPixmap->moveBy(0,ddy);

        }
    }
    else if(!inMaps){
        x+=ddx;
        monsterPixmap->x+=ddx;
//        lifeRect->moveBy((ddx),0);
        monsterPixmap->moveBy((ddx),0);

        y+=ddy;
        monsterPixmap->y+=ddy;
//        lifeRect->moveBy(0,ddy);
        monsterPixmap->moveBy(0,ddy);

    }
    speed=cache;
//    qDebug()<<"MonsterObject Move x="<<x<<" y="<<y;
//    qDebug()<<"ddx:"<<ddx<<" ddy:"<<ddy;
//    qDebug()<<"life x:"<<lifeRect->x()<<" life y:"<<lifeRect->y();
}
/*--------------------------------------------------------------------------------------------------------------------------*/
Annihilater::Annihilater(MonsterPixmap *pixmap,int number,double xx,double yy,Maps* field):MonsterObject (pixmap,number,1,xx,yy,512,368,field,1000,20)
{
    setTimer();
    dir=0;
    value=10;
    weight=5;
    qDebug()<<"create Annihilater";
    maps->value+=value;
}
Annihilater::~Annihilater()
{

}
void Annihilater::setTimer()
{
    moveTimer=new QTimer(this);
    moveTimer->start(10);
    attackTimer=new QTimer(this);
    attackTimer->start(1000);
    lifeTimer=new QTimer(this);
    lifeTimer->start(10);
    dirTimer=new QTimer(this);
    dirTimer->start(30);
//    connect(dirTimer,SIGNAL(timeout()),this,SLOT(changeDirection()));
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    connect(maps,SIGNAL(die()),this,SLOT(destroy()));
    connect(dirTimer,SIGNAL(timeout()),this,SLOT(attackPlayer()));
    connect(lifeTimer,SIGNAL(timeout()),this,SLOT(checkLife()));
}
void Annihilater::changeDirection()
{
//    bool end=true;
//    qDebug()<<"changedirection";
    double xrand=0,yrand=0;
    while((20>xrand||xrand>1000||yrand>740||yrand<20)&&inMaps)
    {
//        end=true;
        double dir=qrand()%360;
        xrand=x+100*sin(dir);
        yrand=y+100*cos(dir);
//        QPolygon p;
//        qDebug()<<xTo<<" "<<yTo;
        if(xrand>20&&xrand<1000&&yrand>20&&yrand<740)
        {
            xTo=xrand;
            yTo=yrand;
            break;
        }

    }
}
void Annihilater::attackPlayer(){
    if(inMaps){
        Bullet *blt;
        BulletPixmap *bltpix;
        bltpix=new BulletPixmap(":/res/weapon.png",maps->scene,"Bullet",x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,2,2);
        blt=new Bullet(bltpix,x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,dir+=0.12,5,atk,maps);
    }
}
void Annihilater::move()
{
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
    if(20<x&&x<1000&&20<y&&y<740){
        inMaps=true;
        xTo=x;
        yTo=y;
    }
    else inMaps=false;

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
//            lifeRect->moveBy(ddx,0);
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
//            lifeRect->moveBy(0,ddy);
            monsterPixmap->moveBy(0,ddy);

        }
    }
    else if(!inMaps){
        x+=ddx;
        monsterPixmap->x+=ddx;
//        lifeRect->moveBy((ddx),0);
        monsterPixmap->moveBy((ddx),0);

        y+=ddy;
        monsterPixmap->y+=ddy;
//        lifeRect->moveBy(0,ddy);
        monsterPixmap->moveBy(0,ddy);

    }
    speed=cache;
//    //qDebug()<<"MonsterObject Move x="<<x<<" y="<<y;
//    //qDebug()<<"ddx:"<<ddx<<" ddy:"<<ddy;
//    //qDebug()<<"life x:"<<lifeRect->x()<<" life y:"<<lifeRect->y();
}
/*---------------------------------------------------------------------------------------------------------------------------------------*/
Shotgun::Shotgun(MonsterPixmap *pixmap,int number,double xx,double yy,Maps* field):MonsterObject (pixmap,number,2.5,xx,yy,512,368,field,150,50)
{
    setTimer();
    value=4;
    weight=10;
    //qDebug()<<"create ShotGun";
    maps->value+=value;
}
Shotgun::~Shotgun()
{

}
void Shotgun::setTimer()
{
    moveTimer=new QTimer(this);
    moveTimer->start(10);
    attackTimer=new QTimer(this);
    attackTimer->start(1000);
    lifeTimer=new QTimer(this);
    lifeTimer->start(10);
    dirTimer=new QTimer(this);
    dirTimer->start(10);
    atkTimer=new QTimer;
    atkTimer->start(1000);
    connect(dirTimer,SIGNAL(timeout()),this,SLOT(changeDirection()));
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(move()));
    connect(maps,SIGNAL(die()),this,SLOT(destroy()));
    connect(atkTimer,SIGNAL(timeout()),this,SLOT(attackPlayer()));
    connect(lifeTimer,SIGNAL(timeout()),this,SLOT(checkLife()));
}
void Shotgun::changeDirection()
{
//    bool end=true;
//    //qDebug()<<"changedirection";
    xTo=maps->playerPixmap->xP;
    yTo=maps->playerPixmap->yP;
}
void Shotgun::attackPlayer(){
    if(inMaps){
        double dx=xTo-x;
        double dy=yTo-y;
        double distance=sqrt(dx*dx+dy*dy);
        if(distance<200){
            Bullet *blt;
            BulletPixmap *bltpix;
            bltpix=new BulletPixmap(":/res/bullet(5,5).png",maps->scene,"Bullet",x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,5,5);
            blt=new Bullet(bltpix,x+(monsterPixmap->width-10)/2,y+(monsterPixmap->height-10)/2,maps->playerPixmap->xP,maps->playerPixmap->yP,5,atk,maps);
        }
    }
}
void Shotgun::move()
{
    double dx=xTo-x;
    double dy=yTo-y;
    double cache=speed;
    double length=sqrt(dx*dx+dy*dy);
    if(length>60){
        double ddx=speed*dx/length;
        double ddy=speed*dy/length;
        if(length<speed){
            speed=length;
            }
        if(length<speed*2){

            ddx=0;
            ddy=0;
        }
        if(20<x&&x<1000&&20<y&&y<740){
            inMaps=true;
        }
        else inMaps=false;

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
                monsterPixmap->moveBy(0,ddy);
            }
        }
        else if(!inMaps){
            x+=ddx;
            monsterPixmap->x+=ddx;
            monsterPixmap->moveBy((ddx),0);

            y+=ddy;
            monsterPixmap->y+=ddy;
            monsterPixmap->moveBy(0,ddy);
        }
        speed=cache;
//        //qDebug()<<"MonsterObject Move x="<<x<<" y="<<y;
//        //qDebug()<<"ddx:"<<ddx<<" ddy:"<<ddy;
//        //qDebug()<<"life x:"<<lifeRect->x()<<" life y:"<<lifeRect->y();
    }
}
