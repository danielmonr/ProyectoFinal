#ifndef SELECCIONMATRIZ_H
#define SELECCIONMATRIZ_H

#include <QDialog>

namespace Ui {
class SeleccionMatriz;
}

class SeleccionMatriz : public QDialog
{
    Q_OBJECT

public:
    explicit SeleccionMatriz(QWidget *parent = 0);
    ~SeleccionMatriz();

private slots:
    void on_orig_b_clicked();

    void on_perz_b_clicked();

private:
    Ui::SeleccionMatriz *ui;
};

#endif // SELECCIONMATRIZ_H
