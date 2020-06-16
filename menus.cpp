#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "menus.h"
#include "Estructuras/matriz.h"
#include "Estructuras/listadoblecircular.h"


using namespace std;

Menus::Menus(){
    matriz = new Matriz();
    identificador = new ListaDobleCircular();
    transacciones = new ListaDobleCircular();
}

void Menus::menuSesion(){

limpiarPantalla();
 string usu,contra,depa,empresa;
    cout << " Ingrese su usuario: ";
    cin >> usu;
    cout << " Ingrese su contraseña: ";
    cin >> contra;
    if(usu == "admin" && contra == "admin"){
        menuAdmin();
    }else{
        cout <<" Ingrese su departamento: ";
        cin >>depa;
        cout <<" Ingrese su empresa: ";
        cin >>empresa;
        Usuario *retorno = this->matriz->validarSesion(usu,contra,depa,empresa);
        if(retorno != NULL){
            menuUsuario(retorno,depa,empresa);
        }else{
            cout<<"Sus datos no se encuentran en el sistema"<<endl;
            while(true){
                int opcion;
                cout<<"Presione 0 para volver a intentar"<<endl;
                cin >> opcion;
                if(opcion == 0){
                    menuSesion();
                }
            }
        }
    }
}

void Menus::limpiarPantalla(){
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

void Menus::menuAdmin(){
    limpiarPantalla();
    int opcion;
    cout << "-----------------Menu Administrador------------------" << endl;
    cout << "|                                                   |" << endl;
    cout << "| 1. Registrar usuario                              |" << endl;
    cout << "| 2. Reporte matriz dispersa                        |" << endl;
    cout << "| 3. Reporte activos disponibles de un departamento |" << endl;
    cout << "| 4. Reporte activos disponibles de una empresa     |" << endl;
    cout << "| 5. Reporte transacciones                          |" << endl;
    cout << "| 6. Reporte activos de un usuario                  |" << endl;
    cout << "| 7. Activos rentados por un usuario                |" << endl;
    cout << "| 8. Ordenar transacciones                          |" << endl;
    cout << "| 0. Regresar al inicio de sesion                   |" << endl;
    cout << "|                                                   |" << endl;
    cout << "-----------------------------------------------------" << endl;

    while(true){
        cout << " Ingrese el numero de la opcion a realizar: ";
        cin >> opcion;
        switch (opcion) {
            case 0:
                menuSesion();
                break;
            case 1:
                crearUsuario();
                break;
            case 2:
                reporteMatriz();
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            case 6:
                break;
            case 7:
                break;
            case 8:
                break;
            default:
                cout << "  La opcion ingresada no se encuentra en el menu" << endl;
                break;
        }
    }
}

void Menus::crearUsuario(){
    limpiarPantalla();
    string usu,contra,depa,empresa,nombre;
    cout << "Ingrese los datos del usuario a crear" << endl;
    cout << " - Ingrese el nombre completo de usuario: ";
    cin.ignore();
    getline(cin,nombre);
    cout << " - Ingrese nombre del usuario: ";
    getline(cin,usu);
    cout << " - Ingrese contraseña del usuario: ";
    getline(cin,contra);
    cout << " - Ingrese departamento del usuario: ";
    getline(cin,depa);
    cout << " - Ingrese empresa del usuario: ";
    getline(cin,empresa);

    if(this->matriz->agregarUsuario(nombre,usu,contra,depa,empresa)){
        cout<<"El usuario a sido creado con exito"<<endl;
    }else{
        cout<<"El nombre de usuario ingresado ya se encuentra dentro del sistema"<<endl;
    }
    while(true){
        int opcion;
        cout<<"Presione 0 para regresar al menu del administrador"<<endl;
        cin >> opcion;
        if(opcion == 0){
            menuAdmin();
        }
    }
}

void Menus::reporteMatriz(){
    string dot = this->matriz->recorrerMatriz();
    ofstream archivo;
    archivo.open("/home/jose/Escritorio/matriz.dot",ios::out);
    archivo << dot;
    archivo.close();
    system("dot /home/jose/Escritorio/matriz.dot -Tpng -o /home/jose/Escritorio/matriz.png");
    cout<<"Se a generado el reporte con exito"<<endl;
    while(true){
        int opcion;
        cout<<"Presione 0 para regresar al menu del administrador"<<endl;
        cin >> opcion;
        if(opcion == 0){
            menuAdmin();
        }
    }
}

void Menus::menuUsuario(Usuario* usuarioActual, string depa, string empresa){
    limpiarPantalla();
    int opcion;
    cout << usuarioActual->getUsuario()<<": "<<endl;
    cout << "-------Menu Usuario--------" << endl;
    cout << "|                         |" << endl;
    cout << "| 1. Agregar activo       |" << endl;
    cout << "| 2. Eliminar activo      |" << endl;
    cout << "| 3. Modificar activo     |" << endl;
    cout << "| 4. Rentar activo        |" << endl;
    cout << "| 5. Activos rentados     |" << endl;
    cout << "| 6. Mis activos rentados |" << endl;
    cout << "| 7. Cerrar sesion        |" << endl;
    cout << "|                         |" << endl;
    cout << "---------------------------" << endl;

    while(true){
        cout << " Ingrese el numero de la opcion a realizar: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                crearActivo(usuarioActual,depa,empresa);
                break;
            case 2:
                eliminarActivo(usuarioActual,depa,empresa);
                break;
            case 3:
                modificarActivo(usuarioActual,depa,empresa);
                break;
            case 4:
                rentarActivos(usuarioActual,depa,empresa);
                break;
            case 5:
                activosRentados(usuarioActual,depa,empresa);
                break;
            case 6:
                misActivosRentados(usuarioActual,depa,empresa);
                break;
            case 7:
                menuSesion();
                break;
            default:
                cout << "  La opcion ingresada no se encuentra en el menu" << endl;
                break;
        }
    }
}

void Menus::modificarActivo(Usuario* usuario, string depa,string empresa){
    string retorno = usuario->getAVL()->retornarActivos(), id, descripcion;
    cout << retorno;
    cout << "Ingrese el ID del activo a modificar ";
    cin.ignore();
    getline(cin,id);
    Activo* activo = usuario->getAVL()->modificar(id);
    if(activo != NULL){
        cout << "Ingrese la nueva descripcion del activo";
        getline(cin,descripcion);
        activo->setDescripcion(descripcion);
        cout << "Activo modificado: ";
        cout << "ID: " << activo->getID() << endl;
        cout << "Nombre: " << activo->getNombre() << endl;
        cout << "Descripcion: " << activo->getDescripcion() << endl;
    }else{
        cout << "El id del activo ingresado no existe en el sistema";
    }
}

void Menus::eliminarActivo(Usuario* usuario, string depa, string empresa){
    string retorno = usuario->getAVL()->retornarActivos(), id;
    cout << retorno;
    cout << "Ingrese el ID del activo a eliminar; ";
    cin.ignore();
    getline(cin,id);
    if(usuario->getAVL()->eliminar(id)){
        cout << "El activo se a eliminado exitosamente";
    }else{
        cout << "El id del activo ingresado no existe en el sistema";
    }
}

void Menus::crearActivo(Usuario* usuario,string depa,string empresa){
    string nombre,descripcion;
    cout << "Ingrese el nombre del activo: ";
    cin.ignore();
    getline(cin,nombre);
    cout << "Ingrese la descripcion del activo: ";
    getline(cin,descripcion);
    usuario->getAVL()->insertar(new Activo(obtenerID(),nombre,descripcion,false));
    cout << "El activo a sido creado con exito!";
}

string Menus::obtenerID(){
     string id;
     while(true){
        id = this->identificador->generarID();
        if(this->identificador->verificarID(id) == false){
            this->identificador->insertar(id);
            break;
        }
      }
     return id;
}

void Menus::rentarActivos(Usuario* usuario,string depa,string empresa){
    ListaDobleCircular* temp = this->matriz->catalogoDeActivos();
    string catalogo,id,tiempo;
    NodoL* aux = temp->getCabeza();

    do {
        catalogo += "ID: "+aux->activo->getID()+" Nombre: "+aux->activo->getNombre()+" Descripcion: "
                + aux->activo->getDescripcion()+"\n";
        aux = aux->siguiente;
    } while (aux!=temp->getCabeza());
    aux = temp->getCabeza();
    cout << catalogo;
    cin.ignore();
    cout << "Ingrese el id del activo a rentar: ";
    getline(cin,id);
    do {
        if(aux->activo->getID() == id){
            aux->activo->setRentado(true);
            break;
        }
            aux = aux->siguiente;
    } while (aux!=temp->getCabeza());
    cout << "Ingrese el tiempo de renta del activo: ";
    getline(cin,tiempo);

    time_t t = time(0);
    tm* calendario = localtime(&t);
    string fecha = to_string(calendario->tm_mday) + "/" + to_string(calendario->tm_mon) + "/" + to_string(calendario->tm_year);
    transacciones->insertar(new Transaccion(obtenerID(),aux->activo->getID(),
                                            usuario->getUsuario(),depa,empresa,fecha,tiempo));
}

void Menus::activosRentados(Usuario* usuario, string depa, string empresa){
    string retorno = this->transacciones->transaccionesPropias(usuario->getUsuario(), depa, empresa);
    cout << retorno;
    cout << "1. Devolver un activo";
    cout << "0. regresar al menu de usuario";
    string opcion,id;
    string* activo;
    getline(cin,opcion);
    if(opcion == "1"){
        cout << "Ingrese el ID del activo a regresar: ";
        getline(cin,id);
        activo = transacciones->eliminar(id);
        if(activo[0]!="NULL"){
            Usuario* usu = matriz->cambiarEstadoActivo(usuario->getUsuario(),depa,empresa);
            Activo* active = usu->getAVL()->modificar(activo[1]);
            active->setRentado(false);
            cout << "Se a devuelto el activo";
        }else{
            cout << "EL id ingresado no se encuentra en el sistema";
        }
    }else{
    }
}

void Menus::misActivosRentados(Usuario* usuario, string depa, string empresa){
    string retorno = usuario->getAVL()->retornarActivosRentados();
    cout << retorno;
}
