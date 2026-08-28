#ifndef TABLERO_VISUAL_H
#define TABLERO_VISUAL_H

#include <SFML/Graphics.hpp>

class TableroVisual {
private:
    const int FILAS = 20;
    const int COLUMNAS = 10;
    const float TAMANO_CELDA = 30.0f;
    
    sf::Vector2f posicionOrigen;
    sf::RectangleShape celdaFondo;
    sf::RectangleShape celdaOcupada;

public:
    TableroVisual(float x, float y);
    void renderizar(sf::RenderWindow& ventana);
};

#endif
