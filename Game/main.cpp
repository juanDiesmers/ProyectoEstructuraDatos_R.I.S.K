#include <iostream>
#include "risk.h"

using namespace std;

int main(){
    vector<Jugador> jugadores;
    vector<Territorio> territorios;

    bool juego_inicializado = false;
    bool juego_terminado = true;
    int turno_actual = 0;

    string comando;


    while (!juego_terminado)
    {
       cout << "$ ";
       cin >> comando;

       if(comando == "inicializar" || comando == "i"){
            if(!juego_inicializado){
                juego_inicializado = inicializarJuego(jugadores, territorios);
            }
       } else if 
    }
    
    return 0;
}