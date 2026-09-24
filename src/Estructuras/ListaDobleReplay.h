#ifndef LISTA_DOBLE_REPLAY_H
#define LISTA_DOBLE_REPLAY_H

#include "../Game/TipoPieza.h"
#include "../Estructuras/ListaTablero.h"

struct EstadoReplay {
    TipoPieza tablero[20][10];
    int puntaje;
};

struct NodoReplay {
    EstadoReplay estado;
    NodoReplay* siguiente;
    NodoReplay* anterior;

    NodoReplay(const EstadoReplay& est) : estado(est), siguiente(nullptr), anterior(nullptr) {}
};

class ListaDobleReplay {
private:
    NodoReplay* cabeza;
    NodoReplay* cola;
    NodoReplay* actual;

public:
    ListaDobleReplay();
    ~ListaDobleReplay();

    void registrarEstado(const ListaTablero& tablero, int puntaje);
    
    bool hayAnterior() const;
    bool haySiguiente() const;
    
    EstadoReplay retroceder();
    EstadoReplay avanzar();
    
    void limpiar();
};

#endif
