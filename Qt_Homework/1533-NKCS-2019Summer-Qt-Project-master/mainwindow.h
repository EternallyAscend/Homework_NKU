#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "head.h"
#include "maps.h"
#include "gameover.h"
class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    Maps *w;
    Maps *m;
    QWidget *that;
    Gameover *gameover;
    QTimer *closeTimer();
signals:

public slots:
    void rewritew();
    void rewritem();
};

#endif // MAINWINDOW_H
