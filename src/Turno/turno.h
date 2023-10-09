#ifndef TURNO_H
#define TURNO_H
#include "../risk.h"
#include "../Asignacion/asignacion.h"

//Funcion de Turno del jugador
void turnoJugador(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios);
//Salir del juego
void salir();

bool validacionJugador(std::vector<Jugador>& jugadores, int id_jugador_actual);
void obtenerNuevasUnidades(std::vector<Jugador>& jugadores, int id_jugador_actual, std::vector<Territorio>& territorios);
void realizarAtaques(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios, int id_jugador_actual);
void realizarFortificaciones(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios, int id_jugador_actual);

#endif //TURNO_H