#ifndef LISTA_TABLERO_H
#define LISTA_TABLERO_H

#include "../Game/Pieza.h"

struct NodoFila {
    TipoPieza celdas[10];
    NodoFila* siguiente;

    NodoFila() {
        for (int i = 0; i < 10; ++i) {
            celdas[i] = TipoPieza::Ninguna;
        }
        siguiente = nullptr;
    }
};

class ListaTablero {
private:
    NodoFila* cabeza;
    
public:
    ListaTablero();
    ~ListaTablero();

    bool colisiona(const Pieza& p, int nuevaX, int nuevaY) const;
    void fijarPieza(const Pieza& p);
    int limpiarLineas();
    TipoPieza obtenerCelda(int fila, int columna) const;
    void vaciar();
};

#endif
