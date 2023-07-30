#ifndef RISK_H
#define RISK_H

#include <string>
#include <vector>

//Declaraciones de las estructuras para paises y continentes
struct Territorio{
    int id;
    std::string nombre;
    std::string jugador;
    int unidades_ejercito;
    std::vector<int> territorios_vecinos;
};

//Estructura para representar un jugador
struct Jugador{
    std::string nombre;
    std::string color;
    std::vector<Territorio> territorio;
    std::vector<int> tarjetas;
};

//funciones del componente 1: Configuracion del juego
bool inicializarJuego(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios);
bool turnoJugador(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios);
void salir();

//funcion para el componente 2: Almacenamento de partidas
bool guardarPartida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios);
bool guardarPartidaComprimida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios);
bool inicializarPartida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios);

//funciones para el componente 3: Estrategia del juego
bool constoConquista(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios, std::string territorio);
bool conquistaMasBarata(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios);

//Declararion de la funcion de ayuda
void mostrarAyuda();

#endif //risk.h