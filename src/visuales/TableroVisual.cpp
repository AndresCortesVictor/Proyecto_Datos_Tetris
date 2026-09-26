#include "TableroVisual.h"

TableroVisual::TableroVisual(float x, float y) : posicionOrigen(x, y) {
    celdaFondo.setSize(sf::Vector2f(TAMANO_CELDA - 1.0f, TAMANO_CELDA - 1.0f)); 
    celdaFondo.setFillColor(sf::Color(50, 50, 50));
    celdaFondo.setOutlineColor(sf::Color(30, 30, 30));
    celdaFondo.setOutlineThickness(1.0f);

    celdaOcupada.setSize(sf::Vector2f(TAMANO_CELDA - 1.0f, TAMANO_CELDA - 1.0f));
    celdaOcupada.setFillColor(sf::Color::White);

    // TRATAR DE CORREGIR ESTO DE LAS CELDAS OCUPADAS
}

void TableroVisual::renderizar(sf::RenderWindow& ventana, const ListaTablero& tableroLogico) {
    for (int fila = 0; fila < FILAS; ++fila) {
        for (int col = 0; col < COLUMNAS; ++col) {
            float posX = posicionOrigen.x + (col * TAMANO_CELDA);
            float posY = posicionOrigen.y + (fila * TAMANO_CELDA);
            
            TipoPieza tipo = tableroLogico.obtenerCelda(fila, col);
            
            if (tipo != TipoPieza::Ninguna) {
                sf::Color color;
                switch (tipo) {
                    case TipoPieza::I: color = sf::Color::Cyan; break;
                    case TipoPieza::O: color = sf::Color::Yellow; break;
                    case TipoPieza::T: color = sf::Color(128, 0, 128); break;
                    case TipoPieza::S: color = sf::Color::Green; break;
                    case TipoPieza::Z: color = sf::Color::Red; break;
                    case TipoPieza::J: color = sf::Color::Blue; break;
                    case TipoPieza::L: color = sf::Color(255, 165, 0); break;
                    default: color = sf::Color::White; break;
                }
                celdaOcupada.setFillColor(color);
                celdaOcupada.setPosition(sf::Vector2f(posX, posY));
                ventana.draw(celdaOcupada);
            } else {
                celdaFondo.setPosition(sf::Vector2f(posX, posY));
                ventana.draw(celdaFondo);
            }
        }
    }
}
