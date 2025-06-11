#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include <QList>

           class Bullet : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    Bullet(int posx, int posy);  // ← ya no sin argumentos
private slots:
    void activar();
    void eliminar();
private:
    QList<QGraphicsPixmapItem*> partesExplosion;
};

#endif // BULLET_H
