#include "Pieza.h"

Pieza::Pieza() : tipo(TipoPieza::Ninguna), posX(0), posY(0), orientacion(0) {
    actualizarVisual();
}

Pieza::Pieza(TipoPieza t) : tipo(t), posX(3), posY(0), orientacion(0) {
    actualizarVisual();
}

TipoPieza Pieza::getTipo() const {
    return tipo;
}

void Pieza::actualizarVisual() {
    if (tipo != TipoPieza::Ninguna) {
        visual.configurar(tipo, 250.0f, 0.0f, posX, posY);
    }
}

void Pieza::dibujar(sf::RenderWindow& ventana) {
    if (tipo != TipoPieza::Ninguna) {
        visual.renderizar(ventana);
    }
}

int Pieza::getX() const { return posX; }
int Pieza::getY() const { return posY; }

void Pieza::setX(int x) { 
    posX = x; 
    actualizarVisual(); 
}

void Pieza::setY(int y) { 
    posY = y; 
    actualizarVisual(); 
}

void Pieza::mover(int dx, int dy) {
    posX += dx;
    posY += dy;
    actualizarVisual();
}

void Pieza::rotar() {
    orientacion = (orientacion + 1) % 4;
    actualizarVisual(); // Might not do anything since PiezaVisual draws squares, but good for completeness
}

void Pieza::deshacerRotacion() {
    orientacion = (orientacion + 3) % 4;
    actualizarVisual();
}

void Pieza::obtenerPosicionesRelativas(int posiciones[4][2]) const {
    for(int i=0; i<4; i++){ posiciones[i][0] = 0; posiciones[i][1] = 0; }
    
    // Configuración base (orientación 0)
    switch (tipo) {
        case TipoPieza::I:
            posiciones[0][0] = 0; posiciones[0][1] = 1;
            posiciones[1][0] = 1; posiciones[1][1] = 1;
            posiciones[2][0] = 2; posiciones[2][1] = 1;
            posiciones[3][0] = 3; posiciones[3][1] = 1;
            break;
        case TipoPieza::O:
            posiciones[0][0] = 1; posiciones[0][1] = 0;
            posiciones[1][0] = 2; posiciones[1][1] = 0;
            posiciones[2][0] = 1; posiciones[2][1] = 1;
            posiciones[3][0] = 2; posiciones[3][1] = 1;
            break;
        case TipoPieza::T:
            posiciones[0][0] = 1; posiciones[0][1] = 0;
            posiciones[1][0] = 0; posiciones[1][1] = 1;
            posiciones[2][0] = 1; posiciones[2][1] = 1;
            posiciones[3][0] = 2; posiciones[3][1] = 1;
            break;
        case TipoPieza::S:
            posiciones[0][0] = 1; posiciones[0][1] = 0;
            posiciones[1][0] = 2; posiciones[1][1] = 0;
            posiciones[2][0] = 0; posiciones[2][1] = 1;
            posiciones[3][0] = 1; posiciones[3][1] = 1;
            break;
        case TipoPieza::Z:
            posiciones[0][0] = 0; posiciones[0][1] = 0;
            posiciones[1][0] = 1; posiciones[1][1] = 0;
            posiciones[2][0] = 1; posiciones[2][1] = 1;
            posiciones[3][0] = 2; posiciones[3][1] = 1;
            break;
        case TipoPieza::J:
            posiciones[0][0] = 0; posiciones[0][1] = 0;
            posiciones[1][0] = 0; posiciones[1][1] = 1;
            posiciones[2][0] = 1; posiciones[2][1] = 1;
            posiciones[3][0] = 2; posiciones[3][1] = 1;
            break;
        case TipoPieza::L:
            posiciones[0][0] = 2; posiciones[0][1] = 0;
            posiciones[1][0] = 0; posiciones[1][1] = 1;
            posiciones[2][0] = 1; posiciones[2][1] = 1;
            posiciones[3][0] = 2; posiciones[3][1] = 1;
            break;
        default:
            break;
    }
    
    // Aplicar rotaciones
    for (int r = 0; r < orientacion; ++r) {
        for (int i = 0; i < 4; ++i) {
            int x = posiciones[i][0];
            int y = posiciones[i][1];
            
            if (tipo == TipoPieza::I) {
                // Rotar en matriz 4x4
                posiciones[i][0] = 3 - y;
                posiciones[i][1] = x;
            } else if (tipo == TipoPieza::O) {
                // No hace nada
            } else {
                // Rotar en matriz 3x3
                posiciones[i][0] = 2 - y;
                posiciones[i][1] = x;
            }
        }
    }
}
