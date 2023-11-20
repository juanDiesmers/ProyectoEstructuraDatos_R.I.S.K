#include "risk.h"
#include <iostream>
#include <fstream>
using namespace std;

//Implementacion de la funcion para cargar los datos y relizar operaciones

void limpiarPantalla() {
    #ifdef _WIN32
        system("cls");
    #else
        cout << "\x1B[2J\x1B[H"; // Código ANSI para limpiar la pantalla en sistemas UNIX
    #endif
}

void pausarPantalla() {
    #ifdef _WIN32
        system("pause");
    #else
        cout << "Presione enter para continuar..." << endl;
        cin.ignore();
        cin.get();
    #endif
}

void pantallaPrincipal() {
    limpiarPantalla();
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "|                                                                                  |" << endl;
    cout << "|                            Bienvenid@ al Juego Risk                              |" << endl;
    cout << "|                                                                                  |" << endl;
    cout << " Por favor, digite el comando 'ayuda' para desplegar todos los comandos disponibles." << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
}



// Declaración de la función de ayuda
void mostrarAyuda() {
    limpiarPantalla();
    fstream ayuda;
    string texto;
    ayuda.open("help.txt", ios::in); //archivo de modo lectura

    if(ayuda.fail()){
        std::cout << "No se pudo abrir el archivo" << endl;
    }
    
    while(!ayuda.eof()){
	getline(ayuda,texto);
	std::cout << texto << endl;
    }

    ayuda.close();

    std::cout << "Ingreso correctamente a la función mostrar Ayuda." << std::endl;
    
}

