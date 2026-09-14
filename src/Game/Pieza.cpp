#include "Pieza.h"

Pieza::Pieza() : tipo(TipoPieza::Ninguna), posX(4), posY(0) {
}

Pieza::Pieza(TipoPieza t) : tipo(t), posX(3), posY(0) {
    actualizarVisual();
}

TipoPieza Pieza::getTipo() const {
    return tipo;
}

void Pieza::mover(int dx, int dy) {
    posX += dx;
    posY += dy;
    actualizarVisual();
}

void Pieza::actualizarVisual() {
    if (tipo != TipoPieza::Ninguna) {
        visual.configurar(tipo, posX, posY);
    }
}

void Pieza::dibujar(sf::RenderWindow& ventana) {
    if (tipo != TipoPieza::Ninguna) {
        visual.renderizar(ventana);
    }
}
