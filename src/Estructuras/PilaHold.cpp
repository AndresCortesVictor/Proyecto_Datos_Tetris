#include "PilaHold.h"

PilaHold::PilaHold() : cima(nullptr) {
}

PilaHold::~PilaHold() {
    if (cima != nullptr) {
        delete cima;
    }
}

void PilaHold::push(Pieza p) {
    if (cima != nullptr) {
        delete cima;
    }
    cima = new NodoPila(p);
}

Pieza PilaHold::pop() {
    if (cima == nullptr) {
        return Pieza(TipoPieza::Ninguna);
    }
    Pieza p = cima->dato;
    delete cima;
    cima = nullptr;
    return p;
}

Pieza PilaHold::verCima() const {
    if (cima != nullptr) {
        return cima->dato;
    }
    return Pieza(TipoPieza::Ninguna);
}

bool PilaHold::estaVacia() const {
    return cima == nullptr;
}
