#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "guardar.h"
#include "../Asignacion/asignacion.h"
#include "../risk.h"

using namespace std; 

// Función para guardar la partida en un archivo de texto
bool guardarPartida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    std::ofstream archivo(nombre_archivo);
    
    if (!archivo.is_open()) {
        return false;  // No se pudo abrir el archivo
    }

    // Guardar información de jugadores
    
    for (const Jugador& jugador : jugadores) {
        archivo << "JUGADOR\n";
        archivo << "ID: " << jugador.id << "\n";
        archivo << "Nombre: " << jugador.nombre << "\n";
        archivo << "Número de Piezas: " << jugador.numPiezas << "\n";
        archivo << "Color: " << jugador.color << "\n";
        archivo << "Territorios\n";
        for (const Territorio& territorio : jugador.territorio) {
            archivo << "  ID: " << territorio.id << "\n";
            archivo << "  Nombre: " << territorio.nombre << "\n";
            archivo << "  PerteneceJugador: " << territorio.jugador << "\n";
            archivo << "  Unidades de Ejército: " << territorio.unidades_ejercito << "\n";
            archivo << "  Continente: " << territorio.continente << "\n";
            archivo << "  Territorios Vecinos: ";
            for (int vecino : territorio.territorios_vecinos) {
                archivo << vecino << " ";
            }
            archivo << "\n";
            archivo << "  Vecinos Enemigos:\n";
            for (const VecinoEnemigo& vecinoEnemigo : territorio.vecinos_enemigos) {
                archivo << "    ID: " << vecinoEnemigo.id << "\n";
                archivo << "    NombreVecino: " << vecinoEnemigo.nombre << "\n";
                archivo << "    Es Enemigo: " << (vecinoEnemigo.esEnemigo ? "true" : "false") << "\n";
            }
            archivo << "\n";
        }
        archivo << "Tarjetas: ";
        for (int tarjeta : jugador.tarjetas) {
            archivo << tarjeta << " ";
        }
        archivo << "\n\n";
        archivo <<"-----------------------------------------------------------------------------------------------";
        archivo << "\n";
    }

    archivo.close();
    return true;
}


bool inicializarPartida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    std::ifstream archivo(nombre_archivo);
    
    if (!archivo.is_open()) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        return false;
    }

    std::string linea;
    std::string jugador_del_ultimo_territorio;

    while (std::getline(archivo, linea)) {
        if (linea == "JUGADOR" || linea == "-----------------------------------------------------------------------------------------------") {
            Jugador jugador;
            while (std::getline(archivo, linea) && !linea.empty()) {
                std::istringstream iss(linea);
                std::string campo, valor;
                iss >> campo >> valor;
                if (campo == "ID:") {
                    if (valor.empty()) {
                        std::cerr << "Error: ID de jugador vacío." << std::endl;
                        return false;
                    }
                    jugador.id = std::stoi(valor);
                } else if (campo == "Nombre:") {
                    jugador.nombre = valor;
                } else if (campo == "Número" && valor == "de" && iss >> campo >> valor) {
                    if (valor.empty()) {
                        std::cerr << "Error: Número de piezas de jugador vacío." << std::endl;
                        return false;
                    }
                    jugador.numPiezas = std::stoi(valor);
                } else if (campo == "Color:") {
                    jugador.color = valor;
                } else if (campo == "Territorios") {
                    jugador_del_ultimo_territorio = jugador.nombre;
                } else if (campo == "ID:") {
                    Territorio territorio;
                    territorio.jugador = jugador_del_ultimo_territorio;
                    if (valor.empty()) {
                        std::cerr << "Error: ID de territorio vacío." << std::endl;
                        return false;
                    }
                    territorio.id = std::stoi(valor);
                    while (std::getline(archivo, linea) && !linea.empty()) {
                        std::istringstream iss_territorio(linea);
                        iss_territorio >> campo >> valor;
                        if (campo == "Nombre:") {
                            territorio.nombre = valor;
                        } else if (campo == "PerteneceJugador:") {
                            territorio.jugador = valor;
                        } else if (campo == "Unidades" && valor == "de" && iss_territorio >> campo >> valor) {
                            if (valor.empty()) {
                                std::cerr << "Error: Número de unidades de territorio vacío." << std::endl;
                                return false;
                            }
                            territorio.unidades_ejercito = std::stoi(valor);
                        } else if (campo == "Continente:") {
                            territorio.continente = valor;
                        } else if (campo == "Territorios" && valor == "Vecinos:") {
                            while (iss_territorio >> valor) {
                                if (valor.empty()) {
                                    std::cerr << "Error: ID de territorio vecino vacío." << std::endl;
                                    return false;
                                }
                                territorio.territorios_vecinos.push_back(std::stoi(valor));
                            }
                        } else if (campo == "Vecinos" && valor == "Enemigos:") {
                            while (std::getline(archivo, linea) && !linea.empty()) {
                                std::istringstream iss_enemigo(linea);
                                VecinoEnemigo vecino_enemigo;
                                iss_enemigo >> campo >> valor;
                                if (campo == "ID:") {
                                    if (valor.empty()) {
                                        std::cerr << "Error: ID de vecino enemigo vacío." << std::endl;
                                        return false;
                                    }
                                    vecino_enemigo.id = std::stoi(valor);
                                } else if (campo == "NombreVecino:") {
                                    vecino_enemigo.nombre = valor;
                                } else if (campo == "Es" && valor == "Enemigo:") {
                                    iss_enemigo >> valor;  // Leer "true" o "false"
                                    if (valor.empty() || (valor != "true" && valor != "false")) {
                                        std::cerr << "Error: Valor de 'Es Enemigo' inválido." << std::endl;
                                        return false;
                                    }
                                    vecino_enemigo.esEnemigo = (valor == "true");
                                    territorio.vecinos_enemigos.push_back(vecino_enemigo);
                                }
                            }
                        }
                    }
                    territorios.push_back(territorio);
                } else if (campo == "Tarjetas:") {
                    // Maneja las tarjetas si es necesario
                }
            }
            jugadores.push_back(jugador);
        }
    }

    archivo.close();
    return true;
}




bool guardarPartidaComprimida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    limpiarPantalla();
    std::cout << "Ingreso correctamente a la función guardarPartidaComprimida." << std::endl;
    return true;
}

void mostrarDatos(const std::vector<Jugador>& jugadores, const std::vector<Territorio>& territorios) {
    // Mostrar datos de jugadores
    std::cout << "Jugadores:\n";
    for (const Jugador& jugador : jugadores) {
        std::cout << "ID: " << jugador.id << "\n";
        std::cout << "Nombre: " << jugador.nombre << "\n";
        std::cout << "Número de Piezas: " << jugador.numPiezas << "\n";
        std::cout << "Color: " << jugador.color << "\n";
        std::cout << "Tarjetas: ";
        for (int tarjeta : jugador.tarjetas) {
            std::cout << tarjeta << " ";
        }
        std::cout << "\n\n";
    }

    // Mostrar datos de territorios
    std::cout << "Territorios:\n";
    for (const Territorio& territorio : territorios) {
        std::cout << "ID: " << territorio.id << "\n";
        std::cout << "Nombre: " << territorio.nombre << "\n";
        std::cout << "Pertenece al Jugador: " << territorio.jugador << "\n";
        std::cout << "Unidades de Ejército: " << territorio.unidades_ejercito << "\n";
        std::cout << "Continente: " << territorio.continente << "\n";
        std::cout << "Territorios Vecinos: ";
        for (int vecino : territorio.territorios_vecinos) {
            std::cout << vecino << " ";
        }
        std::cout << "\n";
        std::cout << "Vecinos Enemigos:\n";
        for (const VecinoEnemigo& vecinoEnemigo : territorio.vecinos_enemigos) {
            std::cout << "  ID: " << vecinoEnemigo.id << "\n";
            std::cout << "  NombreVecino: " << vecinoEnemigo.nombre << "\n";
            std::cout << "  Es Enemigo: " << (vecinoEnemigo.esEnemigo ? "Sí" : "No") << "\n";
        }
        std::cout << "\n";
    }
}




//corregir
/*
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
        archivo << jugadores[i].tarjetas.size() << " "; //Cantidad de cartas que tiene el jugador
        //archivo << jugadores[i].tarjetas[j].tipo << " "; //Tipo de carta que tiene el jugador
        }
    }
    } else {
    // Si el archivo no se pudo abrir, muestra un mensaje de error
    std::cerr << "No se pudo abrir el archivo." << std::endl;
    }
}*/