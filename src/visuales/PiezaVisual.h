#ifndef PIEZA_VISUAL_H
#define PIEZA_VISUAL_H

#include <SFML/Graphics.hpp>
#include "../Game/TipoPieza.h"

class PiezaVisual {
private:
    sf::RectangleShape bloques[4];
    static constexpr float TAMANO_CELDA = 30.0f;
    static constexpr float ORIGEN_X = 250.0f;
    static constexpr float ORIGEN_Y = 0.0f;

public:
    PiezaVisual();
    void configurar(TipoPieza tipo, int gridX, int gridY);
    void renderizar(sf::RenderWindow& ventana);
};

#endif
