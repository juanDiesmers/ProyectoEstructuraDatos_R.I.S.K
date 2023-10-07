#ifndef RISK_H
#define RISK_H

#include "Asignacion/asignacion.h"

void limpiarPantalla();
void pantallaPrincipal();
void pausarPantalla();

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