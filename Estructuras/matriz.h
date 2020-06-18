#ifndef MATRIZ_H
#define MATRIZ_H
#include <iostream>
#include "Objetos/usuario.h"
#include "Estructuras/listadoblecircular.h"

using namespace std;

struct NodoM{
    NodoM* arriba;
    NodoM* abajo;
    NodoM* derecha;
    NodoM* izquierda;
    NodoM* afuera;
    NodoM* adentro;
    int posX;
    int posY;
    string nombre;
    Usuario* usuario;
    NodoM(NodoM*, NodoM*, NodoM*, NodoM*, NodoM*, NodoM*, int, int, string, Usuario*);
};

class Matriz{
    public:
        Matriz();
        bool agregarUsuario(string, string, string, string, string);
        bool verificarExistencia(string, string, string);
        Usuario* validarSesion(string, string, string, string);
        string recorrerMatriz();
        string catalogoDeActivos();
        Usuario* cambiarEstadoActivo(string, string, string);
        Usuario* devolverUsuario(string, string, string);
        string activosDeEmpresa(string);
        string activosDeDepartamento(string);
        Activo* buscarActivo(string);
        string recorrerDepartamentos();
        string recorrerEmpresas();
        string usuariosMatriz();
    private:
        NodoM* origen;
        bool verificarCabecerasHorizontales(string);
        bool verificarCabecerasVerticales(string);
        void crearCabeceraHorizontal(string);
        void crearCabeceraVertical(string);
        NodoM* buscarDepartamento(string);
        NodoM* buscarEmpresa(string);

};

#endif // MATRIZ_H
