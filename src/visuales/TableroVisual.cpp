#include "TableroVisual.h"
#include "../Estructuras/ListaTablero.h"

TableroVisual::TableroVisual() {
    fondo.setSize(sf::Vector2f(COLUMNAS * TAMANO_CELDA, FILAS * TAMANO_CELDA));
    fondo.setPosition(sf::Vector2f(250.0f, 0.0f));
    fondo.setFillColor(sf::Color(20, 20, 20));

    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            celdasVacias[i][j].setSize(sf::Vector2f(TAMANO_CELDA - 1.0f, TAMANO_CELDA - 1.0f));
            celdasVacias[i][j].setPosition(sf::Vector2f(250.0f + j * TAMANO_CELDA, i * TAMANO_CELDA));
            celdasVacias[i][j].setFillColor(sf::Color(30, 30, 30));
            celdasVacias[i][j].setOutlineColor(sf::Color(50, 50, 50));
            celdasVacias[i][j].setOutlineThickness(1.0f);
        }
    }

    bloqueLleno.setSize(sf::Vector2f(TAMANO_CELDA - 1.0f, TAMANO_CELDA - 1.0f));
    bloqueLleno.setOutlineColor(sf::Color(0, 0, 0, 100));
    bloqueLleno.setOutlineThickness(1.0f);
}

sf::Color TableroVisual::getColorDeTipo(TipoPieza tipo) const {
    switch (tipo) {
        case TipoPieza::I: return sf::Color::Cyan;
        case TipoPieza::O: return sf::Color::Yellow;
        case TipoPieza::T: return sf::Color::Magenta;
        case TipoPieza::S: return sf::Color::Green;
        case TipoPieza::Z: return sf::Color::Red;
        case TipoPieza::J: return sf::Color::Blue;
        case TipoPieza::L: return sf::Color(255, 165, 0);
        default: return sf::Color::Transparent;
    }
}

void TableroVisual::renderizar(sf::RenderWindow& ventana, const ListaTablero& tableroLogico) {
    ventana.draw(fondo);
    for (int i = 0; i < FILAS; ++i) {
        for (int j = 0; j < COLUMNAS; ++j) {
            ventana.draw(celdasVacias[i][j]);

            TipoPieza celdaLogica = tableroLogico.obtenerCelda(i, j);
            if (celdaLogica != TipoPieza::Ninguna) {
                bloqueLleno.setFillColor(getColorDeTipo(celdaLogica));
                bloqueLleno.setPosition(sf::Vector2f(250.0f + j * TAMANO_CELDA, i * TAMANO_CELDA));
                ventana.draw(bloqueLleno);
            }
        }
    }
}
