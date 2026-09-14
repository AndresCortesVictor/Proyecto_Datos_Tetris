#include "Juego.h"
#include <SFML/Window/Event.hpp>

Juego::Juego() : ventana(sf::VideoMode({800, 600}), "Tetris"),
                 tableroVisual(250.0f, 0.0f),
                 estadoActual(EstadoJuego::Portada) {
    
    ventana.setFramerateLimit(FPS);
    
    if (fuente.openFromFile("assets/arial.ttf")) {
        titulo.emplace(fuente);
        titulo->setString("TETRIS");
        titulo->setCharacterSize(80);
        titulo->setPosition(sf::Vector2f(260.0f, 150.0f));
        
        textoPresionaTecla.emplace(fuente);
        textoPresionaTecla->setString("Presiona ENTER para jugar");
        textoPresionaTecla->setCharacterSize(30);
        textoPresionaTecla->setPosition(sf::Vector2f(220.0f, 350.0f));
    }
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
        
        if (evento->is<sf::Event::KeyPressed>()) {
            auto keyPressed = evento->getIf<sf::Event::KeyPressed>();
            if (estadoActual == EstadoJuego::Portada) {
                if (keyPressed->code == sf::Keyboard::Key::Enter) {
                    estadoActual = EstadoJuego::Jugando;
                    relojPartida.restart();
                    
                    Evento e1 = {TipoEvento::AumentarVelocidad, 20.0f};
                    Evento e2 = {TipoEvento::PiezaEspecial, 45.0f};
                    Evento e3 = {TipoEvento::InvertirControles, 60.0f};
                    colaEventos.encolarOrdenado(e1);
                    colaEventos.encolarOrdenado(e2);
                    colaEventos.encolarOrdenado(e3);
                    
                    piezaActiva = colaPiezas.sacarPieza();
                }
            }
        }
    }
}

void Juego::actualizar() {
    if (estadoActual == EstadoJuego::Jugando) {
        float tiempoActual = relojPartida.getElapsedTime().asSeconds();
        
        if (!colaEventos.estaVacia()) {
            Evento siguienteEvento = colaEventos.verFrente();
            if (tiempoActual >= siguienteEvento.tiempoDisparo) {
                Evento eventoEjecutar = colaEventos.desencolarEvento(tiempoActual);
                
                if (eventoEjecutar.tipo == TipoEvento::AumentarVelocidad) {
                    
                } else if (eventoEjecutar.tipo == TipoEvento::PiezaEspecial) {
                    
                } else if (eventoEjecutar.tipo == TipoEvento::InvertirControles) {
                    
                }
            }
        }
    }
}

void Juego::renderizar() {
    ventana.clear(sf::Color(30, 30, 30));
    
    if (estadoActual == EstadoJuego::Portada) {
        renderizarPortada();
    } else if (estadoActual == EstadoJuego::Jugando) {
        renderizarJuego();
    }
    
    ventana.display();
}

void Juego::renderizarPortada() {
    if (titulo) {
        ventana.draw(*titulo);
    }
    if (textoPresionaTecla) {
        ventana.draw(*textoPresionaTecla);
    }
}

void Juego::renderizarJuego() {
    tableroVisual.renderizar(ventana);
    piezaActiva.dibujar(ventana);
    interfazVisual.renderizar(ventana);
}
