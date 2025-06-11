
#include <Player.h>
#include <QDebug>
#include <QKeyEvent>
#include <Bullet.h>
#include <Enemy.h>
#include <Bloque.h>
#include <BloqueDestructible.h>
#include <QDebug>
#include <QGraphicsScene>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QUrl>

Player::Player(QGraphicsItem *parent): QGraphicsPixmapItem(parent){
    bulletsound = new QMediaPlayer();
    bulletoutput = new QAudioOutput();  // Crear la salida de audio
    bulletsound->setAudioOutput(bulletoutput);
    bulletsound->setSource(QUrl("qrc:/sounds/080884_bullet-hit-39872.mp3"));
    // Cargar la hoja de sprites
    spriteSheet = QPixmap(":/images/spites.png");

    // Recortar un sprite para cada dirección (ajusta según tu sprite sheet real)
    frameDown  = spriteSheet.copy(  48,  0, 16, 16);  // mirando abajo
    frameLeft  = spriteSheet.copy( 0,  0, 16, 16);  // mirando izquierda
    frameRight = spriteSheet.copy( 0,  16, 16, 16);  // mirando derecha
    frameUp    = spriteSheet.copy( 48,  16, 16, 16);  // mirando arriba

    // Mostrar la imagen inicial (mirando abajo)
    setPixmap(frameDown.scaled(48, 48));


}

void Player::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left) {
        if (pos().x() > 48){
            setPos(x() - 8, y());
            setPixmap(frameLeft.scaled(48, 48));
        }
        QList<QGraphicsItem *> items = collidingItems();
        bool chocoConBloque = false;

        for (int i = 0; i < items.size(); i++) {
            if (typeid(*items[i]) == typeid(Bloque) || typeid(*items[i]) == typeid(BloqueDestructible)) {
                chocoConBloque = true;
                break;
            }
        }

        if (chocoConBloque) {
            setPos(x() + 8, y());  // Deshacer movimiento
        } else {
            setPixmap(frameLeft.scaled(48, 48));
        }
    }


    else if (event->key() == Qt::Key_Right) {
        if (pos().x() < 720){
            setPos(x() + 8, y());
            setPixmap(frameLeft.scaled(48, 48));
        }
        QList<QGraphicsItem *> items = collidingItems();
        bool chocoConBloque = false;

        for (int i = 0; i < items.size(); i++) {
            if (typeid(*items[i]) == typeid(Bloque) || typeid(*items[i]) == typeid(BloqueDestructible)) {
                chocoConBloque = true;
                break;
            }
        }
        if (chocoConBloque) {
            setPos(x() - 8, y());  // Deshacer movimiento
        } else {
            setPixmap(frameRight.scaled(48, 48));  // Solo si sí se movió
        }
    }

    else if (event->key() == Qt::Key_Up){
        if (pos().y() > 48){
            setPos(x(), y() - 8);
            setPixmap(frameUp.scaled(48, 48));
        }
        QList<QGraphicsItem *> items = collidingItems();
        bool chocoConBloque = false;

        for (int i = 0; i < items.size(); i++) {
            if (typeid(*items[i]) == typeid(Bloque) || typeid(*items[i]) == typeid(BloqueDestructible)) {
                chocoConBloque = true;
                break;
            }
        }

        if (chocoConBloque) {
            setPos(x(), y() + 8);  // Deshacer
        } else {
            setPixmap(frameUp.scaled(48, 48));
        }
    }
    else if (event->key() == Qt::Key_Down){
        if (pos().y() < 576){
            setPos(x(), y() + 8);
            setPixmap(frameDown.scaled(48, 48));
        }
        QList<QGraphicsItem *> items = collidingItems();
        bool chocoConBloque = false;

        for (int i = 0; i < items.size(); i++) {
            if (typeid(*items[i]) == typeid(Bloque) || typeid(*items[i]) == typeid(BloqueDestructible)) {
                chocoConBloque = true;
                break;
            }
        }
        if (chocoConBloque) {
            setPos(x(), y() - 8);  // Deshacer
        } else {
            setPixmap(frameDown.scaled(48, 48));
        }
    }
    else if (event->key() == Qt::Key_Space) {
        Bullet* explosion = new Bullet(x(), y());
        scene()->addItem(explosion);

        if (bulletsound->playbackState() == QMediaPlayer::PlayingState)
            bulletsound->setPosition(0);
        else if (bulletsound->playbackState() == QMediaPlayer::StoppedState)
            bulletsound->play();
    }

}


void Player::spawn()
{
    //Crear un enemigo
    Enemy *enemy =new Enemy();
    scene() -> addItem(enemy);
}
