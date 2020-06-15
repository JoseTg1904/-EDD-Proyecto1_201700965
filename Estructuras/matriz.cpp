#include <iostream>
#include "matriz.h"

using namespace std;

NodoM::NodoM(NodoM* arriba, NodoM* abajo, NodoM* derecha, NodoM* izquierda, NodoM* afuera, NodoM* adentro,
             int posX, int posY, string nombre, Usuario* usuario){
    this->arriba = arriba;
    this->abajo = abajo;
    this->derecha = derecha;
    this->izquierda = izquierda;
    this->afuera = afuera;
    this->adentro = adentro;
    this->posX = posX;
    this->posY = posY;
    this->nombre = nombre;
    this->usuario = usuario;
}

Matriz::Matriz(){
    this->origen = new NodoM(NULL, NULL, NULL, NULL, NULL, NULL, 0, 0, "Origen", NULL);
}

bool Matriz::verificarCabecerasHorizontales(string depa){
    NodoM* aux = this->origen;

    if(aux->derecha == NULL){
        return false;
    }else{
        while(aux != NULL){
            if(aux->nombre == depa){
                return true;
            }
            aux = aux->derecha;
        }
        return false;
    }
}

void Matriz::crearCabeceraHorizontal(string depa){
    if(verificarCabecerasHorizontales(depa) == false){
        NodoM* aux = this->origen;
        int x = 1;
        while(aux->derecha != NULL){
            aux = aux->derecha;
            x++;
        }
        aux->derecha = new NodoM(NULL, NULL, NULL, aux, NULL, NULL, x, 0, depa, NULL);
    }
}

bool Matriz::verificarCabecerasVerticales(string empresa){
    NodoM* aux = this->origen;

    if(aux->abajo == NULL){
        return false;
    }else{
        while(aux != NULL){
            if(aux->nombre == empresa){
                return true;
            }
            aux = aux->abajo;
        }
        return false;
    }
}

void Matriz::crearCabeceraVertical(string empresa){
    if(verificarCabecerasVerticales(empresa) == false){
        NodoM* aux = this->origen;
        int y = 1;
        while(aux->abajo != NULL){
            aux = aux->abajo;
            y++;
        }
        aux->abajo = new NodoM(aux, NULL, NULL, NULL, NULL, NULL, 0, y, empresa, NULL);
    }
}

void Matriz::recorrerDepartamentos(){
    NodoM* aux = this->origen;
    while(aux != NULL){
        cout<< aux->nombre<<endl;
        aux = aux->derecha;
    }
}

void Matriz::recorrerEmpresas(){
    NodoM* aux = this->origen;
    while(aux != NULL){
        cout << aux->nombre<<endl;
        aux = aux->abajo;
    }
}

NodoM* Matriz::buscarDepartamento(string depa){
    NodoM* aux = this->origen;
    while(aux != NULL){
        if(aux->nombre == depa){
            break;
        }
        aux = aux->derecha;
    }
    return aux;
}

NodoM* Matriz::buscarEmpresa(string empresa){
    NodoM* aux = this->origen;
    while(aux != NULL){
        if(aux->nombre == empresa){
            break;
        }
        aux = aux->abajo;
    }
    return aux;
}

bool Matriz::verificarExistencia(string usu, string depa, string empresa){
    NodoM* columna = buscarDepartamento(depa);
    NodoM* fila = buscarEmpresa(empresa);
    int x = columna->posX, y = fila->posY;
    if(columna->abajo == NULL || fila->derecha == NULL ){
        return true;
    }else{
        bool band = false;
        while(columna != NULL){
            if(columna->posX == x && columna->posY == y){
                band = true;
                break;
            }
            columna = columna->abajo;
        }
        if(band){
            while(columna != NULL){
                if(columna->usuario->getUsuario() == usu){
                    return false;
                }
                columna = columna->adentro;
            }
        }
        return true;
    }
}

bool Matriz::agregarUsuario(string nombre, string usu, string contra, string depa, string empresa){
    crearCabeceraHorizontal(depa);
    crearCabeceraVertical(empresa);
    if(verificarExistencia(usu, depa, empresa)){
        NodoM* columna = buscarDepartamento(depa);
        NodoM* fila = buscarEmpresa(empresa);
        NodoM* listado;
        int x = columna->posX, y = fila->posY;
        Usuario* usuario = new Usuario(nombre, usu, contra);
        NodoM* nuevo = new NodoM(NULL, NULL, NULL, NULL, NULL, NULL, x, y, "Listado", usuario);
        if(columna->abajo == NULL && fila->derecha == NULL){
            nuevo->arriba = columna;
            nuevo->izquierda = fila;
            columna->abajo = nuevo;
            fila->derecha = nuevo;
            return true;
        }else{
            bool band = false;
            if(columna->abajo == NULL){
                while(fila->derecha != NULL){
                    fila = fila->derecha;
                }
                fila->derecha = nuevo;
                columna->abajo = nuevo;
                nuevo->izquierda = fila;
                nuevo->arriba = columna;
                return true;
            }else if(fila->derecha == NULL){
                while (columna->abajo != NULL) {
                    columna = columna->abajo;
                }
                columna->abajo = nuevo;
                fila->derecha = nuevo;
                nuevo->arriba = columna;
                nuevo->izquierda = fila;
                return true;
            }else{
                while(columna != NULL){
                    if(columna->posX == x && columna->posY == y){
                        listado = columna;
                        band = true;
                        break;
                    }
                    columna = columna->abajo;
                }
                if(band){
                    while(listado->adentro != NULL){
                        listado = listado->adentro;
                    }
                    listado->adentro = nuevo;
                    nuevo->afuera = listado;
                    return true;
                }else{
                    columna = buscarDepartamento(depa);
                    while(columna->abajo != NULL){
                        columna = columna->abajo;
                    }
                    while(fila->derecha != NULL){
                        fila = fila->derecha;
                    }
                    columna->abajo = nuevo;
                    fila->derecha = nuevo;
                    nuevo->arriba = columna;
                    nuevo->izquierda = fila;
                    return true;
                }
            }
        }
    }else{
        return false;
    }
    return false;
}

string Matriz::recorrerMatriz(){
    string dot = "digraph G{\nnode[shape = box]\n";
    NodoM* fila = this->origen;
    NodoM* columna = this->origen;
    while(fila != NULL){
        string rank = "{rank = same; ";
        while(columna != NULL){
            string actual = to_string(columna->posX) + to_string(columna->posY);
            if(columna->nombre == "Listado"){
                NodoM* aux = columna;
                dot += actual + " [label = <<table border = \"0\">";
                while(aux != NULL){
                    dot += "<tr><td> " + aux->usuario->getUsuario() + "</td></tr> \n";
                    aux = aux->adentro;
                }
                dot += "</table>> ]\n";

            }else{
                dot +=  actual+" [label = " + columna->nombre + "]\n";
            }

            if(columna->arriba != NULL){
                string arriba = to_string(columna->arriba->posX) + to_string(columna->arriba->posY);
                dot += actual + " -> " + arriba + "\n" ;
            }
            if(columna->abajo != NULL){
                string abajo = to_string(columna->abajo->posX) + to_string(columna->abajo->posY);
                dot += actual + " -> " + abajo + "\n" ;
            }
            if(columna->derecha != NULL){
                string derecha = to_string(columna->derecha->posX) + to_string(columna->derecha->posY);
                dot += actual + " -> " + derecha + "\n" ;
            }
            if(columna->izquierda != NULL){
                string izquierda = to_string(columna->izquierda->posX) + to_string(columna->izquierda->posY);
                dot += actual + " -> " + izquierda + "\n";
            }
            rank += actual + ";";
            columna = columna->derecha;
        }
        rank += "}\n";
        dot += rank;
        fila = fila->abajo;
        columna = fila;
    }
    dot += "}";
    return dot;
}

Usuario* Matriz::validarSesion(string usu, string contra, string depa, string empresa){
    if(verificarCabecerasHorizontales(depa) == false || verificarCabecerasVerticales(empresa) == false){
        return NULL;
    }
    NodoM* columna = buscarDepartamento(depa);
    NodoM* fila = buscarEmpresa(empresa);
    int x = columna->posX, y = fila->posY;
    bool band = false;

    while(columna != NULL){
        if(columna->posX == x && columna->posY == y){
            band = true;
            break;
        }
        columna = columna->abajo;
    }

    if(band){
        band = false;
        while(columna != NULL){
            if(columna->usuario->getUsuario() == usu && columna->usuario->getContra() == contra){
                band = true;
                break;
            }
            columna = columna->adentro;
        }
        if(band){
            return columna->usuario;
        }else{
            return NULL;
        }
    }
    return NULL;
}

ListaDobleCircular* Matriz::catalogoDeActivos(){
    NodoM* fila = this->origen;
    NodoM* columna = this->origen;
    ListaDobleCircular* retorno = new ListaDobleCircular();

    while(fila != NULL){
        while(columna != NULL){
            ListaDobleCircular* temp = columna->usuario->getAVL()->devolverActivosDisponibles();
            NodoL* aux = temp->getCabeza();
            do {
                retorno->insertar(aux->activo);
                aux = aux->siguiente;
            } while (aux != temp->getCabeza());
            columna = columna->derecha;
        }
        fila = fila->abajo;
        columna = fila;
    }
    return retorno;
}
