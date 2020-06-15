#ifndef USUARIO_H
#define USUARIO_H
#include <iostream>
#include "Estructuras/avl.h"

using namespace std;

class Usuario{
    public:
        Usuario(string,string,string);
        string getUsuario();
        string getContra();
        AVL* getAVL();
    private:
        string nombre;
        string usuario;
        string contra;
        AVL *avl;
};

#endif // USUARIO_H
