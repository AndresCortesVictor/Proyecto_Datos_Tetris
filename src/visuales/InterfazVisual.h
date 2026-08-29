#ifndef INTERFAZ_VISUAL_H
#define INTERFAZ_VISUAL_H

#include <SFML/Graphics.hpp>
#include <optional>

class InterfazVisual {
private:
    sf::RectangleShape cajaHold;
    sf::RectangleShape cajaNext;
    sf::RectangleShape cajaScore;
    
    sf::Font fuente;
    std::optional<sf::Text> textoHold;
    std::optional<sf::Text> textoNext;
    std::optional<sf::Text> textoScore;

public:
    InterfazVisual();
    
    void actualizarPuntaje(int puntos);
    void renderizar(sf::RenderWindow& ventana);
};

#endif
