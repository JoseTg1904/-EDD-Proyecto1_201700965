#include <iostream>
#include "transaccion.h"
#include <cstdlib>
#include <ctime>

using namespace std;
Transaccion::Transaccion(string idTran, string idActivo, string usuario, string depa, string empresa, string fecha,
                         string tiempo, Activo* activo){
    this->idTran = idTran;
    this->idActivo = idActivo;
    this->usuario = usuario;
    this->depa = depa;
    this->empresa = empresa;
    this->fecha = fecha;
    this->tiempo = tiempo;
    this->activo = activo;
}

string Transaccion::getIdTran(){
    return this->idTran;
}

string Transaccion::getIdActivo(){
    return this->idActivo;
}

string Transaccion::getUsuario(){
    return this->usuario;
}

string Transaccion::getDepa(){
    return this->depa;
}

string Transaccion::getEmpresa(){
    return this->empresa;
}

string Transaccion::getTiempo(){
    return this->tiempo;
}

Activo* Transaccion::getActivo(){
    return this->activo;
}
