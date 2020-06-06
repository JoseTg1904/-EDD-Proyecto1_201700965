#ifndef MATRIZ_H
#define MATRIZ_H
#include <iostream>
#include "Objetos/usuario.h"
#include "nodo.h"
using namespace std;



class Matriz{
    public:
        Nodo *origen;
        Matriz();
        bool agregarUsuario(string,string,string,string,string);
        bool verificarExistencia(string,string,string);
        Usuario* validarSesion(string,string,string,string);
        string recorrerMatriz();
    private:
        bool verificarCabecerasHorizontales(string);
        bool verificarCabecerasVerticales(string);
        void crearCabeceraHorizontal(string);
        void crearCabeceraVertical(string);
        Nodo* buscarDepartamento(string);
        Nodo* buscarEmpresa(string);
        void recorrerDepartamentos();
        void recorrerEmpresas();
};

#endif // MATRIZ_H
