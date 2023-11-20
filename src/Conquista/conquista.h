#ifndef CONQUISTA_H
#define CONQUISTA_H

#include "../Asignacion/asignacion.h"
#include "../risk.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <unordered_map>


// Struct para representar un grafo de territorios y sus conexiones enemigas
class Grafo {
public:
    Grafo();
    void SetIdJugadorEnTurno(int idJugador);
    void InsertarTerritorio(const Territorio &territorio, int idJugador);
    void InsertarConexionEnemiga(unsigned long territorio1, unsigned long territorio2, int peso, int idJugadorActual);
    void AgregarTerritoriosJugador(const std::vector<Territorio>& territoriosJugador, int idJugador);

    unsigned long NumeroTerritorios() const;
    const Territorio &ObtenerTerritorio(unsigned long indice) const;

    bool TieneConexionEnemiga(unsigned long territorio1, unsigned long territorio2, int idJugadorActual) const;

    std::vector<int> ObtenerConexionesEnemigas(unsigned long territorio, int idJugadorActual) const;
    int calcularCostoConquista(const Territorio& inicio, const Territorio& destino, const Grafo& grafoEnemigos, int idJugadorActual);
    int calcularMenorCostoConquista(const Territorio& inicio, const Territorio& destino, const Grafo& grafoEnemigos, int idJugadorActual);
    void MostrarInformacionGrafo() const;

private:
    std::vector<Territorio> territorios;
    std::vector<std::vector<bool>> matrizAdyacencia;
    int idJugadorEnTurno;
};



//funciones para el componente 3: Estrategia del juego
bool constoConquista(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios, std::string territorio);
bool conquistaMasBarata(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios);



#endif // CONQUISTA_H