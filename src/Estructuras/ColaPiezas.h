#ifndef COLA_PIEZAS_H
#define COLA_PIEZAS_H

#include "../Game/Pieza.h"

struct NodoPieza {
    Pieza dato;
    NodoPieza* siguiente;
    NodoPieza(Pieza p) : dato(p), siguiente(nullptr) {}
};

class ColaPiezas {
private:
    NodoPieza* frente;
    NodoPieza* final;
    int cantidad;

    void generarBolsa(Pieza bolsa[7]);

public:
    ColaPiezas();
    ~ColaPiezas();

    void insertarBolsa(const Pieza bolsa[7]);
    Pieza sacarPieza();
    Pieza verDentro(int posicion) const;
    bool estaVacia() const;
    void vaciar();
};

#endif
