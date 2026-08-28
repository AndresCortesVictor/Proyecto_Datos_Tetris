#ifndef INTERFAZ_VISUAL_H
#define INTERFAZ_VISUAL_H

#include <SFML/Graphics.hpp>

class InterfazVisual {
private:
    sf::RectangleShape cajaHold;
    sf::RectangleShape cajaNext;
    sf::RectangleShape cajaScore;
    
    sf::Font fuente;
    sf::Text textoHold;
    sf::Text textoNext;
    sf::Text textoScore;
    
    bool fuenteCargada;

public:
    InterfazVisual();
    
    void actualizarPuntaje(int puntos);
    void renderizar(sf::RenderWindow& ventana);
};

#endif
