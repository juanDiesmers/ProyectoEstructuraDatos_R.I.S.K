#include <iostream>
#include <limits>
#include <algorithm>

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
void obtenerNuevasUnidades(std::vector<Jugador>& jugadores, int id_jugador_actual) {
    //Busacar  al jugador actual en el vector de jugadores
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
    //imprimir la cantidad total de unidades que el jugador puede reclamar
    cout << "El jugador con ID " << id_jugador_actual << " puede reclamar " << unidades_por_territorio << " unidades" << endl;

    //Actualizar la unidedes del jugador en sus territorios
    for (Territorio& territorio : jugador_actual->territorio) {
        territorio.unidades_ejercito += unidades_por_territorio;
    }
    }
} 
//funcion para realizar fortificaciones
void realizarFortificaciones(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios, int id_jugador_actual) {
    //Buscar al jugador actual en el vector de jugadores
    Jugador* jugador_actual = nullptr;
    for (int i = 0; i < jugadores.size(); i++) {
        if (jugadores[i].id == id_jugador_actual) {
            jugador_actual = &jugadores[i];
            break;
        }
    }
    //Mostrar los territorios del jugador actual
    cout << "Territorios controlados por el jugador con ID " << id_jugador_actual << ":" << endl;
    for (const Territorio& territorio : jugador_actual->territorio) {
        cout << "ID" << territorio.id << " "<< territorio.nombre << "(Unidades: " << territorio.unidades_ejercito << ")" << endl;
    }

    //Pedir al jugador que seleccione un territorio de origen
    int id_territorio_origen;
    cout << "Seleccione el ID del territorio de origen: ";
    cin >> id_territorio_origen;

    //Econtrar el territorio de origen seleccionado
    Territorio* territorio_origen = nullptr;
    for (int i = 0; i < territorios.size(); i++) {
        if(territorios[i].id == id_territorio_origen && territorios[i].jugador == jugador_actual->nombre){
            territorio_origen = &territorios[i];
            break;
        }
    }
    if(!territorio_origen){
        cout << "El territorio de origen no valido" << endl;
        return;
    }

    //mostrar los territorios adyacentes controlados por el jugador actual
    cout << "Territorios adyacentes controlados al territorio de origen (" << territorio_origen->nombre << "):" << endl;
    for (int id_territorio_vecino : territorio_origen->territorios_vecinos) {
        for(const Territorio& t : jugador_actual->territorio){
            if(id_territorio_vecino == t.id){
                cout << t.nombre << "(Unidades: " << t.unidades_ejercito << ")" << endl;
                break;
            }
        }
    }

    //Pedir al jugador que seleccione un territorio de destino
    int id_territorio_destino;
    cout << "Seleccione el ID del territorio de destino: ";
    cin >> id_territorio_destino;

    //Encontrar el territorio de destino seleccionado
    Territorio* territorio_destino = nullptr;
    for(int i = 0; i < territorios.size(); i++){
        if(territorios[i].id == id_territorio_destino && territorios[i].jugador == jugador_actual->nombre){
            territorio_destino = &territorios[i];
            break;
        }
    }
    if(!territorio_destino){
        cout << "El territorio de destino no valido" << endl;
        return;
    }

    //Pedir al jugador la cantidad de unidades a mover
    int unidades_a_mover;
    cout << "Ingrese la cantidad de unidades a mover: ";
    cin >> unidades_a_mover;

    //verificar si el movimiento es valido y actualizar las unidades
    if (unidades_a_mover < 1 || unidades_a_mover >= territorio_origen->unidades_ejercito) {
        cout << "Movimiento invalido. Debe mover al menos una unidad y no puede mover mas de las que tiene en el territorio de origen." << endl;
        return;
    }

    //realizar la fortificacion
    territorio_origen->unidades_ejercito -= unidades_a_mover;
    territorio_destino->unidades_ejercito += unidades_a_mover;
    
    cout << "Se han movido " << unidades_a_mover << "unidades del territorio " << territorio_origen->nombre << " al territorio " << territorio_destino->nombre << "." << endl;
}

// Función para realizar ataques
void realizarAtaques(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios, int id_jugador_actual) {
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

    if (!territorio_valido) {
        cout << "El territorio seleccionado no es valido" << endl;
        return;
    }

    // Seleccionar un territorio vecino para atacar
    int territorio_objetivo;
    // Mostrar información de los territorios enemigos
    cout << "Territorios enemigos al jugador " << jugador_actual->nombre << ":" << endl;
    for (const Jugador& otroJugador : jugadores) {
        if (otroJugador.id != jugador_actual->id) {
            cout << "Territorios controlados por el jugador con ID " << otroJugador.id << ":" << endl;
            for (const Territorio& territorio : otroJugador.territorio) {
                cout << "Territorio ID " << territorio.id << " - " << territorio.nombre << " (Unidades: " << territorio.unidades_ejercito << ")" << endl;
            }
        }
    }
    cout << "Ingrese el ID del territorio que desea atacar: ";
    cin >> territorio_objetivo;

    // Buscar el territorio objetivo
    Territorio* territorio_objetivo_ptr = nullptr;
    for (Territorio& territorio : territorios) {
        if (territorio.id == territorio_objetivo) {
            territorio_objetivo_ptr = &territorio;
            break;
        }
    }

    if (!territorio_objetivo_ptr) {
        cout << "El territorio seleccionado no es valido" << endl;
        return;
    }

    // Lanzar dados y realizar comparaciones
    int dados_ataque = 3;
    int dados_defensa = 2;

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

    // Actualizar unidades en los territorios según el resultado del ataque
if (unidades_perdidas_defensa > 0) {
    territorio_objetivo_ptr->unidades_ejercito -= unidades_perdidas_defensa; // El defensor pierde las unidades correspondientes
    if (territorio_objetivo_ptr->unidades_ejercito < 1) {
        territorio_objetivo_ptr->jugador = jugador_actual->nombre; // El territorio es conquistado por el atacante
        territorio_objetivo_ptr->unidades_ejercito = unidades_perdidas_ataque; // El atacante ocupa el territorio con sus unidades restantes
    } else {
        territorio_objetivo_ptr->jugador = jugador_actual->nombre; // El territorio es conquistado por el atacante
    }
} else {
    // El ataque no fue exitoso, el defensor mantiene sus unidades
    territorio_objetivo_ptr->unidades_ejercito += unidades_perdidas_ataque;
}

    cout << "Ataque realizado exitosamente" << endl;
    cout << "Unidades perdidas en el ataque: " << unidades_perdidas_ataque << endl;
    cout << "Unidades perdidas en la defensa: " << unidades_perdidas_defensa << endl;
}
