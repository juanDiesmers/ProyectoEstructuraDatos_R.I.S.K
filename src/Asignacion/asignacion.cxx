#include <iostream> 
#include <vector>
#include <string>
#include <algorithm> 

#include "asignacion.h"
#include "../turno/turno.h"
#include "../risk.h"

using namespace std;

vector<string> paisesAmericaDelNorte = {"Alaska", "Alberta", "America Central", "Estados unidos Orientales", "Groenlandia", "Territorio Noroccidental", "Ontario", "Quebec", "Estados Unidos Occidentales"};
vector<string> paisesAmericaDelSur = {"Argentina", "Brasil", "Peru", "Venezuela"};
vector<string> paisesEuropa = {"Gran Bretania", "Islandia", "Europa del norte", "Escandinavia", "Europa del sur", "Ucrania", "Europa Occidenal"};
vector<string> paisesAfrica = {"Congo", "Africa Oriental", "Egipto", "Madagascar", "Africa del norte", "Africa del Sur"};
vector<string> paisesAsia = {"Afghanistan", "China", "India", "Irkutsk", "Japon", "Kamchatka", "Medio oriente", "Mongolia", "Siam", "Siberia", "Ural", "Yakutsk"};
vector<string> paisesAustralia = {"Australia Oriental", "Indonesia", "Nueva Guinea", "Australia Occidental"};

// Funciones del componente 1: Configuracion del juego
void  inicializarJuego(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios){
    limpiarPantalla();
    std::cout << "Ingreso correctamente a la funcion inicializarJuego." << std::endl;
      if (!jugadores.empty() || !territorios.empty()) {
        cout << "El juego ya ha sido inicializado." << endl;
        return;
    }

    cout << "Bienvenido a la inicializacion del juego Risk!" << endl;

    int num_jugadores;

    while (num_jugadores < 2 || num_jugadores > 6) {
        cout << "Ingrese el numero de jugadores (2-6): ";
        cin >> num_jugadores;

        if (num_jugadores < 2 || num_jugadores > 6) {
            cout << "Numero de jugadores no valido." << endl;
        }
    }

    jugadores.resize(num_jugadores);

    // Lógica para asignar la cantidad de piezas según el número de jugadores
    int numPiezas;
    if (num_jugadores == 2) {
        numPiezas = 40;
    } else if (num_jugadores == 3) {
        numPiezas = 35;
    } else if (num_jugadores == 4) {
        numPiezas = 30;
    } else if (num_jugadores == 5) {
        numPiezas = 25;
    } else if (num_jugadores == 6) {
        numPiezas = 20;
    }
    

    //arrglar si se coloca un numero
    for (int i = 0; i < num_jugadores; i++) {
        cout << "Jugador " << i + 1 << ": Ingrese su nombre (solo un nombre): ";
        cin >> jugadores[i].nombre;

        bool color_valido = false;
        while (!color_valido) {
            cout << "Seleccione su color (verde, azul, rojo, amarillo, negro, gris): ";
            cin >> jugadores[i].color;

        // Convertir la entrada del usuario a minúsculas
            transform(jugadores[i].color.begin(), jugadores[i].color.end(), jugadores[i].color.begin(), ::tolower);

        // Validar color
        if (jugadores[i].color == "verde" || jugadores[i].color == "azul" ||
            jugadores[i].color == "rojo" || jugadores[i].color == "amarillo" ||
            jugadores[i].color == "negro" || jugadores[i].color == "gris") {
            color_valido = true;
            } else {
            cout << "Color no valido. Seleccione un color correcto." << endl;
            }
        }
        // Validar que el color no esté en uso por otro jugador
        for (int j = 0; j < i; j++) {
            if (jugadores[j].color == jugadores[i].color) {
                cout << "Color ya esta en uso por otro jugador. Seleccione otro." << endl;
                color_valido = false;
                break;
            }
        }
        if (!color_valido) {
            i--; // Repetir el ciclo para el mismo jugador
            continue;
        }

        jugadores[i].id = i + 1; // Asignar ID de jugador
    }

    cout << "Jugadores registrados:" << endl;
    for (const Jugador& jugador : jugadores) {
        cout << "ID: " << jugador.id << " | Nombre: " << jugador.nombre << " | Color: " << jugador.color << endl;
    }

     // Mostrar el primer jugador registrado con su color
    cout << endl << "Primer Jugador: " << jugadores[0].nombre << " | Color: " << jugadores[0].color << endl;


    // Asignar la cantidad de piezas a cada jugador -----------------------------------------------------
    for (Jugador& jugador : jugadores) {
        jugador.numPiezas = numPiezas;
    }

    // Lógica para seleccionar continentes y territorios
    for (Jugador& jugador : jugadores) {
    cout << endl <<"Turno de " << jugador.nombre << " para seleccionar continentes y territorios:" << endl;

    string pais_seleccionado; // Declaración de pais_seleccionado
    string continente_seleccionado;

    bool paisValido = false; // Bandera para controlar si se eligió un país válido
    
    while (!paisValido) { // Repetir hasta que se elija un país válido
    cout << "Lista de continentes disponibles:" << endl;
    cout << "1. America del Norte" << endl;
    cout << "2. America del Sur" << endl;
    cout << "3. Europa" << endl;
    cout << "4. Africa" << endl;
    cout << "5. Asia" << endl;
    cout << "6. Oceania" << endl;

    int opcion_continente;
    cout << "Seleccione un continente (1-6): ";
    cin >> opcion_continente;

    int opcion_pais;

    switch (opcion_continente) {
        case 1: // América del Norte
            cout <<endl<< "Lista de paises disponibles en America del Norte:" << endl;
            cout << "1. Alaska" << endl;
            cout << "2. Alberta" << endl;
            cout << "3. America Central" << endl;
            cout << "4. Estados unidos Orientales" << endl;
            cout << "5. Groeenlandia" << endl;
            cout << "6. Territorio Noroccidental" << endl;
            cout << "7. Ontario" << endl;
            cout << "8. Quebec" << endl;
            cout << "9. Estados Unidos Occidentales" << endl;

            cout << "Seleccione un pais (1-9): ";
            cin >> opcion_pais;

            // Validar la opción del país y asignar el nombre a pais_seleccionado
            if (opcion_pais >= 1 && opcion_pais <= 9) {
               pais_seleccionado = paisesAmericaDelNorte[opcion_pais - 1]; // Asigna el nombre real del país
                    continente_seleccionado = "America del Norte"; // Asigna el continente seleccionado
                } else {
                cout << "Opcion de pais no valida." << endl;
                    while (true) {
                        cout << "Seleccione un pais (1-9): ";
                        cin >> opcion_pais;

                        if (opcion_pais >= 1 && opcion_pais <= 9) {
                            pais_seleccionado = paisesAmericaDelNorte[opcion_pais - 1];
                            continente_seleccionado = "America del Norte";
                            paisValido = true;
                            break; // Sale del ciclo interno cuando se ingresa un dato válido
                        } else {
                            cout << "Opcion de pais no valida." << endl;
                            
                        }
                    }
            }
        
            break;

        case 2: // América del Sur
            cout <<endl<< "Lista de paises disponibles en America del Sur:" << endl;
            cout << "1. Argentina" << endl;
            cout << "2. Brasil" << endl;
            cout << "3. Peru" << endl;
            cout << "4. Venezuela" << endl;

            cout << "Seleccione un pais (1-4): ";
            cin >> opcion_pais;

            // Validar la opción del país y asignar el nombre a pais_seleccionado
            if (opcion_pais >= 1 && opcion_pais <= 4) {
                    pais_seleccionado = paisesAmericaDelSur[opcion_pais - 1]; // Asigna el nombre real del país
                    continente_seleccionado = "America del Sur"; // Asigna el continente seleccionado
                } else {
                cout << "Opcion de pais no valida." << endl;
                while (true) {
                        cout << "Seleccione un pais (1-4): ";
                        cin >> opcion_pais;

                        if (opcion_pais >= 1 && opcion_pais <= 4) {
                            pais_seleccionado = paisesAmericaDelSur[opcion_pais - 1];
                            continente_seleccionado = "America del Sur";
                            paisValido = true;
                            break;
                        } else {
                            cout << "Opcion de pais no valida." << endl;
                        }
                    }
                }
        
            break;

        case 3: //Europa
            cout <<endl<< "Lista de paises disponibles en Europa:" << endl;
            cout << "1. Gran Bretania" << endl;
            cout << "2. Islandia" << endl;
            cout << "3. Europa del norte" << endl;
            cout << "4. Escandinavia" << endl;
            cout << "5. Europa del sur" << endl;
            cout << "6. Ucrania" << endl;
            cout << "7. Europa Occidenal" << endl;

            cout << "Seleccione un pais (1-7): ";
            cin >> opcion_pais;

            // Validar la opción del país y asignar el nombre a pais_seleccionado
            if (opcion_pais >= 1 && opcion_pais <= 7) {
                pais_seleccionado = paisesEuropa[opcion_pais - 1]; // Asigna el nombre real del país
                    continente_seleccionado = "Europa"; // Asigna el continente seleccionado
                } else {
                cout << "Opcion de pais no valida." << endl;
                while (true) {
                        cout << "Seleccione un pais (1-7): ";
                        cin >> opcion_pais;

                        if (opcion_pais >= 1 && opcion_pais <= 7) {
                            pais_seleccionado = paisesAmericaDelSur[opcion_pais - 1];
                            continente_seleccionado = "Europa";
                            paisValido = true;
                            break;
                        } else {
                            cout << "Opcion de pais no valida." << endl;
                        }
                    }
                }
        

            break;

        case 4: // Africa
            cout <<endl<< "Lista de paises disponibles en Africa:" << endl;
            cout << "1. Congo" << endl;
            cout << "2. Africa Oriental" << endl;
            cout << "3. Egipto" << endl;
            cout << "4. Madagascar" << endl;
            cout << "5. Africa del norte" << endl;
            cout << "6. Africa del Sur" << endl;

            cout << "Seleccione un pais (1-6): ";
            cin >> opcion_pais;

            // Validar la opción del país y asignar el nombre a pais_seleccionado
            if (opcion_pais >= 1 && opcion_pais <= 6) {
                pais_seleccionado = paisesAfrica[opcion_pais - 1]; // Asigna el nombre real del país
                    continente_seleccionado = "Africa"; // Asigna el continente seleccionado
                } else {
                cout << "Opcion de pais no valida." << endl;
                while (true) {
                        cout << "Seleccione un pais (1-6): ";
                        cin >> opcion_pais;

                        if (opcion_pais >= 1 && opcion_pais <= 6) {
                            pais_seleccionado = paisesAmericaDelSur[opcion_pais - 1];
                            continente_seleccionado = "Africa";
                            paisValido = true;
                            break;
                        } else {
                            cout << "Opcion de pais no valida." << endl;
                        }
                    }
                }
            

            break;    
        
        case 5: // Asia
            cout <<endl<< "Lista de paises disponibles en Asia:" << endl;
            cout << "1. Afghanistán" << endl;
            cout << "2. China" << endl;
            cout << "3. India" << endl;
            cout << "4. Irkutsk" << endl;
            cout << "5. Japon" << endl;
            cout << "6. Kamchatka" << endl;
            cout << "7. Medio oriente" << endl;
            cout << "8. Mongolia" << endl;
            cout << "9. Siam" << endl;
            cout << "10. Siberia" << endl;
            cout << "11. Ural" << endl;
            cout << "12. Yakutsk" << endl;

            cout << "Seleccione un pais (1-12): ";
            cin >> opcion_pais;

            // Validar la opción del país y asignar el nombre a pais_seleccionado
            if (opcion_pais >= 1 && opcion_pais <= 12) {
                pais_seleccionado = paisesAsia[opcion_pais - 1]; // Asigna el nombre real del país
                    continente_seleccionado = "Asia"; // Asigna el continente seleccionado
                } else {
                cout << "Opcion de pais no valida." << endl;
                while (true) {
                        cout << "Seleccione un pais (1-12): ";
                        cin >> opcion_pais;

                        if (opcion_pais >= 1 && opcion_pais <= 12) {
                            pais_seleccionado = paisesAmericaDelSur[opcion_pais - 1];
                            continente_seleccionado = "Asia";
                            paisValido = true;
                            break;
                        } else {
                            cout << "Opcion de pais no valida." << endl;
                        }
                    }
                }
            

            break; 

        case 6: // Australia
            cout <<endl<< "Lista de paises disponibles en Australia:" << endl;
            cout << "1. Australia Oriental" << endl;
            cout << "2. Indonesia" << endl;
            cout << "3. Nueva Guinea" << endl;
            cout << "4. Australia Occidental" << endl;

            cout << "Seleccione un pais (1-4): ";
            cin >> opcion_pais;

            // Validar la opción del país y asignar el nombre a pais_seleccionado
            if (opcion_pais >= 1 && opcion_pais <= 4) {
                pais_seleccionado = paisesAustralia[opcion_pais - 1]; // Asigna el nombre real del país
                    continente_seleccionado = "Australia"; // Asigna el continente seleccionado
                } else {
                cout << "Opcion de pais no valida." << endl;
                while (true) {
                        cout << "Seleccione un pais (1-4): ";
                        cin >> opcion_pais;

                        if (opcion_pais >= 1 && opcion_pais <= 4) {
                            pais_seleccionado = paisesAmericaDelSur[opcion_pais - 1];
                            continente_seleccionado = "Australia";
                            paisValido = true;
                            break;
                        } else {
                            cout << "Opcion de pais no valida." << endl;
                        }
                    }
                }
            

            break; 

        default:
            cout << "Opcion de continente no valida." << endl;
            break;
    }

        //if (!pais_seleccionado.empty()) { (en caso de no verificar)

    // Verificar si el país ya ha sido seleccionado por otro jugador
        bool paisYaSeleccionado = false;
        for (const Jugador& otroJugador : jugadores) {
            for (const Territorio& territorio : otroJugador.territorio) {
                if (territorio.nombre == pais_seleccionado) {
                    paisYaSeleccionado = true;
                    break;
                }
            }
            if (paisYaSeleccionado) {
                cout << "El pais <" << pais_seleccionado << "> ya ha sido seleccionado por otro jugador. Elige otro pais." << endl;
                break;
            }
        }

    if (!paisYaSeleccionado) {
        paisValido = true; // Marcar que se eligió un país válido
        Territorio territorio;
        territorio.nombre = pais_seleccionado;// se gurda el pais seleccionado
        territorio.jugador = jugador.nombre; // se guarda el territorio en cada Jugador
        territorio.id = jugador.territorio.size() + 1; // Asignar un ID único al territorio
        territorio.unidades_ejercito = 1; // Asignar una unidad al territorio
        
        territorio.continente = continente_seleccionado; // Asignar el continente al territorio


        jugador.territorio.push_back(territorio); // Agregar el territorio al vector del jugador
        territorios.push_back(territorio); // Agregar el territorio a la lista global de territorios
        jugador.numPiezas--; // Restar una pieza al jugador

        cout << endl <<"< "<< jugador.nombre << " > ha seleccionado el territorio << " << pais_seleccionado << " >> en el continente << " << continente_seleccionado <<" >>" << endl;
        cout << "Piezas restantes de " << jugador.nombre << ": " << jugador.numPiezas << endl;
        cout << "Pieza asignada a " << territorio.nombre << ", Numero de piezas actual: "<< jugador.numPiezas << endl;

        // Asignar territorios vecinos solo del mismo continente y otros jugadores
        for (Territorio& territorio : jugador.territorio) {
            for (const Territorio& otroTerritorio : territorios) {
                if (otroTerritorio.continente == territorio.continente && otroTerritorio.nombre != territorio.nombre) {
                    territorio.territorios_vecinos.push_back(otroTerritorio.id);
                }
            }
    
            // Agrega este mensaje de depuración para ver los nombres de los territorios vecinos
            cout << "Territorio " << territorio.nombre << " tiene los siguientes vecinos: ";
            for (int vecino_id : territorio.territorios_vecinos) {
                const Territorio& vecino = territorios[vecino_id - 1];
                cout << vecino.nombre << ", ";
            }
            cout << endl;
        }
        
            
        }   
    
    }

}
    // Informar que la inicialización fue exitosa
    cout << "El juego se ha inicializado correctamente." << endl;
}



