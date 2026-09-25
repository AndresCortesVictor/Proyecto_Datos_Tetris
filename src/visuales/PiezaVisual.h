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
    void configurar(TipoPieza tipo, float offsetX, float offsetY, int gridX = 0, int gridY = 0, float escala = 1.0f);
    void renderizar(sf::RenderWindow& ventana);
};

#endif
