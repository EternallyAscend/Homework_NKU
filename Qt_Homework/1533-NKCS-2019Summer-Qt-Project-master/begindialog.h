#ifndef BEGINDIALOG_H
#define BEGINDIALOG_H
#include "head.h"
#include <QWidget>

class BeginDialog : public QWidget
{
    Q_OBJECT
public:
    explicit BeginDialog(QWidget *parent = nullptr);
    ~BeginDialog();


    int difficult;//1,2,3.
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *cmenu;
    QAction *start;
    QAction *end;
    QAction *copy;
    QAction *easy;
    QAction *middle;
    QAction *hard;
    QLabel *title;
    QLabel *choose;
    QToolButton *choice;
    QMenu *select;
    QPushButton *submit;
    QPushButton *cancel;
    QStatusBar *status;
    QLabel *statuslabel;

    void paintEvent(QPaintEvent *event);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
signals:
    void exit();
    void ok();
    void veryEasy();
    void normal();
    void veryHard();
private slots:
    void closepage();
    void selectDifficult();
};

#endif // BEGINDIALOG_H
