#ifndef VENTANA_H
#define VENTANA_H

#include <QMainWindow>
#include<stdlib.h>
#include <time.h>

namespace Ui {
class Ventana;
}

class Ventana : public QMainWindow
{
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = 0);
    ~Ventana();

private slots:
    void on_Jugar_b_clicked();

    void on_Resolver_b_clicked();

private:
    Ui::Ventana *ui;
};

#endif // VENTANA_H
