#include "OrdenamientoPuntajes.h"

OrdenamientoPuntajes::OrdenamientoPuntajes() {}
OrdenamientoPuntajes::~OrdenamientoPuntajes() {}

// ==========================================
// INSERTION SORT O(n^2) - De mayor a menor
// ==========================================
void OrdenamientoPuntajes::insertionSort(NodoPuntaje*& cabeza) {
    // Si la lista esta vacia o solo tiene 1 elemento, ya esta ordenada
    if (!cabeza || !cabeza->siguiente) return;

    NodoPuntaje* ordenada = nullptr;
    NodoPuntaje* actual = cabeza;

    while (actual != nullptr) {
        NodoPuntaje* siguiente = actual->siguiente;
        
        // Insercion al principio si 'ordenada' esta vacia o si el puntaje actual es mayor
        if (ordenada == nullptr || actual->dato.puntos >= ordenada->dato.puntos) {
            actual->siguiente = ordenada;
            ordenada = actual;
        } else {
            // Buscar la posicion correcta en la lista 'ordenada'
            NodoPuntaje* temp = ordenada;
            while (temp->siguiente != nullptr && temp->siguiente->dato.puntos > actual->dato.puntos) {
                temp = temp->siguiente;
            }
            actual->siguiente = temp->siguiente;
            temp->siguiente = actual;
        }
        actual = siguiente;
    }
    // Actualizar la cabeza para que apunte a la nueva lista ordenada
    cabeza = ordenada;
}

// ==========================================
// MERGE SORT O(n log n) - De mayor a menor
// ==========================================
void OrdenamientoPuntajes::mergeSort(NodoPuntaje*& cabeza) {
    cabeza = mergeSortRec(cabeza);
}

// Funcion recursiva principal de Merge Sort
NodoPuntaje* OrdenamientoPuntajes::mergeSortRec(NodoPuntaje* cabeza) {
    // Caso base: 0 o 1 nodo
    if (!cabeza || !cabeza->siguiente) {
        return cabeza;
    }

    NodoPuntaje* izq;
    NodoPuntaje* der;

    // 1. Dividir la lista a la mitad
    dividir(cabeza, &izq, &der);

    // 2. Ordenar recursivamente ambas mitades
    izq = mergeSortRec(izq);
    der = mergeSortRec(der);

    // 3. Unir (mezclar) las mitades ya ordenadas
    return merge(izq, der);
}

// Mezcla dos sublistas ordenadas
NodoPuntaje* OrdenamientoPuntajes::merge(NodoPuntaje* izq, NodoPuntaje* der) {
    if (!izq) return der;
    if (!der) return izq;

    NodoPuntaje* resultado = nullptr;

    // Ordenamos de mayor a menor puntaje
    if (izq->dato.puntos >= der->dato.puntos) {
        resultado = izq;
        resultado->siguiente = merge(izq->siguiente, der);
    } else {
        resultado = der;
        resultado->siguiente = merge(izq, der->siguiente);
    }
    return resultado;
}

// Utiliza la tecnica de "tortuga y liebre" (puntero rapido y lento) para encontrar la mitad de la lista
void OrdenamientoPuntajes::dividir(NodoPuntaje* fuente, NodoPuntaje** frente, NodoPuntaje** atras) {
    NodoPuntaje* rapido;
    NodoPuntaje* lento;
    
    lento = fuente;
    rapido = fuente->siguiente;

    // Avanzamos 'rapido' dos nodos y 'lento' un nodo
    while (rapido != nullptr) {
        rapido = rapido->siguiente;
        if (rapido != nullptr) {
            lento = lento->siguiente;
            rapido = rapido->siguiente;
        }
    }

    // 'lento' se queda justo antes de la mitad
    *frente = fuente;
    *atras = lento->siguiente;
    lento->siguiente = nullptr;
}
