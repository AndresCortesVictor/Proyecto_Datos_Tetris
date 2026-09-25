#include "GestorPuntajes.h"
#include <fstream>

GestorPuntajes::GestorPuntajes(const std::string& ruta) : cabeza(nullptr), rutaArchivo(ruta) {
}

GestorPuntajes::~GestorPuntajes() {
    liberarLista();
}

void GestorPuntajes::liberarLista() {
    NodoPuntaje* actual = cabeza;
    while (actual != nullptr) {
        NodoPuntaje* temp = actual;
        actual = actual->siguiente;
        delete temp;
    }
    cabeza = nullptr;
}

void GestorPuntajes::cargarPuntajes() {
    liberarLista();
    std::ifstream archivo(rutaArchivo);
    if (archivo.is_open()) {
        std::string nombre;
        int puntos;
        while (archivo >> nombre >> puntos) {
            agregarPuntaje(nombre, puntos);
        }
        archivo.close();
    }
}

void GestorPuntajes::guardarPuntajes() {
    std::ofstream archivo(rutaArchivo);
    if (archivo.is_open()) {
        NodoPuntaje* actual = cabeza;
        while (actual != nullptr) {
            archivo << actual->dato.nombre << " " << actual->dato.puntos << "\n";
            actual = actual->siguiente;
        }
        archivo.close();
    }
}

void GestorPuntajes::agregarPuntaje(const std::string& nombre, int puntos) {
    Puntaje p;
    p.nombre = nombre;
    p.puntos = puntos;
    
    NodoPuntaje* nuevo = new NodoPuntaje(p);
    
    if (cabeza == nullptr) {
        cabeza = nuevo;
    } else {
        NodoPuntaje* actual = cabeza;
        while (actual->siguiente != nullptr) {
            actual = actual->siguiente;
        }
        actual->siguiente = nuevo;
    }
}

void GestorPuntajes::ordenarPorInsercion() {
    OrdenamientoPuntajes::insertionSort(cabeza);
}

void GestorPuntajes::ordenarPorMerge() {
    OrdenamientoPuntajes::mergeSort(cabeza);
}

NodoPuntaje* GestorPuntajes::getLista() const {
    return cabeza;
}
