#ifndef JUEGO_H
#define JUEGO_H

#include <QDialog>
#include<stdlib.h>
#include <time.h>
#include <iostream>
#include <config.h>

using namespace std;

#define N 9

namespace Ui {
class Juego;
}

class Juego : public QDialog
{
    Q_OBJECT

public:
    explicit Juego(QWidget *parent = 0);
    ~Juego();

private slots:
    void won_validate();
    void on_b1_clicked();

    void on_b2_clicked();

    void on_b3_clicked();

    void on_b4_clicked();

    void on_b5_clicked();

    void on_b6_clicked();

    void on_b7_clicked();

    void on_b8_clicked();

    void on_b9_clicked();

private:
    int mod;

    int matInicial[9];
    int matFinal[9];
    int restaMatInicialFinal[9];
    int matResultado[9];
    bool won;

    Ui::Juego *ui;
    void cambiaTextoInicial();
    void escondeBotones();
    void generaMatriz(int[N], int);
    /*void escogeMatriz(int[N], int);
    void resuelveProblema(int[N], int[N], int[N], int[N][N], int, int);
    void gaussJordan(int A[][N], int* b, int mod);
    int modulo(int, int);
    int inversoMultiplicativo(int x, int m);
    void intercambiarRenglones(int* x, int* y, int n);
    void escalarRenglon(int* x, int alfa, int mod, int n);
    void sumarRenglon(int* x, int* y, int alfa, int mod, int n);*/
};

#endif // JUEGO_H
