#include "ListaDobleReplay.h"
#include <iostream>

ListaDobleReplay::ListaDobleReplay() : cabeza(nullptr), cola(nullptr), actual(nullptr) {
}

ListaDobleReplay::~ListaDobleReplay() {
    limpiar();
}

void ListaDobleReplay::limpiar() {
    NodoReplay* temp = cabeza;
    while (temp != nullptr) {
        NodoReplay* borrar = temp;
        temp = temp->siguiente;
        delete borrar;
    }
    cabeza = nullptr;
    cola = nullptr;
    actual = nullptr;
}

void ListaDobleReplay::registrarEstado(const ListaTablero& tableroActual, int puntajeActual) {
    if (actual != nullptr && actual != cola) {
        NodoReplay* temp = actual->siguiente;
        while (temp != nullptr) {
            NodoReplay* borrar = temp;
            temp = temp->siguiente;
            delete borrar;
        }
        cola = actual;
        cola->siguiente = nullptr;
    }

    EstadoReplay nuevoEstado;
    nuevoEstado.puntaje = puntajeActual;
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 10; ++j) {
            nuevoEstado.tablero[i][j] = tableroActual.obtenerCelda(i, j);
        }
    }

    NodoReplay* nuevoNodo = new NodoReplay(nuevoEstado);
    
    if (cabeza == nullptr) {
        cabeza = nuevoNodo;
        cola = nuevoNodo;
    } else {
        cola->siguiente = nuevoNodo;
        nuevoNodo->anterior = cola;
        cola = nuevoNodo;
    }
    
    actual = cola;
}

bool ListaDobleReplay::hayAnterior() const {
    return actual != nullptr && actual->anterior != nullptr;
}

bool ListaDobleReplay::haySiguiente() const {
    return actual != nullptr && actual->siguiente != nullptr;
}

EstadoReplay ListaDobleReplay::retroceder() {
    if (hayAnterior()) {
        actual = actual->anterior;
    }
    return actual->estado;
}

EstadoReplay ListaDobleReplay::avanzar() {
    if (haySiguiente()) {
        actual = actual->siguiente;
    }
    return actual->estado;
}
