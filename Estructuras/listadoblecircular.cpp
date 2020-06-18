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
    ordenarAscendente(this->cabeza,1);
}

void ListaDobleCircular::ordenarAscendente(NodoL* temp, int tam){
    cout << "tamaño lista: "<<this->tamanio<<" tam: "<<tam<<endl;
    if(tam <= this->tamanio){
        NodoL* aux = this->cabeza;
        do {
            if(aux->transaccion->getIdTran() < temp->transaccion->getIdTran()){
                Transaccion* transaccion = aux->transaccion;
                aux->transaccion = temp->transaccion;
                temp->transaccion = transaccion;
            }
            aux = aux->siguiente;
        } while (aux!=this->cabeza);
        tam++;
        ordenarAscendente(temp->siguiente,tam);
    }
}

void ListaDobleCircular::ordenarDescendente(){
    ordenarAscendente(this->cabeza,1);
}

void ListaDobleCircular::ordenarDescendente(NodoL* temp, int tam){
    if(tam <= this->tamanio){
        NodoL* aux = this->cabeza;
        do {
            if(aux->transaccion->getIdTran() > temp->transaccion->getIdTran()){
                Transaccion* transaccion = aux->transaccion;
                aux->transaccion = temp->transaccion;
                temp->transaccion = transaccion;
            }
            aux = aux->siguiente;
        } while (aux!=this->cabeza);
        tam++;
        ordenarDescendente(temp->siguiente,tam);
    }
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
    string dot = "digraph Lista_Doble{\nrankdir = LR";
    do {
        if(aux->transaccion->getActivo()->getRentado()){
            dot += "\"" + aux->transaccion->getIdTran() + "\"" + " [ label = \"ID: " + aux->transaccion->getIdTran() +
                    "\nNombre: "+ aux->transaccion->getActivo()->getNombre() +
                    "\nUsuario: "+aux->transaccion->getUsuario() + "\" style = filled color = red]\n";
        }else{
            dot += "\"" + aux->transaccion->getIdTran() + "\"" + " [ label = \"" + aux->transaccion->getIdTran() + "\" style = filled color = green]\n";
        }

        dot += "\"" + aux->transaccion->getIdTran() + "\"" + " -> " + "\"" + aux->siguiente->transaccion->getIdTran() + "\"" + "\n";
        aux = aux->siguiente;
    } while (aux != this->cabeza);
    aux = this->cabeza;

    do { 
        dot += "\"" + aux->transaccion->getIdTran() + "\"" + " -> " + "\"" + aux->anterior->transaccion->getIdTran() + "\"" + "\n";
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

string ListaDobleCircular::transaccionesPropias(string usu, string depa, string empresa){
    string retorno;
    NodoL* aux = this->cabeza;
    do {
        if(aux->transaccion->getUsuario() == usu && aux->transaccion->getDepa() == depa &&
                aux->transaccion->getEmpresa() == empresa){
            retorno += "ID: " + aux->transaccion->getActivo()->getID() + " Nombre: " + aux->transaccion->getActivo()->getNombre() +
                    " Tiempo: "+aux->transaccion->getTiempo() + " dias\n";
        }
        aux = aux->siguiente;
    } while (aux!=this->cabeza);
    return retorno;
}

string ListaDobleCircular::transaccionesGrafo(string usu, string depa, string empresa, ListaDobleCircular* lista){
    ListaDobleCircular* auxLista = new ListaDobleCircular();
    NodoL* auxNodo = lista->getCabeza();
    do{
        if(auxNodo->transaccion->getUsuario() == usu && auxNodo->transaccion->getDepa() == depa && auxNodo->transaccion->getEmpresa() == empresa){
            auxLista->insertar(auxNodo->transaccion);
        }
        auxNodo = auxNodo->siguiente;
    }while(auxNodo != lista->getCabeza());
    return auxLista->generarGrafo();
}

Activo* ListaDobleCircular::devolverActivo(string id_activo){
    NodoL* aux = this->cabeza;
    Activo* retorno = NULL;
    do {
        if(aux->transaccion->getActivo()->getID() == id_activo){
            retorno = aux->transaccion->getActivo();
            break;
        }
    } while (aux != this->cabeza);
    return retorno;
}
