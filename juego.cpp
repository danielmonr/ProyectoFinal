#include "juego.h"
#include "ui_juego.h"

Juego::Juego(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Juego)
{

    botones = (QPushButton**) malloc (9*sizeof(QPushButton*));
    *botones = ui->b1;
    *(botones+1) = ui->b2;
    *(botones+2) = ui->b3;
    *(botones+3) = ui->b4;
    *(botones+4) = ui->b5;
    *(botones+5) = ui->b6;
    *(botones+6) = ui->b7;
    *(botones+7) = ui->b8;
    *(botones+8) = ui->b9;

    if(Config::mod_st){
        mod = 2;
    }
    else{
        mod = 3;
    }

    int matOriginal[N][N] = {
                    { 1, 1, 0, 1, 0, 0, 0, 0, 0 },
                    { 1, 1, 1, 0, 1, 0, 0, 0, 0 },
                    { 0, 1, 1, 0, 0, 1, 0, 0, 0 },
                    { 1, 0, 0, 1, 1, 0, 1, 0, 0 },
                    { 1, 0, 1, 0, 1, 0, 1, 0, 1 },
                    { 0, 0, 1, 0, 1, 1, 0, 0, 1 },
                    { 0, 0, 0, 1, 0, 0, 1, 1, 0 },
                    { 0, 0, 0, 0, 1, 0, 1, 1, 1 },
                    { 0, 0, 0, 0, 0, 1, 0, 1, 1 }
    };

    int matPersonalizada[N][N]{
                { 1, 1, 0, 1, 0, 0, 0, 0, 0 },
                { 1, 1, 1, 0, 1, 0, 0, 0, 0 },
                { 0, 1, 1, 0, 0, 1, 0, 0, 0 },
                { 1, 0, 0, 1, 1, 0, 1, 0, 0 },
                { 1, 1, 1, 1, 1, 1, 1, 1, 1 },
                { 0, 0, 1, 0, 1, 1, 0, 0, 1 },
                { 0, 0, 0, 1, 0, 0, 1, 1, 0 },
                { 0, 0, 0, 0, 1, 0, 1, 1, 1 },
                { 0, 0, 0, 0, 0, 1, 0, 1, 1 }
        };

    srand(time(NULL));
    for (int i = 0; i < 9; i++){
        matResultado[i] = 0;
    }

    generaMatriz(matInicial, mod);

    if(!Config::jugar_st){
        if(Config::orig_st)
            resuelveProblema(restaMatInicialFinal, matInicial, matFinal, matOriginal, mod, 1);
        else
            resuelveProblema(restaMatInicialFinal, matInicial, matFinal, matPersonalizada, mod, 2);
    }

    ui->setupUi(this);
}

Juego::~Juego()
{
    delete ui;
}

//funcion que genera aleatoriamente una matriz segun el modulo seleccionado
void Juego::generaMatriz(int matInicial[9], int mod){
    for (int i = 0; i < 9; i++){
        matInicial[i] = rand() % mod;
        if (i != 0 && i % (3) == 0){
            cout << endl;
        }
        cout << matInicial[i] << " ";
    }
    cout << endl;
}

// Funcion que ayuda al usuario a generar la matriz inicial
void Juego::escogeMatriz(int matInicial[9], int mod){
    cout << "Siguiendo el esquema: " << endl << "1 2 3" << endl << "4 5 6" << endl << "7 8 9" << endl;
    cout << "Si su numero no va de acuerdo con el modulo que escogio, se le hara automaticamente el modulo";
    for (int i = 0; i < 9; i++){
        cout << endl << "Dame la posicion:  " << i + 1 << endl;
        cin >> matInicial[i];
        matInicial[i] = matInicial[i] % mod;
    }
    cout << endl << endl;
    for (int i = 0; i < 9; i++){
        if (i != 0 && i % (3) == 0){
            cout << endl;
        }
        cout << matInicial[i] << " ";
    }
    cout << endl;
}

// Funcion que resuleve el problema.
void Juego::resuelveProblema(int restaMatInicialFinal[9], int matInicial[9], int matFinal[9], int matTransf[N][N], int mod, int op){
    for (int i = 0; i < 9; i++){
        // GEneracion de la matriz suma
        if ((matFinal[i] - matInicial[i]) < 0){
            restaMatInicialFinal[i] = ((matFinal[i] - matInicial[i]) + mod);
        }
        else{
            restaMatInicialFinal[i] = (matFinal[i] - matInicial[i]) % mod;
        }
        cout << restaMatInicialFinal[i] << endl;
    }

    gaussJordan(matTransf, restaMatInicialFinal, mod);

    for (int i = 0; i < N; i++){
        cout <<"Picar el boton " << i+1 << ":  " << restaMatInicialFinal[i] << " veces \n";
    }


}



int Juego::modulo(int x, int m) {
    if (x >= 0)
        return x % m;
    else {
        int k = floor((x + 0.0) / m);
        return x - (k * m);
    }
}


int Juego::inversoMultiplicativo(int x, int m) {
    for (int i = 1; i < m; ++i)
        if ((x * i) % m == 1)
            return i;
    return -1;
}


void Juego::intercambiarRenglones(int* x, int* y, int n) {
    int temp;
    for (int i = 0; i < n; ++i) {
        temp = x[i];
        x[i] = y[i];
        y[i] = temp;
    }
}

void Juego::escalarRenglon(int* x, int alfa, int mod, int n) {
    for (int i = 0; i < n; ++i)
        x[i] = modulo(x[i] * alfa, mod);
}

void Juego::sumarRenglon(int* x, int* y, int alfa, int mod, int n) {
    for (int i = 0; i < n; ++i)
        x[i] = modulo(x[i] + (alfa * y[i]), mod);
}



void Juego::gaussJordan(int A [][N], int* b, int mod) {
    int inverso, alfa;

    for (int i = 0; i < N; ++i) {
        if (inversoMultiplicativo(A[i][i], mod) == -1) {
            int j = i + 1;
            while (j < N && inversoMultiplicativo(A[j][i], mod) == -1)
                ++j;

            if (j != N) {
                intercambiarRenglones(A[i], A[j], N);
                intercambiarRenglones(b + i, b + j, 1);
            }

            else {
                cout << "La matriz no se puede invertir" << endl;
                exit(-1);
            }
        }

        inverso = inversoMultiplicativo(A[i][i], mod);

        escalarRenglon(A[i], inverso, mod, N);
        escalarRenglon(b + i, inverso, mod, 1);

        for (int j = 0; j < N; ++j) {
            if (j != i) {
                alfa = -1 * A[j][i];
                sumarRenglon(A[j], A[i], alfa, mod, N);
                sumarRenglon(b + j, b + i, alfa, mod, 1);
            }
        }
    }
}

void Juego::setNumeros(int matriz[9]){
    for(int i = 0; i < 9; ++i){
        (*(botones+i))->setText(QString("%1").arg(matriz[i]));
    }
}

void Juego::on_b1_clicked()
{

}

void Juego::on_b2_clicked()
{

}

void Juego::on_b3_clicked()
{

}

void Juego::on_b4_clicked()
{

}

void Juego::on_b5_clicked()
{

}

void Juego::on_b6_clicked()
{

}

void Juego::on_b7_clicked()
{

}

void Juego::on_b8_clicked()
{

}

void Juego::on_b9_clicked()
{

}
