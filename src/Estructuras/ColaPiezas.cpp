#include "ColaPiezas.h"
#include <cstdlib>
#include <ctime>

ColaPiezas::ColaPiezas() : frente(nullptr), final(nullptr), cantidad(0) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    Pieza bolsaInicial[7];
    generarBolsa(bolsaInicial);
    insertarBolsa(bolsaInicial);
}

ColaPiezas::~ColaPiezas() {
    while (frente != nullptr) {
        NodoPieza* temp = frente;
        frente = frente->siguiente;
        delete temp;
    }
}

void ColaPiezas::generarBolsa(Pieza bolsa[7]) {
    bolsa[0] = Pieza(TipoPieza::I);
    bolsa[1] = Pieza(TipoPieza::O);
    bolsa[2] = Pieza(TipoPieza::T);
    bolsa[3] = Pieza(TipoPieza::S);
    bolsa[4] = Pieza(TipoPieza::Z);
    bolsa[5] = Pieza(TipoPieza::J);
    bolsa[6] = Pieza(TipoPieza::L);

    for (int i = 6; i > 0; --i) {
        int j = std::rand() % (i + 1);
        Pieza temp = bolsa[i];
        bolsa[i] = bolsa[j];
        bolsa[j] = temp;
    }
}

void ColaPiezas::insertarBolsa(const Pieza bolsa[7]) {
    for (int i = 0; i < 7; ++i) {
        NodoPieza* nuevo = new NodoPieza(bolsa[i]);
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
    
    delete temp;
    cantidad--;
    
    if (cantidad <= 3) {
        Pieza nuevaBolsa[7];
        generarBolsa(nuevaBolsa);
        insertarBolsa(nuevaBolsa);
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
