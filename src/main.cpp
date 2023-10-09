#include "Asignacion/asignacion.h"
#include "Turno/turno.h"
#include "Guardar/guardar.h"
#include "risk.h"
#include <iostream>
#include <vector>

using namespace std;

// cd src
// g++ -o main main.cpp risk.cxx Turno/turno.cxx Turno/funcionesTurno.cxx asignacion/asignacion.cxx Guardar/guardar.cxx
// ./main

int main() {
  vector<Jugador> jugadores;
  vector<Territorio> territorios;

  bool juego_terminado = false;
  int turno_actual = 0;

  string comando;

  pantallaPrincipal();

  while (!juego_terminado) {
    cout << "$ ";
    cin >> comando;

    switch (comando[0]) {
    case 'i':
      if (comando == "inicializarJuego" || comando == "i") {
        inicializarJuego(jugadores, territorios);
      } else if (comando == "inicializarPartida" || comando == "ip") {
        inicializarPartida("partida_guardada.txt", jugadores, territorios);
      }
      break;
    case 't':
      if (comando == "turnoJugador" || comando == "tj") {
        turnoJugador(jugadores, territorios);
      }
      break;
    case 's':
      if (comando == "salir" || comando == "s") {
        salir();
        juego_terminado = true;
      }
      break;
    case 'g':
      if (comando == "guardarPartida" || comando == "gp") {
        guardarPartida("partida_guardada.txt", jugadores, territorios);
      } else if (comando == "guardarPartidaComprimida" || comando == "gpc") {
        guardarPartidaComprimida("partida_comprimida", jugadores, territorios);
      }
      break;
    case 'c':
      if (comando == "costoConquista" || comando == "cc") {
        constoConquista(jugadores, territorios, "territorio_deseado");
      } else if (comando == "conquistaMasBarata" || comando == "cmb") {
        conquistaMasBarata(jugadores, territorios);
      }
      break;
    case 'a':
      if (comando == "ayuda" || comando == "a") {
        mostrarAyuda();
      }
      break;
    default:
      limpiarPantalla();
      cout << "Comando inválido. Para ver la lista de comandos disponibles, "
              "ingrese 'a' o 'ayuda'."
           << endl;
      break;
    }
  }
  limpiarPantalla();
  return 0;
}
