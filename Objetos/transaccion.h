#ifndef TRANSACCION_H
#define TRANSACCION_H
#include <iostream>
#include "Objetos/activo.h"

using namespace std;

class Transaccion{
    public:
        Transaccion(string, string, string, string, string, string, string,Activo*);
        string getIdTran();
        string getIdActivo();
        string getUsuario();
        string getDepa();
        string getEmpresa();
        string getTiempo();
        Activo* getActivo();
    private:
        string idTran;
        string idActivo;
        string usuario;
        string depa;
        string empresa;
        string fecha;
        string tiempo;
        Activo* activo;
};

#endif // TRANSACCION_H
