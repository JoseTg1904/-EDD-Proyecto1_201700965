#ifndef MENUS_H
#define MENUS_H
#include "Estructuras/matriz.h"
#include "Estructuras/listadoblecircular.h"
#include "Objetos/usuario.h"
#include <iostream>

class Menu{
    public:
        void menuSesion();
        Menu();
    private:
        Matriz* matriz;
        ListaDobleCircular* identificador;
        ListaDobleCircular* transacciones;
        void menuAdmin();
        void limpiarPantalla();
        void crearUsuario();
        void reporteMatriz();
        void menuUsuario(Usuario*, string, string);
        void crearActivo(Usuario*, string, string);
        void eliminarActivo(Usuario*, string, string);
        void modificarActivo(Usuario*, string, string);
        void rentarActivos(Usuario*, string, string);
        void activosRentados(Usuario*, string, string);
        void misActivosRentados(Usuario*, string, string);
        void activosPorDepartamento();
        void activosPorEmpresa();
        void reporteTransacciones();
        void reporteActivosPorUsuario();
        void reporteActivosRentadosPorUsuario();
        string obtenerID();
};

#endif // MENUS_H
