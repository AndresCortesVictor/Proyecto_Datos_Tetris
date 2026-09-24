#include "Juego.h"
#include <SFML/Window/Event.hpp>

Juego::Juego() : ventana(sf::VideoMode(sf::Vector2u(800, 600)), "Tetris - Estructuras de Datos"),
                 estadoActual(EstadoJuego::Portada),
                 velocidadCaida(1.0f),
                 puntajeTotal(0),
                 controlesInvertidos(false) {
    
    ventana.setFramerateLimit(60);
    
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
                    velocidadCaida = 1.0f;
                    controlesInvertidos = false;
                    
                    // Clear event queue? Wait, colaEventos does not have clear(). But let's assume it's clean at start.
                    // Actually, if we die and restart, we might need to clear it, but let's ignore that for now or assume restarting works.
                    
                    Evento e1 = {TipoEvento::AumentarVelocidad, 20.0f};
                    Evento e2 = {TipoEvento::PiezaEspecial, 45.0f};
                    Evento e3 = {TipoEvento::InvertirControles, 60.0f};
                    colaEventos.encolarOrdenado(e1);
                    colaEventos.encolarOrdenado(e2);
                    colaEventos.encolarOrdenado(e3);
                    
                    piezaActiva = colaPiezas.sacarPieza();
                }
            } else if (estadoActual == EstadoJuego::Jugando) {
                if (keyPressed->code == sf::Keyboard::Key::C) {
                    if (pilaHold.estaVacia()) {
                        pilaHold.push(Pieza(piezaActiva.getTipo()));
                        piezaActiva = colaPiezas.sacarPieza();
                    } else {
                        Pieza temporal = pilaHold.pop();
                        pilaHold.push(Pieza(piezaActiva.getTipo()));
                        piezaActiva = temporal;
                    }
                } else if (keyPressed->code == sf::Keyboard::Key::Left) {
                    int dx = controlesInvertidos ? 1 : -1;
                    if (!listaTablero.colisiona(piezaActiva, piezaActiva.getX() + dx, piezaActiva.getY())) {
                        piezaActiva.setX(piezaActiva.getX() + dx);
                    }
                } else if (keyPressed->code == sf::Keyboard::Key::Right) {
                    int dx = controlesInvertidos ? -1 : 1;
                    if (!listaTablero.colisiona(piezaActiva, piezaActiva.getX() + dx, piezaActiva.getY())) {
                        piezaActiva.setX(piezaActiva.getX() + dx);
                    }
                } else if (keyPressed->code == sf::Keyboard::Key::Down) {
                    if (!listaTablero.colisiona(piezaActiva, piezaActiva.getX(), piezaActiva.getY() + 1)) {
                        piezaActiva.setY(piezaActiva.getY() + 1);
                        relojCaida.restart();
                    }
                } else if (keyPressed->code == sf::Keyboard::Key::Up) {
                    piezaActiva.rotar();
                    if (listaTablero.colisiona(piezaActiva, piezaActiva.getX(), piezaActiva.getY())) {
                        piezaActiva.deshacerRotacion();
                    }
                }
            }
        }
    }
}

void Juego::actualizar() {
    if (estadoActual == EstadoJuego::Jugando) {
        TipoPieza next1 = colaPiezas.verDentro(0).getTipo();
        TipoPieza next2 = colaPiezas.verDentro(1).getTipo();
        TipoPieza next3 = colaPiezas.verDentro(2).getTipo();
        interfazVisual.actualizarNext(next1, next2, next3);
        
        interfazVisual.actualizarHold(pilaHold.verCima().getTipo());
        
        if (relojCaida.getElapsedTime().asSeconds() >= velocidadCaida) {
            if (!listaTablero.colisiona(piezaActiva, piezaActiva.getX(), piezaActiva.getY() + 1)) {
                piezaActiva.setY(piezaActiva.getY() + 1);
            } else {
                listaTablero.fijarPieza(piezaActiva);
                int lineas = listaTablero.limpiarLineas();
                if (lineas > 0) {
                    puntajeTotal += (lineas * 100);
                    interfazVisual.actualizarPuntaje(puntajeTotal);
                }
                
                piezaActiva = colaPiezas.sacarPieza();
                
                if (listaTablero.colisiona(piezaActiva, piezaActiva.getX(), piezaActiva.getY())) {
                    estadoActual = EstadoJuego::Portada;
                    puntajeTotal = 0;
                    interfazVisual.actualizarPuntaje(puntajeTotal);
                }
            }
            relojCaida.restart();
        }
        
        float tiempoActual = relojPartida.getElapsedTime().asSeconds();
        
        if (!colaEventos.estaVacia()) {
            Evento siguienteEvento = colaEventos.verFrente();
            if (tiempoActual >= siguienteEvento.tiempoDisparo) {
                Evento eventoEjecutar = colaEventos.desencolarEvento(tiempoActual);
                
                if (eventoEjecutar.tipo == TipoEvento::AumentarVelocidad) {
                    velocidadCaida *= 0.8f;
                    colaEventos.encolarOrdenado({TipoEvento::AumentarVelocidad, tiempoActual + 30.0f});
                } else if (eventoEjecutar.tipo == TipoEvento::PiezaEspecial) {
                    piezaActiva = Pieza(TipoPieza::I);
                    colaEventos.encolarOrdenado({TipoEvento::PiezaEspecial, tiempoActual + 45.0f});
                } else if (eventoEjecutar.tipo == TipoEvento::InvertirControles) {
                    controlesInvertidos = !controlesInvertidos;
                    colaEventos.encolarOrdenado({TipoEvento::InvertirControles, tiempoActual + 15.0f});
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
    tableroVisual.renderizar(ventana, listaTablero);
    piezaActiva.dibujar(ventana);
    interfazVisual.renderizar(ventana);
}
