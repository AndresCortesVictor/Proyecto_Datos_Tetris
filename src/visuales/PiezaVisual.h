#ifndef PIEZA_VISUAL_H
#define PIEZA_VISUAL_H

#include <SFML/Graphics.hpp>

class PiezaVisual {
private:
    sf::RectangleShape bloques[4];
    const float TAMANO_CELDA = 30.0f;

public:
    PiezaVisual();
    void configurarPiezaPrueba(float xOrigenTablero, float yOrigenTablero, sf::Color color);
    void renderizar(sf::RenderWindow& ventana);
};

#endif
