#ifndef INTERFAZ_VISUAL_H
#define INTERFAZ_VISUAL_H

#include <SFML/Graphics.hpp>
#include <optional>
#include "PiezaVisual.h"
#include "../Game/TipoPieza.h"

class InterfazVisual {
private:
    sf::RectangleShape cajaHold;
    sf::RectangleShape cajaNext;
    sf::RectangleShape cajaScore;
    
    sf::Font fuente;
    std::optional<sf::Text> textoHold;
    std::optional<sf::Text> textoNext;
    std::optional<sf::Text> textoScore;

    PiezaVisual piezaHold;
    PiezaVisual piezasNext[3];

public:
    InterfazVisual();
    
    void actualizarPuntaje(int puntos);
    void actualizarHold(TipoPieza p);
    void actualizarNext(TipoPieza p1, TipoPieza p2, TipoPieza p3);
    void renderizar(sf::RenderWindow& ventana);
};

#endif
