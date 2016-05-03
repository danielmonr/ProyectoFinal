#include "seleccionmatriz.h"
#include "ui_seleccionmatriz.h"
#include "juego.h"
#include "solucion.h"
#include "config.h"

SeleccionMatriz::SeleccionMatriz(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SeleccionMatriz)
{
    ui->setupUi(this);
}

SeleccionMatriz::~SeleccionMatriz()
{
    delete ui;
}

void SeleccionMatriz::on_orig_b_clicked()
{
    Config::orig_st = true;
    if(Config::jugar_st){
        Juego j;
        j.setModal(true);
        j.exec();
    }
    else{
        Solucion sol;
        sol.setModal(true);
        sol.exec();
    }
}

void SeleccionMatriz::on_perz_b_clicked()
{
    Config::orig_st = false;
    if(Config::jugar_st){
        Juego j;
        j.setModal(true);
        j.exec();
    }
    else{
        Solucion sol;
        sol.setModal(true);
        sol.exec();
    }
}
