#include <iostream>
#include "risk.h"

using namespace std;

int main(){
    vector<Jugador> jugadores;
    vector<Territorio> territorios;

    bool juego_inicializado = false;
    bool juego_terminado = false;
    int turno_actual = 0;

    string comando;

    while (!juego_terminado)
    {
       cout << "$ ";
       cin >> comando;

       switch (comando[0]){
        case 'i':
            if(comando == "inicializar_juego" || comando == "i"){
                inicializarJuego(jugadores, territorios);
            }
            break;
        case 't':
            if(comando == "turno_jugador" || comando == "tj"){
                turnoJugador(jugadores, territorios);
            }
            break;
        case 's':
            if(comando ==  "salir" || comando == "s"){
                salir();
            }
            break;
        case 'a':
            if(comando == "ayuda" || comando == "a"){
                mostrarAyuda();
            }
            break;
        defualt:
            cout << "Comando invalido. Para ver la lista de comandos disponilbes, ingrese 'a' o 'ayuda'. " << endl;
       }
    }
    return 0;
}