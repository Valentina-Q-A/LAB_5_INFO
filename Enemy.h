#ifndef ENEMY_H
#define ENEMY_H

//#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QObject>
#include <QKeyEvent>
#include <Player.h>


          class Enemy:public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy();
public slots:
    void mover();
};


#endif // ENEMY_H

