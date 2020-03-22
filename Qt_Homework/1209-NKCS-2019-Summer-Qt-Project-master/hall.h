#ifndef HALL_H
#define HALL_H

#include "head.h"
#include <QObject>

class Hall : public QGraphicsPixmapItem
{
//    Q_OBJECT
public:
    explicit Hall(QString url,int x,int y,int width,int height,QGraphicsScene *scene,QString name="wall");
    ~Hall();
    int hallWidth;
    int hallHeight;
    QGraphicsScene *hallscene;
    QString Name;
//    QGraphicsPixmapItem *pixmap;
signals:

public slots:
};

#endif // HALL_H
//2019.07.05 08:14
