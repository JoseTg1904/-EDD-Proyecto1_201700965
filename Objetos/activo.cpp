#include "activo.h"

Activo::Activo(string id, string nombre, string descripcion, bool rentado){
    this->id = id;
    this->nombre = nombre;
    this->descripcion = descripcion;
    this->rentado = rentado;
}

string Activo::getID(){
    return this->id;
}

string Activo::getNombre(){
    return this->nombre;
}

void Activo::setDescripcion(string descripcion){
    this->descripcion = descripcion;
}

string Activo::getDescripcion(){
    return this->descripcion;
}

bool Activo::getRentado(){
    return this->rentado;
}

void Activo::setRentado(bool rentado){
    this->rentado = rentado;
}
