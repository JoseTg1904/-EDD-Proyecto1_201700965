#ifndef TRANSACCION_H
#define TRANSACCION_H
#include <iostream>

using namespace std;

class Transaccion{
    public:
        Transaccion(string, string, string, string, string, string, string);
        string getIdTran();
        string getIdActivo();
    private:
        string idTran;
        string idActivo;
        string usuario;
        string depa;
        string empresa;
        string fecha;
        string tiempo;
};

#endif // TRANSACCION_H
