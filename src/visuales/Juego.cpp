#include "Juego.h"
#include <SFML/Window/Event.hpp>

Juego::Juego() : ventana(sf::VideoMode({800, 600}), "Tetris"),
                 tableroVisual(250.0f, 0.0f) {
    ventana.setFramerateLimit(FPS);
    piezaActual.configurarPiezaPrueba(250.0f, 0.0f, sf::Color::Cyan);
}

void Juego::ejecutar() {
    while (ventana.isOpen()) {
        procesarEventos();
        actualizar();
        renderizar();
    }
}

void Juego::procesarEventos() {
    while (const std::optional<sf::Event> evento = ventana.pollEvent()) {
        if (evento->is<sf::Event::Closed>()) {
            ventana.close();
        }
    }
}

void Juego::actualizar() {
}

void Juego::renderizar() {
    ventana.clear(sf::Color(30, 30, 30));
    tableroVisual.renderizar(ventana);
    piezaActual.renderizar(ventana);
    interfazVisual.renderizar(ventana);
    ventana.display();
}
