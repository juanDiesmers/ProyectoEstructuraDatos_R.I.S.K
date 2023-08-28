#include <iostream> 
#include <limits>
#include "turno.h"

#include "../Asignacion/asignacion.h"
#include "../risk.h"

using namespace std;

void turnoJugador(vector<Jugador>& jugadores, vector<Territorio>& territorios){
    limpiarPantalla();

    //Verificar que hay jugadores en la lista
    if(jugadores.empty()){
        cout << "Inicializacion de la partida fallida. No hay jugadores en el juego." << endl;
        cout << "Saliendo de turnoJugador" << endl;
        return;
    }
    //Escribir en pantalla que ingreso a la funcion de TurnoJugador
    cout << "Ingreso a la funcion de TurnoJugador" << endl;

    //Ciclo para verificar que le jugador tiene el turno
    int indice_jugador_actual = 0;
    bool jugador_valido = false;

    do{
        Jugador& jugador_actual = jugadores[indice_jugador_actual];//obtener el jugador actual
        // Imprimir la lista de jugadores que estÃ¡n jugando
        cout << "Jugadores en juego:" << endl;
        for (const Jugador& jugador : jugadores) {
            cout << "- ID: " << jugador.id << ", Nombre: " << jugador.nombre << endl;
        }
        //Pedir el ID del jugador
        int id_jugador_actual;
        do{
            cout << "Ingrese el ID del jugador actual: ";
            if(cin >> id_jugador_actual){
                if(id_jugador_actual == -1){
                    return;
                }
                jugador_valido = validacionJugador(jugadores, id_jugador_actual);
                if(!jugador_valido ){
                    cout << "El ID del jugador no es valido" << endl;
                }
            } else {
                cout << "Entrada invalida. Por favor, ingrese un numero valido " << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }while(!jugador_valido);

        //Realizar acciones del jugador actual (obtener nuevas unidades, atacar, fortificar)
        obtenerNuevasUnidades(jugadores, id_jugador_actual);
        realizarAtaques(jugadores, territorios, id_jugador_actual);
        realizarFortificaciones(jugadores, territorios, id_jugador_actual);

        //mostrar mensaje de turno terminado
        cout << "Turno del jugador " << jugador_actual.nombre << " terminado" << endl;
        //Cambiar al siguiente jugador en la lista
        indice_jugador_actual = (indice_jugador_actual + 1) % jugadores.size();
    }while(true);
    std::cout << "Saliendo de turnoJugador" << std::endl;
}
void salir() {
    limpiarPantalla();
    std::cout << "Saliendo del juego. Hasta luego!" << std::endl;
    //system ("clear");
    exit(0);//finaliza la ejecucion del programa
}   