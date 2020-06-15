#include <iostream>
#include "transaccion.h"
#include <cstdlib>
#include <ctime>

using namespace std;
Transaccion::Transaccion(string idTran, string idActivo, string usuario, string depa, string empresa, string fecha,
                         string tiempo){
    this->idTran = idTran;
    this->idActivo = idActivo;
    this->usuario = usuario;
    this->depa = depa;
    this->empresa = empresa;
    this->fecha = fecha;
    this->tiempo = tiempo;

}

string Transaccion::getIdTran(){
    return this->idTran;
}
