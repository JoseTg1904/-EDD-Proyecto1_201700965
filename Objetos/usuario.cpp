#include <iostream>
#include "usuario.h"
#include "Estructuras/avl.h"

using namespace std;

Usuario::Usuario(string nombre, string usuario, string contra){
    this->nombre = nombre;
    this->usuario = usuario;
    this->contra = contra;
    this->avl = new AVL();
}

string Usuario::getUsuario(){
    return this->usuario;
}

string Usuario::getContra(){
    return this->contra;
}

AVL* Usuario::getAVL(){
    return this->avl;
}
