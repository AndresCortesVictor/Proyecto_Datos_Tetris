#ifndef PIEZA_VISUAL_H
#define PIEZA_VISUAL_H

#include <SFML/Graphics.hpp>
#include "../Game/TipoPieza.h"

class PiezaVisual {
private:
    sf::RectangleShape bloques[4];
    static constexpr float TAMANO_CELDA = 30.0f;

public:
    PiezaVisual();
    void configurar(TipoPieza tipo, float offsetX, float offsetY, float gridX = 0, float gridY = 0);
    void renderizar(sf::RenderWindow& ventana);
};

#endif
