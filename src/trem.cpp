#include "trem.h"
#include <QtCore>
#include <QtDebug>

static QMutex mutex[7];
static int areasOcupadas[7] = {0};

//Construtor
Trem::Trem(int ID, int x, int y){
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

//Função a ser executada após executar trem->START
void Trem::run() {
    while(true) {
        if (velocidade != 200) {
            switch(ID) {
            case 1: //Trem 1
                if (x == 310 && y == 150 && areasOcupadas[0] == 1) {
                    areasOcupadas[0] = 0;
                    mutex[0].unlock();
                }
                else if (x == 180 && y == 150 && areasOcupadas[2] == 1) {
                    areasOcupadas[2] = 0;
                    mutex[2].unlock();
                }

                if (y == 30 && x < 330) {
                    //direita
                    //verifica se há trem na região crítica 0
                    if (x == 310) {
                        if (mutex[0].tryLock()) {
                            areasOcupadas[0] = 1;
                            x += 10;
                        }
                    } else {
                        x += 10;
                    }
                }
                else if (x == 330 && y < 150) {
                    //desce
                    //entra na reg. crit. 0
                    //verifica região 2
                    if (y == 130) {
                        if (mutex[2].tryLock()) {
                            areasOcupadas[2] = 1;
                            y += 10;
                        }
                    } else {
                        y += 10;
                    }
                }
                else if (x > 60 && y == 150) {
                    //esquerda
                    x -= 10;
                }
                else {
                    // sobe
                    y -= 10;
                }

                emit updateGUI(ID, x, y);    //Emite um sinal
                break;

            case 2: //Trem 2
                if (x == 580 && y == 150 && areasOcupadas[1] == 1) {
                    mutex[1].unlock();
                    areasOcupadas[1] = 0;
                }
                else if (x == 440 && y == 150 && areasOcupadas[4] == 1) {
                    mutex[4].unlock();
                    areasOcupadas[4] = 0;
                }
                else if (x == 330 && y == 130 && areasOcupadas[3] == 1) {
                    mutex[3].unlock();
                    areasOcupadas[3] = 0;
                }
                else if (x == 350 && y == 30 && areasOcupadas[0] == 1) {
                    mutex[0].unlock();
                    areasOcupadas[0] = 0;
                }

                if (y == 30 && x < 600) {
                    //direita
                    //verifica se há trem na região 1 e 4
                    if (x == 580) {
                        if (mutex[1].tryLock()) {
                            if (mutex[4].tryLock()) {
                                areasOcupadas[1] = 1;
                                areasOcupadas[4] = 1;
                                x += 10;
                            } else {
                                mutex[1].unlock();
                            }
                        }
                    } else {
                        x += 10;
                    }
                }
                else if (x == 600 && y < 150) {
                    //desce
                    //entra na região crítica 1
                    y += 10;
                }
                else if (x > 330 && y == 150) {
                    //esquerda
                    //verifica as regiões 3 e 0
                    if (x == 490) {
                        if (mutex[3].tryLock()) {
                            if (mutex[0].tryLock()) {
                                areasOcupadas[3] = 1;
                                areasOcupadas[0] = 1;
                                x -= 10;
                            } else {
                                mutex[3].unlock();
                            }
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

                emit updateGUI(ID, x, y);    //Emite um sinal
                break;

            case 3: //Trem 3
                if (x == 620 && y == 30 && areasOcupadas[1] == 1) {
                    mutex[1].unlock();
                    areasOcupadas[1] = 0;
                }
                else if (x == 600 && y == 130 && areasOcupadas[5] == 1) {
                    mutex[5].unlock();
                    areasOcupadas[5] = 0;
                }

                if (y == 30 && x < 870) {
                    //direita
                    x += 10;
                } else if (x == 870 && y < 150) {
                    //desce
                    y += 10;
                } else if (x > 600 && y == 150) {
                    //esquerda
                    if (x == 760) {
                        //verifica região crítica 5
                        if (mutex[5].tryLock()) {
                            areasOcupadas[5] = 1;
                            x -= 10;
                        }
                    } else if (x == 620) {
                        //verifica região crítica 1
                        if (mutex[1].tryLock()) {
                            areasOcupadas[1] = 1;
                            x -= 10;
                        }
                    } else {
                        x -= 10;
                    }
                }
                else {
                    //sobe na região crítica 1
                    y -= 10;
                }

                emit updateGUI(ID, x,y);    //Emite um sinal
                break;
            case 4: //Trem 4
                if (x == 354 && y == 150 && areasOcupadas[2] == 1) {
                    mutex[2].unlock();
                    areasOcupadas[2] = 0;
                }
                else if (x == 464 && y == 170 && areasOcupadas[3] == 1) {
                    mutex[3].unlock();
                    areasOcupadas[3] = 0;
                }
                else if (x == 444 && y == 270 && areasOcupadas[6] == 1) {
                    mutex[6].unlock();
                    areasOcupadas[6] = 0;
                }

                if (y == 150 && x < 464) {
                    //direita
                    if (x == 444) {
                        //verifica a região crítica 6
                        if (mutex[6].tryLock()) {
                            areasOcupadas[6] = 1;
                            x += 10;
                        }
                    } else {
                       x += 10;
                    }
                }
                else if (x == 464 && y < 270) {
                    //desce
                    //entra na região 6
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
                        if (mutex[2].tryLock()) {
                            if (mutex[3].tryLock()) {
                                areasOcupadas[2] = 1;
                                areasOcupadas[3] = 1;
                                y -= 10;
                            } else {
                                mutex[2].unlock();
                            }
                        }
                    } else {
                        y -= 10;
                    }
                }

                emit updateGUI(ID, x,y);    //Emite um sinal
                break;
            case 5: //Trem 5
                if (x == 624 && y == 150 && areasOcupadas[4] == 1) {
                    mutex[4].unlock();
                    areasOcupadas[4] = 0;
                }
                else if (x == 734 && y == 170 && areasOcupadas[5] == 1) {
                    mutex[5].unlock();
                    areasOcupadas[5] = 0;
                }
                else if (x == 484 && y == 150 && areasOcupadas[6] == 1) {
                    mutex[6].unlock();
                    areasOcupadas[6] = 0;
                }

                if (y == 150 && x < 734) {
                    //direita
                    //verifica a região crítica 5
                    if (x == 574) {
                        if (mutex[5].tryLock()) {
                            areasOcupadas[5] = 1;
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
                        if (mutex[6].tryLock()) {
                            if (mutex[4].tryLock()) {
                                areasOcupadas[4] = 1;
                                areasOcupadas[6] = 1;
                                x -= 10;
                            } else {
                                mutex[6].unlock();
                            }
                        }
                    } else {
                        x -= 10;
                    }
                }
                else {
                    //sobe
                    y -= 10;
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




