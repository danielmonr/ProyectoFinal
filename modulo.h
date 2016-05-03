#ifndef MODULO_H
#define MODULO_H

#include <QWidget>

namespace Ui {
class Modulo;
}

class Modulo : public QWidget
{
    Q_OBJECT

public:
    explicit Modulo(QWidget *parent = 0);
    ~Modulo();

private:
    Ui::Modulo *ui;
};

#endif // MODULO_H
