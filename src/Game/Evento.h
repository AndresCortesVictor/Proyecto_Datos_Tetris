#ifndef EVENTO_H
#define EVENTO_H

enum class TipoEvento {
    AumentarVelocidad,
    PiezaEspecial,
    InvertirControles
};

struct Evento {
    TipoEvento tipo;
    float tiempoDisparo;
};

#endif
