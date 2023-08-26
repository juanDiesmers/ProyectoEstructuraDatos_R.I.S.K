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
    std::vector<int> territorios_vecinos;
};

//Estructura para representar un jugador
struct Jugador{
    std::string nombre;
    std::string color;
    std::vector<Territorio> territorio;
    std::vector<int> tarjetas;
};

#endif //ASIGNACION_H