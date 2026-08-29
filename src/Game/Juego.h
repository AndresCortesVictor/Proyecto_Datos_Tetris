#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include <optional>
#include "../visuales/TableroVisual.h"
#include "../visuales/PiezaVisual.h"
#include "../visuales/InterfazVisual.h"
#include "../Estructuras/ColaEventos.h"

enum class EstadoJuego {
    Portada,
    Jugando
};

class Juego {
private:
    sf::RenderWindow ventana;
    const unsigned int FPS = 60;
    
    TableroVisual tableroVisual;
    PiezaVisual piezaActual;
    InterfazVisual interfazVisual;

    EstadoJuego estadoActual;
    sf::Font fuente;
    std::optional<sf::Text> titulo;
    std::optional<sf::Text> textoPresionaTecla;
    
    sf::Clock relojPartida;
    ColaEventos colaEventos;

    void procesarEventos();
    void actualizar();
    void renderizar();
    void renderizarPortada();
    void renderizarJuego();

public:
    Juego();
    void ejecutar();
};

#endif
