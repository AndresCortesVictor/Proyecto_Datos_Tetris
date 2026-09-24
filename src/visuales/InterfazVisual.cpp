#include "InterfazVisual.h"
#include <string>

InterfazVisual::InterfazVisual() {
    cajaHold.setSize(sf::Vector2f(120.0f, 120.0f));
    cajaHold.setPosition(sf::Vector2f(80.0f, 50.0f));
    cajaHold.setFillColor(sf::Color(40, 40, 40));
    cajaHold.setOutlineColor(sf::Color(100, 100, 100));
    cajaHold.setOutlineThickness(2.0f);

    cajaNext.setSize(sf::Vector2f(140.0f, 250.0f));
    cajaNext.setPosition(sf::Vector2f(600.0f, 50.0f));
    cajaNext.setFillColor(sf::Color(40, 40, 40));
    cajaNext.setOutlineColor(sf::Color(100, 100, 100));
    cajaNext.setOutlineThickness(2.0f);

    cajaScore.setSize(sf::Vector2f(160.0f, 60.0f));
    cajaScore.setPosition(sf::Vector2f(580.0f, 320.0f));
    cajaScore.setFillColor(sf::Color(40, 40, 40));
    cajaScore.setOutlineColor(sf::Color(100, 100, 100));
    cajaScore.setOutlineThickness(2.0f);

    if (fuente.openFromFile("assets/arial.ttf")) {
        textoHold.emplace(fuente);
        textoHold->setString("HOLD");
        textoHold->setCharacterSize(20);
        textoHold->setPosition(sf::Vector2f(110.0f, 20.0f));

        textoNext.emplace(fuente);
        textoNext->setString("NEXT");
        textoNext->setCharacterSize(20);
        textoNext->setPosition(sf::Vector2f(630.0f, 20.0f));

        textoScore.emplace(fuente);
        textoScore->setString("SCORE: 0");
        textoScore->setCharacterSize(20);
        textoScore->setPosition(sf::Vector2f(590.0f, 335.0f));
    }
}

void InterfazVisual::actualizarPuntaje(int puntos) {
    if (textoScore) {
        textoScore->setString("SCORE: " + std::to_string(puntos));
    }
}

void InterfazVisual::actualizarNext(TipoPieza t1, TipoPieza t2, TipoPieza t3) {
    piezasNext[0].configurar(t1, 620.0f, 80.0f);
    piezasNext[1].configurar(t2, 620.0f, 150.0f);
    piezasNext[2].configurar(t3, 620.0f, 220.0f);
}

void InterfazVisual::actualizarHold(TipoPieza t) {
    piezaHold.configurar(t, 100.0f, 75.0f);
}

void InterfazVisual::renderizar(sf::RenderWindow& ventana) {
    ventana.draw(cajaHold);
    ventana.draw(cajaNext);
    ventana.draw(cajaScore);
    
    if (textoHold) ventana.draw(*textoHold);
    if (textoNext) ventana.draw(*textoNext);
    if (textoScore) ventana.draw(*textoScore);
    
    piezaHold.renderizar(ventana);
    
    for (int i = 0; i < 3; ++i) {
        piezasNext[i].renderizar(ventana);
    }
}
