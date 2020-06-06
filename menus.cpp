#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <cstdlib>
#include "menus.h"
#include "Estructuras/matriz.h"

using namespace std;

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
        Usuario *retorno = matriz->validarSesion(usu,contra,depa,empresa);
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
    cin.ignore();
    getline(cin,usu);
    cout << " - Ingrese contraseña del usuario: ";
    cin.ignore();
    getline(cin,contra);
    cout << " - Ingrese departamento del usuario: ";
    cin.ignore();
    getline(cin,depa);
    cout << " - Ingrese empresa del usuario: ";
    cin.ignore();
    getline(cin,empresa);
    cout<<nombre<<endl;
    if(matriz->agregarUsuario(nombre,usu,contra,depa,empresa)){
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
    string dot = matriz->recorrerMatriz();
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
        if(opcion==0){
            menuAdmin();
        }
    }
}

void Menus::menuUsuario(Usuario *usuarioActual,string depa,string empresa){
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
                break;
            case 2:
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
                menuSesion();
                break;
            default:
                cout << "  La opcion ingresada no se encuentra en el menu" << endl;
                break;
        }
    }
}
