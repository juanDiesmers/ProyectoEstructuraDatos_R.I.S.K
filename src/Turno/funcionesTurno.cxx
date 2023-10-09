#include <ctime>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <algorithm>
#include <random>
#include <chrono>


#include "../Asignacion/asignacion.h"
#include "../risk.h"
#include "turno.h"

using namespace std;

//Validacion del jugador
bool validacionJugador(vector<Jugador>& jugadores, int id_jugador_actual) {
    //funcion para validar que el jugador tiene el turno
    //declaracion de variables
    bool validado = false;
    //Recorrer el vector de jugadores
    for (int i = 0; i < jugadores.size(); i++){
        //Verificar si el id del jugador es igual al id del jugador actual
        if(jugadores[i].id == id_jugador_actual){
            //Si es igual, entonces el jugador tiene el turno
            validado = true;
            break;
        }
    }
    //Si no encontro el jugador en el bucle, informar que no forma parte del juego
    if(!validado){
        cout << "El jugador con ID " << id_jugador_actual << " no forma parte del juego" << endl;
    }
    return validado;
}

//Funcion para obtener nuevas unidades
void obtenerNuevasUnidades(std::vector<Jugador>& jugadores, int id_jugador_actual, std::vector<Territorio>& territorios) {
    // Buscar al jugador actual en el vector de jugadores
    Jugador* jugador_actual = nullptr;
    for (int i = 0; i < jugadores.size(); i++) {
        if (jugadores[i].id == id_jugador_actual) {
            jugador_actual = &jugadores[i];
            break;
        }
    }

    // Calcular la cantidad de territorios controlados por el jugador
    int territorios_controlados = jugador_actual->territorio.size();

    // Calcular la cantidad de unidades adicionales basadas en territorios controlados
    int unidades_por_territorio = territorios_controlados / 3;

    // Asignar tropas adicionales a cada territorio del jugador según el continente
    for (Territorio& territorio : jugador_actual->territorio) {
        int tropas_adicionales = 0; // Inicializar el número de tropas adicionales

        if (territorio.continente == "America del Norte") {
            tropas_adicionales = 5; // Asignar 5 unidades por territorio en América del Norte
        } else if (territorio.continente == "America del Sur") {
            tropas_adicionales = 2; // Asignar 2 unidades por territorio en América del Sur
        } else if (territorio.continente == "Europa") {
            tropas_adicionales = 7; // Asignar 7 unidades por territorio en Europa
        } else if (territorio.continente == "Africa") {
            tropas_adicionales = 3; // Asignar 3 unidades por territorio en África
        } else if (territorio.continente == "Asia") {
            tropas_adicionales = 10; // Asignar 10 unidades por territorio en Asia
        } else if (territorio.continente == "Australia") {
            tropas_adicionales = 2; // Asignar 2 unidades por territorio en Australia
        }

        // Actualizar las tropas del territorio
        territorio.unidades_ejercito += (tropas_adicionales + unidades_por_territorio);
    }

    // Imprimir la cantidad total de unidades que el jugador puede reclamar
    cout << "El jugador con ID " << id_jugador_actual << " puede reclamar " << unidades_por_territorio << " unidades" << endl;
}
//funcion para realizar fortificaciones
void realizarFortificaciones(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios, int id_jugador_actual) {

    //Buscar el jugador actual en el vector de jugadores
    Jugador* jugador_actual = nullptr;
    for (int i = 0; i < jugadores.size(); i++) {
        if (jugadores[i].id == id_jugador_actual) {
            jugador_actual = &jugadores[i];
            break;
        }
    }

    //Mostrar los territorios controlados por el jugador actual
    cout << "Territorios controlados por el jugador con ID " << id_jugador_actual << ":" << endl;
    for (const Territorio& territorio : jugador_actual->territorio) {
        cout << "ID " << territorio.id << " " << territorio.nombre << " (Unidades: " << territorio.unidades_ejercito << ")" << endl;
    }

    int id_territorio_origen;
    Territorio* territorio_origen = nullptr;

    //Utilizar un bucle para validar que el territorio origen es valido
    while (true) {
        cout << "Seleccione el ID del territorio de Origen: ";
        cin >> id_territorio_origen;

        territorio_origen = nullptr; // Reiniciar el puntero

        for (int i = 0; i < territorios.size(); i++) {
            if (territorios[i].id == id_territorio_origen && territorios[i].jugador == jugador_actual->nombre) {
                territorio_origen = &territorios[i];
                break;
            }
        }

        if (territorio_origen) {
            break; // Salir del bucle si el territorio es válido
        }

        cout << "El territorio seleccionado no es valido. Por favor, seleccione un territorio valido." << endl;
    }

    //Mostrar los territorios adyascente controlados por el jugador actual
    cout << "Territorios adyascentes controlados por el jugador con ID " << id_jugador_actual << ":" << endl;
    for (int id_territorio_vecino : territorio_origen->territorios_vecinos) {
        for (const Territorio& t : jugador_actual->territorio) {
            if  (id_territorio_vecino == t.id) {
                cout << t.nombre << "(Unideades:  "<< t.unidades_ejercito<<")"<< endl;
                break;
            }
        }
    }

    int id_territorio_destino;
    Territorio* territorio_destino = nullptr;
    while (true) {
        cout << "Seleccione el id del territorio de destino: ";
        cin >> id_territorio_destino;

        //Encontrar el territorio de destino en el vector de territorios
        for (int i = 0; i < territorios.size(); i++) {
            if (territorios[i].id == id_territorio_destino && territorios[i].jugador == jugador_actual->nombre) {
                territorio_destino = &territorios[i];
                break;
            }
        }

        if (territorio_destino) {
            break; // Salir del bucle si el territorio es válido
        }

        cout << "El territorio seleccionado no es valido. Por favor, seleccione un territorio valido." << endl;
    }

    //Pedir al jugador que ingrese la cantidad de unidades a mover
    int unidades_a_mover;
    while (true) {
        cout << "Ingrese la cantidad de unidades a mover: ";
        cin >> unidades_a_mover;

        if (unidades_a_mover >= 1 && unidades_a_mover > territorio_origen->unidades_ejercito) {
            break; // Salir del bucle si la cantidad es válida
        }

        cout << "La cantidad ingresada no es valida. Por favor, ingrese una cantidad valida." << endl;
    }

    //Realizar la fortificacion
    //Actualizar unidades del territorio de origen
    for (Territorio& territorio : jugador_actual->territorio) {
        if (territorio.id == id_territorio_origen) {
            territorio.unidades_ejercito -= unidades_a_mover;
            break;
        }
    }
    //Actualizar unidades del territorio de destino
    for (Territorio& territorio : jugador_actual->territorio) {
        if (territorio.id == id_territorio_destino) {
            territorio.unidades_ejercito += unidades_a_mover;
            break;
        }
    }
}

// Función para realizar ataques
void realizarAtaques(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios, int id_jugador_actual) {
    srand(static_cast<unsigned int>(time(nullptr)));
    // Obtener el jugador actual
    Jugador* jugador_actual = nullptr;
    for (int i = 0; i < jugadores.size(); i++) {
        if (jugadores[i].id == id_jugador_actual) {
            jugador_actual = &jugadores[i];
            break;
        }
    }

    pausarPantalla();
    limpiarPantalla();
    cout << "Realizando ataques..." << endl;

    // Permitir al jugador seleccionar un territorio desde el cual atacar
    int territorio_ataque;
    while (true) {
        // Mostrar los territorios del jugador actual
        cout << "Territorios controlados por el jugador con ID " << id_jugador_actual << ":" << endl;
        for (const Territorio& territorio : jugador_actual->territorio) {
            cout << "ID " << territorio.id << " " << territorio.nombre << " (Unidades: " << territorio.unidades_ejercito << ")" << endl;
        }
        cout << "Ingrese el ID del territorio desde el cual desea atacar: ";
        cin >> territorio_ataque;

        // Validar que el territorio seleccionado es del jugador y tiene al menos 2 unidades
        bool territorio_valido = false;
        for (Territorio& territorio : jugador_actual->territorio) {
            if (territorio.id == territorio_ataque && territorio.unidades_ejercito >= 2) {
                territorio_valido = true;
                break;
            }
        }

        if (territorio_valido) {
            break; // Salir del bucle si el territorio es válido
        }

        cout << "El territorio seleccionado no es valido. Por favor, seleccione un territorio valido." << endl;
    }   

// Seleccionar un territorio vecino para atacar
    int territorio_objetivo;

    while (true) {
        //Mostrar los territorios enemigos 
        cout << "Territorios enemigos al jugador con ID " << id_jugador_actual << ":" << endl;
        bool enemigoPresente  = false;
        for (const Jugador& otroJugador : jugadores) {
            if (otroJugador.id != id_jugador_actual) {
                for (const Territorio& territorio : otroJugador.territorio) {
                    cout << "Territorio ID: " << territorio.id << " - " << territorio.nombre << "(Unidades:"  << territorio.unidades_ejercito<<")" << endl;
                    enemigoPresente = true;
                }
            }
        }

        if (!enemigoPresente) {
            cout << "No hay territorios enemigos disponibles para atacar." << endl;
            return;
        }

        cout << "Ingrese el ID del territorio que desea atacar: " << endl;
        cin >> territorio_objetivo;

        bool territorio_valido = false;
        //Validar si el territorio objetivo es valido
        for (const Jugador& otroJugador : jugadores) {
            for (const Territorio& territorio : otroJugador.territorio) {
                if (territorio.id == territorio_objetivo) {
                    //territorio objetivo es validp
                    territorio_valido = true;
                    break;
                }
            }
            if (territorio_valido) {
                break;
            }
        }
        if(territorio_valido){
            break;
        }
        cout << "El territorio seleccionado no es valido. Por favor, seleccione un territorio valido." << endl;
    }

    int dados_ataque = 3;
    int dados_defensa = 2;
    cout << "Lanzando dados: " << endl;
    // Lanzar dados de ataque
    vector<int> resultado_ataque;
    for (int i = 0; i < dados_ataque; i++) {
        int resultado = rand() % 6 + 1; // número aleatorio entre 1 y 6
        resultado_ataque.push_back(resultado);
    }
    sort(resultado_ataque.rbegin(), resultado_ataque.rend());

    // Lanzar dados de defensa
    vector<int> resultados_defensa;
    for (int i = 0; i < dados_defensa; i++) {
        int resultado = rand() % 6 + 1; // número aleatorio entre 1 y 6
        resultados_defensa.push_back(resultado);
    }
    sort(resultados_defensa.rbegin(), resultados_defensa.rend());


    // Mostrar resultado de los dados de ataque 
    cout << "Resultado de los dados de ataque: ";
    for (int i = 0; i < dados_ataque; i++) {
        cout << resultado_ataque[i] << " ";
    }
    cout << endl;
    
    //Mostrar los reusltados de los dados de defensa
    cout << "Resultado de los dados de defensa: ";
    for (int i = 0; i < dados_defensa; i++) {
        cout << resultados_defensa[i] << " ";
    }
    cout << endl;

    // Realizar comparaciones y actualizar unidades en los territorios
    int unidades_perdidas_ataque = 0;
    int unidades_perdidas_defensa = 0;

    for (int i = 0; i < min(dados_ataque, dados_defensa); i++) {
        if (resultado_ataque[i] > resultados_defensa[i]) {
            unidades_perdidas_defensa++;
        } else {
            unidades_perdidas_ataque++;
        }
    }

    cout << "Ataque realizado con exito " << endl;
    cout << "Unidades perdidas por el atacante: " << unidades_perdidas_ataque << endl;
    cout << "Unidades perdidas por el defensor: " << unidades_perdidas_defensa << endl;

    //Actualizar unidades del atacante
    for (Territorio& territorio : jugador_actual->territorio) {
        if (territorio.id == territorio_ataque) {
            territorio.unidades_ejercito -= unidades_perdidas_ataque;
            break;
        }
    }
    //Actualizar unidades del defensor
    for (Jugador& otroJugador : jugadores) {
        for (Territorio& territorio : otroJugador.territorio) {
            if (territorio.id == territorio_objetivo) {
                territorio.unidades_ejercito -= unidades_perdidas_defensa;
                break;
            }
        }
    }

    //Verificar si el defensor perdio todos sus tropas y el atacante gano el territorio
    bool defensor_perdio = false;
    int territorio_objetivo_index = -1;

    for (Jugador& otroJugador : jugadores) {
        if (otroJugador.id != jugador_actual->id) {
            for (int i = 0; i < otroJugador.territorio.size(); i++) {
                if (otroJugador.territorio[i].id == territorio_objetivo && otroJugador.territorio[i].unidades_ejercito <= 0) {
                    defensor_perdio = true;
                    cout << "El defensor perdio el territorio." << endl;
                    territorio_objetivo_index = i;
                    break;
                }
            }
        }
    }
    //si el defensor perdio el territorio, este pasa al jugador atacante
    if (defensor_perdio) {
        // Agregar el territorio al jugador atacante
        for (Territorio& territorio : territorios) {
            if (territorio.id == territorio_objetivo) {
                territorio.jugador = jugador_actual->nombre;
                territorio.unidades_ejercito = 0;
                jugador_actual->territorio.push_back(territorio);
                break;
            }
        }

        // Eliminar el territorio del jugador defensor
        for (int i = 0; i < jugadores.size(); i++) {
            if (jugadores[i].id != jugador_actual->id) {
                jugadores[i].territorio.erase(jugadores[i].territorio.begin() + territorio_objetivo_index);
                break;
            }
        }
        cout << "El territorio ahora pertenece al jugador con ID " << id_jugador_actual << endl;
    }
}