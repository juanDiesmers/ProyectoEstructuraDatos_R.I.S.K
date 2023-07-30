#ifndef RISK_H
#define RISK_H

#include <string>
#include <vector>
#include <map>

//Declaraciones de las estructuras para paises y continentes
struct Pais{
    std::string nombre;
    std::string continente;
    int ejercitos;
};

struct Continente{
    std::string nombre;
    int bonusEjercito;
};

//Declaracion de la clase para el jugador
class Jugador{
public:
    std::string nombre;
    std::vector<Pais> paisesControlados;

    //

    //Declaraciòn de la funcion para que el jugador realice acciones
    void conquistaPais(Pais& pais, int ejercitos);
    void atacarPais(Pais& pais, int ejercitos);
    void reagruparEjercitos(Pais& origen, Pais& destino, int ejercitos);

};

//Declaracion de las funciones para cargar los datos y realizar opercaiones
void cargarPaises(std::vector<Pais>& paises);
void cargarContinentes(std::vector<Continente>& continentes);
void cargarFronteras(std::map<std::string, std::vector<std::string >>& fronteras);
void asignarObjetivosAleatorios(std::vector<Jugador>& jugadores);
void asignarObjetivosPorPaises(std::vector<Jugador>& jugadores);
void asignarObjetivosPorContinente(std::vector<Jugador>& jugadores);
void asignarObjetivosPorJugador(Jugador& jugador);
void mostrarObjetivos(const std::vector<Jugador>& jugadores);
void mostrarObjetivosJugador(const Jugador& jugador);
void mostrarPaises(const std::vector<Pais>& paises);
void mostrarContinente(const std::vector<Continente>& continentes);
void mostrarFronteras(const std::map<std::string , std::vector<std::string>>& fronteras);
void mostrarConquista(const std::string& nombreTerritorio);

//Declararion de la funcion de ayuda
void mostrarAyuda();

#endif //risk.h