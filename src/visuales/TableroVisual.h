#ifndef TABLERO_VISUAL_H
#define TABLERO_VISUAL_H

#include <SFML/Graphics.hpp>
#include "../Game/TipoPieza.h"

class ListaTablero;

class TableroVisual {
private:
    sf::RectangleShape fondo;
    sf::RectangleShape celdasVacias[20][10];
    sf::RectangleShape bloqueLleno;
    
    static constexpr int FILAS = 20;
    static constexpr int COLUMNAS = 10;
    static constexpr float TAMANO_CELDA = 30.0f;

public:
    TableroVisual();
    sf::Color getColorDeTipo(TipoPieza tipo) const;
    void renderizar(sf::RenderWindow& ventana, const ListaTablero& tableroLogico);
};

#endif
