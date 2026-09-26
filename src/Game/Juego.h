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
#include "../Estructuras/ListaDobleReplay.h"
#include "Pieza.h"

using namespace std;

enum class EstadoJuego {
    Portada,
    Jugando,
    MenuPuntajes,
    GameOver,
    CargaDatos,
    Replay,
    Pausa
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
    std::optional<sf::Text> textoVerReplay;
    std::optional<sf::Text> textoAvisoEvento;
    
    std::optional<sf::Text> textoNombre;
    
    sf::RectangleShape fondoPausa;
    std::optional<sf::Text> textoPausaTitulo;
    std::optional<sf::Text> textoPausaContinuar;
    std::optional<sf::Text> textoPausaSalir;
    
    float finVelocidad = 0.0f;
    float finInvertidos = 0.0f;
    float finAviso = 0.0f;
    
    sf::Clock relojPartida;
    sf::Clock relojCaida;
    sf::Clock relojPausa;
    float tiempoOffset = 0.0f;
    ColaEventos colaEventos;
    ColaPiezas colaPiezas;
    PilaHold pilaHold;
    GestorPuntajes gestorPuntajes;
    ListaDobleReplay listaReplay;
    ListaTablero tablero;
    Pieza piezaActiva;
    int puntajeActual;
    string nombreIngresado;

    void procesarEventos();
    void actualizar();
    void renderizar();
    void renderizarPortada();
    void renderizarMenuPuntajes();
    void renderizarJuego();
    void renderizarGameOver();
    void renderizarCargaDatos();
    void renderizarPausa();
    
    void guardarSnapshot();

public:
    Juego();
    void ejecutar();
};

#endif
