#ifndef PIEZA_H
#define PIEZA_H

#include "TipoPieza.h"
#include "../visuales/PiezaVisual.h"

class Pieza {
private:
    TipoPieza tipo;
    int posX;
    int posY;
    PiezaVisual visual;

    void actualizarVisual();

public:
    Pieza();
    Pieza(TipoPieza t);

    TipoPieza getTipo() const;
    void mover(int dx, int dy);
    void dibujar(sf::RenderWindow& ventana);
};

#endif
