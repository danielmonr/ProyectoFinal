#include "dialogmodulo.h"
#include "ui_dialogmodulo.h"
#include "seleccionmatriz.h"
#include "config.h"

DialogModulo::DialogModulo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogModulo)
{
    ui->setupUi(this);
}

DialogModulo::~DialogModulo()
{
    delete ui;
}


void DialogModulo::on_mod2_b_clicked()
{
    Config::mod_st = true;
    SeleccionMatriz sm;
    sm.setModal(true);
    sm.exec();
}

void DialogModulo::on_mod3_b_clicked()
{
    Config::mod_st = false;
    SeleccionMatriz sm;
    sm.setModal(true);
    sm.exec();
}
