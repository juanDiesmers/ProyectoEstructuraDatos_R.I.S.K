#include "guardado.h"


void llenarArchivo(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios){

    std::string nombre;
    std::cout << "Para el guardado, escriba el nombre del archivo" << std::endl;
    std::cin >> nombre;
    std::ofstream archivo(nombre);

    if (archivo.is_open()) {
    // El archivo se abrió correctamente

    archivo << "Cantidad de jugadores: " << jugadores.size() << std::endl;

    for(int i = 0; i < jugadores.size(); i ++){
        for(int j = 0; j < territorios.size(); j++){
        archivo << jugadores[i].nombre << " "; //Nombre
        archivo << jugadores[i].color << " "; //Color
        archivo << jugadores[i].territorio.size() << " "; //Cantidad de territorios que ocupa
        archivo << jugadores[i].territorio[j].id << " "; //Identificador de cada pais
        archivo << jugadores[i].territorio[j].unidades_ejercito << " "; // Cantidad de unidades que tiene junto a el
        archivo << jugadores[i].cartas.size() << " "; //Cantidad de cartas que tiene el jugador
        archivo << jugadores[i].cartas[j].tipo << " "; //Tipo de carta que tiene el jugador
        }
    }
    } else {
    // Si el archivo no se pudo abrir, muestra un mensaje de error
    std::cerr << "No se pudo abrir el archivo." << std::endl;
    }
}