#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "menus.h"
#include "Estructuras/matriz.h"
#include "Estructuras/listadoblecircular.h"
#include "Estructuras/avl.h"


using namespace std;

Menus::Menus(){
    matriz = new Matriz();
    identificador = new ListaDobleCircular();
    transacciones = new ListaDobleCircular();
}

void Menus::menuSesion(){
    limpiarPantalla();
    string usu,contra,depa,empresa;
    cout << "Ingrese su usuario: ";
    cin >> usu;
    cout << "Ingrese su contraseña: ";
    cin >> contra;
    if(usu == "admin" && contra == "admin"){
        menuAdmin();
    }else{
        cout << "Ingrese su departamento: ";
        cin >> depa;
        cout << "Ingrese su empresa: ";
        cin >> empresa;
        Usuario *retorno = this->matriz->validarSesion(usu, contra, depa, empresa);
        if(retorno != NULL){
            menuUsuario(retorno, depa, empresa);
        }else{
            cout << endl << "Sus datos no se encuentran en el sistema" << endl;
            while(true){
                int opcion;
                cout << "Presione 0 para volver a intentar" << endl;
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
    cout << "| 0. Regresar al inicio de sesion                   |" << endl;
    cout << "|                                                   |" << endl;
    cout << "-----------------------------------------------------" << endl;
    while(true){
        cout << "Ingrese el numero de la opcion a realizar: ";
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
                activosPorDepartamento();
                break;
            case 4:
                activosPorEmpresa();
                break;
            case 5:
                reporteTransacciones();
                break;
            case 6:
                reporteActivosPorUsuario();
                break;
            case 7:
                reporteActivosRentadosPorUsuario();
                break;
            default:
                cout << endl << "La opcion ingresada no se encuentra en el menu" << endl;
                cout << "Pruebe nuevamente" << endl << endl;
                break;
        }
    }
}

void Menus::crearUsuario(){
    limpiarPantalla();
    string usu, contra, depa, empresa, nombre;
    cout << "Ingrese los datos del usuario a crear" << endl;
    cout << " - Ingrese el nombre completo de usuario: ";
    cin.ignore();
    getline(cin, nombre);
    cout << " - Ingrese nombre del usuario: ";
    getline(cin, usu);
    cout << " - Ingrese contraseña del usuario: ";
    getline(cin, contra);
    cout << " - Ingrese departamento del usuario: ";
    getline(cin, depa);
    cout << " - Ingrese empresa del usuario: ";
    getline(cin, empresa);

    if(this->matriz->agregarUsuario(nombre, usu, contra, depa, empresa)){
        cout << endl << "El usuario a sido creado con exito" << endl;
    }else{
        cout << endl << "El nombre de usuario ingresado ya se encuentra dentro del sistema" << endl;
    }
    while(true){
        int opcion;
        cout << endl << "Presione 0 para regresar al menu del administrador" << endl;
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
    cout << endl << "Se a generado el reporte con exito" << endl;
    while(true){
        int opcion;
        cout << endl << "Presione 0 para regresar al menu del administrador" << endl;
        cin >> opcion;
        if(opcion == 0){
            menuAdmin();
        }
    }
}

void Menus::menuUsuario(Usuario* usuarioActual, string depa, string empresa){
    limpiarPantalla();
    int opcion;
    cout << usuarioActual->getUsuario() << ": " << endl;
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
        cout << "Ingrese el numero de la opcion a realizar: ";
        cin >> opcion;
        switch (opcion) {
            case 1:
                crearActivo(usuarioActual, depa, empresa);
                break;
            case 2:
                eliminarActivo(usuarioActual, depa, empresa);
                break;
            case 3:
                modificarActivo(usuarioActual, depa, empresa);
                break;
            case 4:
                rentarActivos(usuarioActual, depa, empresa);
                break;
            case 5:
                activosRentados(usuarioActual, depa, empresa);
                break;
            case 6:
                misActivosRentados(usuarioActual, depa, empresa);
                break;
            case 7:
                menuSesion();
                break;
            default:
                cout << endl << "La opcion ingresada no se encuentra en el menu" << endl << endl;
                break;
        }
    }
}

void Menus::modificarActivo(Usuario* usuario, string depa, string empresa){
    limpiarPantalla();
    string retorno = usuario->getAVL()->retornarActivos(), id, descripcion;
    cout << retorno;
    cout << endl << "Ingrese el ID del activo a modificar: ";
    cin.ignore();
    getline(cin, id);
    Activo* activo = usuario->getAVL()->modificar(id);
    if(activo != NULL){
        cout << endl << "Ingrese la nueva descripcion del activo: ";
        getline(cin, descripcion);
        activo->setDescripcion(descripcion);
        cout << endl << "Activo modificado: " << endl;
        cout << endl << "ID: " << activo->getID() << endl;
        cout << "Nombre: " << activo->getNombre() << endl;
        cout << "Descripcion: " << activo->getDescripcion() << endl;
    }else{
        cout << endl << "El ID del activo ingresado no existe en el sistema" << endl;
    }
    while(true){
        int opcion;
        cout << endl << "Presione 0 para regresar al menu usuario" << endl;
        cin >> opcion;
        if(opcion == 0){
            menuUsuario(usuario, depa, empresa);
        }
    }
}

void Menus::eliminarActivo(Usuario* usuario, string depa, string empresa){
    limpiarPantalla();
    Activo* activo = NULL;
    string retorno = usuario->getAVL()->retornarActivos(), id;
    cout << retorno;
    cout << endl << "Ingrese el ID del activo a eliminar: ";
    cin.ignore();
    getline(cin, id);
    activo = usuario->getAVL()->eliminar(id);
    if(activo != NULL){
        cout << endl << "El activo se a eliminado exitosamente" << endl;
        cout << endl << "ID: " << activo->getID() << endl;
        cout << "Nombre: " << activo->getNombre() << endl;
        cout << "Descripcion: " << activo->getDescripcion() << endl;
    }else{
        cout << endl << "El id del activo ingresado no existe en el sistema" << endl;
    }
    while(true){
        int opcion;
        cout << endl << "Presione 0 para regresar al menu usuario" << endl;
        cin >> opcion;
        if(opcion == 0){
            menuUsuario(usuario, depa, empresa);
        }
    }
}

void Menus::crearActivo(Usuario* usuario, string depa, string empresa){
    limpiarPantalla();
    string nombre, descripcion;
    cout << "Ingrese el nombre del activo: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "Ingrese la descripcion del activo: ";
    getline(cin, descripcion);
    usuario->getAVL()->insertar(new Activo(obtenerID(), nombre, descripcion, false));
    cout << endl << "El activo a sido creado con exito!" << endl;
    while(true){
        int opcion;
        cout << endl << "Presione 0 para regresar al menu usuario" << endl;
        cin >> opcion;
        if(opcion == 0){
            menuUsuario(usuario, depa, empresa);
        }
    }
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
    limpiarPantalla();
    cout << this->matriz->catalogoDeActivos();
    string id, tiempo;
    cin.ignore();
    cout << endl << "Ingrese el id del activo a rentar: ";
    getline(cin, id);
    Activo* activo = this->matriz->buscarActivo(id);
    if(activo!=NULL){
        activo->setRentado(true);
        cout << "Ingrese el tiempo de renta del activo: ";
        getline(cin,tiempo);
        time_t t = time(0);
        tm* calendario = localtime(&t);
        string fecha = to_string(calendario->tm_mday) + "/" + to_string(calendario->tm_mon) + "/" + to_string(calendario->tm_year);
        this->transacciones->insertar(new Transaccion(obtenerID(),activo->getID(), usuario->getUsuario(), depa, empresa, fecha, tiempo, activo));
        cout << "Se a rentado el activo con exito"<<endl;
    }else{
        cout << endl << "El id ingresado no se encuentra en el sistema"<<endl;
    }
    while(true){
        int opcion;
        cout << endl << "Presione 0 para regresar al menu usuario" << endl;
        cin >> opcion;
        if(opcion == 0){
            menuUsuario(usuario, depa, empresa);
        }
    }
}

void Menus::activosRentados(Usuario* usuario, string depa, string empresa){
    limpiarPantalla();
    string retorno = this->transacciones->transaccionesPropias(usuario->getUsuario(), depa, empresa);
    cout << "Activos que e rentado: " << endl;
    cout << retorno;
    cout << endl << "1. Devolver un activo" << endl;
    cout << "0. regresar al menu de usuario" << endl;
    cout << "Presione una de las opciones para ser realizada: ";
    string opcion,id;
    Activo* activo;
    cin.ignore();
    getline(cin, opcion);
    if(opcion == "1"){
        cout << endl << "Ingrese el ID del activo a regresar: ";
        getline(cin, id);
        activo = transacciones->devolverActivo(id);
        if(activo != NULL){
            activo->setRentado(false);
            cout << endl << "Se a devuelto el activo:" << endl;
            cout << "ID: " << activo->getID() << endl;
            cout << "Nombre: " << activo->getNombre() << endl;
            cout << "Descricpion: " << activo->getDescripcion() << endl;
        }else{
            cout << "EL id ingresado no se encuentra en el sistema";
        }
        while(true){
            int opcion;
            cout << endl << "Presione 0 para regresar al menu usuario" << endl;
            cin >> opcion;
            if(opcion == 0){
                menuUsuario(usuario, depa, empresa);
            }
        }
    }else{
        menuUsuario(usuario, depa, empresa);
    }
}

void Menus::misActivosRentados(Usuario* usuario, string depa, string empresa){
    limpiarPantalla();
    string retorno = usuario->getAVL()->retornarActivosRentados();
    cout << retorno;
    while(true){
        int opcion;
        cout << endl << "Presione 0 para regresar al menu usuario" << endl;
        cin >> opcion;
        if(opcion == 0){
            menuUsuario(usuario, depa, empresa);
        }
    }
}

void Menus::activosPorDepartamento(){
    string depa;
    cout << endl << this->matriz->recorrerDepartamentos();
    cout << endl << "Ingrese el nombre del departamento: ";
    cin.ignore();
    getline(cin,depa);
    string dot = this->matriz->activosDeDepartamento(depa);
    ofstream archivo;
    archivo.open("/home/jose/Escritorio/activosXDepa.dot",ios::out);
    archivo << dot;
    archivo.close();
    system("dot /home/jose/Escritorio/activosXDepa.dot -Tpng -o /home/jose/Escritorio/activosXDepa.png");
    cout << endl << "Se a generado el reporte con exito" << endl;
    while(true){
        int opcion;
        cout << endl << "Presione 0 para regresar al menu del administrador" << endl;
        cin >> opcion;
        if(opcion == 0){
            menuAdmin();
        }
    }
}

void Menus::activosPorEmpresa(){
    string empresa;
    cout << this->matriz->recorrerEmpresas();
    cout << endl << "Ingrese el nombre de la empresa: ";
    cin.ignore();
    getline(cin,empresa);
    string dot = this->matriz->activosDeEmpresa(empresa);
    ofstream archivo;
    archivo.open("/home/jose/Escritorio/activosXEmpresa.dot",ios::out);
    archivo << dot;
    archivo.close();
    system("dot /home/jose/Escritorio/activosXEmpresa.dot -Tpng -o /home/jose/Escritorio/activosXEmpresa.png");
    cout<<endl<<"Se a generado el reporte con exito"<<endl;
    while(true){
        int opcion;
        cout<<endl<<"Presione 0 para regresar al menu del administrador"<<endl;
        cin >> opcion;
        if(opcion == 0){
            menuAdmin();
        }
    }
}

void Menus::reporteTransacciones(){
    string opcion, dot;
    ofstream archivo;
    cout << "1. Ascendente" << endl;
    cout << "2. Descendente" << endl;
    cout << "Ingrese la opcion de ordenamiento para las transacciones: ";
    cin.ignore();
    getline(cin,opcion);
    if(opcion == "1"){
        this->transacciones->ordenarAscendente();
        dot = this->transacciones->generarGrafo();
        archivo.open("/home/jose/Escritorio/tranAsc.dot",ios::out);
        archivo << dot;
        archivo.close();
        system("dot /home/jose/Escritorio/tranAsc.dot -Tpng -o /home/jose/Escritorio/tranAsc.png");
    }else{
        this->transacciones->ordenarDescendente();
        dot = this->transacciones->generarGrafo();
        archivo.open("/home/jose/Escritorio/tranDesc.dot",ios::out);
        archivo << dot;
        archivo.close();
        system("dot /home/jose/Escritorio/tranDesc.dot -Tpng -o /home/jose/Escritorio/tranDesc.png");
    }
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

void Menus::reporteActivosPorUsuario(){
    string usu, depa, empresa;
    cout << "Ingrese el nombre del usuario: ";
    cin.ignore();
    getline(cin,usu);
    cout << "Ingrese el departamento del usuario: ";
    getline(cin,depa);
    cout << "Ingrese la empresa del usuario: ";
    getline(cin,empresa);
    Usuario* usuario = this->matriz->devolverUsuario(usu, depa, empresa);
    string dot = usuario->getAVL()->retornarGrafo(usu, depa, empresa);
    ofstream archivo;
    archivo.open("/home/jose/Escritorio/activosXUsuario.dot",ios::out);
    archivo << dot;
    archivo.close();
    system("dot /home/jose/Escritorio/activosXUsuario.dot -Tpng -o /home/jose/Escritorio/activosXUsuario.png");
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

void Menus::reporteActivosRentadosPorUsuario(){
    string usu, depa, empresa;
    cout << "Ingrese el nombre del usuario: ";
    cin.ignore();
    getline(cin,usu);
    cout << "Ingrese el departamento del usuario: ";
    getline(cin,depa);
    cout << "Ingrese la empresa del usuario: ";
    getline(cin,empresa);
    string dot = this->transacciones->transaccionesGrafo(usu, depa, empresa,this->transacciones);
    ofstream archivo;
    archivo.open("/home/jose/Escritorio/activosRenXUsuario.dot",ios::out);
    archivo << dot;
    archivo.close();
    system("dot /home/jose/Escritorio/activosRnXUsuario.dot -Tpng -o /home/jose/Escritorio/activosRenXUsuario.png");
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
