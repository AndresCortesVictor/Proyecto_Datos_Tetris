#ifndef COLA_PIEZAS_H
#define COLA_PIEZAS_H

#include "../Game/Pieza.h"
#include <vector>

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

    std::vector<Pieza> generarBolsa();

public:
    ColaPiezas();
    ~ColaPiezas();

    void insertarBolsa(const std::vector<Pieza>& bolsa);
    Pieza sacarPieza();
    Pieza verDentro(int posicion) const;
    bool estaVacia() const;
};

#endif
