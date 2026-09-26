#include "Juego.h"
#include <SFML/Window/Event.hpp>

Juego::Juego() : ventana(sf::VideoMode({800, 600}), "Tetris"),
                 tableroVisual(250.0f, 0.0f),
                 estadoActual(EstadoJuego::Portada),
                 gestorPuntajes("puntajes.txt"),
                 puntajeActual(0) {
    
    ventana.setFramerateLimit(FPS);
    gestorPuntajes.cargarPuntajes();
    
    if (fuente.openFromFile("assets/arial.ttf")) {
        titulo.emplace(fuente);
        titulo->setString("TETRIS");
        titulo->setCharacterSize(80);
        titulo->setPosition(sf::Vector2f(260.0f, 150.0f));
        
        textoPresionaTecla.emplace(fuente);
        textoPresionaTecla->setString("Presiona ENTER para jugar");
        textoPresionaTecla->setCharacterSize(30);
        textoPresionaTecla->setPosition(sf::Vector2f(220.0f, 350.0f));
        
        textoIrPuntajes.emplace(fuente);
        textoIrPuntajes->setString("Presiona P para ver Puntajes");
        textoIrPuntajes->setCharacterSize(20);
        textoIrPuntajes->setPosition(sf::Vector2f(260.0f, 400.0f));
        
        textoTituloPuntajes.emplace(fuente, "MEJORES PUNTAJES", 40);
        textoTituloPuntajes->setPosition(sf::Vector2f(200.0f, 50.0f));
        
        textoInstruccionPuntajes.emplace(fuente, "1: Ordenar (Insercion) | 2: Ordenar (MergeSort) | ESC: Volver", 20);
        textoInstruccionPuntajes->setPosition(sf::Vector2f(120.0f, 100.0f));
        
        for (int i = 0; i < 10; ++i) {
            textosPuntajes[i].emplace(fuente, "", 24);
            textosPuntajes[i]->setPosition(sf::Vector2f(250.0f, 160.0f + (i * 40.0f)));
        }
        
        textoGameOver.emplace(fuente, "GAME OVER", 60);
        textoGameOver->setPosition(sf::Vector2f(230.0f, 200.0f));
        textoGameOver->setFillColor(sf::Color::Red);
        
        textoReintentar.emplace(fuente, "Presiona ENTER para reiniciar o ESC al Menu", 20);
        textoReintentar->setPosition(sf::Vector2f(160.0f, 300.0f));
        
        textoVerReplay.emplace(fuente, "Presiona 'R' para ver el Replay de esta partida", 20);
        textoVerReplay->setPosition(sf::Vector2f(135.0f, 350.0f));

        textoNombre.emplace(fuente, "Ingrese su nombre: ", 20);
        textoNombre->setPosition(sf::Vector2f(300.0f, 200.0f));
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

        if (estadoActual == EstadoJuego::CargaDatos) {
            if (const auto* textEvent = evento->getIf<sf::Event::TextEntered>()) {
                char32_t caracter = textEvent->unicode;
                
                if (caracter == 8) {
                    if (!nombreIngresado.empty()) {
                        nombreIngresado.pop_back();
                    }
                } else if (caracter == 13) {
                    if (!nombreIngresado.empty()) {
                        estadoActual = EstadoJuego::Jugando;
                    }
                } else if (caracter >= 32 && caracter < 128) {
                    if (nombreIngresado.length() < 10) { 
                        nombreIngresado += static_cast<char>(caracter);
                    }
                }
                
                if (textoNombre) {
                    textoNombre->setString("Ingrese su nombre: " + nombreIngresado);
                }
            }
        }
        
        if (evento->is<sf::Event::KeyPressed>()) {
            auto keyPressed = evento->getIf<sf::Event::KeyPressed>();
            if (estadoActual == EstadoJuego::Portada) {
                if (keyPressed->code == sf::Keyboard::Key::Enter) {
                    tablero.vaciar();
                    colaPiezas.vaciar();
                    colaEventos.vaciar();
                    listaReplay.vaciar();
                    while (!pilaHold.estaVacia()) pilaHold.pop();
                    
                    puntajeActual = 0;
                    relojPartida.restart();
                    relojCaida.restart();
                    
                    estadoActual = EstadoJuego::CargaDatos;
                    nombreIngresado = "";
                    if (textoNombre) {
                        textoNombre->setString("Ingrese su nombre: ");
                    }
                    Evento e1 = {TipoEvento::AumentarVelocidad, 20.0f};
                    Evento e2 = {TipoEvento::PiezaEspecial, 45.0f};
                    Evento e3 = {TipoEvento::InvertirControles, 60.0f};
                    colaEventos.encolarOrdenado(e1);
                    colaEventos.encolarOrdenado(e2);
                    colaEventos.encolarOrdenado(e3);
                    
                    piezaActiva = colaPiezas.sacarPieza();
                } else if (keyPressed->code == sf::Keyboard::Key::P) {
                    estadoActual = EstadoJuego::MenuPuntajes;
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
                    if (!tablero.colisiona(piezaActiva, piezaActiva.getX() - 1, piezaActiva.getY())) {
                        guardarSnapshot();
                        piezaActiva.mover(-1, 0);
                    }
                } else if (keyPressed->code == sf::Keyboard::Key::Right) {
                    if (!tablero.colisiona(piezaActiva, piezaActiva.getX() + 1, piezaActiva.getY())) {
                        guardarSnapshot();
                        piezaActiva.mover(1, 0);
                    }
                } else if (keyPressed->code == sf::Keyboard::Key::Down) {
                    if (!tablero.colisiona(piezaActiva, piezaActiva.getX(), piezaActiva.getY() + 1)) {
                        guardarSnapshot();
                        piezaActiva.mover(0, 1);
                        relojCaida.restart();
                    }
                } else if (keyPressed->code == sf::Keyboard::Key::Up) {
                    piezaActiva.rotar();
                    if (tablero.colisiona(piezaActiva, piezaActiva.getX(), piezaActiva.getY())) {
                        piezaActiva.desrotar();
                    } else {
                        piezaActiva.desrotar();
                        guardarSnapshot();
                        piezaActiva.rotar();
                    }
                } else if (keyPressed->code == sf::Keyboard::Key::Space) {
                    guardarSnapshot();
                    while (!tablero.colisiona(piezaActiva, piezaActiva.getX(), piezaActiva.getY() + 1)) {
                        piezaActiva.mover(0, 1);
                    }
                    
                    tablero.fijarPieza(piezaActiva);
                    int lineas = tablero.limpiarLineas();
                    if (lineas > 0) {
                        puntajeActual += (lineas * 100);
                    }
                    
                    piezaActiva = colaPiezas.sacarPieza();
                    
                    if (tablero.colisiona(piezaActiva, piezaActiva.getX(), piezaActiva.getY())) {
                        gestorPuntajes.agregarPuntaje(nombreIngresado, puntajeActual);
                        gestorPuntajes.guardarPuntajes();
                        estadoActual = EstadoJuego::GameOver; 
                    }
                    
                    relojCaida.restart();
                } else if (keyPressed->code == sf::Keyboard::Key::Z) {
                    TipoPieza matrizVieja[20][10];
                    if (listaReplay.deshacer(matrizVieja, piezaActiva, puntajeActual)) {
                        tablero.importarMatriz(matrizVieja);
                        relojCaida.restart();
                    }
                } else if (keyPressed->code == sf::Keyboard::Key::X) {
                    TipoPieza matrizNueva[20][10];
                    if (listaReplay.rehacer(matrizNueva, piezaActiva, puntajeActual)) {
                        tablero.importarMatriz(matrizNueva);
                        relojCaida.restart();
                    }
                }
            } else if (estadoActual == EstadoJuego::MenuPuntajes) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    estadoActual = EstadoJuego::Portada;
                } else if (keyPressed->code == sf::Keyboard::Key::Num1) {
                    gestorPuntajes.ordenarPorInsercion();
                } else if (keyPressed->code == sf::Keyboard::Key::Num2) {
                    gestorPuntajes.ordenarPorMerge();
                }
            } else if (estadoActual == EstadoJuego::GameOver) {
                if (keyPressed->code == sf::Keyboard::Key::Enter) {
                    tablero.vaciar();
                    colaPiezas.vaciar();
                    colaEventos.vaciar();
                    listaReplay.vaciar();
                    while (!pilaHold.estaVacia()) pilaHold.pop();
                    
                    puntajeActual = 0;
                    relojPartida.restart();
                    relojCaida.restart();
                    
                    Evento e1 = {TipoEvento::AumentarVelocidad, 20.0f};
                    Evento e2 = {TipoEvento::PiezaEspecial, 45.0f};
                    Evento e3 = {TipoEvento::InvertirControles, 60.0f};
                    colaEventos.encolarOrdenado(e1);
                    colaEventos.encolarOrdenado(e2);
                    colaEventos.encolarOrdenado(e3);
                    
                    piezaActiva = colaPiezas.sacarPieza();
                    estadoActual = EstadoJuego::Jugando;
                } else if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    estadoActual = EstadoJuego::Portada;
                } else if (keyPressed->code == sf::Keyboard::Key::R) {
                    TipoPieza matrizVieja[20][10];
                    if (listaReplay.iniciarReplay(matrizVieja, piezaActiva, puntajeActual)) {
                        tablero.importarMatriz(matrizVieja);
                        estadoActual = EstadoJuego::Replay;
                        relojCaida.restart();
                    }
                }
            } else if (estadoActual == EstadoJuego::Replay) {
                if (keyPressed->code == sf::Keyboard::Key::Escape) {
                    estadoActual = EstadoJuego::GameOver;
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
        
        interfazVisual.actualizarPuntaje(puntajeActual);

        // Gravedad
        if (relojCaida.getElapsedTime().asSeconds() > 0.5f) {
            guardarSnapshot();
            if (!tablero.colisiona(piezaActiva, piezaActiva.getX(), piezaActiva.getY() + 1)) {
                piezaActiva.mover(0, 1);
            } else {
                tablero.fijarPieza(piezaActiva);
                int lineas = tablero.limpiarLineas();
                if (lineas > 0) {
                    puntajeActual += (lineas * 100);
                }
                
                piezaActiva = colaPiezas.sacarPieza();
                
                if (tablero.colisiona(piezaActiva, piezaActiva.getX(), piezaActiva.getY())) {
                    gestorPuntajes.agregarPuntaje(nombreIngresado, puntajeActual);
                    gestorPuntajes.guardarPuntajes();
                    estadoActual = EstadoJuego::GameOver;
                }
            }
            relojCaida.restart();
        }
    } else if (estadoActual == EstadoJuego::Replay) {
        if (relojCaida.getElapsedTime().asSeconds() > 0.1f) {
            TipoPieza matrizVieja[20][10];
            if (listaReplay.avanzarReplay(matrizVieja, piezaActiva, puntajeActual)) {
                tablero.importarMatriz(matrizVieja);
            } else {
                estadoActual = EstadoJuego::GameOver;
            }
            relojCaida.restart();
        }
    }
}

void Juego::renderizar() {
    ventana.clear(sf::Color(30, 30, 30));
    
    if (estadoActual == EstadoJuego::Portada) {
        renderizarPortada();
    } else if (estadoActual == EstadoJuego::MenuPuntajes) {
        renderizarMenuPuntajes();
    } else if (estadoActual == EstadoJuego::Jugando) {
        renderizarJuego();
    } else if (estadoActual == EstadoJuego::GameOver) {
        renderizarGameOver();
    } else if (estadoActual == EstadoJuego::CargaDatos){
        renderizarCargaDatos();
    } else if (estadoActual == EstadoJuego::Replay) {
        renderizarJuego();
    }
    
    ventana.display();
}

void Juego::renderizarPortada() {
    if (titulo) {
        ventana.draw(*titulo);
    }
    if (textoIrPuntajes) {
        ventana.draw(*textoIrPuntajes);
    }
    if (textoPresionaTecla) {
        ventana.draw(*textoPresionaTecla);
    }
}

void Juego::renderizarMenuPuntajes() {
    if (textoTituloPuntajes) {
        ventana.draw(*textoTituloPuntajes);
    }
    if (textoInstruccionPuntajes) {
        ventana.draw(*textoInstruccionPuntajes);
    }

    NodoPuntaje* actual = gestorPuntajes.getLista();
    int contador = 0; // Para el arreglo (0 a 9)
    
    while (actual != nullptr && contador < 10) {
        std::string linea = std::to_string(contador + 1) + ". " + actual->dato.nombre + " - " + std::to_string(actual->dato.puntos);
        
        if (textosPuntajes[contador]) {
            textosPuntajes[contador]->setString(linea);
            ventana.draw(*textosPuntajes[contador]);
        }
        
        actual = actual->siguiente;
        contador++;
    }
}

void Juego::renderizarJuego() {
    tableroVisual.renderizar(ventana, tablero);
    piezaActiva.dibujar(ventana);
    interfazVisual.renderizar(ventana);
}

void Juego::renderizarGameOver() {
    if (textoGameOver) {
        ventana.draw(*textoGameOver);
    }
    if (textoReintentar) {
        ventana.draw(*textoReintentar);
    }
    if (textoVerReplay) {
        ventana.draw(*textoVerReplay);
    }
}

void Juego::renderizarCargaDatos(){
    if (textoNombre){
        ventana.draw(*textoNombre);
    }
}
void Juego::guardarSnapshot() {
    TipoPieza estado[20][10];
    tablero.exportarMatriz(estado);
    listaReplay.guardarEstado(estado, piezaActiva, puntajeActual);
}
