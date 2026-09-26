#ifndef COLA_EVENTOS_H
#define COLA_EVENTOS_H

#include "../Game/Evento.h"

struct NodoEvento {
    Evento dato;
    NodoEvento* siguiente;
    NodoEvento(Evento e) : dato(e), siguiente(nullptr) {}
};

class ColaEventos {
private:
    NodoEvento* cabeza;
    Evento calcularNuevoEvento(float tiempoActual);

public:
    ColaEventos();
    ~ColaEventos();

    void encolarOrdenado(Evento e);
    Evento desencolarEvento(float tiempoActual);
    bool estaVacia() const;
    Evento verFrente() const;
    void vaciar();
};

#endif
