#include "avl.h"

NodoA::NodoA(NodoA *izquierda, NodoA *derecha, Activo *activo){
    this->izquierda = izquierda;
    this->derecha = derecha;
    this->activo = activo;
}

AVL::AVL(){
    this->raiz = NULL;
}
