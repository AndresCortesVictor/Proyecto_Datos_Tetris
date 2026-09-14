#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include <optional>
#include "../visuales/TableroVisual.h"
#include "../visuales/InterfazVisual.h"
#include "../Estructuras/ColaEventos.h"
#include "../Estructuras/ColaPiezas.h"
#include "Pieza.h"

enum class EstadoJuego {
    Portada,
    Jugando
};

class Juego {
private:
    sf::RenderWindow ventana;
    const unsigned int FPS = 60;
    
    TableroVisual tableroVisual;
    InterfazVisual interfazVisual;

    EstadoJuego estadoActual;
    sf::Font fuente;
    std::optional<sf::Text> titulo;
    std::optional<sf::Text> textoPresionaTecla;
    
    sf::Clock relojPartida;
    ColaEventos colaEventos;
    ColaPiezas colaPiezas;
    Pieza piezaActiva;

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
