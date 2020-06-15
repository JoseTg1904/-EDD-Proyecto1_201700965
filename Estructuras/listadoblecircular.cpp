#include "listadoblecircular.h"

NodoL::NodoL(NodoL* siguiente, NodoL* anterior, Transaccion* transaccion){
    this->siguiente = siguiente;
    this->anterior = anterior;
    this->transaccion = transaccion;
}

NodoL::NodoL(NodoL* siguiente, NodoL* anterior, Activo* activo){
    this->siguiente = siguiente;
    this->anterior = anterior;
    this->activo = activo;
}

NodoL::NodoL(NodoL* siguiente, NodoL* anterior, string cadena){
    this->siguiente = siguiente;
    this->anterior = anterior;
    this->cadena = cadena;
}

ListaDobleCircular::ListaDobleCircular(){
    this->cabeza = NULL;
    this->cola = NULL;
    this->tamanio = 0;
}

void ListaDobleCircular::insertar(Transaccion* transaccion){
    if(cabeza == NULL){
        NodoL* nuevo = new NodoL(NULL, NULL, transaccion);
        cabeza = cola = nuevo;
        nuevo->siguiente = cabeza;
        nuevo->anterior = cola;
        this->tamanio++;
    }else{
        NodoL *nuevo = new NodoL(cabeza, cola, transaccion);
        cola->siguiente = nuevo;
        cabeza->anterior = nuevo;
        cola = nuevo;
        this->tamanio++;
    }
}

void ListaDobleCircular::insertar(string cadena){
    if(cabeza == NULL){
        NodoL* nuevo = new NodoL(NULL, NULL, cadena);
        cabeza = cola = nuevo;
        nuevo->siguiente = cabeza;
        nuevo->anterior = cola;
        this->tamanio++;
    }else{
        NodoL* nuevo = new NodoL(cabeza, cola, cadena);
        cola->siguiente = nuevo;
        cabeza->anterior = nuevo;
        cola = nuevo;
        this->tamanio++;
    }
}

void ListaDobleCircular::insertar(Activo* activo){
    if(cabeza == NULL){
        NodoL* nuevo = new NodoL(NULL, NULL, activo);
        cabeza = cola = nuevo;
        nuevo->siguiente = cabeza;
        nuevo->anterior = cola;
        this->tamanio++;
    }else{
        NodoL* nuevo = new NodoL(cabeza, cola, activo);
        cola->siguiente = nuevo;
        cabeza->anterior = nuevo;
        cola = nuevo;
        this->tamanio++;
    }
}

NodoL* ListaDobleCircular::getCabeza(){
    return this->cabeza;
}

void ListaDobleCircular::ordenarAscendente(){
    NodoL* aux = this->cabeza;
}

void ListaDobleCircular::ordenarDescendente(){
    NodoL* aux = this->cabeza;
}

bool ListaDobleCircular::verificarID(string iden){
    NodoL* aux = this->cabeza;
    bool band = false;
    if(this->cabeza != NULL){
        do {
            if(aux->cadena == iden){
               band = true;
               break;
            }
            aux = aux->siguiente;
        } while (aux != this->cabeza);
    }
    return band;
}

string ListaDobleCircular::generarGrafo(){
    NodoL* aux = this->cabeza;
    string dot = "digraph Lista_Doble{\n";

    do {
        dot += "\"" + aux->cadena + "\"" + " [ label = \"" + aux->cadena/*transaccion->getIdTran()*/ + "\" ]\n";
        dot += "\""+aux->cadena + "\"" + " -> " + "\""+aux->siguiente->cadena+ "\"" + "\n";
        aux = aux->siguiente;
    } while (aux != this->cabeza);
    aux = this->cabeza;

    do { 
        dot += "\""+aux->cadena+"\"" + " -> " + "\""+aux->anterior->cadena+"\"" + "\n";
        aux = aux->anterior;
    } while (aux != this->cabeza);

    dot += "}";
    return dot;
}

string ListaDobleCircular::generarID(){
    srand(time(NULL));
    string almacen = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string salida = "";
    for(int i = 0; i < 15; i++){
        salida += almacen[rand() % (almacen.length()-1)];
    }
    return salida;
}

string ListaDobleCircular::eliminar(string id_activo){
    string retorno;
    if(this->tamanio == 1){
        if(this->cabeza->transaccion->getIdActivo() == id_activo){
            //retornar los datos para cambiar el estado del activo
            delete this->cabeza;
            delete this->cola;
            this->cabeza = this->cola = NULL;
        }else{
            retorno = "NULL";
            return retorno;
        }

    }else{
        NodoL* aux = this->cabeza;
        do {
            if(aux->transaccion->getIdActivo() == id_activo)
                break;
            aux = aux->siguiente;
        } while (aux!=this->cabeza);

    }

    return retorno;
}
