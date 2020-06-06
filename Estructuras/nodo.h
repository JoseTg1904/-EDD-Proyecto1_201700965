#ifndef NODO_H
#define NODO_H
#include "Objetos/usuario.h"
#include <iostream>

using namespace std;

class Nodo{
    public:
        Nodo *arriba;
        Nodo *abajo;
        Nodo *derecha;
        Nodo *izquierda;
        Nodo *afuera;
        Nodo *adentro;
        int posX;
        int posY;
        string nombre;
        Usuario *usuario;
        Nodo(Nodo*, Nodo*, Nodo*, Nodo*, Nodo*, Nodo*, int, int, string, Usuario*);

};

#endif // NODO_H
