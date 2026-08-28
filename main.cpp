#include "src/visuales/Juego.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    try {
        Juego juego;
        juego.ejecutar();
    } catch (const std::exception& e) {
        cerr << "Error en el juego: " << e.what() << endl;
        return 1;
    }

    return 0;
}
