#include "maps.h"
#include "begindialog.h"
#include "monsters.h"
Maps::Maps(QWidget *parent) :
    QWidget (parent),
    width(1024),height(768)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));

////  // /\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\ //
    selected=false;
    easy=false;
    difficult=false;
    rush=false;
    rushbox=2;
    rushLength=2;
    keyLock=0;
    defence=false;
    maxvalue=3;
    value=0;
    scene=new QGraphicsScene(this);
    scene->setSceneRect(0,0,1024,768);
//    scene->setSceneRect((width-1024)/2,(height-768)/2,width,height);
//scene页面调节为可以随Player移动的大图

    view=new QGraphicsView(this);


//**********************************************************************************************
    st=new BeginDialog(this);
    st->resize(1024,768);
    st->move(0,0);
    st->show();
    connect(st,SIGNAL(exit()),this,SLOT(exit()));
    connect(st,SIGNAL(ok()),this,SLOT(setNoDifficulty()));
    connect(st,SIGNAL(veryEasy()),this,SLOT(setNoDifficulty()));
    connect(st,SIGNAL(normal()),this,SLOT(setNormal()));
    connect(st,SIGNAL(veryHard()),this,SLOT(setHard()));
//************************************************************************Choose The Difficulty

//*********************************************************************************************
    scene->addPixmap(QPixmap(":/res/bgp.jpg"));
    lifebox=new QGraphicsRectItem (20,20,200,20);
    lifebox->setBrush(QBrush(Qt::blue));
    rushLevel=new QGraphicsRectItem(260,20,200,20);
    rushLevel->setBrush(QBrush(Qt::blue));

    scene->addItem(lifebox);
    scene->addItem(rushLevel);
    checkLifeTimer=new QTimer(this);



//*****************************************************************************Create the Scene


//*********************************************************************************************

    valueTimer=new QTimer(this);
    monsterTimer=new QTimer(this);


    connect(monsterTimer,SIGNAL(timeout()),this,SLOT(createMonster()));
    connect(valueTimer,&QTimer::timeout,this,[=](){
        maxvalue++;
    });
    keyLockTimer=new QTimer(this);

//**************************************************************************Create the Monsters

//*********************************************************************************************
    view->resize(1024,768);
    view->setFixedSize(1024,768);
    view->setMinimumSize(1024,768);
    view->setMaximumSize(1024,768);
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setScene(scene);
    view->setCursor(Qt::CrossCursor);
    view->show();
//*****************************************************************Game Page Set Scene and View
}
void Maps::createHall(){


}
void Maps::createMonster(){
//    qsrand(time(NULL));
//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//    if(alivePlayer){
        while(maxvalue>value){
            int QSrandNumber=qrand()%(2*(width+height)-1)+1;
            int monsterX;
            int monsterY;

            if(1<=QSrandNumber&&QSrandNumber<=width){
                monsterX=QSrandNumber;
                monsterY=-100;
            }
            else if(width<QSrandNumber&&QSrandNumber<=width+height){
                monsterX=width+100;
                monsterY=QSrandNumber-width;
            }
            else if(width+height<QSrandNumber&&QSrandNumber<=width*2+height){

                monsterX=QSrandNumber-width-height;
                monsterY=height+100;
            }
            else if(width*2+height<QSrandNumber&&QSrandNumber<=(width+height)*2){
                monsterX=-100;
                monsterY=QSrandNumber-width*2-height;
            }
            else {
                monsterX=1024+100;
                monsterY=(768+100)/2;
            }
            int typenum=qrand()%100;
            if(typenum>=55){
                monsterPixmap=new MonsterPixmap(":/res/gunner(30.30).png",scene,"Monster",monsterX,monsterY,30,30);
                monsterObject=new Gunner(monsterPixmap,0,monsterX,monsterY,this);
            }
            else if(typenum>=40){
                monsterPixmap=new MonsterPixmap(":/res/machinegunner(50,50).png",scene,"Monster",monsterX,monsterY,50,50);
                monsterObject=new MachineGunner(monsterPixmap,0,monsterX,monsterY,this);
            }
            else if(typenum>=15){
                monsterPixmap=new MonsterPixmap(":/res/scatter(30,30).png",scene,"Monster",monsterX,monsterY,30,30);
                monsterObject=new Scatter(monsterPixmap,0,monsterX,monsterY,this);
            }
            else if(typenum>=10){
                if(maxvalue>=3099999){
                    monsterPixmap=new MonsterPixmap(":/res/weapon50.png",scene,"Monster",monsterX,monsterY,50,50);
                    monsterObject=new Annihilater(monsterPixmap,0,monsterX,monsterY,this);
                }
            }
            else {
                monsterPixmap=new MonsterPixmap(":/res/shotgun(20,20).png",scene,"Monster",monsterX,monsterY,20,20);
                monsterObject=new Shotgun(monsterPixmap,0,monsterX,monsterY,this);
            }
//            //qDebug()<<"MonsterX="<<monsterX<<" MonsterY"<<monsterY;
            if(value>=maxvalue)break;
        }
//    }

}

//*********************************************************************************************


//*********************************************************************************************
void Maps::mousePressEvent(QMouseEvent *event){
    if(selected){

        playerPixmap->setFocus();
        if(rush){
            event->ignore();
        }
        else{
            if(event->button()==Qt::LeftButton){
                playerWeaponPixmap=new WeaponPixmap(":/res/playerweapon(5,5).png",scene,"Weapon",playerPixmap->xP+(playerPixmap->width-10)/2,playerPixmap->yP+(playerPixmap->height-10)/2,5,5);
                playerWeaponObject=new WeaponObject(playerWeaponPixmap,playerPixmap->xP+(playerPixmap->width-10)/2,playerPixmap->yP+(playerPixmap->height-10)/2,event->x(),event->y(),10,this);
//                playerObject->life-=100;
//                //qDebug()<<"Life"<<playerObject->life;
                //调试用左键掉血模式
                event->accept();
            }
            else if(event->button()==Qt::RightButton){
                event->accept();
//                playerObject->life+=100;
                //调试用右键加血模式
                //防御函数
            }
            else{
                event->ignore();
            }

        }

        }
    else {
        event->ignore();
    }


//    //qDebug()<<"Mouse Press "<<scene->focusItem();
}
void Maps::mouseReleaseEvent(QMouseEvent *event){
    if(selected){
       playerPixmap->setFocus();
    }
    else{
        event->ignore();
    }
//    //qDebug()<<"Mouse Release "<<scene->focusItem();
}
void Maps::keyPressEvent(QKeyEvent *event){
    if(selected){
//        //qDebug()<<"key Press "<<scene->focusItem();
//        //qDebug()<<"Key Pressed";
        if(rush){
            switch(event->key()){
                case Qt::Key_Space:{
                if(rushLength-1>0){
                    rushLength-=1;
                    rushbox-=1;
                    playerObject->rush();
                    keyLock+=1;
                    rush=true;

                    keyLockTimer->start(500);
                    connect(keyLockTimer,&QTimer::timeout,this,[=](){
                        rush=false;
                        keyLock-=1;
                        if(!keyLock){

                            keyLockTimer->stop();
                        }
                    });
                }
                break;
            }
                case Qt::Key_0:
                    this->close();
                    break;
                case Qt::Key_6:
                    createMonster();
                    break;
                case Qt::Key_9:
                    emit playerObject->died();
                    break;
                default:
                    event->ignore();
                    break;
            }
        }
        else{
            switch(event->key()){
                case 65:
                    playerObject->a=true;
                    event->accept();
//                    ////qDebug()<<"Key:"<<event->key();
                    break;
                case 87:
                    playerObject->w=true;
                    event->accept();
//                    //qDebug()<<"Key:"<<event->key();
                    break;
                case 68:
                    playerObject->d=true;
                    event->accept();
//                    //qDebug()<<"Key:"<<event->key();
                    break;
                case 83:
                    playerObject->s=true;
                    event->accept();
//                    //qDebug()<<"Key:"<<event->key();
                    break;
                case Qt::Key_Space:
                {
                    if(rushLength-1>0){
                        rushLength-=1;
                        rushbox-=1;
                        playerObject->rush();
                        keyLock+=1;
                        rush=true;

                        keyLockTimer->start(500);
                        connect(keyLockTimer,&QTimer::timeout,this,[=](){
                            rush=false;
                            keyLock-=1;

                            keyLockTimer->stop();
                        });
                        if(playerObject->life<900){
                            playerObject->life+=100;
                        }
                    }
                    break;
                }

//                case Qt::Key_0:
//                    monsterObject->life-=10;//刷怪掉血模式
//                    break;
//                case Qt::Key_6:
//                    createMonster();//手动刷怪
//                    break;
                case Qt::Key_9:
                    emit playerObject->died();
                    break;
                case Qt::Key_0:
                    this->close();
                    break;
                default:
                    event->ignore();
                    break;
            }
        }

    }
    else{
        event->ignore();
    }

}
void Maps::keyReleaseEvent(QKeyEvent *event){
    if(selected){
        //qDebug()<<"Mouse Release "<<scene->focusItem();
        switch(event->key()){
            case 65:
                playerObject->a=false;
                event->accept();
                break;
            case 87:
                playerObject->w=false;
                event->accept();
                break;
            case 68:
                playerObject->d=false;
                event->accept();
                break;
            case 83:
                playerObject->s=false;
                event->accept();
                break;

            default:
                event->ignore();
                break;
            }
    }
    else{
        event->ignore();
    }
}
//*********************************************************************************************
Maps::~Maps()
{
    this->close();
}

void Maps::exit(){
    this->close();
}
//*********************************************************************************************

void Maps::setNoDifficulty(){
    selected=true;
    easy=true;
    difficult=false;
    //qDebug()<<"Easy";
    startCreatePlayer();
    //qDebug()<<"START";
    createMonster();
    monsterTimer->start(5000);
    valueTimer->start(10000);
    //qDebug()<<"Monster Created";
}
void Maps::setNormal(){
    selected=true;
    easy=true;
    difficult=true;
    //qDebug()<<"Normal";
    startCreatePlayer();
    //qDebug()<<"START";
    createMonster();
    monsterTimer->start(5000);
    valueTimer->start(5000);
    ////qDebug()<<"Monster Created";
}
void Maps::setHard(){
    selected=true;
    easy=false;
    difficult=true;
    ////qDebug()<<"Hard";
    startCreatePlayer();
    ////qDebug()<<"START";
    createMonster();
    monsterTimer->start(5000);
    valueTimer->start(1000);
    ////qDebug()<<"Monster Created";
}

//***************************************************************************Set the Difficulty


//*********************************************************************************************

void Maps::startCreatePlayer(){
    //qDebug()<<"ConstructedFunction";
    playerPixmap=new PlayerPixmap(":/res/player(20,20).png",scene);
    playerObject=new PlayerObject(playerPixmap);
    //qDebug()<<"The Player Constructed";

    life=new QGraphicsRectItem(20,20,playerObject->life/5,20);
    //qDebug()<<"life constructed";
    if(playerObject->life>=700){
        QBrush lifeGreen(Qt::green);
       this->life->setBrush(lifeGreen);
    }
    if(playerObject->life>400&&playerObject->life<700){
        QBrush lifeYellow(Qt::yellow);
        this->life->setBrush(lifeYellow);
    }
    if(playerObject->life<=400&&playerObject->life>200){
        QBrush lifeOrange(QColor(225,158,53));
        this->life->setBrush(lifeOrange);
    }
    if(playerObject->life<=200){
        QBrush lifeRed(Qt::red);
        this->life->setBrush(lifeRed);
    }
    scene->addItem(life);
    textLife=new QGraphicsTextItem("Life");
    //qDebug()<<"textlife is constructed";
    textLife->setHtml("<h2><font color=red size=2>Life</font></h2>");
    textLife->moveBy(100,20);
    scene->addItem(textLife);
    rushLevel=new QGraphicsRectItem(260,20,rushLength*100,20);
    //qDebug()<<"rushlevel is constructed";
    rushLevel->setBrush(QBrush(Qt::green));
    scene->addItem(rushLevel);
    textRush=new QGraphicsTextItem("Rush");
    textRush->moveBy(340,20);
    textRush->setHtml("<h2><font color=orange size=2>Rush</font></h2>");
    scene->addItem(textRush);
    checkLifeTimer->start(500);
    connect(checkLifeTimer,SIGNAL(timeout()),this,SLOT(checkLife()));
    connect(playerObject,SIGNAL(died()),this,SLOT(rewrite()));
    playerPixmap->setFocus();
    //qDebug()<<"all constructed";
}
void Maps::checkLife(){

    life->setRect(20,20,playerObject->life/5,20);

    if(playerObject->life>=700){
        QBrush lifeGreen(Qt::green);
       this->life->setBrush(lifeGreen);
    }
    if(playerObject->life>400&&playerObject->life<700){
        QBrush lifeYellow(Qt::yellow);
        this->life->setBrush(lifeYellow);
    }
    if(playerObject->life<=400&&playerObject->life>200){
        QBrush lifeOrange(QColor(225,158,53));
        this->life->setBrush(lifeOrange);
    }
    if(playerObject->life<=200){
        QBrush lifeRed(Qt::red);
        this->life->setBrush(lifeRed);
    }

    rushLevel->setBrush(QBrush(Qt::green));
    rushLevel->setRect(260,20,rushLength*100,20);


    if(rushLength<2){
        rushLength+=0.05;
    }
    if(playerObject->life<1000){
        playerObject->life+=10;
    }
}
//****************************************************************************Create the Player

//****************************************************************************Rewrite To RePlay
void Maps::rewrite(){

    alivePlayer=false;

    selected=false;
    rush=false;
    emit die();
    QTimer *closeit=new QTimer(this);
    closeit->start(2000);
    connect(closeit,SIGNAL(timeout()),this,SLOT(close()));

}
//****************************************************************************Rewrite To RePlay

////******************************************************************************************
//2019.07.03 05:36
//2019 07.04 22:31
//2019.07.04 23:58
//2019.07.05 08:44
//2019.07.05 10:11
//2019.07.05 17:09
//2019.07.07 19:31
