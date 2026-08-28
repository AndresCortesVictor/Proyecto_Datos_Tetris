#include "PiezaVisual.h"

PiezaVisual::PiezaVisual() {
    for (int i = 0; i < 4; ++i) {
        bloques[i].setSize(sf::Vector2f(TAMANO_CELDA - 1.0f, TAMANO_CELDA - 1.0f));
        bloques[i].setOutlineColor(sf::Color(0, 0, 0, 100));
        bloques[i].setOutlineThickness(1.0f);
    }
}

void PiezaVisual::configurarPiezaPrueba(float xOrigenTablero, float yOrigenTablero, sf::Color color) {
    int coordenadas[4][2] = {
        {4, 0},
        {3, 1},
        {4, 1},
        {5, 1}
    };
    
    for (int i = 0; i < 4; ++i) {
        bloques[i].setFillColor(color);
        
        float posX = xOrigenTablero + (coordenadas[i][0] * TAMANO_CELDA);
        float posY = yOrigenTablero + (coordenadas[i][1] * TAMANO_CELDA);
        
        bloques[i].setPosition(sf::Vector2f(posX, posY));
    }
}

void PiezaVisual::renderizar(sf::RenderWindow& ventana) {
    for (int i = 0; i < 4; ++i) {
        ventana.draw(bloques[i]);
    }
}
