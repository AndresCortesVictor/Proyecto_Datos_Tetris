#ifndef PIEZA_H
#define PIEZA_H

#include "TipoPieza.h"
#include "../visuales/PiezaVisual.h"

class Pieza {
private:
    TipoPieza tipo;
    int posX;
    int posY;
    int estadoRotacion;
    PiezaVisual visual;

    void actualizarVisual();

public:
    Pieza();
    Pieza(TipoPieza t);

    TipoPieza getTipo() const;
    void mover(int dx, int dy);
    void rotar();
    void desrotar();
    void dibujar(sf::RenderWindow& ventana);

    int getX() const;
    int getY() const;
    void obtenerPosicionesRelativas(int posiciones[4][2]) const;
};

#endif
