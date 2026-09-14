#include "ColaPiezas.h"
#include <algorithm>
#include <random>
#include <chrono>

ColaPiezas::ColaPiezas() : frente(nullptr), final(nullptr), cantidad(0) {
    insertarBolsa(generarBolsa());
}

ColaPiezas::~ColaPiezas() {
    while (frente != nullptr) {
        NodoPieza* temp = frente;
        frente = frente->siguiente;
        delete temp;
    }
}

std::vector<Pieza> ColaPiezas::generarBolsa() {
    std::vector<Pieza> bolsa = {
        {TipoPieza::I}, {TipoPieza::O}, {TipoPieza::T},
        {TipoPieza::S}, {TipoPieza::Z}, {TipoPieza::J}, {TipoPieza::L}
    };
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(bolsa.begin(), bolsa.end(), std::default_random_engine(seed));
    
    return bolsa;
}

void ColaPiezas::insertarBolsa(const std::vector<Pieza>& bolsa) {
    for (const auto& p : bolsa) {
        NodoPieza* nuevo = new NodoPieza(p);
        if (frente == nullptr) {
            frente = nuevo;
            final = nuevo;
        } else {
            final->siguiente = nuevo;
            final = nuevo;
        }
        cantidad++;
    }
}

Pieza ColaPiezas::sacarPieza() {
    if (frente == nullptr) {
        return Pieza{TipoPieza::Ninguna};
    }
    
    NodoPieza* temp = frente;
    Pieza p = temp->dato;
    frente = frente->siguiente;
    
    if (frente == nullptr) {
        final = nullptr;
    }
    temp->siguiente = nullptr;
    delete temp;
    cantidad--;
    
    if (cantidad <= 3) {
        insertarBolsa(generarBolsa());
    }
    
    return p;
}

Pieza ColaPiezas::verDentro(int posicion) const {
    if (posicion < 0 || posicion >= cantidad || frente == nullptr) {
        return Pieza{TipoPieza::Ninguna};
    }
    
    NodoPieza* actual = frente;
    for (int i = 0; i < posicion; ++i) {
        actual = actual->siguiente;
    }
    return actual->dato;
}

bool ColaPiezas::estaVacia() const {
    return frente == nullptr;
}
