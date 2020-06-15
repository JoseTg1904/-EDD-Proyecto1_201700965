#ifndef AVL_H
#define AVL_H
#include "Objetos/activo.h"
#include "Estructuras/listadoblecircular.h"

struct NodoA{
    NodoA* izquierda;
    NodoA* derecha;
    NodoA* padre;
    Activo* activo;
    int altura;
    NodoA(NodoA*, NodoA*, NodoA*, Activo*, int);
};

class AVL{
    public:
        AVL();
        void insertar(Activo*);
        bool eliminar(string);
        bool buscar(string);
        Activo* modificar(string);
        string retornarActivos();
        string retornarActivosRentados();
        ListaDobleCircular* devolverActivosDisponibles();
    private:
        NodoA* raiz;
        string activos;
        void eliminar(NodoA*, string);
        Activo* buscarMenor(NodoA*);
        void generarGrafo(NodoA*);
        void calcularAltura(NodoA*);
        void llenarListaActivos(NodoA*);
        void activosDisponibles(ListaDobleCircular*, NodoA*);
        void activosRentados(NodoA*);
};

#endif // AVL_H
