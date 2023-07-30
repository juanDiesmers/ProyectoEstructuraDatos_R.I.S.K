#include "risk.h"
#include <iostream>

using namespace std;
//Implementacion de la funcion para cargar los datos y relizar operaciones

// Funciones del componente 1: Configuracion del juego
bool inicializarJuego(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    std::cout << "Ingreso correctamente a la función inicializarJuego." << std::endl;
    return true;
}

bool turnoJugador(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    std::cout << "Ingreso correctamente a la función turnoJugador." << std::endl;
    return true;

}

void salir() {
    std::cout << "Saliendo..." << std::endl;
}

// Funciones para el componente 2: Almacenamento de partidas
bool guardarPartida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    std::cout << "Ingreso correctamente a la función guardarPartida." << std::endl;
    return true;
}

bool guardarPartidaComprimida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    std::cout << "Ingreso correctamente a la función guardarPartidaComprimida." << std::endl;
    return true;
}

bool inicializarPartida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    std::cout << "Ingreso correctamente a la función inicializarPartida." << std::endl;
    return true;
}

// Funciones para el componente 3: Estrategia del juego
bool constoConquista(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios, std::string territorio) {
    std::cout << "Ingreso correctamente a la función constoConquista." << std::endl;
    return true;
}

bool conquistaMasBarata(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    std::cout << "Ingreso correctamente a la función conquistaMasBarata." << std::endl;
    return true;
}

// Declaración de la función de ayuda
void mostrarAyuda() {
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
    
}


