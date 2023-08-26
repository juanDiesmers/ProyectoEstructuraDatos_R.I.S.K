#include <iostream> 
#include "turno.h"

#include "../Asignacion/asignacion.h"
#include "../risk.h"

using namespace std;
bool validacionJugador(vector<Jugador>& jugadores, int id_jugador_actual);
void obtenerNuevasUnidades(std::vector<Jugador>& jugadores, int id_jugador_actual);
void realizarAtaques(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios, int id_jugador_actual);
void realizarFortificaciones(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios, int id_jugador_actual);

void turnoJugador(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios){
    limpiarPantalla();

    //Escribir por pantalla que ingreso a la funcion de TurnoJugador
    cout << "Ingreso a la funcion de TurnoJugador" << endl;

    //Ciclo para verificar que el jugdor tiene el turno
    int id_jugador_actual;
    bool juagador_valido = false;
    do{
        //pedir el id del jugador
        cout << "Ingrese el ID del jugador: ";
        cin >> id_jugador_actual;
        juagador_valido = validacionJugador(jugadores, id_jugador_actual);
        if(juagador_valido == false){
            cout << "El jugador con ID " << id_jugador_actual << " no tiene el turno" << endl;
        } else {
            //Llamar a la funcion para obtener nuevas unidades
            obtenerNuevasUnidades(jugadores, id_jugador_actual);

            //Llamar a la funcion para realizar ataques
            realizarAtaques(jugadores, territorios, id_jugador_actual);

            //Llamar a la funcion para realizar fortificaciones
            realizarFortificaciones(jugadores, territorios, id_jugador_actual);
        }
        }while (!juagador_valido);
}

//Funiones del programa turno
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
void obtenerNuevasUnidades(std::vector<Jugador>& jugadores, int id_jugador_actual) {
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

    // Verificar si el jugador tiene el control de continentes completos y agregar unidades por continente
    for (const Territorio& territorio : jugador_actual->territorio) {
        // Verificar si el jugador controla todos los territorios de un continente
        bool controla_continente = true;
        for (int id_territorio_vecino : territorio.territorios_vecinos) {
            bool territorio_en_continentes = false;
            for (const Territorio& t : jugador_actual->territorio) {
                if (id_territorio_vecino == t.id) {
                    territorio_en_continentes = true;
                    break;
                }
            }
            if (!territorio_en_continentes) {
                controla_continente = false;
                break;
            }
        }

        // Si controla el continente, agregar unidades según las reglas
        if (controla_continente) {
            if (territorio.id == 1 || territorio.id == 2) {
                unidades_por_territorio += 2; // América del Sur o Australia
            } else if (territorio.id == 3) {
                unidades_por_territorio += 3; // África
            } else if (territorio.id == 4 || territorio.id == 5) {
                unidades_por_territorio += 5; // América del Norte o Europa
            } else if (territorio.id == 6) {
                unidades_por_territorio += 7; // Asia
            }
        }
    }

    //Impirmir la cantidad total de unidades que el jugador puede reclamar
    cout << "El jugador con ID " << id_jugador_actual << " puede reclamar " << unidades_por_territorio << " unidades" << endl;

    //Actualizar las unidades del jugador
    
}  

//funcion para realizar ataques
void realizarAtaques(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios, int id_jugador_actual) {
    cout << "mamahuevo";
}

//funcion para realizar fortificaciones
void realizarFortificaciones(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios, int id_jugador_actual) {
cout << "mamahuevo";
}
void salir() {
    limpiarPantalla();
    std::cout << "Saliendo del juego. Hasta luego!" << std::endl;
    //system ("clear");
    exit(0);//finaliza la ejecucion del programa
}