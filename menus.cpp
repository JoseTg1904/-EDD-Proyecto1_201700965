#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include "menus.h"

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
    string usu,contra,depa,empresa;
    cout << "Ingrese los datos del usuario a crear" << endl;
    cout << " - Ingrese nombre del usuario: ";
    cin >> usu;
    cout << " - Ingrese contraseña del usuario: ";
    cin >> contra;
    cout << " - Ingrese departamento del usuario: ";
    cin >> depa;
    cout << " - Ingrese empresa del usuario: ";
    cin >> empresa;
    //crear objeto usuario
    //validar existencia
    //meterlo a la matriz
}


