#include <iostream>
#include "risk.h"

using namespace std;

int main(){
    vector<Pais> paises;
    vector<Continente> continentes;
    map<string, vector<string>> fronteras;
    cargarPaises(paises);
    cargarContinentes(continentes);
    cargarFronteras(fronteras);

    vector<Jugador> jugadores;
    //cargar jugadores segun necesidades

    bool partidaEnCurso = true;
    while (partidaEnCurso){
        cout << "\nIngrese un comando('help' para ver la lista de comandos disponibles): ";
        string comando;
        cin >> comando;

        //convertir el comando a minusculas para hacerlo insensible a mayusculas
        for(char& c: comando){
            c = tolower(c);
        }

        if (comando == "help"){
            mostrarAyuda();
        }else {
            //uso de un switch para gestionar los comandos
            switch (comando[0]){
                case 'c':
                    if (comando == "cargar_paises" || comando == "cp"){
                        cargarPaises(paises);
                    } else if (comando == "cargar_continentes" || comando == "cc"){
                        cargarContinentes(continentes);
                    } else if (comando == "cargar_fronteras" || comando == "cf"){
                        cargarFronteras(fronteras);
                    } else if (comando == "conquistar_pais" || comando == "cpa"){

                    }
                    break;
                case 'a':
                    if (comando == "asignar_objetivos" || comando == "ao"){
                        asignarObjetivosAleatorios(jugadores);
                    } else if (comando == "asignnar_objetivos_segun_pais" || comando == "aosp"){
                        asignarObjetivosPorPaises(jugadores);
                    } else if (comando == "asignar_objeivos_segun_continente" || comando == "aosc" ){
                        asignarObjetivosPorContinente(jugadores);
                    } else if (comando == "atacar_pais" || comando == "ap"){

                    }
                    break;
                case 'm':
                    if (comando == "mostrar_objetivos" || comando == "mo"){
                        mostrarObjetivos(jugadores);
                    } else if (comando == "mostrar_objetivos_Jugador" || comando == "moj"){
                        
                    } else if (comando == "mostrar_objetivos_pais" || comando == "mop"){

                    } else if (comando == "mostrar_objetivos_continete" || comando == "moc"){

                    } else if (comando == "mostrar_paises" || comando == "mp"){
                        mostrarPaises(paises);
                    } else if (comando == "mostar_continentes" || comando == "mc"){
                        mostrarContinente(continentes);
                    } else if (comando == "mostrar_fronteras" || comando == "mf"){
                        mostrarFronteras(fronteras);
                    }
                    break;
                case 'r':
                    if (comando == "reagrupar_ejercitos" || comando == "re"){

                    }
                    break;
                case 's':
                    if (comando == "salir" || comando == "s"){
                        partidaEnCurso = false;
                    }//escribir mas comandos que sean con s
                    break;
                default:
                    cout << "Comando desconocido.\n";
                    break; 
            }
        }
    }
    return 0;
}