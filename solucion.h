#ifndef SOLUCION_H
#define SOLUCION_H

#include <QDialog>
#include <QLineEdit>
#include <iostream>
#include "config.h"
#include <time.h>

#define N 9

using namespace std;

namespace Ui {
class Solucion;
}

class Solucion : public QDialog
{
    Q_OBJECT

public:
    explicit Solucion(QWidget *parent = 0);
    ~Solucion();

private slots:
    void on_sig_b_clicked();

    void on_res_b_clicked();

private:
    int mod;
    int cont;
    Ui::Solucion *ui;
    QLineEdit** lines;
    int matInicial[9];
    int matFinal[9];
    int restaMatInicialFinal[9];
    int matResultado[9];

    void setNumeros(int[N]);

    void generaMatriz();
    void resuelveProblema(int[N], int[N], int[N], int[N][N], int);
    void gaussJordan(int A[][N], int* b, int mod);
    int modulo(int, int);
    int inversoMultiplicativo(int x, int m);
    void intercambiarRenglones(int* x, int* y, int n);
    void escalarRenglon(int* x, int alfa, int mod, int n);
    void sumarRenglon(int* x, int* y, int alfa, int mod, int n);
};

#endif // SOLUCION_H
