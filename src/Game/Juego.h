#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include <optional>
#include "../visuales/TableroVisual.h"
#include "../visuales/InterfazVisual.h"
#include "../Estructuras/ColaEventos.h"
#include "../Estructuras/ColaPiezas.h"
#include "../Estructuras/PilaHold.h"
#include "../Estructuras/GestorPuntajes.h"
#include "Pieza.h"

enum class EstadoJuego {
    Portada,
    Jugando,
    MenuPuntajes
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
    std::optional<sf::Text> textoIrPuntajes;
    
    std::optional<sf::Text> textoTituloPuntajes;
    std::optional<sf::Text> textoInstruccionPuntajes;
    std::optional<sf::Text> textosPuntajes[10];
    
    sf::Clock relojPartida;
    ColaEventos colaEventos;
    ColaPiezas colaPiezas;
    PilaHold pilaHold;
    GestorPuntajes gestorPuntajes;
    Pieza piezaActiva;

    void procesarEventos();
    void actualizar();
    void renderizar();
    void renderizarPortada();
    void renderizarMenuPuntajes();
    void renderizarJuego();

public:
    Juego();
    void ejecutar();
};

#endif
