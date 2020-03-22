#include "begindialog.h"


BeginDialog::BeginDialog(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::CustomizeWindowHint|Qt::FramelessWindowHint);

    start=new QAction(this);
    start->setText(QString::fromUtf8("Start(&S)"));
    start->setStatusTip("Start to play the game!");
    start->setShortcut(QKeySequence("Ctrl+Shift+S"));
    connect(start,&QAction::triggered,this,[=](){
        emit ok();
        this->close();
    });

    end=new QAction(this);
    end->setText((QString::fromUtf8("End")));
    end->setStatusTip("Exit the game!");
    end->setShortcut(QKeySequence("Ctrl+Shift+E"));

    connect(end,SIGNAL(triggered()),this,SLOT(closepage()));

    copy=new QAction(this);
    copy->setText(QString::fromUtf8("Information(&I)"));
    copy->setStatusTip("Information of the developer.");
    copy->setShortcut(QKeySequence("Z"));
    connect(copy,&QAction::triggered,this,[=](){
        QDialog *copyright=new QDialog(this);
        copyright->setWindowTitle("CopyRight");
        copyright->resize(400,160);
        copyright->setMinimumSize(400,160);
        copyright->setMaximumSize(400,160);
        QFont *fontindialog=new QFont("Microsoft YaHei",16);
        QLabel *textindialog=new QLabel(copyright);
        textindialog->setFont(*fontindialog);
        textindialog->setText("PEACE GAME PRO 7");
        textindialog->move(100,50);
        copyright->show();
        copyright->setAttribute(Qt::WA_DeleteOnClose);
        textindialog->setAttribute(Qt::WA_DeleteOnClose);
    });

    easy=new QAction(this);
    easy->setText(QString::fromUtf8("Easy(&E)"));
    connect(easy,&QAction::triggered,this,[=](){
        emit veryEasy();
        this->close();
    });

    middle=new QAction(this);
    middle->setText(QString::fromUtf8("Normal(&N)"));
    connect(middle,&QAction::triggered,this,[=](){
       emit normal();
       this->close();
    });

    hard=new QAction(this);
    hard->setText(QString::fromUtf8("Hard(&H)"));
    connect(hard,&QAction::triggered,this,[=](){
        emit veryHard();
        this->close();
    });

    menu=new QMenu(this);
    menu->setTitle(QString::fromUtf8("Operator(&O)"));
    menu->addAction(start);
    menu->addAction(end);
    menu->addAction(copy);

    cmenu=new QMenu(this);
    cmenu->setTitle(QString::fromUtf8("Select(&S)"));
    cmenu->addAction(easy);
    cmenu->addAction(middle);
    cmenu->addAction(hard);

    menubar=new QMenuBar(this);
    menubar->addMenu(menu);
    menubar->addMenu(cmenu);

    title=new QLabel(this);
    title->setText(QString::fromUtf8("Peace Game Pro"));
    title->move(140,80);

    choose=new QLabel(this);
    choose->setText(QString::fromUtf8("Select the level of game."));
    choose->move(240,300);

    select=new QMenu(this);
    select->setTitle(QString::fromUtf8("Select"));
    select->addAction(easy);
    select->addAction(middle);
    select->addAction(hard);

    choice=new QToolButton(this);
    choice->setText(QString::fromUtf8("-   Select   -"));
    choice->move(360,400);
    choice->setMenu(select);
    choice->setPopupMode(QToolButton::MenuButtonPopup);


    submit=new QPushButton(this);
    submit->setText(QString::fromUtf8("Rule"));
    submit->move(300,550);
    connect(submit,&QPushButton::clicked,this,[=](){

        QDialog *rule=new QDialog(this);
        rule->setMaximumSize(1024,768);
        rule->setMinimumSize(1024,768);
        rule->move(440,100);
        rule->setWindowTitle("Rules of the Peace Game Pro 7");

            rule->setAutoFillBackground(true);
                 QPalette palette;
                 QPixmap pixmap(":/res/Rule.png");
                 palette.setBrush(QPalette::Window, QBrush(pixmap));
                 rule->setPalette(palette);
        // /\百
        rule->show();
        rule->setAttribute(Qt::WA_DeleteOnClose);
    });

    cancel=new QPushButton(this);
    cancel->setText(QString::fromUtf8("Cancel"));
    cancel->move(600,550);

    connect(cancel,SIGNAL(clicked()),this,SLOT(closepage()));

    status=new QStatusBar(this);

    statuslabel=new QLabel("Information : Peace Game Pro 1.0 (Nankai University College of Software.)",this);
    status->addWidget(statuslabel);
    status->setMinimumWidth(1024);
    status->setMaximumWidth(1024);
    status->move(0,740);

    QFont titles("Microsoft YaHei");
    titles.setPointSize(48);

    QFont standard("Microsoft YaHei",24);

    QPalette white;
    white.setColor(QPalette::WindowText,Qt::white);

    title->setFont(titles);
    select->setFont(standard);
    choice->setFont(standard);
    choose->setFont(standard);
    submit->setFont(standard);
    cancel->setFont(standard);
    title->setPalette(white);
    choose->setPalette(white);
    status->setPalette(white);

}

void BeginDialog::closepage(){
    emit exit();
    this->close();
}
void BeginDialog::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap(":/res/bgc.jpg"),QRect());
}
void BeginDialog::selectDifficult(){
    emit ok();
    this->close();
}
//**********************************************************************************************
void BeginDialog::mousePressEvent(QMouseEvent *event){
    event->ignore();
}
void BeginDialog::mouseReleaseEvent(QMouseEvent *event){
    event->ignore();
}
//*************************************************************Deal with the press/release event
BeginDialog::~BeginDialog(){
    delete start;
    delete end;
    delete copy;
    delete easy;
    delete middle;
    delete hard;
    delete menu;
    delete cmenu;
    delete menubar;
    delete title;
    delete choose;
    delete choice;
    delete submit;
    delete cancel;
    delete status;
//    delete statuslabel;
}
//2019.06.30 20:41
