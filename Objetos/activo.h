#ifndef ACTIVO_H
#define ACTIVO_H
#include <iostream>

using namespace std;

class Activo{
public:
    Activo(string,string,string);
private:
    string nombre;
    string descripcion;
    string id;
};

#endif // ACTIVO_H
