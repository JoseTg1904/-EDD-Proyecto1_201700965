#ifndef MENUS_H
#define MENUS_H
#include "Estructuras/matriz.h"
#include "Objetos/usuario.h"
#include <iostream>

class Menus{
    public:
        void menuSesion();
        Matriz *matriz = new Matriz();
    private:
        void menuAdmin();
        void limpiarPantalla();
        void crearUsuario();
        void reporteMatriz();
        void menuUsuario(Usuario*,string,string);
};

#endif // MENUS_H
