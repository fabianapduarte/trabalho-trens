#include "trem.h"
#include <QtCore>

static QMutex mutex[7];
static bool areasOcupadas[7] = {false};
const int deslocamento = 10;

//Construtor
Trem::Trem(int ID, int x, int y) {
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = 100;
}

void Trem::setVelocidade(int value){
    velocidade = value;
    if (value == 0){
        velocidade = 1;
    }
}

void liberarRegiaoCritica(int regiao) {
    if (areasOcupadas[regiao]) {
        areasOcupadas[regiao] = false;
        mutex[regiao].unlock();
    }
}

bool verificarRegiaoCritica(int regiao) {
    if (mutex[regiao].tryLock()) {
        areasOcupadas[regiao] = true;
        return true;
    }
    return false;
}

bool verificarDuasRegioesCriticas(int regiao1, int regiao2) {
    if (mutex[regiao1].tryLock()) {
        if (mutex[regiao2].tryLock()) {
            areasOcupadas[regiao1] = true;
            areasOcupadas[regiao2] = true;
            return true;
        } else {
            mutex[regiao1].unlock();
        }
    }
    return false;
}

//Função a ser executada após executar trem->START
void Trem::run() {
    while(true) {
        if (velocidade != 200) {
            switch(ID) {
            case 1: //Trem 1
                if (x == 310 && y == 150) {
                    liberarRegiaoCritica(0);
                }
                else if (x == 180 && y == 150) {
                    liberarRegiaoCritica(2);
                }

                if (y == 30 && x < 330) { //direita
                    if (x == 310) {
                        bool livre = verificarRegiaoCritica(0);
                        if (livre) x += deslocamento;
                    } else {
                        x += deslocamento;
                    }
                }
                else if (x == 330 && y < 150) { //baixo
                    if (y == 130) {
                        bool livre = verificarRegiaoCritica(2);
                        if (livre) y += deslocamento;
                    } else {
                        y += deslocamento;
                    }
                }
                else if (x > 60 && y == 150) { //esquerda
                    x -= deslocamento;
                }
                else { // sobe
                    y -= deslocamento;
                }

                emit updateGUI(ID, x, y);    //Emite um sinal
                break;

            case 2: //Trem 2
                if (x == 580 && y == 150) {
                    liberarRegiaoCritica(1);
                }
                else if (x == 440 && y == 150) {
                    liberarRegiaoCritica(4);
                }
                else if (x == 330 && y == 130) {
                    liberarRegiaoCritica(3);
                }
                else if (x == 350 && y == 30) {
                    liberarRegiaoCritica(0);
                }

                if (y == 30 && x < 600) { //direita
                    if (x == 580) {
                        bool livre = verificarDuasRegioesCriticas(1,4);
                        if (livre) x += deslocamento;
                    } else {
                        x += deslocamento;
                    }
                }
                else if (x == 600 && y < 150) { //baixo
                    y += deslocamento;
                }
                else if (x > 330 && y == 150) { //esquerda
                    if (x == 490) {
                        bool livre = verificarDuasRegioesCriticas(3,0);
                        if (livre) x -= deslocamento;
                    } else {
                        x -= deslocamento;
                    }
                }
                else { //cima
                    y -= deslocamento;
                }

                emit updateGUI(ID, x, y);    //Emite um sinal
                break;

            case 3: //Trem 3
                if (x == 620 && y == 30) {
                    liberarRegiaoCritica(1);
                }
                else if (x == 600 && y == 130) {
                    liberarRegiaoCritica(5);
                }

                if (y == 30 && x < 870) { //direita
                    x += deslocamento;
                }
                else if (x == 870 && y < 150) { //desce
                    y += deslocamento;
                }
                else if (x > 600 && y == 150) { //esquerda
                    if (x == 760) {
                        bool livre = verificarRegiaoCritica(5);
                        if (livre) x -= deslocamento;
                    }
                    else if (x == 620) {
                        bool livre = verificarRegiaoCritica(1);
                        if (livre) x -= deslocamento;
                    } else {
                        x -= deslocamento;
                    }
                }
                else {
                    y -= deslocamento;
                }

                emit updateGUI(ID, x,y);    //Emite um sinal
                break;
            case 4: //Trem 4
                if (x == 354 && y == 150) {
                    liberarRegiaoCritica(2);
                }
                else if (x == 464 && y == 170) {
                    liberarRegiaoCritica(3);
                }
                else if (x == 444 && y == 270) {
                    liberarRegiaoCritica(6);
                }

                if (y == 150 && x < 464) { //direita
                    if (x == 444) {
                        bool livre = verificarRegiaoCritica(6);
                        if (livre) x += deslocamento;
                    } else {
                       x += deslocamento;
                    }
                }
                else if (x == 464 && y < 270) { //baixo
                    y += deslocamento;
                }
                else if (x > 194 && y == 270) { //esquerda
                    x -= deslocamento;
                }
                else {  //cima
                    if (y == 170) {
                        bool livre = verificarDuasRegioesCriticas(2,3);
                        if (livre) y -= deslocamento;
                    } else {
                        y -= deslocamento;
                    }
                }

                emit updateGUI(ID, x,y);    //Emite um sinal
                break;

            case 5: //Trem 5
                if (x == 624 && y == 150) {
                    liberarRegiaoCritica(4);
                }
                else if (x == 734 && y == 170) {
                    liberarRegiaoCritica(5);
                }
                else if (x == 484 && y == 150) {
                    liberarRegiaoCritica(6);
                }

                if (y == 150 && x < 734) { //direita
                    if (x == 574) {
                        bool livre = verificarRegiaoCritica(5);
                        if (livre) x += deslocamento;
                    } else {
                        x += deslocamento;
                    }
                }
                else if (x == 734 && y < 270) { //baixo
                    y += deslocamento;
                }
                else if (x > 464 && y == 270) { //esquerda
                    if (x == 484) {
                        bool livre = verificarDuasRegioesCriticas(6,4);
                        if (livre) x -= deslocamento;
                    } else {
                        x -= deslocamento;
                    }
                }
                else { //cima
                    y -= deslocamento;
                }

                emit updateGUI(ID, x, y);    //Emite um sinal
                break;
            default:
                break;
            }
        }
        msleep(velocidade);
    }
}
