#include "modulo.h"
#include "ui_modulo.h"

Modulo::Modulo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Modulo)
{
    ui->setupUi(this);
}

Modulo::~Modulo()
{
    delete ui;
}
