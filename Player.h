#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMediaPlayer>
#include <QAudioOutput>

           class Player:public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Player(QGraphicsItem * parent=0);
    void keyPressEvent(QKeyEvent * event); //Para poder desplazarse izq y der
public slots:
    void spawn();
private:
    QMediaPlayer * bulletsound;
    QAudioOutput * bulletoutput;
    QPixmap spriteSheet;
    QPixmap frameDown;
    QPixmap frameUp;
    QPixmap frameLeft;
    QPixmap frameRight;

};


#endif // PLAYER_H
