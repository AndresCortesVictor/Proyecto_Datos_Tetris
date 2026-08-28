#ifndef ORDENAMIENTO_PUNTAJES_H
#define ORDENAMIENTO_PUNTAJES_H

#include <string>

// Estructura para almacenar un puntaje
struct Puntaje {
    std::string nombre;
    int puntos;
};

// Nodo simple para la lista enlazada de puntajes
struct NodoPuntaje {
    Puntaje dato;
    NodoPuntaje* siguiente;
    
    NodoPuntaje(Puntaje p) : dato(p), siguiente(nullptr) {}
};

class OrdenamientoPuntajes {
public:
    OrdenamientoPuntajes();
    ~OrdenamientoPuntajes();
    
    // O(n^2) - Ordenamiento por Inserción para listas enlazadas
    static void insertionSort(NodoPuntaje*& cabeza);

    // O(n log n) - Ordenamiento por Mezcla (Merge Sort) para listas enlazadas
    static void mergeSort(NodoPuntaje*& cabeza);

private:
    // Funciones auxiliares internas para el Merge Sort
    static NodoPuntaje* mergeSortRec(NodoPuntaje* cabeza);
    static NodoPuntaje* merge(NodoPuntaje* izq, NodoPuntaje* der);
    static void dividir(NodoPuntaje* fuente, NodoPuntaje** frente, NodoPuntaje** atras);
};

#endif
