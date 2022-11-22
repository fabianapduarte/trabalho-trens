#include "trem.h"
#include <QtCore>
#include <QtDebug>

QMutex mutex[7];
int areasCriticas[7] = {0,0,0,0,0,0,0};

//Construtor
Trem::Trem(int ID, int x, int y){
    this->ID = ID;
    this->x = x;
    this->y = y;
    this->velocidade = 100;
}

void Trem::setVelocidade(int value){
    if (value == 200) {
        terminate();
    } else {
        velocidade = value;
        if (value == 0){
            start();
            velocidade = 1;
        }
    }
}

//Função a ser executada após executar trem->START
void Trem::run() {
    while(true) {
        switch(ID) {
        case 1: //Trem 1
            if (y == 30 && x < 330) {
                //direita
                //verifica se há trem na região crítica 0
                if (x == 310) {
                    if (areasCriticas[0] == 0) {
                        mutex[0].lock();
                        areasCriticas[0] = 1;
                        x += 10;
                    }
                } else {
                    x += 10;
                }
            }
            else if (x == 330 && y < 150) {
                //desce
                //entra na reg. crit. 0
                if (y == 130) {
                    if (areasCriticas[2] == 0) {
                        mutex[2].lock();
                        areasCriticas[2] = 1;
                        y += 10;
                    }
                } else {
                    y += 10;
                }
            }
            else if (x > 60 && y == 150) {
                //esquerda
                //entra e sai da região crítica 2
                x -= 10;
            }
            else {
                // sobe
                y -= 10;
            }

            if (x == 310 && y == 150 && areasCriticas[0] == 1) {
                areasCriticas[0] = 0;
                mutex[0].unlock();
            }
            if (x == 180 && y == 150 && areasCriticas[2] == 1) {
                areasCriticas[2] = 0;
                mutex[2].unlock();
            }

            emit updateGUI(ID, x, y);    //Emite um sinal
            break;

        case 2: //Trem 2
            if (y == 30 && x < 600) {
                //direita
                //verifica se há trem na região 1
                if (x == 580) {
                    if (areasCriticas[1] == 0) {
                        mutex[1].lock();
                        areasCriticas[1] = 1;
                        x += 10;
                    }
                } else {
                    x += 10;
                }
            }
            else if (x == 600 && y < 150) {
                //desce
                //entra na região crítica 1
                //verifica se região 4 está livre
                if (y == 130) {
                    if (areasCriticas[4] == 0) {
                        mutex[4].lock();
                        areasCriticas[4] = 1;
                        y += 10;
                    }
                } else {
                    y += 10;
                }
            }
            else if (x > 330 && y == 150) {
                //esquerda
                //entra e sai da reg. crit. 3 e 4
                if (x == 490) {
                    if (areasCriticas[3] == 0) {
                        mutex[3].lock();
                        areasCriticas[3] = 1;
                        x -= 10;
                    }
                } else if (x == 350) {
                    if (areasCriticas[0] == 0) {
                        mutex[0].lock();
                        areasCriticas[0] = 1;
                        x -= 10;
                    }
                } else {
                    x -= 10;
                }
            }
            else {
                //sobe
                //entra na região 0
                y -= 10;
            }

            if (x == 580 && y == 150 && areasCriticas[1] == 1) {
                areasCriticas[1] = 0;
                mutex[1].unlock();
            }
            if (x == 440 && y == 150 && areasCriticas[4] == 1) {
                areasCriticas[4] = 0;
                mutex[4].unlock();
            }
            if (x == 330 && y == 130 && areasCriticas[3] == 1) {
                areasCriticas[3] = 0;
                mutex[3].unlock();
            }
            if (x == 350 && y == 30 && areasCriticas[0] == 1) {
                areasCriticas[0] = 0;
                mutex[0].unlock();
            }

            emit updateGUI(ID, x, y);    //Emite um sinal
            break;

        case 3: //Trem 3
            if (y == 30 && x < 870) {
                //direita
                x += 10;
            } else if (x == 870 && y < 150) {
                //desce
                y += 10;
            } else if (x > 600 && y == 150) {
                //esquerda
                //verifica região crítica 5
                if (x == 760) {
                    if (areasCriticas[5] == 0) {
                        mutex[5].lock();
                        areasCriticas[5] = 1;
                        x -= 10;
                    }
                } else if (x == 620) {
                    //verifica região crítica 1
                    if (areasCriticas[1] == 0) {
                        mutex[1].lock();
                        areasCriticas[1] = 1;
                        x -= 10;
                    }
                } else {
                    x -= 10;
                }
            }
            else {
                //sobe
                //região crítica 1
                y -= 10;
            }

            if (x == 620 && y == 30 && areasCriticas[1] == 1) {
                areasCriticas[1] = 0;
                mutex[1].unlock();
            }
            if (x == 600 && y == 130 && areasCriticas[5] == 1) {
                areasCriticas[5] = 0;
                mutex[5].unlock();
            }

            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 4: //Trem 4
            if (y == 150 && x < 464) {
                //direita
                //verifica a região crítica 3
                if (x == 314) {
                    if (areasCriticas[3] == 0) {
                        mutex[3].lock();
                        areasCriticas[3] = 1;
                        x += 10;
                    }
                } else if (x == 444) {
                    //verifica a região crítica 6
                    if (areasCriticas[6] == 0) {
                        mutex[6].lock();
                        areasCriticas[6] = 1;
                        x += 10;
                    }
                } else {
                   x += 10;
                }
            }
            else if (x == 464 && y < 270) {
                //desce
                y += 10;
            }
            else if (x > 194 && y == 270) {
                //esquerda
                x -= 10;
            }
            else {
                //sobe
                //verifica a região crítica 2
                if (y == 170) {
                    if (areasCriticas[2] == 0) {
                        mutex[2].lock();
                        areasCriticas[2] = 1;
                        y -= 10;
                    }
                } else {
                    y -= 10;
                }
            }

            if (x == 354 && y == 150 && areasCriticas[2] == 1) {
                areasCriticas[2] = 0;
                mutex[2].unlock();
            }
            if (x == 464 && y == 170 && areasCriticas[3] == 1) {
                areasCriticas[3] = 0;
                mutex[3].unlock();
            }
            if (x == 444 && y == 270 && areasCriticas[6] == 1) {
                areasCriticas[6] = 0;
                mutex[6].unlock();
            }

            emit updateGUI(ID, x,y);    //Emite um sinal
            break;
        case 5: //Trem 5
            if (y == 150 && x < 734) {
                //direita
                //verifica a região crítica 5
                if (x == 584) {
                    if (areasCriticas[5] == 0) {
                        mutex[5].lock();
                        areasCriticas[5] = 1;
                        x += 10;
                    }
                } else {
                    x += 10;
                }
            }
            else if (x == 734 && y < 270) {
                //desce
                y += 10;
            }
            else if (x > 464 && y == 270) {
                //esquerda
                //verifica a região crítica 6
                if (x == 484) {
                    if (areasCriticas[6] == 0) {
                        mutex[6].lock();
                        areasCriticas[6] = 1;
                        x -= 10;
                    }
                } else {
                    x -= 10;
                }
            }
            else {
                //sobe
                //verifica a região crítica 4
                if (y == 170) {
                    if (areasCriticas[4] == 0) {
                        mutex[4].lock();
                        areasCriticas[4] = 1;
                        y -= 10;
                    }
                } else {
                    y -= 10;
                }
            }

            if (x == 624 && y == 150 && areasCriticas[4] == 1) {
                areasCriticas[4] = 0;
                mutex[4].unlock();
            }
            if (x == 734 && y == 170 && areasCriticas[5] == 1) {
                areasCriticas[5] = 0;
                mutex[5].unlock();
            }
            if (x == 484 && y == 150 && areasCriticas[6] == 1) {
                areasCriticas[6] = 0;
                mutex[6].unlock();
            }

            emit updateGUI(ID, x, y);    //Emite um sinal
            break;
        default:
            break;
        }
        msleep(velocidade);
    }
}




