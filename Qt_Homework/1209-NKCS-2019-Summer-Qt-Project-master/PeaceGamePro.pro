#-------------------------------------------------
#
# Project created by QtCreator 2019-07-02T15:38:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PeaceGamePro
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        begindialog.cpp \
        bullet.cpp \
        bulletpixmap.cpp \
        gameover.cpp \
        hall.cpp \
        main.cpp \
        mainwindow.cpp \
        maps.cpp \
        monsterobject.cpp \
        monsterpixmap.cpp \
        monsters.cpp \
        playerobject.cpp \
        playerpixmap.cpp \
        weaponobject.cpp \
        weaponpixmap.cpp

HEADERS += \
        begindialog.h \
        bullet.h \
        bulletpixmap.h \
        gameover.h \
        hall.h \
        head.h \
        mainwindow.h \
        maps.h \
        monsterobject.h \
        monsterpixmap.h \
        monsters.h \
        playerobject.h \
        playerpixmap.h \
        weaponobject.h \
        weaponpixmap.h

FORMS +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
