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

// Funciones del componente 1: Configuracion del juego
bool inicializarJuego(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    limpiarPantalla();
    std::cout << "Ingreso correctamente a la función inicializarJuego." << std::endl;
    return true;
}

bool turnoJugador(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    limpiarPantalla();
    std::cout << "Ingreso correctamente a la función turnoJugador." << std::endl;
    return true;

}

void salir() {
    limpiarPantalla();
    std::cout << "Saliendo del juego. Hasta luego!" << std::endl;
    //system ("clear");
    exit(0);//finaliza la ejecucion del programa
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
/*void mostrarAyuda() {
    std::cout << "Ingreso correctamente a la función mostrar Ayuda." << std::endl;

    // Menú de ayuda
    std::cout << "\n==== Menú de Ayuda ====" << std::endl;
    std::cout << "1. Inicializar Juego" << std::endl;
    std::cout << "2. Guardar Partida" << std::endl;
    std::cout << "3. Guardar Partida Comprimida" << std::endl;
    std::cout << "4. Inicializar Partida" << std::endl;
    std::cout << "5. Costo de Conquista" << std::endl;
    std::cout << "6. Conquista Más Barata" << std::endl;
    std::cout << "7. Salir" << std::endl;
    std::cout << "========================" << std::endl;
    
} */


