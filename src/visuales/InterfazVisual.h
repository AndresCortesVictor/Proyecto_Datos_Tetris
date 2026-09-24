#ifndef INTERFAZ_VISUAL_H
#define INTERFAZ_VISUAL_H

#include <SFML/Graphics.hpp>
#include <optional>
#include "PiezaVisual.h"

class InterfazVisual {
private:
    sf::RectangleShape cajaHold;
    sf::RectangleShape cajaNext;
    sf::RectangleShape cajaScore;
    
    sf::Font fuente;
    std::optional<sf::Text> textoHold;
    std::optional<sf::Text> textoNext;
    std::optional<sf::Text> textoScore;

    PiezaVisual piezasNext[3];
    PiezaVisual piezaHold;

public:
    InterfazVisual();
    
    void actualizarPuntaje(int puntos);
    void actualizarNext(TipoPieza t1, TipoPieza t2, TipoPieza t3);
    void actualizarHold(TipoPieza t);
    void renderizar(sf::RenderWindow& ventana);
};

#endif
