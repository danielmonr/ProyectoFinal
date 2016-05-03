#include "ventana.h"
#include "ui_ventana.h"
#include "dialogmodulo.h"
#include "config.h"

Ventana::Ventana(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Ventana)
{
    ui->setupUi(this);
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::on_Jugar_b_clicked()
{
    Config::jugar_st = true;
    DialogModulo mod_w;
    mod_w.setModal(true);
    mod_w.exec();
}

void Ventana::on_Resolver_b_clicked()
{
    Config::jugar_st = false;
    DialogModulo mod_w;
    mod_w.setModal(true);
    mod_w.exec();
}
