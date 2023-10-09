#ifndef GUARDADO_H
#define GUARDADO_H

#include "../Asignacion/asignacion.h"
#include "../risk.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>


//funcion para el componente 2: Almacenamento de partidas
bool inicializarPartida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios);
bool guardarPartida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios);
bool guardarPartidaComprimida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios);
void asignarTerritoriosAJugadores(std::vector<Territorio>& territorios, std::vector<Jugador>& jugadores);

void mostrarDatos(const std::vector<Jugador>& jugadores, const std::vector<Territorio>& territorios);

//corregir
//void llenarArchivo(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios);


#endif //GUARDADO_H