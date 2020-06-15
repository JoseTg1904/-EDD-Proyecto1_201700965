#ifndef LISTADOBLECIRCULAR_H
#define LISTADOBLECIRCULAR_H
#include "Objetos/transaccion.h"
#include "Objetos/activo.h"
#include <iostream>
#include <ctime>

using namespace std;

struct NodoL{
    NodoL* siguiente;
    NodoL* anterior;
    Transaccion* transaccion;
    string cadena;
    Activo* activo;
    NodoL(NodoL*, NodoL*, Transaccion*);
    NodoL(NodoL*, NodoL*, string);
    NodoL(NodoL*, NodoL*, Activo*);

};

class ListaDobleCircular{
    public:
        ListaDobleCircular();
        void insertar(Transaccion*);
        void ordenarAscendente();
        void ordenarDescendente();
        string generarGrafo();
        string generarID();
        bool verificarID(string);
        void insertar(string);
        void insertar(Activo*);
        NodoL* getCabeza();
        string eliminar(string);
    private:
        NodoL* cabeza;
        NodoL* cola;
        int tamanio;
};

#endif // LISTADOBLECIRCULAR_H
