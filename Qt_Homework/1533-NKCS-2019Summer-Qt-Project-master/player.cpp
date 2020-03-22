#include "player.h"

Player::Player(QWidget *parent,QGraphicsScene *scene):QWidget (parent)
{
    life=1000;
    atk=100;
    speed=4;
    weapon=0;
    xP=480;
    yP=360;
    w=a=s=d=space=q=e=pause=false;
    width=50;
    height=50;
    touchHall=false;
    sweapon=scene;
    this->resize(1024,768);
    moveTimer=new QTimer(this);
    moveTimer->start(10);
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(movePlayer()));
    QPixmap picture(":/res/1.png");
    picture.scaled(50,50,Qt::IgnoreAspectRatio);
    pixmap=new QGraphicsPixmapItem(picture);
    scene->addItem(pixmap);
    pixmap->setFlag(QGraphicsItem::ItemIsFocusable);
    pixmap->moveBy((1024-width)/2,(768-height)/2);
}
Player::~Player(){

}
void Player::destory(){
//    this->close();
}
//*********************************************************************************************
void Player::attack(int x,int y){
    Q_UNUSED(x);
    Q_UNUSED(y);
    emit createFarAttack();

}//产生由(xP,yP)->(x,y)的Weapon进攻
void Player::getHurt(int hurt,int percent){
    life-=hurt*percent;
    if(life<=0){
        destory();
    }
}//受到伤害生命值降低
//********************************************************************************Normal Action
//*********************************************************************************************
void Player::moveLeft(){
    if(!touchHall){
        if(xP-speed<0){
            xP=0;
        }
        else{
            xP-=speed;
        }
        if(pixmap->x()-speed<0){
            pixmap->moveBy(-pixmap->x(),0);
        }
        else{
            pixmap->moveBy(-speed,0);
        }
    }
    qDebug()<<"Move X="<<xP<<" Y="<<yP;
}
void Player::moveRight(){
    if(!touchHall){
        if(xP+speed>1024-width){
            xP=1024-width;
        }
        else{
            xP+=speed;
        }
        if(pixmap->x()+speed>1024-width){
            pixmap->moveBy(1024-width-pixmap->x(),0);
        }
        else{
            pixmap->moveBy(speed,0);
        }
    }
    qDebug()<<"Move X="<<xP<<" Y="<<yP;
}
void Player::moveTop(){
    if(!touchHall){
        if(yP-speed<0){
            yP=0;
        }
        else{
            yP-=speed;
        }
        if(pixmap->y()-speed<0){
            pixmap->moveBy(0,-pixmap->y());
        }
        else{
            pixmap->moveBy(0,-speed);
        }
    }
    qDebug()<<"Move X="<<xP<<" Y="<<yP;
}
void Player::moveBottom(){
    if(!touchHall){
        if(yP+speed>768-height){
            yP=768-height;
        }
        else{
            yP+=speed;
        }
        if(pixmap->y()+speed>768-height){
            pixmap->moveBy(0,768-height-pixmap->y());
        }
        else{
            pixmap->moveBy(0,speed);
        }
    }
    qDebug()<<"Move X="<<xP<<" Y="<<yP;
}
//*****************************************************************************Function of Move
//*********************************************************************************************
void Player::rush(){
    if(!space){
        rushTimer=new QTimer(this);
        rushInterval=new QTimer(this);
        rushInterval->start(10000);
        connect(rushInterval,&QTimer::timeout,this,[=](){
            space=false;
            rushInterval->stop();
        });
        rushTimer->start(1000);
        connect(rushTimer,SIGNAL(timeout()),this,SLOT(speedNormal));
        rushTimer->stop();
        speed+=4;
        space=true;
    }
}
void Player::speedNormal(){
    speed-=4;
}
//*****************************************************************************Function of Rush
//*********************************************************************************************
void Player::changeWeapon(){
    if(!(weapon--))weapon=3;
}

void Player::changePosition(int x,int y){
    pixmap->moveBy(x-xP,y-yP);
    xP=x;
    yP=y;
}
void Player::change_elements(){

}
//***************************************************************************Function of Skill
//*******************************************************************
void Player::mousePressEvent(QMouseEvent *event){
    qDebug()<<"press x="<<event->x()<<"  y="<<event->y();
    emit createFarAttack();
}
void Player::mouseReleaseEvent(QMouseEvent *event){
    qDebug()<<"release x="<<event->x()<<"  y="<<event->y();
    pixmap->setFocus();
}
//*************************************************************Delete
//********************************************************************************************
void Player::keyPressEvent(QKeyEvent *event){
    qDebug()<<"Key Pressed";
    switch(event->key()){
        case 65:
            a=true;
            event->accept();
            qDebug()<<"Key:"<<event->key();
            break;
        case 87:
            w=true;
            event->accept();
            qDebug()<<"Key:"<<event->key();
            break;
        case 68:
            d=true;
            event->accept();
            qDebug()<<"Key:"<<event->key();
            break;
        case 83:
            s=true;
            event->accept();
            qDebug()<<"Key:"<<event->key();
            break;

        default:
            event->ignore();
            break;
        }
}
void Player::keyReleaseEvent(QKeyEvent *event){
    qDebug()<<"Key Released";
    switch(event->key()){
        case 65:
            a=false;
            event->accept();
            break;
        case 87:
            w=false;
            event->accept();
            break;
        case 68:
            d=false;
            event->accept();
            break;
        case 83:
            s=false;
            event->accept();
            break;
        default:
            event->ignore();
            break;
        }
    pixmap->setFocus();
}
void Player::movePlayer(){
        if(w){
            moveTop();
        }
        if(a){
            moveLeft();
        }
        if(d){
            moveRight();
        }
        if(s){
            moveBottom();
        }
}

//**********************************************************************************Key Press*
//2019.07.03 05:05
