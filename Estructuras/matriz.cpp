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

string Matriz::recorrerDepartamentos(){
    string retorno = "Departamentos disponibles:\n";
    NodoM* aux = this->origen;
    while(aux != NULL){
        if(aux->nombre != "Origen"){
            retorno += aux->nombre + "\n";
        }
        aux = aux->derecha;
    }
    return retorno;
}

string Matriz::recorrerEmpresas(){
    string retorno = "Empresas disponibles:\n";
    NodoM* aux = this->origen;
    while(aux != NULL){
        if(aux->nombre != "Origen"){
            retorno += aux->nombre + "\n";
        }
        aux = aux->abajo;
    }
    return retorno;
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

string Matriz::catalogoDeActivos(){
    NodoM* fila = this->origen;
    NodoM* columna = this->origen;
    string retorno = "Activos disponibles:\n";
    while(fila != NULL){
        while(columna != NULL){
            if(columna->nombre=="Listado"){
                retorno += columna->usuario->getAVL()->devolverActivosDisponibles();
            }
            columna = columna->derecha;
        }
        fila = fila->abajo;
        columna = fila;
    }
    return retorno;
}

Usuario* Matriz::cambiarEstadoActivo(string usu, string depa, string empresa){
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
            if(columna->usuario->getUsuario() == usu){
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

string Matriz::activosDeEmpresa(string empresa){
    NodoM* aux = buscarEmpresa(empresa);
    NodoM* usuarios;
    NodoM* aux1 = this->origen->derecha;
    aux = aux->derecha;
    string grafo = "digraph Arboles{\n";
    while(aux != NULL && aux1 != NULL){
        usuarios = aux;
        while (usuarios != NULL) {
            grafo += usuarios->usuario->getAVL()->retornarGrafo(usuarios->usuario->getUsuario(), aux1->nombre, empresa);
            grafo += "\n";
            usuarios = usuarios->adentro;
        }
        aux = aux->derecha;
        aux1 = aux1->derecha;
    }
    grafo += "}";
    return grafo;
}

string Matriz::activosDeDepartamento(string depa){
    NodoM* aux = buscarDepartamento(depa);
    NodoM* usuarios;
    NodoM* aux1 = this->origen->abajo;
    aux = aux->abajo;
    string grafo = "digraph Arboles{\n";
    while(aux != NULL && aux1 != NULL){
        usuarios = aux;
        while (usuarios != NULL) {
            grafo += usuarios->usuario->getAVL()->retornarGrafo(usuarios->usuario->getUsuario(), depa,
                                                                aux1->nombre);
            grafo += "\n";
            usuarios = usuarios->adentro;
        }
        aux = aux->abajo;
        aux1 = aux1->abajo;
    }
    grafo += "}";
    return grafo;
}

Usuario* Matriz::devolverUsuario(string usu, string depa, string empresa){
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
            if(columna->usuario->getUsuario() == usu){
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

Activo* Matriz::buscarActivo(string id_activo){
    NodoM* fila = this->origen;
    NodoM* columna = this->origen;
    Activo* retorno = NULL;
    bool band = false;

    while(fila != NULL){
        while(columna != NULL){
            if(columna->nombre=="Listado"){
                retorno = columna->usuario->getAVL()->modificar(id_activo);
                if(retorno !=NULL){
                    band = true;
                    break;
                }
            }
            columna = columna->derecha;
        }
        if(band){
            break;
        }
        fila = fila->abajo;
        columna = fila;
    }
    return retorno;
}

string Matriz::usuariosMatriz(){
    NodoM* fila = this->origen;
    NodoM* columna = this->origen;
    string retorno = "Usuarios disponibles:\n", depa, empresa;
    while(fila != NULL){
        depa = columna->nombre;
        empresa = fila->nombre;
        while(columna != NULL){
            if(columna->nombre=="Listado"){
                retorno += "Usuario: " + columna->usuario->getUsuario() + " Departamento: " + depa
                        + " Empresa: " + empresa + "\n";
            }
            columna = columna->derecha;
        }
        fila = fila->abajo;
        columna = fila;
    }
    return retorno;
}
