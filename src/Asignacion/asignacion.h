#ifndef ASIGNACION_H
#define ASIGNACION_H

#include <string>
#include <vector>

//Declaraciones de las estructuras para paises y continentes
struct Territorio{
    int id;
    std::string nombre;
    std::string jugador;
    int unidades_ejercito;
    std::string continente;
    std::vector<int> territorios_vecinos;
};

//Estructura para representar un jugador
struct Jugador{
    int id;
    int numPiezas;
    std::string nombre;
    std::string color;
    std::vector<Territorio> territorio;
    std::vector<int> tarjetas;
};
//funciones del componente 1: Configuracion del juego
void inicializarJuego(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios);


//eliminar al final

#endif //ASIGNACION_H