#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "guardar.h"
#include "huffman.h"
#include "../Asignacion/asignacion.h"
#include "../risk.h"



using namespace std; 

// Función para guardar la partida en un archivo de texto
bool guardarPartida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    limpiarPantalla();
    std::cout << "Ingreso correctamente a la función guardarPartida." << std::endl;
    
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
            archivo << "  Vecinos Enemigos\n";
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

    Jugador jugador;
    Territorio territorio;
    VecinoEnemigo vecinoEnemigo;

    std::string linea;
    while (std::getline(archivo, linea)) {
    if (linea == "JUGADOR") {
        // Comenzamos a procesar datos de un nuevo jugador
        jugador = {};  // Inicializar jugador
    } else if (linea == "Territorios") {
        // Comenzamos a procesar datos de territorios
        territorio = {};  // Inicializar territorio
    } else {
        size_t pos = linea.find(":");
        if (pos != std::string::npos) {
            std::string etiqueta = linea.substr(0, pos);
            std::string valor = linea.substr(pos + 2);  // +2 para omitir el ':' y el espacio

            if (etiqueta == "ID") {
                jugador.id = std::stoi(valor);
            } else if (etiqueta == "Número de Piezas") {
                jugador.numPiezas = std::stoi(valor);
            } else if (etiqueta == "Nombre") {
                jugador.nombre = valor;
            } else if (etiqueta == "Color") {
                jugador.color = valor;
            } else if (etiqueta == "  ID") {
                territorio.id = std::stoi(valor);
            } else if (etiqueta == "  Nombre") {
                territorio.nombre = valor;
            } else if (etiqueta == "  PerteneceJugador") {
                territorio.jugador = valor;
            } else if (etiqueta == "  Unidades de Ejército") {
                territorio.unidades_ejercito = std::stoi(valor);
            } else if (etiqueta == "  Continente") {
                territorio.continente = valor;
            } else if (etiqueta == "  Territorios Vecinos") {
                //territorio.territorios_vecinos = valor;
            } else if (etiqueta == "  Vecinos Enemigos") {
                // Comenzamos a procesar datos de vecinos enemigos
                vecinoEnemigo = {};  // Inicializar vecino enemigo
            } else if (etiqueta == "    ID") {
                vecinoEnemigo.id = std::stoi(valor);
            } else if (etiqueta == "    NombreVecino") {
                vecinoEnemigo.nombre = valor;
            } else if (etiqueta == "    Es Enemigo") {
                vecinoEnemigo.esEnemigo = (valor == "true");
                territorio.vecinos_enemigos.push_back(vecinoEnemigo);  // Agregar vecino enemigo a territorio
            }
        }
    }

    // Verificar si se ha completado la lectura de datos de un jugador o territorio
    if (linea.empty()) {
        if (!jugador.nombre.empty()) {
            jugadores.push_back(jugador);
            jugador = {};  // Reinicializar jugador
        } else if (!territorio.nombre.empty()) {
            territorios.push_back(territorio);
            territorio = {};  // Reinicializar territorio
        }
    }
}
    // Cerrar el archivo después de leer
    archivo.close();
    /*
    // Agregar el jugador a la lista de jugadores (si lo deseas)
    jugadores.push_back(jugador);
    // Agregar el territorio a la lista de territorios
    territorios.push_back(territorio);
    // Ahora los datos están en la estructura Jugador
    std::cout << "ID: " << jugador.id << std::endl;
    std::cout << "Numero de Piezas: " << jugador.numPiezas << std::endl;
    std::cout << "Nombre: " << jugador.nombre << std::endl;
    std::cout << "Color: " << jugador.color << std::endl;
    */
    mostrarDatos(jugadores, territorios);
    asignarTerritoriosAJugadores(territorios, jugadores);
    return true;
}

//aisgnar territorios
// Función para asignar territorios a jugadores
void asignarTerritoriosAJugadores(std::vector<Territorio>& territorios, std::vector<Jugador>& jugadores) {
    for (Territorio& territorio : territorios) {
        for (Jugador& jugador : jugadores) {
            if (territorio.jugador == jugador.nombre) {
                jugador.territorio.push_back(territorio);
                break; // No es necesario buscar más jugadores
            }
        }
    }
    /*
    for (const Jugador& jugador : jugadores) {
        std::cout << "Jugador: " << jugador.nombre << std::endl;
        for (const Territorio& territorio : jugador.territorio) {
            std::cout << "Territorio: " << territorio.nombre << std::endl;
            // Imprime más información del territorio si es necesario
        }
    }
    */

}




bool guardarPartidaComprimida(std::string nombre_archivo, std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    limpiarPantalla();

    std::ifstream archivo_entrada("partida_guardada.txt");

    if (!archivo_entrada.is_open()) {
        std::cout << "No se pudo abrir el archivo." << std::endl;
        return false;
    }

    std::string contenido((std::istreambuf_iterator<char>(archivo_entrada)), (std::istreambuf_iterator<char>()));
    archivo_entrada.close();
    Huffman huffman;
    huffman.compress(contenido);

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