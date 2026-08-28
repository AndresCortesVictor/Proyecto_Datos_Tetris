#ifndef JUEGO_H
#define JUEGO_H

#include <SFML/Graphics.hpp>
#include "TableroVisual.h"
#include "PiezaVisual.h"
#include "InterfazVisual.h"

class Juego {
private:
    sf::RenderWindow ventana;
    const unsigned int FPS = 60;
    
    TableroVisual tableroVisual;
    PiezaVisual piezaActual;
    InterfazVisual interfazVisual;

    void procesarEventos();
    void actualizar();
    void renderizar();

public:
    Juego();
    void ejecutar();
};

#endif
