#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Cria o trem com seu (ID, posição X, posição Y)
    trem1 = new Trem(1,60,30);
    trem2 = new Trem(2,330,30);
    trem3 = new Trem(3,600,30);
    trem4 = new Trem(4,194,150);
    trem5 = new Trem(5,464,150);

    /*
     * Conecta o sinal UPDATEGUI à função UPDATEINTERFACE.
     * Ou seja, sempre que o sinal UPDATEGUI foi chamado, será executada a função UPDATEINTERFACE.
     * Os 3 parâmetros INT do sinal serão utilizados na função.
     * Trem1 e Trem2 são os objetos que podem chamar o sinal. Se um outro objeto chamar o
     * sinal UPDATEGUI, não haverá execução da função UPDATEINTERFACE
     */
    connect(trem1,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem2,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem3,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem4,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));
    connect(trem5,SIGNAL(updateGUI(int,int,int)),SLOT(updateInterface(int,int,int)));

    trem1->start();
    trem2->start();
    trem3->start();
    trem4->start();
    trem5->start();

}

//Função que será executada quando o sinal UPDATEGUI for emitido
void MainWindow::updateInterface(int id, int x, int y){
    switch(id){
    case 1: //Atualiza a posição do objeto da tela (quadrado) que representa o trem1
        ui->label_trem1->setGeometry(x,y,21,17);
        //imprime na tela as coordenadas
        ui->xyT1->setText(QString::number(x)+" - "+QString::number(y));
        break;
    case 2: //Atualiza a posição do objeto da tela (quadrado) que representa o trem2
        ui->label_trem2->setGeometry(x,y,21,17);
        ui->xyT2->setText(QString::number(x)+" - "+QString::number(y));
        break;
    case 3: //Atualiza a posição do objeto da tela (quadrado) que representa o trem3
        ui->label_trem3->setGeometry(x,y,21,17);
        ui->xyT3->setText(QString::number(x)+" - "+QString::number(y));
        break;
    case 4: //Atualiza a posição do objeto da tela (quadrado) que representa o trem4
        ui->label_trem4->setGeometry(x,y,21,17);
        ui->xyT4->setText(QString::number(x)+" - "+QString::number(y));
        break;
    case 5: //Atualiza a posição do objeto da tela (quadrado) que representa o trem5
        ui->label_trem5->setGeometry(x,y,21,17);
        ui->xyT5->setText(QString::number(x)+" - "+QString::number(y));
        break;
    default:
        break;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_horizontalSlider_1_valueChanged(int value){
    trem1->setVelocidade(value);
    ui->velT1->setText(QString::number(value));
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value){
    trem2->setVelocidade(value);
    ui->velT2->setText(QString::number(value));
}

void MainWindow::on_horizontalSlider_3_valueChanged(int value){
    trem3->setVelocidade(value);
    ui->velT3->setText(QString::number(value));
}

void MainWindow::on_horizontalSlider_4_valueChanged(int value){
    trem4->setVelocidade(value);
    ui->velT4->setText(QString::number(value));
}

void MainWindow::on_horizontalSlider_5_valueChanged(int value){
    trem5->setVelocidade(value);
    ui->velT5->setText(QString::number(value));
}

