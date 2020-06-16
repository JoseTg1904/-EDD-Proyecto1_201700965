#include "avl.h"

NodoA::NodoA(NodoA* izquierda, NodoA* derecha, NodoA* padre, Activo* activo,int altura){
    this->izquierda = izquierda;
    this->derecha = derecha;
    this->padre = padre;
    this->activo = activo;
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
    int altura = 0;
    while(aux != NULL){
        aux->altura = altura;
        altura++;
        aux = aux->padre;
    }
}

bool AVL::buscar(string id_activo){
    NodoA* aux = this->raiz;
    bool band = false;

    while(aux != NULL){
        if(aux->activo->getID() > id_activo){
            aux = aux->izquierda;
        }else if(aux->activo->getID() < id_activo){
            aux = aux->derecha;
        }else if(aux->activo->getID() == id_activo){
            band = true;
            break;
        }
    }

    return band;
}

bool AVL::eliminar(string id_activo){
    bool band = false;

    if(buscar(id_activo)){
        eliminar(this->raiz,id_activo);
        band = true;
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
            delete (aux->izquierda);
            aux->izquierda = NULL;
        }else if(aux->izquierda == NULL && aux->derecha != NULL){
            aux->activo = aux->derecha->activo;
            delete (aux->derecha);
            aux->derecha = NULL;
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

ListaDobleCircular* AVL::devolverActivosDisponibles(){
    ListaDobleCircular* temp = new ListaDobleCircular();
    if(this->raiz->activo->getRentado() == false)
        temp->insertar(this->raiz->activo);

    activosDisponibles(temp,this->raiz);
    return temp;
}

void AVL::activosDisponibles(ListaDobleCircular* temp, NodoA* aux){
    if(aux->izquierda != NULL){
        if(aux->izquierda->activo->getRentado()==false)
            temp->insertar(aux->izquierda->activo);
        activosDisponibles(temp, aux->izquierda);
    }
    if(aux->derecha !=NULL){
        if(aux->derecha->activo->getRentado()==false)
            temp->insertar(aux->derecha->activo);
        activosDisponibles(temp, aux->derecha);
    }
}

string AVL::retornarActivosRentados(){
    activos = "Activos disponibles:\n";
    if(this->raiz->activo->getRentado())
        activos += "ID: " + this->raiz->activo->getID() + " Nombre: " + this->raiz->activo->getNombre() + "\n";
    activosRentados(this->raiz);
    return activos;
}

void AVL::activosRentados(NodoA* aux){
    if(aux->izquierda != NULL){
        if(aux->izquierda->activo->getRentado())
        activos += "ID: " + aux->izquierda->activo->getID() + " Nombre: " +
                aux->izquierda->activo->getNombre() + "\n";
        activosRentados(aux->izquierda);
    }
    if(aux->derecha !=NULL){
        if(aux->derecha->activo->getRentado())
        activos += "ID: " + aux->derecha->activo->getID() + " Nombre: " +
                aux->derecha->activo->getNombre() + "\n";
        activosRentados(aux->derecha);
    }
}

string AVL::retornarGrafo(string usuario){
    activos = usuario + " [ label = \"Propietario: "+usuario+"\"]\n";
    activos += usuario + " -> " + this->raiz->activo->getID();
    activos += this->raiz->activo->getID() + "[ label = \"ID: "+ this->raiz->activo->getID() +
            " Nombre: "+this->raiz->activo->getNombre() + " \"";
    if(this->raiz->activo->getRentado()){
        activos += "style = filled color = red ]\n";
    }else{
        activos += "style = filled color = green ]\n";
    }
    generarGrafo(this->raiz);
    return activos;
}

void AVL::generarGrafo(NodoA* aux){
    if(aux->izquierda != NULL){
        activos += aux->izquierda->activo->getID() + "[ label = \"ID: "+ aux->izquierda->activo->getID() +
                " Nombre: "+aux->izquierda->activo->getNombre() + " \"";
        if(aux->izquierda->activo->getRentado()){
            activos += "style = filled color = red ]\n";
        }else{
            activos += "style = filled color = green ]\n";
        }
        activos += aux->activo->getID() + " -> " + aux->izquierda->activo->getID()+"\n";
        generarGrafo(aux->izquierda);
    }
    if(aux->derecha !=NULL){
        activos += aux->derecha->activo->getID() + "[ label = \"ID: "+ aux->derecha->activo->getID() +
                " Nombre: "+aux->derecha->activo->getNombre() + " \"";
        if(aux->derecha->activo->getRentado()){
            activos += "style = filled color = red ]\n";
        }else{
            activos += "style = filled color = green ]\n";
        }
        activos += aux->activo->getID() + " -> " + aux->derecha->activo->getID()+"\n";
        generarGrafo(aux->derecha);
    }
}
