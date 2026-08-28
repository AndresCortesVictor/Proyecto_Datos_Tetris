#ifndef ORDENAMIENTO_PUNTAJES_H
#define ORDENAMIENTO_PUNTAJES_H

#include <string>

struct Puntaje {
    std::string nombre;
    int puntos;
};

struct NodoPuntaje {
    Puntaje dato;
    NodoPuntaje* siguiente;
    
    NodoPuntaje(Puntaje p) : dato(p), siguiente(nullptr) {}
};

class OrdenamientoPuntajes {
public:
    OrdenamientoPuntajes();
    ~OrdenamientoPuntajes();
    
    static void insertionSort(NodoPuntaje*& cabeza);

    static void mergeSort(NodoPuntaje*& cabeza);

private:
    static NodoPuntaje* mergeSortRec(NodoPuntaje* cabeza);
    static NodoPuntaje* merge(NodoPuntaje* izq, NodoPuntaje* der);
    static void dividir(NodoPuntaje* fuente, NodoPuntaje** frente, NodoPuntaje** atras);
};

#endif
