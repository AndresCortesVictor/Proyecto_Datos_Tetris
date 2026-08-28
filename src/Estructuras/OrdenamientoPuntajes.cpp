#include "OrdenamientoPuntajes.h"

OrdenamientoPuntajes::OrdenamientoPuntajes() {}
OrdenamientoPuntajes::~OrdenamientoPuntajes() {}

void OrdenamientoPuntajes::insertionSort(NodoPuntaje*& cabeza) {
    if (!cabeza || !cabeza->siguiente) return;

    NodoPuntaje* ordenada = nullptr;
    NodoPuntaje* actual = cabeza;

    while (actual != nullptr) {
        NodoPuntaje* siguiente = actual->siguiente;
        
        if (ordenada == nullptr || actual->dato.puntos >= ordenada->dato.puntos) {
            actual->siguiente = ordenada;
            ordenada = actual;
        } else {
            NodoPuntaje* temp = ordenada;
            while (temp->siguiente != nullptr && temp->siguiente->dato.puntos > actual->dato.puntos) {
                temp = temp->siguiente;
            }
            actual->siguiente = temp->siguiente;
            temp->siguiente = actual;
        }
        actual = siguiente;
    }
    cabeza = ordenada;
}

void OrdenamientoPuntajes::mergeSort(NodoPuntaje*& cabeza) {
    cabeza = mergeSortRec(cabeza);
}

NodoPuntaje* OrdenamientoPuntajes::mergeSortRec(NodoPuntaje* cabeza) {
    if (!cabeza || !cabeza->siguiente) {
        return cabeza;
    }

    NodoPuntaje* izq;
    NodoPuntaje* der;

    dividir(cabeza, &izq, &der);

    izq = mergeSortRec(izq);
    der = mergeSortRec(der);

    return merge(izq, der);
}

NodoPuntaje* OrdenamientoPuntajes::merge(NodoPuntaje* izq, NodoPuntaje* der) {
    if (!izq) return der;
    if (!der) return izq;

    NodoPuntaje* resultado = nullptr;

    if (izq->dato.puntos >= der->dato.puntos) {
        resultado = izq;
        resultado->siguiente = merge(izq->siguiente, der);
    } else {
        resultado = der;
        resultado->siguiente = merge(izq, der->siguiente);
    }
    return resultado;
}

void OrdenamientoPuntajes::dividir(NodoPuntaje* fuente, NodoPuntaje** frente, NodoPuntaje** atras) {
    NodoPuntaje* rapido;
    NodoPuntaje* lento;
    
    lento = fuente;
    rapido = fuente->siguiente;

    while (rapido != nullptr) {
        rapido = rapido->siguiente;
        if (rapido != nullptr) {
            lento = lento->siguiente;
            rapido = rapido->siguiente;
        }
    }

    *frente = fuente;
    *atras = lento->siguiente;
    lento->siguiente = nullptr;
}
