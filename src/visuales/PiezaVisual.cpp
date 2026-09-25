#include "PiezaVisual.h"

PiezaVisual::PiezaVisual() {
    for (int i = 0; i < 4; ++i) {
        bloques[i].setSize(sf::Vector2f(TAMANO_CELDA - 1.0f, TAMANO_CELDA - 1.0f));
        bloques[i].setOutlineColor(sf::Color(0, 0, 0, 100));
        bloques[i].setOutlineThickness(1.0f);
    }
}

void PiezaVisual::configurar(TipoPieza tipo, float offsetX, float offsetY, int gridX, int gridY, float escala) {
    int coordenadas[4][2] = {0};
    sf::Color color;

    switch (tipo) {
        case TipoPieza::I:
            coordenadas[0][0] = 0; coordenadas[0][1] = 1;
            coordenadas[1][0] = 1; coordenadas[1][1] = 1;
            coordenadas[2][0] = 2; coordenadas[2][1] = 1;
            coordenadas[3][0] = 3; coordenadas[3][1] = 1;
            color = sf::Color::Cyan;
            break;
        case TipoPieza::O:
            coordenadas[0][0] = 1; coordenadas[0][1] = 0;
            coordenadas[1][0] = 2; coordenadas[1][1] = 0;
            coordenadas[2][0] = 1; coordenadas[2][1] = 1;
            coordenadas[3][0] = 2; coordenadas[3][1] = 1;
            color = sf::Color::Yellow;
            break;
        case TipoPieza::T:
            coordenadas[0][0] = 1; coordenadas[0][1] = 0;
            coordenadas[1][0] = 0; coordenadas[1][1] = 1;
            coordenadas[2][0] = 1; coordenadas[2][1] = 1;
            coordenadas[3][0] = 2; coordenadas[3][1] = 1;
            color = sf::Color::Magenta;
            break;
        case TipoPieza::S:
            coordenadas[0][0] = 1; coordenadas[0][1] = 0;
            coordenadas[1][0] = 2; coordenadas[1][1] = 0;
            coordenadas[2][0] = 0; coordenadas[2][1] = 1;
            coordenadas[3][0] = 1; coordenadas[3][1] = 1;
            color = sf::Color::Green;
            break;
        case TipoPieza::Z:
            coordenadas[0][0] = 0; coordenadas[0][1] = 0;
            coordenadas[1][0] = 1; coordenadas[1][1] = 0;
            coordenadas[2][0] = 1; coordenadas[2][1] = 1;
            coordenadas[3][0] = 2; coordenadas[3][1] = 1;
            color = sf::Color::Red;
            break;
        case TipoPieza::J:
            coordenadas[0][0] = 0; coordenadas[0][1] = 0;
            coordenadas[1][0] = 0; coordenadas[1][1] = 1;
            coordenadas[2][0] = 1; coordenadas[2][1] = 1;
            coordenadas[3][0] = 2; coordenadas[3][1] = 1;
            color = sf::Color::Blue;
            break;
        case TipoPieza::L:
            coordenadas[0][0] = 2; coordenadas[0][1] = 0;
            coordenadas[1][0] = 0; coordenadas[1][1] = 1;
            coordenadas[2][0] = 1; coordenadas[2][1] = 1;
            coordenadas[3][0] = 2; coordenadas[3][1] = 1;
            color = sf::Color(255, 165, 0);
            break;
        default:
            color = sf::Color::Transparent;
            break;
    }

    float tamanoEscalado = TAMANO_CELDA * escala;
    for (int i = 0; i < 4; ++i) {
        bloques[i].setSize(sf::Vector2f(tamanoEscalado - 1.0f, tamanoEscalado - 1.0f));
        bloques[i].setFillColor(color);
        float px = offsetX + ((gridX + coordenadas[i][0]) * tamanoEscalado);
        float py = offsetY + ((gridY + coordenadas[i][1]) * tamanoEscalado);
        bloques[i].setPosition(sf::Vector2f(px, py));
    }
}

void PiezaVisual::renderizar(sf::RenderWindow& ventana) {
    for (int i = 0; i < 4; ++i) {
        ventana.draw(bloques[i]);
    }
}
