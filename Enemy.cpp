#include <Enemy.h>
#include <QTimer>
#include <QDebug>
#include <QGraphicsScene>
#include <QObject>
//#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <stdlib.h> //rand() numero muy grande
#include <Game.h>
#include <QMessageBox>


extern Game *game;

Enemy::Enemy(){
    //Configurar posición aleatoria
    int random_number =rand() % 700; //(para que no se salga de escenario)
    setPos(random_number,0); //Aparece en cualquier lugar pero desde 0 (cielo)
    setPixmap(QPixmap(":/images/enemigo2.png"));
    //setRect(0,0,100,100);
    //Funcion conectar
    QTimer * timer = new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(mover()));
    timer -> start(50);  //50ms
    /*if (game->health->getHealth() <= 0) {
        QMessageBox::information(nullptr, "Game Over", "¡Perdiste! Salud en 0.");
        // opcional: cerrar juego
        qApp->quit();
    }*/

}

void Enemy::mover(){
    //mover la bala
    setPos(x(),y()+5);
    if (pos().y()>600){ //Si se sale de la pantalla se elimine
        // Decrementar la vida
        game -> health ->decrease();
        scene() -> removeItem(this);
        delete this;
        //qDebug() << "Borrada";
    }
}

