#ifndef GESTOR_PUNTAJES_H
#define GESTOR_PUNTAJES_H

#include "OrdenamientoPuntajes.h"
#include <string>

class GestorPuntajes {
private:
    NodoPuntaje* cabeza;
    std::string rutaArchivo;

    void liberarLista();

public:
    GestorPuntajes(const std::string& ruta);
    ~GestorPuntajes();

    void cargarPuntajes();
    void guardarPuntajes();
    void agregarPuntaje(const std::string& nombre, int puntos);
    
    void ordenarPorInsercion();
    void ordenarPorMerge();

    NodoPuntaje* getLista() const;
};

#endif
