#include "seleccionmatriz.h"
#include "ui_seleccionmatriz.h"
#include "juego.h"
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
    Juego j;
    j.setModal(true);
    j.exec();
}

void SeleccionMatriz::on_perz_b_clicked()
{
    Config::orig_st = false;
    Juego j;
    j.setModal(true);
    j.exec();
}
