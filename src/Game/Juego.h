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
#include "../Estructuras/ListaTablero.h"
#include "Pieza.h"

enum class EstadoJuego {
    Portada,
    Jugando,
    MenuPuntajes,
    GameOver
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
    
    std::optional<sf::Text> textoGameOver;
    std::optional<sf::Text> textoReintentar;
    
    sf::Clock relojPartida;
    sf::Clock relojCaida;
    ColaEventos colaEventos;
    ColaPiezas colaPiezas;
    PilaHold pilaHold;
    GestorPuntajes gestorPuntajes;
    ListaTablero tablero;
    Pieza piezaActiva;
    int puntajeActual;

    void procesarEventos();
    void actualizar();
    void renderizar();
    void renderizarPortada();
    void renderizarMenuPuntajes();
    void renderizarJuego();
    void renderizarGameOver();

public:
    Juego();
    void ejecutar();
};

#endif
