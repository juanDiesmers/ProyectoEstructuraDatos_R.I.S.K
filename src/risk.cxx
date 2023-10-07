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

void pantallaPrincipal() {
    limpiarPantalla();
    cout << "-----------------------------------------------------------------------------------" << endl;
    cout << "|                                                                                  |" << endl;
    cout << "|                            Bienvenid@ al Juego Risk                              |" << endl;
    cout << "|                                                                                  |" << endl;
    cout << " Por favor, digite el comando 'ayuda' para desplegar todos los comandos disponibles." << endl;
    cout << "-----------------------------------------------------------------------------------" << endl;
}

// Funciones para el componente 2: Almacenamento de partidas
bool guardarPartida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    limpiarPantalla();
    std::cout << "Ingreso correctamente a la función guardarPartida." << std::endl;
    return true;
}

bool guardarPartidaComprimida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    limpiarPantalla();
    std::cout << "Ingreso correctamente a la función guardarPartidaComprimida." << std::endl;
    return true;
}

bool inicializarPartida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    limpiarPantalla();
    std::cout << "Ingreso correctamente a la función inicializarPartida." << std::endl;
    return true;
}

// Funciones para el componente 3: Estrategia del juego
bool constoConquista(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios, std::string territorio) {
    limpiarPantalla();
    std::cout << "Ingreso correctamente a la función constoConquista." << std::endl;
    return true;
}

bool conquistaMasBarata(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    limpiarPantalla();
    std::cout << "Ingreso correctamente a la función conquistaMasBarata." << std::endl;
    return true;
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

