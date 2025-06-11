#ifndef BOMB_H
#define BOMB_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>

class Bomb : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    explicit Bomb(int centerX, int centerY, QGraphicsScene *scene, QObject *parent = nullptr);
private slots:
    void explode();
    void cleanup();
private:
    QList<QGraphicsPixmapItem*> partes;
    QGraphicsScene *m_scene;
};

#endif // BOMB_H
