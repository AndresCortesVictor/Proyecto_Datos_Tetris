#include "ColaEventos.h"
#include <cstdlib>

ColaEventos::ColaEventos() : cabeza(nullptr) {
}

ColaEventos::~ColaEventos() {
    while (cabeza != nullptr) {
        NodoEvento* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}

void ColaEventos::encolarOrdenado(Evento e) {
    NodoEvento* nuevo = new NodoEvento(e);
    
    if (cabeza == nullptr || e.tiempoDisparo < cabeza->dato.tiempoDisparo) {
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        return;
    }
    
    NodoEvento* actual = cabeza;
    while (actual->siguiente != nullptr && actual->siguiente->dato.tiempoDisparo <= e.tiempoDisparo) {
        actual = actual->siguiente;
    }
    
    nuevo->siguiente = actual->siguiente;
    actual->siguiente = nuevo;
}

Evento ColaEventos::calcularNuevoEvento(float tiempoActual) {
    Evento e;
    int randomTipo = std::rand() % 3;
    
    switch (randomTipo) {
        case 0: e.tipo = TipoEvento::AumentarVelocidad; break;
        case 1: e.tipo = TipoEvento::PiezaEspecial; break;
        case 2: e.tipo = TipoEvento::InvertirControles; break;
    }
    
    float tiempoExtra = 15.0f + static_cast<float>(std::rand() % 20);
    e.tiempoDisparo = tiempoActual + tiempoExtra;
    
    return e;
}

Evento ColaEventos::desencolarEvento(float tiempoActual) {
    if (cabeza == nullptr) {
        return Evento{TipoEvento::AumentarVelocidad, 0.0f};
    }
    
    NodoEvento* temp = cabeza;
    Evento e = temp->dato;
    cabeza = cabeza->siguiente;
    temp->siguiente = nullptr;
    delete temp;
    
    Evento nuevoEvento = calcularNuevoEvento(tiempoActual);
    encolarOrdenado(nuevoEvento);
    
    return e;
}

bool ColaEventos::estaVacia() const {
    return cabeza == nullptr;
}

Evento ColaEventos::verFrente() const {
    if (cabeza != nullptr) return cabeza->dato;
    return Evento{TipoEvento::AumentarVelocidad, 0.0f};
}

void ColaEventos::vaciar() {
    while (cabeza != nullptr) {
        NodoEvento* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
    }
}
