#include "weapon.h"
Weapon::Weapon(QWidget *parent,int xx,int yy,int toX,int toY,int wspeed,QGraphicsScene *scene) : QWidget(parent)
{
    this->resize(1024,768);
    this->move(0,0);
    speed=wspeed;
    QPixmap picture(":/res/weapon.png");
    pixmap=new QGraphicsPixmapItem(picture);
    scene->addItem(pixmap);
    pixmap->moveBy(xx,yy);
    x=xx;
    y=yy;
    xxx=xx;
    yyy=yy;
    xTo=toX;
    yTo=toY;
    attacktime=new QTimer(this);
    attacktime->start(10);
    deleteattack=new QTimer(this);
    deleteattack->start(5000);
    connect(attacktime,&QTimer::timeout,this,[=](){
        moveTo();
    });
    connect(deleteattack,&QTimer::timeout,this,[=](){
        attacktime->stop();
        deleteattack->stop();
        delete pixmap;
    });
    connect(this,&Weapon::touchHall,[=](){
        attacktime->stop();
        deleteattack->start(1);
    });
    qDebug()<<"Constructed x="<<x<<" y="<<y;
}//*********************************************************************************************
void Weapon::moveTo(){

    int dx=xTo-xxx;
    int dy=yTo-yyy;
    int cache=speed;
    double length=sqrt(dx*dx+dy*dy);
    if(length<speed){
        speed=length;
    }
    if(length){
        if(x+speed*dx/length<=0){
            x=0;
            emit touchHall();
        }

        else if(x+speed*dx/length>=1024){
            x=1024;
            emit touchHall();
        }
        else{
            x+=speed*dx/length;
        }
        if(y+speed*dy/length<=0){
            y=0;
            emit touchHall();
        }
        else if(y+speed*dy/length>=768){
            y=768;
            emit touchHall();
        }
        else{
            y+=speed*dy/length;
        }
        if(pixmap->x()-speed*dx/length<0){
            x=0;
            emit touchHall();
        }
        else if(pixmap->x()+speed*dx/length>1024){
            x=1024;
            emit touchHall();
        }
        else{
            pixmap->moveBy((speed*dx/length),0);
        }
        if(pixmap->y()-speed*dy/length<0){
            y=0;
            emit touchHall();
        }
        else if(pixmap->y()+speed*dy/length<0){
            y=1024;
            emit touchHall();
        }
        else{
            pixmap->moveBy(0,speed*dy/length);
        }
    }
    speed=cache;
    qDebug()<<"Move x="<<x<<" y="<<y;
}//*********************************************************************************************
void Weapon::destroy(){
    if(pixmap){
        delete pixmap;
    }
}
//2019.07.03 04:00
