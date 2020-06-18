#include "avl.h"

NodoA::NodoA(NodoA* izquierda, NodoA* derecha, NodoA* padre, Activo* activo, int altura){
    this->izquierda = izquierda;
    this->derecha = derecha;
    this->padre = padre;
    this->activo = activo;
    this->altura = altura;
}

NodoA::NodoA(NodoA* izquierda, NodoA* derecha, NodoA* padre, int valor, int altura){
    this->izquierda = izquierda;
    this->derecha = derecha;
    this->padre = padre;
    this->valor = valor;
    this->altura = altura;
}

AVL::AVL(){
    this->raiz = NULL;
}

void AVL::insertar(Activo* activo){
    if(raiz == NULL){
        raiz = new NodoA(NULL, NULL, NULL, activo, 0);
    }else{
        NodoA* aux = this->raiz;
        while(true){
            if(aux->activo->getID() > activo->getID()){
                if(aux->izquierda == NULL){
                    aux->izquierda = new NodoA(NULL, NULL, aux, activo, 0);
                    calcularAltura(aux->izquierda);
                    break;
                }
                aux = aux->izquierda;
            }else if(aux->activo->getID() < activo->getID()){
                if(aux->derecha == NULL){
                    aux->derecha = new NodoA(NULL, NULL, aux, activo, 0);
                    calcularAltura(aux->derecha);
                    break;
                }
                aux = aux->derecha;
            }else{
                break;
            }
        }
    }
}

void AVL::calcularAltura(NodoA* aux){
    int altura = 1, fe = 0;
    while(aux != NULL){
        aux->altura = altura;
        if(altura != 1){
            if(aux->derecha == NULL){
                fe = 0 - aux->izquierda->altura;
            }else if(aux->izquierda == NULL){
                fe = aux->derecha->altura - 0;
            }else{
                fe = aux->derecha->altura - aux->izquierda->altura;
            }
        }
        //II ROTAR DERECHA COMPROBAR SI ES SIMPLE O DOBLE
        if(fe == -2){
            int it = 0;
            NodoA* aux1 = aux;
            while(aux1 != NULL){
                it++;
                aux1 = aux1->izquierda;
            }
            //rotacion simple a la derecha
            if(it == 3){
                NodoA* actual = aux;
                NodoA* anterior = aux->izquierda;
                if(anterior->derecha == NULL){
                    actual->izquierda = NULL;
                }else{
                    actual->izquierda = anterior->derecha;
                }
                actual->izquierda->padre = actual;
                anterior->derecha = actual;
                if(actual->padre == NULL){
                    anterior->padre = NULL;
                }else{
                    anterior->padre = actual->padre;
                }
                actual->padre = anterior;
                actual->altura = actual->altura - 1;
                if(actual == this->raiz){
                    this->raiz = anterior;
                }
                actual = anterior;
            //rotacion doble a la derecha
            }else{
                NodoA* actual = aux;
                NodoA* anteriorI = aux->izquierda;
                NodoA* anteriorID = aux->izquierda->derecha;
                if(anteriorID->izquierda == NULL){
                    anteriorI->derecha = NULL;
                }else{
                    anteriorI->derecha = anteriorID->izquierda;
                }
                if(anteriorI->derecha != NULL){
                    anteriorI->derecha->padre = anteriorI;
                }

                anteriorID->izquierda = anteriorI;
                anteriorID->izquierda->padre = anteriorID;
                if(anteriorID->derecha == NULL){
                    actual->izquierda = NULL;
                }else{
                    actual->izquierda = anteriorID->derecha;
                }
                if(actual->izquierda != NULL){
                    actual->izquierda->padre = actual;
                }
                anteriorID->derecha = actual;
                actual->padre = anteriorID;
                if(actual == this->raiz){
                    this->raiz = anteriorID;
                    anteriorID->padre = NULL;
                }
                actual->altura = actual->altura - 2;
                anteriorID->altura = anteriorID->altura + 1;
                anteriorI->altura = anteriorI->altura - 1;
                actual = anteriorID;
            }
        //DD ROTAR IZQUIERDA COMPROBAR SI ES SIMPLE O DOBLE
        }else if(fe == 2){
            int it = 0;
            NodoA* aux1 = aux;
            while(aux1 != NULL){
                it++;
                aux1 = aux1->derecha;
            }
            //rotacion simple a la izquierda
            if(it == 3){
                NodoA* actual = aux;
                NodoA* anterior = aux->derecha;
                if(anterior->izquierda == NULL){
                    actual->derecha = NULL;
                }else{
                    actual->derecha = anterior->izquierda;
                }
                actual->derecha->padre = actual;
                anterior->izquierda = actual;
                if(actual->padre == NULL){
                    anterior->padre = NULL;
                }else{
                    anterior->padre = actual->padre;
                }
                actual->padre = anterior;
                actual->altura = actual->altura - 1;
                if(actual == this->raiz){
                    this->raiz = anterior;
                }
                actual = anterior;
            //rotacion doble a la izquierda
            }else{
                NodoA* actual = aux;
                NodoA* anteriorD = aux->derecha;
                NodoA* anteriorDI = aux->derecha->izquierda;
                if(anteriorDI->derecha == NULL){
                    anteriorD->izquierda = NULL;
                }else{
                    anteriorD->izquierda = anteriorDI->derecha;
                }
                if(anteriorD->izquierda != NULL){
                    anteriorD->izquierda->padre = anteriorD;
                }

                anteriorDI->derecha = anteriorD;
                anteriorDI->derecha->padre = anteriorDI;
                if(anteriorDI->izquierda == NULL){
                    actual->derecha = NULL;
                }else{
                    actual->derecha = anteriorDI->izquierda;
                }
                if(actual->derecha != NULL){
                    actual->derecha->padre = actual;
                }
                anteriorDI->izquierda = actual;
                actual->padre = anteriorDI;
                if(actual == this->raiz){
                    this->raiz = anteriorDI;
                    anteriorDI->padre = NULL;
                }
                actual->altura = actual->altura - 2;
                anteriorDI->altura = anteriorDI->altura + 1;
                anteriorD->altura = anteriorD->altura - 1;
                actual = anteriorDI;
            }
        }
        altura++;
        aux = aux->padre;
    }
}

Activo* AVL::buscar(string id_activo){
    NodoA* aux = this->raiz;
    Activo* band = NULL;

    while(aux != NULL){
        if(aux->activo->getID() > id_activo){
            aux = aux->izquierda;
        }else if(aux->activo->getID() < id_activo){
            aux = aux->derecha;
        }else if(aux->activo->getID() == id_activo){
            band = aux->activo;
            break;
        }
    }

    return band;
}

Activo* AVL::eliminar(string id_activo){
    Activo* band = buscar(id_activo);
    if(band != NULL){
        eliminar(this->raiz, id_activo);
    }
    return band;
}

void AVL::eliminar(NodoA* aux, string id_activo){
    if(aux == NULL){
        return;
    }else if(aux->activo->getID() < id_activo){
       eliminar(aux->derecha, id_activo);
    }else if(aux->activo->getID() > id_activo){
        eliminar(aux->izquierda, id_activo);
    }else{
        if(aux->izquierda != NULL && aux->derecha == NULL){
            aux->activo = aux->izquierda->activo;
            aux->izquierda = NULL;
            delete (aux->izquierda);
        }else if(aux->izquierda == NULL && aux->derecha != NULL){
            aux->activo = aux->derecha->activo;
            aux->derecha = NULL;
            delete (aux->derecha);
        }else if(aux->izquierda == NULL && aux->derecha == NULL){
            if(aux->padre->activo->getID() < aux->activo->getID()){
                aux->padre->derecha = NULL;
            }else{
                aux->padre->izquierda = NULL;
            }
            if(aux == this->raiz){
                this->raiz = NULL;
            }
            delete(aux);
        }else{
            Activo* retorno = buscarMenor(aux);
            aux->activo = retorno;
        }
    }
}

Activo* AVL::buscarMenor(NodoA* aux){
    Activo* val;
    aux = aux->izquierda;
    while(aux->derecha != NULL){
        aux = aux->derecha;
    }
    if(aux->padre->activo->getID() < aux->activo->getID()){
        aux->padre->derecha = NULL;
    }else{
        aux->padre->izquierda = NULL;
    }
    val = aux->activo;
    delete (aux);
    return val;
}

string AVL::retornarActivos(){
    activos = "Activos disponibles:\n";
    activos += "ID: " + this->raiz->activo->getID() + " Nombre: " + this->raiz->activo->getNombre() + "\n";
    llenarListaActivos(this->raiz);
    return activos;
}

void AVL::llenarListaActivos(NodoA* aux){
    if(aux->izquierda != NULL){
        activos += "ID: " + aux->izquierda->activo->getID() + " Nombre: " +
                aux->izquierda->activo->getNombre() + "\n";
        llenarListaActivos(aux->izquierda);
    }
    if(aux->derecha !=NULL){
        activos += "ID: " + aux->derecha->activo->getID() + " Nombre: " +
                aux->derecha->activo->getNombre() + "\n";
        llenarListaActivos(aux->derecha);
    }
}

Activo* AVL::modificar(string id_activo){
    NodoA* aux = this->raiz;
    Activo* retorno = NULL;

    while(aux != NULL){
        if(aux->activo->getID() > id_activo){
            aux = aux->izquierda;
        }else if(aux->activo->getID() < id_activo){
            aux = aux->derecha;
        }else if(aux->activo->getID() == id_activo){
            retorno = aux->activo;
            break;
        }
    }

    return retorno;
}

string AVL::devolverActivosDisponibles(){
    activos = "";
    if(this->raiz->activo->getRentado() == false){
        activos += "ID: "+this->raiz->activo->getID()+" Nombre: "+this->raiz->activo->getNombre()+" Descripcion: "
                + this->raiz->activo->getDescripcion()+"\n";
    }
    activosDisponibles(this->raiz);
    return activos;
}

void AVL::activosDisponibles(NodoA* aux){
    if(aux->izquierda != NULL){
        if(aux->izquierda->activo->getRentado() == false){
            activos += "ID: "+aux->izquierda->activo->getID()+" Nombre: "+aux->izquierda->activo->getNombre()+" Descripcion: "
                    + aux->izquierda->activo->getDescripcion()+"\n";
        }
        activosDisponibles(aux->izquierda);
    }
    if(aux->derecha != NULL){
        if(aux->derecha->activo->getRentado() == false){
            activos += "ID: "+aux->derecha->activo->getID()+" Nombre: "+aux->derecha->activo->getNombre()+" Descripcion: "
                    + aux->derecha->activo->getDescripcion()+"\n";
        }
        activosDisponibles(aux->derecha);
    }
}

string AVL::retornarActivosRentados(){
    activos = "Mis activos rentados:\n";
    if(this->raiz->activo->getRentado()){
        activos += "ID: " + this->raiz->activo->getID() + " Nombre: " + this->raiz->activo->getNombre() + "\n";
    }
    activosRentados(this->raiz);
    return activos;
}

void AVL::activosRentados(NodoA* aux){
    if(aux->izquierda != NULL){
        if(aux->izquierda->activo->getRentado()){
            activos += "ID: " + aux->izquierda->activo->getID() + " Nombre: " + aux->izquierda->activo->getNombre() + "\n";
        }
        activosRentados(aux->izquierda);
    }
    if(aux->derecha !=NULL){
        if(aux->derecha->activo->getRentado()){
            activos += "ID: " + aux->derecha->activo->getID() + " Nombre: " + aux->derecha->activo->getNombre() + "\n";
        }
        activosRentados(aux->derecha);
    }
}

string AVL::retornarGrafo(string usuario, string depa, string empresa){
    string id = "\""+usuario+depa+empresa+"\"";
    activos = id + " [ label = \"Propietario: "+usuario+"\nDepartamento: "+
            depa+"\n Empresa: " + empresa + "\"]\n";
    activos += id + " -> \"" + this->raiz->activo->getID() + "\"\n";
    if(this->raiz->activo->getRentado()){
        activos += "\"" + this->raiz->activo->getID() + "\"" +
                " [ label = \"ID: " + this->raiz->activo->getID() + " \nNombre: "
                + this->raiz->activo->getNombre() +" \"style = filled color = red ]\n";
    }else{
        activos += "\"" + this->raiz->activo->getID() + "\"" +
                " [ label = \"ID: " + this->raiz->activo->getID() + " \nNombre: "
                + this->raiz->activo->getNombre() +" \"style = filled color = green ]\n";
    }
    generarGrafo(this->raiz);
    return activos;
}

void AVL::generarGrafo(NodoA* aux){
    if(aux->izquierda != NULL){
        if(aux->izquierda->activo->getRentado()){
            activos += "\"" + aux->izquierda->activo->getID() + "\"" +
                    " [ label = \"ID: " + aux->izquierda->activo->getID() + " \nNombre: "
                    + aux->izquierda->activo->getNombre() +" \"style = filled color = red ]\n";
        }else{
            activos += "\"" + aux->izquierda->activo->getID() + "\"" +
                    " [ label = \"ID: " + aux->izquierda->activo->getID() + " \nNombre: "
                    + aux->izquierda->activo->getNombre() +" \"style = filled color = green ]\n";
        }
        activos += "\"" + aux->activo->getID() + "\" -> \"" + aux->izquierda->activo->getID()+"\"\n";
        generarGrafo(aux->izquierda);
    }
    if(aux->derecha !=NULL){
        if(aux->derecha->activo->getRentado()){
            activos += "\"" + aux->derecha->activo->getID() + "\"" +
                    " [ label = \"ID: " + aux->derecha->activo->getID() + " \nNombre: "
                    + aux->derecha->activo->getNombre() +" \"style = filled color = red ]\n";
        }else{
            activos += "\"" + aux->derecha->activo->getID() + "\"" +
                    " [ label = \"ID: " + aux->derecha->activo->getID() + " \nNombre: "
                    + aux->derecha->activo->getNombre() +" \"style = filled color = green ]\n";
        }
        activos += "\"" + aux->activo->getID() + "\" -> \"" + aux->derecha->activo->getID()+"\"\n";
        generarGrafo(aux->derecha);
    }
}
