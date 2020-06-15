#ifndef ACTIVO_H
#define ACTIVO_H
#include <iostream>

using namespace std;

class Activo{
    public:
        Activo(string, string, string, bool);
        string getID();
        string getNombre();
        void setDescripcion(string);
        string getDescripcion();
        bool getRentado();
        void setRentado(bool);
    private:
        string id;
        string nombre;
        string descripcion;
        bool rentado;
};

#endif // ACTIVO_H
