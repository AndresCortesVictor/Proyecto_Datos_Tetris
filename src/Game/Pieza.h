#ifndef PIEZA_H
#define PIEZA_H

#include "TipoPieza.h"
#include "../visuales/PiezaVisual.h"

class Pieza {
private:
    TipoPieza tipo;
    int posX;
    int posY;
    int orientacion;
    PiezaVisual visual;

    void actualizarVisual();

public:
    Pieza();
    Pieza(TipoPieza t);

    TipoPieza getTipo() const;
    int getX() const;
    int getY() const;
    void setX(int x);
    void setY(int y);
    void rotar();
    void deshacerRotacion();
    void obtenerPosicionesRelativas(int posiciones[4][2]) const;
    void mover(int dx, int dy);
    void dibujar(sf::RenderWindow& ventana);
};

#endif
