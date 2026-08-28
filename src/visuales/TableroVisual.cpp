#include "TableroVisual.h"

TableroVisual::TableroVisual(float x, float y) : posicionOrigen(x, y) {
    celdaFondo.setSize(sf::Vector2f(TAMANO_CELDA - 1.0f, TAMANO_CELDA - 1.0f)); 
    celdaFondo.setFillColor(sf::Color(50, 50, 50));
    celdaFondo.setOutlineColor(sf::Color(30, 30, 30));
    celdaFondo.setOutlineThickness(1.0f);

    celdaOcupada.setSize(sf::Vector2f(TAMANO_CELDA - 1.0f, TAMANO_CELDA - 1.0f));
    celdaOcupada.setFillColor(sf::Color::White);
}

void TableroVisual::renderizar(sf::RenderWindow& ventana) {
    for (int fila = 0; fila < FILAS; ++fila) {
        for (int col = 0; col < COLUMNAS; ++col) {
            float posX = posicionOrigen.x + (col * TAMANO_CELDA);
            float posY = posicionOrigen.y + (fila * TAMANO_CELDA);
            
            bool estaOcupada = false; 
            
            if (estaOcupada) {
                celdaOcupada.setPosition(sf::Vector2f(posX, posY));
                ventana.draw(celdaOcupada);
            } else {
                celdaFondo.setPosition(sf::Vector2f(posX, posY));
                ventana.draw(celdaFondo);
            }
        }
    }
}
