#ifndef AVL_H
#define AVL_H
#include "Objetos/activo.h"

struct NodoA{
    NodoA *izquierda;
    NodoA *derecha;
    Activo *activo;
    NodoA(NodoA*, NodoA*, Activo*);
};

class AVL{
    public:
        AVL();
    private:
        NodoA *raiz;
};

#endif // AVL_H
