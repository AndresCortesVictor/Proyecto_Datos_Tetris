#ifndef LISTA_DOBLE_REPLAY_H
#define LISTA_DOBLE_REPLAY_H

#include "../Game/Pieza.h"

struct NodoReplay {
    TipoPieza matriz[20][10];
    Pieza piezaActiva;
    int puntaje;
    
    NodoReplay* siguiente;
    NodoReplay* anterior;
    
    NodoReplay(const TipoPieza m[20][10], Pieza p, int pts) 
        : piezaActiva(p), puntaje(pts), siguiente(nullptr), anterior(nullptr) {
        for(int i = 0; i < 20; i++) {
            for(int j = 0; j < 10; j++) {
                matriz[i][j] = m[i][j];
            }
        }
    }
};

class ListaDobleReplay {
private:
    NodoReplay* cabeza;
    NodoReplay* final;
    NodoReplay* actual;

public:
    ListaDobleReplay();
    ~ListaDobleReplay();
    
    void guardarEstado(const TipoPieza matriz[20][10], Pieza pActiva, int puntaje);
    bool deshacer(TipoPieza destino[20][10], Pieza& pActiva, int& puntaje);
    void vaciar();
};

#endif
