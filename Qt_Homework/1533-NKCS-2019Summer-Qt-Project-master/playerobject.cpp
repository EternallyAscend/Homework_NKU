#include "playerobject.h"

PlayerObject::PlayerObject(PlayerPixmap *pixmap)
{
    life=1000;
    atk=50;
    weapon=0;
    speed=1.2;
    playerPixmap=pixmap;
    w=a=s=d=q=e=space=false;
    pause=false;
    moveTimer=new QTimer(this);
    moveTimer->start(10);
    connect(moveTimer,SIGNAL(timeout()),this,SLOT(movePlayer()));
    connect(this,&PlayerObject::died,this,[=](){
        alivePlayer=false;
    });
    playerPixmap->playerObject=this;
}
PlayerObject::~PlayerObject(){

}
void PlayerObject::destory(){

}
//*********************************************************************************************
void PlayerObject::attack(int x,int y){
    Q_UNUSED(x);
    Q_UNUSED(y);
    emit createFarAttack();

}//产生由(xP,yP)->(x,y)的Weapon进攻
void PlayerObject::getHurt(double hurt,double percent){
    life-=hurt*percent;
    if(life<=0){
        destory();
    }
}//受到伤害生命值降低
//********************************************************************************Normal Action
//*********************************************************************************************
void PlayerObject::moveLeft(){
    if(!playerPixmap->touchHall){
        if(playerPixmap->xP-speed<0){
            playerPixmap->xP=0;
        }
        else{
            playerPixmap->xP-=speed;
        }
        if(playerPixmap->x()-speed<0){
            playerPixmap->moveBy(-playerPixmap->x(),0);
        }
        else{
            playerPixmap->moveBy(-speed,0);
        }
    }
    qDebug()<<"Move X="<<playerPixmap->xP<<" Y="<<playerPixmap->yP;
}
void PlayerObject::moveRight(){
    if(!playerPixmap->touchHall){
        if(playerPixmap->xP+speed>1024-playerPixmap->width){
            playerPixmap->xP=1024-playerPixmap->width;
        }
        else{
            playerPixmap->xP+=speed;
        }
        if(playerPixmap->x()+speed>1024-playerPixmap->width){
            playerPixmap->moveBy(1024-playerPixmap->width-playerPixmap->x(),0);
        }
        else{
            playerPixmap->moveBy(speed,0);
        }
    }
    qDebug()<<"Move X="<<playerPixmap->xP<<" Y="<<playerPixmap->yP;
}
void PlayerObject::moveTop(){
    if(!playerPixmap->touchHall){
        if(playerPixmap->yP-speed<0){
            playerPixmap->yP=0;
        }
        else{
            playerPixmap->yP-=speed;
        }
        if(playerPixmap->y()-speed<0){
            playerPixmap->moveBy(0,-playerPixmap->y());
        }
        else{
            playerPixmap->moveBy(0,-speed);
        }
    }
    qDebug()<<"Move X="<<playerPixmap->xP<<" Y="<<playerPixmap->yP;
}
void PlayerObject::moveBottom(){
    if(!playerPixmap->touchHall){
        if(playerPixmap->yP+speed>768-playerPixmap->height){
            playerPixmap->yP=768-playerPixmap->height;
        }
        else{
            playerPixmap->yP+=speed;
        }
        if(playerPixmap->y()+speed>768-playerPixmap->height){
            playerPixmap->moveBy(0,768-playerPixmap->height-playerPixmap->y());
        }
        else{
            playerPixmap->moveBy(0,speed);
        }
    }
    qDebug()<<"Move X="<<playerPixmap->xP<<" Y="<<playerPixmap->yP;
}
//*****************************************************************************Function of Move
//*********************************************************************************************
void PlayerObject::rush(){
    if(!space){
        rushTimer=new QTimer(this);

        rushTimer->start(500);
        connect(rushTimer,SIGNAL(timeout()),this,SLOT(speedNormal()));
        speed+=4;
        space=true;
    }
}
void PlayerObject::speedNormal(){
    rushTimer->stop();
    space=false;
    speed=2;
}
//*****************************************************************************Function of Rush
//*********************************************************************************************
void PlayerObject::changeWeapon(){
    if(!(weapon--))weapon=3;
}

void PlayerObject::changePosition(int x,int y){
    playerPixmap->moveBy(x-playerPixmap->xP,y-playerPixmap->yP);

    playerPixmap->xP=x;
    playerPixmap->yP=y;
}
void PlayerObject::change_elements(){

}
//***************************************************************************Function of Skill
//*******************************************************************
void PlayerObject::mousePressEvent(QMouseEvent *event){
    qDebug()<<"press x="<<event->x()<<"  y="<<event->y();
    emit createFarAttack();
}
void PlayerObject::mouseReleaseEvent(QMouseEvent *event){
    qDebug()<<"release x="<<event->x()<<"  y="<<event->y();
    playerPixmap->setFocus();
}
//*************************************************************Delete
//********************************************************************************************
void PlayerObject::keyPressEvent(QKeyEvent *event){
//    qDebug()<<"Key Pressed";
    switch(event->key()){
        case 65:
            a=true;
            event->accept();
//            qDebug()<<"Key:"<<event->key();
            break;
        case 87:
            w=true;
            event->accept();
//            qDebug()<<"Key:"<<event->key();
            break;
        case 68:
            d=true;
            event->accept();
//            qDebug()<<"Key:"<<event->key();
            break;
        case 83:
            s=true;
            event->accept();
//            qDebug()<<"Key:"<<event->key();
            break;

        default:
            event->ignore();
            break;
        }
}
void PlayerObject::keyReleaseEvent(QKeyEvent *event){
//    qDebug()<<"Key Released";
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
        playerPixmap->setFocus();
}
void PlayerObject::movePlayer(){
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
        if(life<=0){
            life=0;
            emit died();
        }
        if(life>1000){
            life=1000;
        }
}

//**********************************************************************************Key Press*
//2019.07.03 05:05
//2019.07.04 20:27
//2019.07.05 00:24
//2019.07.05 08:40
