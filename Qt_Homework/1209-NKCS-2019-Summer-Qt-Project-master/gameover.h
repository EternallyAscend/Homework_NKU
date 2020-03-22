#ifndef GAMEOVER_H
#define GAMEOVER_H
#include "head.h"
#include <QWidget>

class Gameover : public QDialog
{
    Q_OBJECT
public:
    explicit Gameover(QWidget *parent = nullptr);

    QTimer *closeTimer;
    QPalette *p;
signals:

public slots:
};

#endif // GAMEOVER_H
