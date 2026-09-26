#include "Pieza.h"

Pieza::Pieza() : tipo(TipoPieza::Ninguna), posX(4), posY(0), estadoRotacion(0) {
}

Pieza::Pieza(TipoPieza t) : tipo(t), posX(3), posY(0), estadoRotacion(0) {
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

void Pieza::rotar() {
    estadoRotacion = (estadoRotacion + 1) % 4;
    actualizarVisual();
}

void Pieza::desrotar() {
    estadoRotacion = (estadoRotacion + 3) % 4;
    actualizarVisual();
}

void Pieza::actualizarVisual() {
    if (tipo != TipoPieza::Ninguna) {
        int coordenadas[4][2];
        obtenerPosicionesRelativas(coordenadas);
        visual.configurar(tipo, 250.0f, 0.0f, posX, posY, 1.0f, coordenadas);
    }
}

void Pieza::dibujar(sf::RenderWindow& ventana) {
    if (tipo != TipoPieza::Ninguna) {
        visual.renderizar(ventana);
    }
}

int Pieza::getX() const { return posX; }
int Pieza::getY() const { return posY; }

void Pieza::obtenerPosicionesRelativas(int posiciones[4][2]) const {
    for(int i=0; i<4; i++){ posiciones[i][0] = 0; posiciones[i][1] = 0; }
    
    switch (tipo) {
        case TipoPieza::I:
            if (estadoRotacion == 0 || estadoRotacion == 2) {
                posiciones[0][0] = 0; posiciones[0][1] = 1;
                posiciones[1][0] = 1; posiciones[1][1] = 1;
                posiciones[2][0] = 2; posiciones[2][1] = 1;
                posiciones[3][0] = 3; posiciones[3][1] = 1;
            } else {
                posiciones[0][0] = 1; posiciones[0][1] = 0;
                posiciones[1][0] = 1; posiciones[1][1] = 1;
                posiciones[2][0] = 1; posiciones[2][1] = 2;
                posiciones[3][0] = 1; posiciones[3][1] = 3;
            }
            break;
        case TipoPieza::O:
            posiciones[0][0] = 1; posiciones[0][1] = 0;
            posiciones[1][0] = 2; posiciones[1][1] = 0;
            posiciones[2][0] = 1; posiciones[2][1] = 1;
            posiciones[3][0] = 2; posiciones[3][1] = 1;
            break;
        case TipoPieza::T:
            if (estadoRotacion == 0) {
                posiciones[0][0] = 1; posiciones[0][1] = 0;
                posiciones[1][0] = 0; posiciones[1][1] = 1;
                posiciones[2][0] = 1; posiciones[2][1] = 1;
                posiciones[3][0] = 2; posiciones[3][1] = 1;
            } else if (estadoRotacion == 1) {
                posiciones[0][0] = 1; posiciones[0][1] = 0;
                posiciones[1][0] = 1; posiciones[1][1] = 1;
                posiciones[2][0] = 2; posiciones[2][1] = 1;
                posiciones[3][0] = 1; posiciones[3][1] = 2;
            } else if (estadoRotacion == 2) {
                posiciones[0][0] = 0; posiciones[0][1] = 1;
                posiciones[1][0] = 1; posiciones[1][1] = 1;
                posiciones[2][0] = 2; posiciones[2][1] = 1;
                posiciones[3][0] = 1; posiciones[3][1] = 2;
            } else {
                posiciones[0][0] = 1; posiciones[0][1] = 0;
                posiciones[1][0] = 0; posiciones[1][1] = 1;
                posiciones[2][0] = 1; posiciones[2][1] = 1;
                posiciones[3][0] = 1; posiciones[3][1] = 2;
            }
            break;
        case TipoPieza::S:
            if (estadoRotacion == 0 || estadoRotacion == 2) {
                posiciones[0][0] = 1; posiciones[0][1] = 0;
                posiciones[1][0] = 2; posiciones[1][1] = 0;
                posiciones[2][0] = 0; posiciones[2][1] = 1;
                posiciones[3][0] = 1; posiciones[3][1] = 1;
            } else {
                posiciones[0][0] = 1; posiciones[0][1] = 0;
                posiciones[1][0] = 1; posiciones[1][1] = 1;
                posiciones[2][0] = 2; posiciones[2][1] = 1;
                posiciones[3][0] = 2; posiciones[3][1] = 2;
            }
            break;
        case TipoPieza::Z:
            if (estadoRotacion == 0 || estadoRotacion == 2) {
                posiciones[0][0] = 0; posiciones[0][1] = 0;
                posiciones[1][0] = 1; posiciones[0][1] = 0; // Fix: typo from older code
                posiciones[1][0] = 1; posiciones[1][1] = 0;
                posiciones[2][0] = 1; posiciones[2][1] = 1;
                posiciones[3][0] = 2; posiciones[3][1] = 1;
            } else {
                posiciones[0][0] = 2; posiciones[0][1] = 0;
                posiciones[1][0] = 1; posiciones[1][1] = 1;
                posiciones[2][0] = 2; posiciones[2][1] = 1;
                posiciones[3][0] = 1; posiciones[3][1] = 2;
            }
            break;
        case TipoPieza::J:
            if (estadoRotacion == 0) {
                posiciones[0][0] = 0; posiciones[0][1] = 0;
                posiciones[1][0] = 0; posiciones[1][1] = 1;
                posiciones[2][0] = 1; posiciones[2][1] = 1;
                posiciones[3][0] = 2; posiciones[3][1] = 1;
            } else if (estadoRotacion == 1) {
                posiciones[0][0] = 1; posiciones[0][1] = 0;
                posiciones[1][0] = 2; posiciones[1][1] = 0;
                posiciones[2][0] = 1; posiciones[2][1] = 1;
                posiciones[3][0] = 1; posiciones[3][1] = 2;
            } else if (estadoRotacion == 2) {
                posiciones[0][0] = 0; posiciones[0][1] = 1;
                posiciones[1][0] = 1; posiciones[1][1] = 1;
                posiciones[2][0] = 2; posiciones[2][1] = 1;
                posiciones[3][0] = 2; posiciones[3][1] = 2;
            } else {
                posiciones[0][0] = 1; posiciones[0][1] = 0;
                posiciones[1][0] = 1; posiciones[1][1] = 1;
                posiciones[2][0] = 0; posiciones[2][1] = 2;
                posiciones[3][0] = 1; posiciones[3][1] = 2;
            }
            break;
        case TipoPieza::L:
            if (estadoRotacion == 0) {
                posiciones[0][0] = 2; posiciones[0][1] = 0;
                posiciones[1][0] = 0; posiciones[1][1] = 1;
                posiciones[2][0] = 1; posiciones[2][1] = 1;
                posiciones[3][0] = 2; posiciones[3][1] = 1;
            } else if (estadoRotacion == 1) {
                posiciones[0][0] = 1; posiciones[0][1] = 0;
                posiciones[1][0] = 1; posiciones[1][1] = 1;
                posiciones[2][0] = 1; posiciones[2][1] = 2;
                posiciones[3][0] = 2; posiciones[3][1] = 2;
            } else if (estadoRotacion == 2) {
                posiciones[0][0] = 0; posiciones[0][1] = 1;
                posiciones[1][0] = 1; posiciones[1][1] = 1;
                posiciones[2][0] = 2; posiciones[2][1] = 1;
                posiciones[3][0] = 0; posiciones[3][1] = 2;
            } else {
                posiciones[0][0] = 0; posiciones[0][1] = 0;
                posiciones[1][0] = 1; posiciones[1][1] = 0;
                posiciones[2][0] = 1; posiciones[2][1] = 1;
                posiciones[3][0] = 1; posiciones[3][1] = 2;
            }
            break;
        default:
            break;
    }
}
