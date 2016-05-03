#ifndef DIALOGMODULO_H
#define DIALOGMODULO_H

#include <QDialog>

namespace Ui {
class DialogModulo;
}

class DialogModulo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogModulo(QWidget *parent = 0);
    ~DialogModulo();

private slots:
    void on_mod2_b_clicked();

    void on_mod3_b_clicked();

private:
    Ui::DialogModulo *ui;
};

#endif // DIALOGMODULO_H
