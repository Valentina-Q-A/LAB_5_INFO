#include "Bomb.h"
#include "Game.h"
#include "BloqueDestructible.h"
#include "Enemy.h"
#include "Player.h"
#include <QGraphicsScene>
#include <QPixmap>
#include <QDebug>
#include <QVector>

extern Game *game;

Bomb::Bomb(int cx, int cy, QGraphicsScene *scene, QObject *parent)
    : QObject(parent), QGraphicsPixmapItem(), m_scene(scene)
{
    QPixmap sheet(":/images/spites.png");
    int paso = 48;
    struct ParteDef { int dx, dy, sx, sy; };
    QVector<ParteDef> defs = {
                              { 0,   0, 112,  96},
                              { 0, -paso,112,  80},
                              { 0,  paso,112, 112},
                              {-paso, 0,  96,  96},
                              { paso, 0, 128,  96},
                              };

    for (const ParteDef &d : defs) {
        QPixmap sprite = sheet.copy(d.sx, d.sy, 16, 16).scaled(paso, paso);
        auto *p = new QGraphicsPixmapItem(sprite);
        p->setPos(cx + d.dx, cy + d.dy);
        p->setZValue(1);
        m_scene->addItem(p);
        partes.append(p);
    }

    QTimer *tExplode = new QTimer(this);
    tExplode->setSingleShot(true);
    connect(tExplode, &QTimer::timeout, this, &Bomb::explode);
    tExplode->start(3000);

    QTimer *tCleanup = new QTimer(this);
    tCleanup->setSingleShot(true);
    connect(tCleanup, &QTimer::timeout, this, &Bomb::cleanup);
    tCleanup->start(3500);
}

void Bomb::explode()
{
    for (auto *parte : partes) {
        auto items = parte->collidingItems();
        for (auto *item : items) {
            if (auto *e = dynamic_cast<Enemy*>(item)) {
                game->score->increase();
                m_scene->removeItem(e);
                delete e;
            }
            else if (auto *b = dynamic_cast<BloqueDestructible*>(item)) {
                qDebug() << "Bloque destruido en:" << b->pos();
                m_scene->removeItem(b);
                delete b;
            }
            else if (auto *pl = dynamic_cast<Player*>(item)) {
                game->health->decrease();
            }
        }
    }
}

void Bomb::cleanup()
{
    for (auto *parte : partes) {
        m_scene->removeItem(parte);
        delete parte;
    }
    delete this;
}
