#include <iostream>
#include "asignacion.h"
#include "../risk.h"

using namespace std;

vector<string> paisesAmericaDelNorte = {"Alaska", "Alberta", "America Central", "Estados Unidos Orientales", "Groenlandia", "Territorio Noroccidental", "Ontario", "Quebec", "Estados Unidos Occidentales"};
vector<string> paisesAmericaDelSur = {"Argentina", "Brasil", "Peru", "Venezuela"};
vector<string> paisesEuropa = {"Gran Bretania", "Islandia", "Europa del norte", "Escandinavia", "Europa del sur", "Ucrania", "Europa Occidenal"};
vector<string> paisesAfrica = {"Congo", "Africa Oriental", "Egipto", "Madagascar", "Africa del norte", "Africa del Sur"};
vector<string> paisesAsia = {"Afghanistan", "China", "India", "Irkutsk", "Japon", "Kamchatka", "Medio oriente", "Mongolia", "Siam", "Siberia", "Ural", "Yakutsk"};
vector<string> paisesAustralia = {"Australia Oriental", "Indonesia", "Nueva Guinea", "Australia Occidental"};

// Funciones del componente 1: Configuración del juego
bool inicializarJuego(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios){
    limpiarPantalla();
    cout << "Ingresando a la función inicializarJuego." << endl;
    
    if (!jugadores.empty() || !territorios.empty()) {
        cout << "El juego ya ha sido inicializado." << endl;
        return false;
    }

    cout << "Bienvenido a la inicialización del juego Risk!" << endl;

    int num_jugadores;

    while (num_jugadores < 2 || num_jugadores > 6) {
        cout << "Ingrese el número de jugadores (2-6): ";
        cin >> num_jugadores;

        if (num_jugadores < 2 || num_jugadores > 6) {
            cout << "Número de jugadores no válido." << endl;
        }
    }

    jugadores.resize(num_jugadores); 

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
                cout << "Color no válido. Seleccione un color correcto." << endl;
            }
        }

        // Validar que el color no esté en uso por otro jugador
        for (int j = 0; j < i; j++) {
            if (jugadores[j].color == jugadores[i].color) {
                cout << "Color ya está en uso por otro jugador. Seleccione otro." << endl;
                color_valido = false;
                break;
            }
        }

        if (!color_valido) {
            i--; // Repetir el ciclo para el mismo jugador
            continue;
        }

        jugadores[i].id = i + 1; 
    }

    cout << "Jugadores registrados: " << endl;
    for(const Jugador& jugador : jugadores) {
        cout << "ID: " << jugador.id << "| Nombre: " <<  jugador.nombre << "| Color: " << jugador.color << endl;  
    }
    pausarPantalla();
    limpiarPantalla();
    
    cout << "Primer jugador: " << jugadores[0].nombre << "| Color: " << jugadores[0].color << endl;

    for (Jugador& jugador : jugadores) {
        jugador.numPiezas = numPiezas;
    }

    int territoriosAsignados = 0;

    do {
        for (Jugador& jugador : jugadores) {
            cout << endl << "Turno de " << jugador.nombre << " para seleccionar continentes y territorios:" << endl;

            string pais_seleccionado; 
            string continente_seleccionado;

            bool paisValido = false; 

            while (!paisValido) {
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
                    case 1: 
                        cout << "Lista de paises disponibles en America del Norte:" << endl;
                        for (int i = 0; i < paisesAmericaDelNorte.size(); i++) {
                            cout << i + 1 << ". " << paisesAmericaDelNorte[i] << endl;
                        }
                        break;
                    case 2: 
                        cout << "Lista de paises disponibles en America del Sur:" << endl;
                        for (int i = 0; i < paisesAmericaDelSur.size(); i++) {
                            cout << i + 1 << ". " << paisesAmericaDelSur[i] << endl;
                        }
                        break;
                    case 3: 
                        cout << "Lista de paises disponibles en Europa:" << endl;
                        for (int i = 0; i < paisesEuropa.size(); i++) {
                            cout << i + 1 << ". " << paisesEuropa[i] << endl;
                        }
                        break;
                    case 4: 
                        cout << "Lista de paises disponibles en Africa:" << endl;
                        for (int i = 0; i < paisesAfrica.size(); i++) {
                            cout << i + 1 << ". " << paisesAfrica[i] << endl;
                        }
                        break;
                    case 5: 
                        cout << "Lista de paises disponibles en Asia:" << endl;
                        for (int i = 0; i < paisesAsia.size(); i++) {
                            cout << i + 1 << ". " << paisesAsia[i] << endl;
                        }
                        break;
                    case 6: 
                        cout << "Lista de paises disponibles en Oceania:" << endl;
                        for (int i = 0; i < paisesAustralia.size(); i++) {
                            cout << i + 1 << ". " << paisesAustralia[i] << endl;
                        }
                        break;
                    default:
                        cout << "Opcion de continente no valida." << endl;
                        break;
                }

                cout << "Seleccione un pais (1-6";
                switch (opcion_continente) {
                    case 1: cout << paisesAmericaDelNorte.size(); break;
                    case 2: cout << paisesAmericaDelSur.size(); break;
                    case 3: cout << paisesEuropa.size(); break;
                    case 4: cout << paisesAfrica.size(); break;
                    case 5: cout << paisesAsia.size(); break;
                    case 6: cout << paisesAustralia.size(); break;
                }
                cout << "): ";
                cin >> opcion_pais;

                switch (opcion_continente) {
                    case 1: 
                        if (opcion_pais >= 1 && opcion_pais <= paisesAmericaDelNorte.size()) {
                            pais_seleccionado = paisesAmericaDelNorte[opcion_pais - 1];
                            continente_seleccionado = "América del Norte";
                            paisValido = true;
                        }
                        break;
                    case 2: 
                        if (opcion_pais >= 1 && opcion_pais <= paisesAmericaDelSur.size()) {
                            pais_seleccionado = paisesAmericaDelSur[opcion_pais - 1];
                            continente_seleccionado = "América del Sur";
                            paisValido = true;
                        }
                        break;
                    case 3: 
                        if (opcion_pais >= 1 && opcion_pais <= paisesEuropa.size()) {
                            pais_seleccionado = paisesEuropa[opcion_pais - 1];
                            continente_seleccionado = "Europa";
                            paisValido = true;
                        }
                        break;
                    case 4: 
                        if (opcion_pais >= 1 && opcion_pais <= paisesAfrica.size()) {
                            pais_seleccionado = paisesAfrica[opcion_pais - 1];
                            continente_seleccionado = "África";
                            paisValido = true;
                        }
                        break;
                    case 5: 
                        if (opcion_pais >= 1 && opcion_pais <= paisesAsia.size()) {
                            pais_seleccionado = paisesAsia[opcion_pais - 1];
                            continente_seleccionado = "Asia";
                            paisValido = true;
                        }
                        break;
                    case 6: 
                        if (opcion_pais >= 1 && opcion_pais <= paisesAustralia.size()) {
                            pais_seleccionado = paisesAustralia[opcion_pais - 1];
                            continente_seleccionado = "Oceanía";
                            paisValido = true;
                        }
                        break;
                    default:
                        cout << "Opción de país no válida." << endl;
                        break;
                }
            }

            bool paisYaSeleccionado = false;
            for (const Jugador& otroJugador : jugadores) {
                for (const Territorio& territorio : otroJugador.territorio) {
                    if (territorio.nombre == pais_seleccionado) {
                        paisYaSeleccionado = true;
                        break;
                    }
                }
                if (paisYaSeleccionado) {
                    cout << "El país <" << pais_seleccionado << "> ya ha sido seleccionado por otro jugador. Elige otro país." << endl;
                    break;
                }
            }

            if (!paisYaSeleccionado) {
                paisValido = true; 
                Territorio territorio;
                territorio.nombre = pais_seleccionado;
                territorio.jugador = jugador.nombre;
                territorio.id = territorios.size() + 1;
                territorio.unidades_ejercito = 1;
                territorio.continente = continente_seleccionado;

                jugador.territorio.push_back(territorio);
                territorios.push_back(territorio);
                jugador.numPiezas--;

                cout << endl << "<" << jugador.nombre << "> ha seleccionado el territorio <" << pais_seleccionado << "> en el continente <" << continente_seleccionado << ">" << endl;
                cout << "Piezas restantes de " << jugador.nombre << ": " << jugador.numPiezas << endl;
                cout << "Pieza asignada a " << territorio.nombre << ", Numero de piezas actual: " << jugador.numPiezas << endl;

                for (Territorio& t : territorios) {
                    if (t.continente == continente_seleccionado && t.nombre != pais_seleccionado) {
                        territorio.territorios_vecinos.push_back(t.id);
                    }
                }

                //Agregar el territorio como "enemigo" al otro jugador
                for (Jugador& otroJugador : jugadores) {
                    if (otroJugador.id != jugador.id) {
                        for (Territorio& otroTerritorio : otroJugador.territorio) {
                            if (otroTerritorio.nombre == pais_seleccionado) {
                                VecinoEnemigo vecino;
                                vecino.nombre = territorio.nombre;
                                vecino.esEnemigo = true;
                                otroTerritorio.vecinos_enemigos.push_back(vecino);
                            }
                        }
                    }
                }

                cout << "Territorio " << territorio.nombre << " tiene los siguientes enemigos: ";
for (const Jugador& otroJugador : jugadores) {
    if (otroJugador.id != jugador.id) {
        for (const Territorio& otroTerritorio : otroJugador.territorio) {
            for (const VecinoEnemigo& vecino : otroTerritorio.vecinos_enemigos) {
                if (vecino.nombre == territorio.nombre && vecino.esEnemigo) {
                    if (otroTerritorio.nombre != territorio.nombre) {
                        cout << otroTerritorio.nombre << ", ";
                    }
                }
            }
        }
    }
}
                cout << endl;
            }
        }
        territoriosAsignados++;
        if (territoriosAsignados == 2) {
            break;
        }

    } while (territoriosAsignados != 2);

    cout << "EL juego se ha inicializado correctamente." << endl;

    return true;
}