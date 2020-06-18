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
    int valor;
    NodoA(NodoA*, NodoA*, NodoA*, Activo*, int);
    NodoA(NodoA*, NodoA*, NodoA*, int, int);
};

class AVL{
    public:
        AVL();
        void insertar(Activo*);
        Activo* eliminar(string);
        Activo* modificar(string);
        string retornarActivos();
        string retornarActivosRentados();
        string devolverActivosDisponibles();
        string retornarGrafo(string, string, string);
    private:
        Activo* buscar(string);
        NodoA* raiz;
        string activos;
        void eliminar(NodoA*, string);
        Activo* buscarMenor(NodoA*);
        void calcularAltura(NodoA*);
        void llenarListaActivos(NodoA*);
        void activosDisponibles(NodoA*);
        void activosRentados(NodoA*);
        void generarGrafo(NodoA*);
};

#endif // AVL_H
