#include "juego.h"
#include "ui_juego.h"
#include <math.h>
#include <string.h>

Juego::Juego(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Juego)
{


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
    //cout<<button[0][0]->text().toStdString()<<endl;
    cambiaTextoInicial();
}

Juego::~Juego()
{
    delete ui;
}
void Juego::cambiaTextoInicial(){
    QString s;
    ui->b1->setText(QString::number(matInicial[0]));
    ui->b2->setText(QString::number(matInicial[1]));
    ui->b3->setText(QString::number(matInicial[2]));
    ui->b4->setText(QString::number(matInicial[3]));
    ui->b5->setText(QString::number(matInicial[4]));
    ui->b6->setText(QString::number(matInicial[5]));
    ui->b7->setText(QString::number(matInicial[6]));
    ui->b8->setText(QString::number(matInicial[7]));
    ui->b9->setText(QString::number(matInicial[8]));

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
        // Generacion de la matriz suma
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

void Juego::on_b1_clicked()
{
    //Modulo 2 en juego con matriz original (valido para matriz especial)
    if(Config::jugar_st && Config::mod_st){
        ui->b1->setText(QString::number((ui->b1->text().toInt()+1)%2));
        ui->b2->setText(QString::number((ui->b2->text().toInt()+1)%2));
        ui->b4->setText(QString::number((ui->b4->text().toInt()+1)%2));
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%2));
    }
    //Modulo 3 en juego con matriz original  (valido para matriz especial)
    if(Config::jugar_st && !Config::mod_st){
        ui->b1->setText(QString::number((ui->b1->text().toInt()+1)%3));
        ui->b2->setText(QString::number((ui->b2->text().toInt()+1)%3));
        ui->b4->setText(QString::number((ui->b4->text().toInt()+1)%3));
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%3));
    }
}

void Juego::on_b2_clicked()
{
    if(Config::jugar_st && Config::orig_st && Config::mod_st){
        ui->b1->setText(QString::number((ui->b1->text().toInt()+1)%2));
        ui->b2->setText(QString::number((ui->b2->text().toInt()+1)%2));
        ui->b3->setText(QString::number((ui->b3->text().toInt()+1)%2));
    }
    if(Config::jugar_st && Config::orig_st && !Config::mod_st){
        ui->b1->setText(QString::number((ui->b1->text().toInt()+1)%3));
        ui->b2->setText(QString::number((ui->b2->text().toInt()+1)%3));
        ui->b3->setText(QString::number((ui->b3->text().toInt()+1)%3));
    }
     //Modulo 2 en juego con matriz  especial
    if(Config::jugar_st && !Config::orig_st && Config::mod_st){
        ui->b1->setText(QString::number((ui->b1->text().toInt()+1)%2));
        ui->b2->setText(QString::number((ui->b2->text().toInt()+1)%2));
        ui->b3->setText(QString::number((ui->b3->text().toInt()+1)%2));
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%2));
    }
    //Modulo 3 en juego con matriz  especial
    if(Config::jugar_st && !Config::orig_st && !Config::mod_st){
        ui->b1->setText(QString::number((ui->b1->text().toInt()+1)%3));
        ui->b2->setText(QString::number((ui->b2->text().toInt()+1)%3));
        ui->b3->setText(QString::number((ui->b3->text().toInt()+1)%3));
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%3));
    }

}

void Juego::on_b3_clicked()
{
    if(Config::jugar_st && Config::mod_st){
        ui->b2->setText(QString::number((ui->b2->text().toInt()+1)%2));
        ui->b3->setText(QString::number((ui->b3->text().toInt()+1)%2));
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%2));
        ui->b6->setText(QString::number((ui->b6->text().toInt()+1)%2));
    }
    if(Config::jugar_st && !Config::mod_st){
        ui->b2->setText(QString::number((ui->b2->text().toInt()+1)%3));
        ui->b3->setText(QString::number((ui->b3->text().toInt()+1)%3));
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%3));
        ui->b6->setText(QString::number((ui->b6->text().toInt()+1)%3));
    }
}

void Juego::on_b4_clicked()
{
    if(Config::jugar_st && Config::orig_st && Config::mod_st){
        ui->b1->setText(QString::number((ui->b1->text().toInt()+1)%2));
        ui->b4->setText(QString::number((ui->b4->text().toInt()+1)%2));
        ui->b7->setText(QString::number((ui->b7->text().toInt()+1)%2));
     }
    if(Config::jugar_st && Config::orig_st && !Config::mod_st){
        ui->b1->setText(QString::number((ui->b1->text().toInt()+1)%3));
        ui->b4->setText(QString::number((ui->b4->text().toInt()+1)%3));
        ui->b7->setText(QString::number((ui->b7->text().toInt()+1)%3));
     }
    if(Config::jugar_st && !Config::orig_st && Config::mod_st){
        ui->b1->setText(QString::number((ui->b1->text().toInt()+1)%2));
        ui->b4->setText(QString::number((ui->b4->text().toInt()+1)%2));
        ui->b7->setText(QString::number((ui->b7->text().toInt()+1)%2));
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%2));
     }
    if(Config::jugar_st && !Config::orig_st && !Config::mod_st){
        ui->b1->setText(QString::number((ui->b1->text().toInt()+1)%3));
        ui->b4->setText(QString::number((ui->b4->text().toInt()+1)%3));
        ui->b7->setText(QString::number((ui->b7->text().toInt()+1)%3));
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%3));
     }
}

void Juego::on_b5_clicked()
{
    if(Config::jugar_st && Config::mod_st){
        ui->b2->setText(QString::number((ui->b2->text().toInt()+1)%2));
        ui->b4->setText(QString::number((ui->b4->text().toInt()+1)%2));
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%2));
        ui->b6->setText(QString::number((ui->b6->text().toInt()+1)%2));
        ui->b8->setText(QString::number((ui->b8->text().toInt()+1)%2));
    }
    if(Config::jugar_st && !Config::mod_st){
        ui->b2->setText(QString::number((ui->b2->text().toInt()+1)%3));
        ui->b4->setText(QString::number((ui->b4->text().toInt()+1)%3));
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%3));
        ui->b6->setText(QString::number((ui->b6->text().toInt()+1)%3));
        ui->b8->setText(QString::number((ui->b8->text().toInt()+1)%3));
    }
}

void Juego::on_b6_clicked()
{
    if(Config::jugar_st && Config::orig_st && Config::mod_st){
        ui->b3->setText(QString::number((ui->b3->text().toInt()+1)%2));
        ui->b6->setText(QString::number((ui->b6->text().toInt()+1)%2));
        ui->b9->setText(QString::number((ui->b9->text().toInt()+1)%2));
    }
    if(Config::jugar_st && Config::orig_st && !Config::mod_st){
        ui->b3->setText(QString::number((ui->b3->text().toInt()+1)%3));
        ui->b6->setText(QString::number((ui->b6->text().toInt()+1)%3));
        ui->b9->setText(QString::number((ui->b9->text().toInt()+1)%3));
    }
    if(Config::jugar_st && !Config::orig_st && Config::mod_st){
        ui->b3->setText(QString::number((ui->b3->text().toInt()+1)%2));
        ui->b6->setText(QString::number((ui->b6->text().toInt()+1)%2));
        ui->b9->setText(QString::number((ui->b9->text().toInt()+1)%2));
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%2));
    }
    if(Config::jugar_st && !Config::orig_st && !Config::mod_st){
        ui->b3->setText(QString::number((ui->b3->text().toInt()+1)%3));
        ui->b6->setText(QString::number((ui->b6->text().toInt()+1)%3));
        ui->b9->setText(QString::number((ui->b9->text().toInt()+1)%3));
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%3));
    }
}

void Juego::on_b7_clicked()
{
    if(Config::jugar_st  && Config::mod_st){
        ui->b4->setText(QString::number((ui->b4->text().toInt()+1)%2));
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%2));
        ui->b7->setText(QString::number((ui->b7->text().toInt()+1)%2));
        ui->b8->setText(QString::number((ui->b8->text().toInt()+1)%2));
    }
    if(Config::jugar_st && !Config::mod_st){
        ui->b4->setText(QString::number((ui->b4->text().toInt()+1)%3));
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%3));
        ui->b7->setText(QString::number((ui->b7->text().toInt()+1)%3));
        ui->b8->setText(QString::number((ui->b8->text().toInt()+1)%3));
    }


}

void Juego::on_b8_clicked()
{
    if(Config::jugar_st && Config::orig_st && Config::mod_st){
        ui->b7->setText(QString::number((ui->b7->text().toInt()+1)%2));
        ui->b8->setText(QString::number((ui->b8->text().toInt()+1)%2));
        ui->b9->setText(QString::number((ui->b9->text().toInt()+1)%2));
    }
    if(Config::jugar_st && Config::orig_st && !Config::mod_st){
        ui->b7->setText(QString::number((ui->b7->text().toInt()+1)%3));
        ui->b8->setText(QString::number((ui->b8->text().toInt()+1)%3));
        ui->b9->setText(QString::number((ui->b9->text().toInt()+1)%3));
    }
    if(Config::jugar_st && !Config::orig_st && Config::mod_st){
        ui->b7->setText(QString::number((ui->b7->text().toInt()+1)%2));
        ui->b8->setText(QString::number((ui->b8->text().toInt()+1)%2));
        ui->b9->setText(QString::number((ui->b9->text().toInt()+1)%2));
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%2));
    }
    if(Config::jugar_st && !Config::orig_st && !Config::mod_st){
        ui->b7->setText(QString::number((ui->b7->text().toInt()+1)%3));
        ui->b8->setText(QString::number((ui->b8->text().toInt()+1)%3));
        ui->b9->setText(QString::number((ui->b9->text().toInt()+1)%3));
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%3));
    }
}

void Juego::on_b9_clicked()
{
    if(Config::jugar_st && Config::mod_st){
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%2));
        ui->b6->setText(QString::number((ui->b6->text().toInt()+1)%2));
        ui->b8->setText(QString::number((ui->b8->text().toInt()+1)%2));
        ui->b9->setText(QString::number((ui->b9->text().toInt()+1)%2));
    }
    if(Config::jugar_st && !Config::mod_st){
        ui->b5->setText(QString::number((ui->b5->text().toInt()+1)%3));
        ui->b6->setText(QString::number((ui->b6->text().toInt()+1)%3));
        ui->b8->setText(QString::number((ui->b8->text().toInt()+1)%3));
        ui->b9->setText(QString::number((ui->b9->text().toInt()+1)%3));
    }
}
