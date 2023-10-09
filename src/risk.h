#ifndef RISK_H
#define RISK_H

#include "Asignacion/asignacion.h"

void limpiarPantalla();
void pantallaPrincipal();
void pausarPantalla();

//funciones para el componente 3: Estrategia del juego
bool constoConquista(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios, std::string territorio);
bool conquistaMasBarata(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios);

//Declararion de la funcion de ayuda
void mostrarAyuda();

#endif //risk.h