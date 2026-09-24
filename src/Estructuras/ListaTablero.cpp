#include "ListaTablero.h"

ListaTablero::ListaTablero() {
    cabeza = new NodoFila();
    NodoFila* actual = cabeza;
    for (int i = 1; i < 20; ++i) {
        actual->siguiente = new NodoFila();
        actual = actual->siguiente;
    }
}

ListaTablero::~ListaTablero() {
    NodoFila* actual = cabeza;
    while (actual != nullptr) {
        NodoFila* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
}

bool ListaTablero::colisiona(const Pieza& p, int nuevaX, int nuevaY) const {
    int coords[4][2];
    p.obtenerPosicionesRelativas(coords);

    for (int i = 0; i < 4; ++i) {
        int cX = nuevaX + coords[i][0];
        int cY = nuevaY + coords[i][1];

        if (cX < 0 || cX >= 10 || cY >= 20) {
            return true;
        }

        if (cY >= 0) {
            TipoPieza celda = obtenerCelda(cY, cX);
            if (celda != TipoPieza::Ninguna) {
                return true;
            }
        }
    }
    return false;
}

void ListaTablero::fijarPieza(const Pieza& p) {
    int coords[4][2];
    p.obtenerPosicionesRelativas(coords);
    int px = p.getX();
    int py = p.getY();

    for (int i = 0; i < 4; ++i) {
        int cX = px + coords[i][0];
        int cY = py + coords[i][1];

        if (cY >= 0 && cY < 20 && cX >= 0 && cX < 10) {
            NodoFila* actual = cabeza;
            for (int f = 0; f < cY; ++f) {
                if (actual != nullptr) {
                    actual = actual->siguiente;
                }
            }
            if (actual != nullptr) {
                actual->celdas[cX] = p.getTipo();
            }
        }
    }
}

int ListaTablero::limpiarLineas() {
    int lineasLimpias = 0;
    NodoFila* actual = cabeza;
    NodoFila* previo = nullptr;

    while (actual != nullptr) {
        bool llena = true;
        for (int c = 0; c < 10; ++c) {
            if (actual->celdas[c] == TipoPieza::Ninguna) {
                llena = false;
                break;
            }
        }

        if (llena) {
            lineasLimpias++;
            NodoFila* aBorrar = actual;
            
            if (previo == nullptr) {
                cabeza = actual->siguiente;
                actual = cabeza;
            } else {
                previo->siguiente = actual->siguiente;
                actual = actual->siguiente;
            }
            
            delete aBorrar;
            
            NodoFila* nuevaFila = new NodoFila();
            nuevaFila->siguiente = cabeza;
            cabeza = nuevaFila;
        } else {
            previo = actual;
            actual = actual->siguiente;
        }
    }
    return lineasLimpias;
}

TipoPieza ListaTablero::obtenerCelda(int fila, int columna) const {
    if (fila < 0 || fila >= 20 || columna < 0 || columna >= 10) {
        return TipoPieza::Ninguna;
    }
    NodoFila* actual = cabeza;
    for (int i = 0; i < fila; ++i) {
        if (actual == nullptr) return TipoPieza::Ninguna;
        actual = actual->siguiente;
    }
    if (actual != nullptr) {
        return actual->celdas[columna];
    }
    return TipoPieza::Ninguna;
}
