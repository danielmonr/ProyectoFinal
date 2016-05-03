#include "solucion.h"
#include "ui_solucion.h"

Solucion::Solucion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Solucion)
{
    ui->setupUi(this);
    lines = (QLineEdit**) malloc (9*sizeof(QLineEdit*));
    *lines = ui->le_1;
    *(lines+1) = ui->le_2;
    *(lines+2) = ui->le_3;
    *(lines+3) = ui->le_4;
    *(lines+4) = ui->le_5;
    *(lines+5) = ui->le_6;
    *(lines+6) = ui->le_7;
    *(lines+7) = ui->le_8;
    *(lines+8) = ui->le_9;

    for (int i = 0; i < 9;++i){
        (*(lines+i))->setAlignment(Qt::AlignCenter);
    }

    if(Config::mod_st){
        mod = 2;
    }
    else{
        mod = 3;
    }


    cont = 0;

    srand(time(NULL));
    for (int i = 0; i < 9; i++){
        matResultado[i] = 0;
        matFinal[i] = 1;
    }
    matFinal[4] = 0;
}

Solucion::~Solucion()
{
    delete ui;
    free(lines);
}

void Solucion::on_sig_b_clicked()
{
    (*(lines + cont))->setStyleSheet("QLineEdit { background: rgb(255, 255, 255); }");
    cout << "Presionado" << endl;
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


    while(restaMatInicialFinal[cont] == 0){
        cont++;
        if (cont > 8){
            ui->sig_b->setEnabled(false);
            return;
        }
    }
    int i = cont;
        if(restaMatInicialFinal[i] > 0){
            (*(lines + i))->setStyleSheet("QLineEdit { background: rgb(0, 255, 0); }");
            cout << "entro" << endl;
            for(int j = 0; j < 9; ++j){
                if(Config::orig_st){
                    matResultado[j] = (matResultado[j] + matOriginal[j][i])%mod;
                }
                else{
                    matResultado[j] = modulo(matResultado[j] +matPersonalizada[j][i], mod);
                }
                cout << matResultado[j] << endl;
            }
        }

        if (restaMatInicialFinal[i] > 0)
            restaMatInicialFinal[i] -= 1;

        setNumeros(matResultado);
}

void Solucion::setNumeros(int n[9]){
    cout << "poniendo numeros" << endl;
    for(int i = 0; i <9 ; ++i){
        QString s = QString::number(n[i]);
        (*(lines+i))->setText(s);
    }
}

void Solucion::on_res_b_clicked()
{
    for(int i = 0; i < 9; ++i){
        (*(lines+i))->setEnabled(false);
    }
    generaMatriz();
    cout << "Mat inicial: ";
    for(int i = 0; i < 9; ++i){
        cout << matInicial[i] << ",";
    }
    cout << endl << "Mat final: ";
    for(int i = 0; i < 9; ++i){
        cout << matFinal[i] << ",";
    }
    cout << endl;


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

    if(Config::orig_st)
        resuelveProblema(restaMatInicialFinal, matInicial, matFinal, matOriginal, mod);
    else
        resuelveProblema(restaMatInicialFinal, matInicial, matFinal, matPersonalizada, mod);

    ui->sig_b->setEnabled(true);
    ui->res_b->setEnabled(false);
    cout << "Matriz a presionar: ";
    for(int i = 0; i < 9; ++i){
        cout << restaMatInicialFinal[i] << ",";
    }
    cout << endl;
}

void Solucion::generaMatriz(){
    for(int i = 0; i < 9; ++i){
        matInicial[i] = modulo((*(lines+i))->text().toInt(), mod);
        cout << matInicial[i] << ",";
        matResultado[i] = matInicial[i];
    }
    cout << endl;
}

// Funcion que resuleve el problema.
void Solucion::resuelveProblema(int restaMatInicialFinal[9], int matInicial[9], int matFinal[9], int matTransf[N][N], int mod){
    for (int i = 0; i < 9; i++){
        // Generacion de la matriz suma
        if ((matFinal[i] - matInicial[i]) < 0){
            restaMatInicialFinal[i] = ((matFinal[i] - matInicial[i]) + mod);
        }
        else{
            restaMatInicialFinal[i] = (matFinal[i] - matInicial[i]) % mod;
        }
        //cout << restaMatInicialFinal[i] << endl;
    }

    gaussJordan(matTransf, restaMatInicialFinal, mod);

    /*for (int i = 0; i < N; i++){
        cout <<"Picar el boton " << i+1 << ":  " << restaMatInicialFinal[i] << " veces \n";
    }*/


}



int Solucion::modulo(int x, int m) {
    if (x >= 0)
        return x % m;
    else {
        int k = floor((x + 0.0) / m);
        return x - (k * m);
    }
}


int Solucion::inversoMultiplicativo(int x, int m) {
    for (int i = 1; i < m; ++i)
        if ((x * i) % m == 1)
            return i;
    return -1;
}


void Solucion::intercambiarRenglones(int* x, int* y, int n) {
    int temp;
    for (int i = 0; i < n; ++i) {
        temp = x[i];
        x[i] = y[i];
        y[i] = temp;
    }
}

void Solucion::escalarRenglon(int* x, int alfa, int mod, int n) {
    for (int i = 0; i < n; ++i)
        x[i] = modulo(x[i] * alfa, mod);
}

void Solucion::sumarRenglon(int* x, int* y, int alfa, int mod, int n) {
    for (int i = 0; i < n; ++i)
        x[i] = modulo(x[i] + (alfa * y[i]), mod);
}



void Solucion::gaussJordan(int A [][N], int* b, int mod) {
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
