#include "Bullet.h"
#include "Game.h"
#include "Enemy.h"
#include "BloqueDestructible.h"
#include "Player.h"
#include <QGraphicsScene>
#include <QPixmap>

extern Game* game;

Bullet::Bullet(int posx, int posy) {
    QPixmap spriteSheet(":/images/spites.png");
    int paso = 48;

    struct Parte {
        QString nombre;
        int offsetX, offsetY;
        int sx, sy;  // sprite X/Y dentro de spriteSheet
    };

    Parte partes[9] = {
                       {"center",      0,    0, 112,  96},
                       {"up-mid",      0, -paso, 112,  80},
                       {"up-end",      0, -2*paso, 112,  64},
                       {"down-mid",    0,  paso, 112,  112},
                       {"down-end",    0,  2*paso, 112,  128},
                       {"left-mid", -paso,    0,  96,  96},
                       {"left-end", -2*paso,  0,  80,  96},
                       {"right-mid", paso,    0, 128,  96},
                       {"right-end", 2*paso,  0, 144,  96},
                       };

    for (int i = 0; i < 9; i++) {
        QPixmap sprite = spriteSheet.copy(partes[i].sx, partes[i].sy, 16, 16);
        QGraphicsPixmapItem* parte = new QGraphicsPixmapItem();
        parte->setPixmap(sprite);
        parte->setOffset(0, 0);
        parte->setScale(3.0);  // 16 * 3 = 48

        parte->setZValue(1);
        parte->setPos(posx + partes[i].offsetX, posy + partes[i].offsetY);
        game->scene->addItem(parte);
        partesExplosion.append(parte);

        qDebug() << "[DEBUG] Parte añadida en:" << parte->pos()
                 << " Bounding rect:" << parte->sceneBoundingRect();
    }


    QTimer::singleShot(3000, this, SLOT(activar()));
    QTimer::singleShot(3000, this, SLOT(eliminar()));
}

void Bullet::activar() {
    qDebug() << "\n=== Verificando escena ===";
    for (QGraphicsPixmapItem* parte : partesExplosion) {
        if (parte->scene() != game->scene) {
            qDebug() << "[ERROR] Parte no pertenece a la escena!";
        }
    }

    for (QGraphicsItem* item : game->scene->items()) {
        if (BloqueDestructible* bloque = dynamic_cast<BloqueDestructible*>(item)) {
            if (bloque->scene() != game->scene) {
                qDebug() << "[ERROR] Bloque destructible no pertenece a la escena!";
            }
        }
    }

    for (QGraphicsPixmapItem* parte : partesExplosion) {
        QRectF rectExplosion = parte->sceneBoundingRect();

        for (QGraphicsItem* item : game->scene->items()) {
            if (Enemy* enemigo = dynamic_cast<Enemy*>(item)) {
                if (rectExplosion.intersects(enemigo->sceneBoundingRect())) {
                    game->score->increase();
                    game->scene->removeItem(enemigo);
                    delete enemigo;
                }
            }
            else if (BloqueDestructible* bloque = dynamic_cast<BloqueDestructible*>(item)) {
                if (rectExplosion.intersects(bloque->sceneBoundingRect())) {
                    qDebug() << "Bloque destruido en:" << bloque->pos();
                    game->scene->removeItem(bloque);
                    delete bloque;
                }
            }
            else if (Player* jugador = dynamic_cast<Player*>(item)) {
                if (rectExplosion.intersects(jugador->sceneBoundingRect())) {
                    game->health->decrease();
                }
            }
        }
    }
}


void Bullet::eliminar() {
    for (QGraphicsPixmapItem* parte : partesExplosion) {
        game->scene->removeItem(parte);
        delete parte;
    }
    delete this;
}



