#ifndef PILA_HOLD_H
#define PILA_HOLD_H

#include "../Game/Pieza.h"

struct NodoPila {
    Pieza dato;
    NodoPila* siguiente;
    NodoPila(Pieza p) : dato(p), siguiente(nullptr) {}
};

class PilaHold {
private:
    NodoPila* cima;

public:
    PilaHold();
    ~PilaHold();

    void push(Pieza p);
    Pieza pop();
    Pieza verCima() const;
    bool estaVacia() const;
};

#endif
