#include "Game/Juego.h"
#include <iostream>
#include <exception>

using namespace std;

int main(int argc, char *argv[]) {
    try {
        Juego juego;
        juego.ejecutar();
    } catch (const std::exception& e) {
        cerr << e.what() << endl;
        return 1;
    }
    return 0;
}
