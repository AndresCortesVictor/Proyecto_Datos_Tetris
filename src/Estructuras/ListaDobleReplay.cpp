#include "ListaDobleReplay.h"

ListaDobleReplay::ListaDobleReplay() : cabeza(nullptr), final(nullptr), actual(nullptr) {
}

ListaDobleReplay::~ListaDobleReplay() {
    vaciar();
}

void ListaDobleReplay::vaciar() {
    NodoReplay* iter = cabeza;
    while (iter != nullptr) {
        NodoReplay* temp = iter;
        iter = iter->siguiente;
        delete temp;
    }
    cabeza = nullptr;
    final = nullptr;
    actual = nullptr;
}

void ListaDobleReplay::guardarEstado(const TipoPieza matriz[20][10], Pieza pActiva, int puntaje) {
    if (actual != final) {
        NodoReplay* iter = actual != nullptr ? actual->siguiente : cabeza;
        while (iter != nullptr) {
            NodoReplay* temp = iter;
            iter = iter->siguiente;
            delete temp;
        }
        final = actual;
        if (final != nullptr) {
            final->siguiente = nullptr;
        } else {
            cabeza = nullptr;
        }
    }
    
    NodoReplay* nuevo = new NodoReplay(matriz, pActiva, puntaje);
    
    if (cabeza == nullptr) {
        cabeza = nuevo;
        final = nuevo;
        actual = nuevo;
    } else {
        final->siguiente = nuevo;
        nuevo->anterior = final;
        final = nuevo;
        actual = final;
    }
}

bool ListaDobleReplay::deshacer(TipoPieza destino[20][10], Pieza& pActiva, int& puntaje) {
    if (actual == nullptr || actual->anterior == nullptr) {
        return false;
    }
    
    actual = actual->anterior;
    
    for(int i = 0; i < 20; i++) {
        for(int j = 0; j < 10; j++) {
            destino[i][j] = actual->matriz[i][j];
        }
    }
    pActiva = actual->piezaActiva;
    puntaje = actual->puntaje;
    
    return true;
}
