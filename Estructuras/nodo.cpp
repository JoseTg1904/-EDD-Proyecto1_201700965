#include <iostream>
#include "nodo.h"


Nodo::Nodo(Nodo *arriba, Nodo *abajo, Nodo *derecha, Nodo *izquierda, Nodo *afuera, Nodo *adentro,
           int posX, int posY, string nombre, Usuario *usuario){
    this->arriba = arriba;
    this->abajo = abajo;
    this->derecha = derecha;
    this->izquierda = izquierda;
    this->afuera = afuera;
    this->adentro = adentro;
    this->posX = posX;
    this->posY = posY;
    this->nombre = nombre;
    this->usuario = usuario;
}
