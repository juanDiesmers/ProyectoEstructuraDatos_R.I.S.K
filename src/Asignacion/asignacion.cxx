#include <iostream>
#include "asignacion.h"
#include "../risk.h"

#include <cstdlib> // Necesario para rand() y srand()
#include <ctime>   // Necesario para time()
#include <algorithm> // Necesario para std::shuffle
#include <random>    // Necesario para motores de números aleatorios
#include <chrono>    // Necesario para semilla aleatoria

using namespace std;

vector<string> paisesAmericaDelNorte = {"Alaska", "Alberta", "America Central", "Estados Unidos Orientales", "Groenlandia", "Territorio Noroccidental", "Ontario", "Quebec", "Estados Unidos Occidentales"};
vector<string> paisesAmericaDelSur = {"Argentina", "Brasil", "Peru", "Venezuela"};
vector<string> paisesEuropa = {"Gran Bretania", "Islandia", "Europa del norte", "Escandinavia", "Europa del sur", "Ucrania", "Europa Occidenal"};
vector<string> paisesAfrica = {"Congo", "Africa Oriental", "Egipto", "Madagascar", "Africa del norte", "Africa del Sur"};
vector<string> paisesAsia = {"Afghanistan", "China", "India", "Irkutsk", "Japon", "Kamchatka", "Medio oriente", "Mongolia", "Siam", "Siberia", "Ural", "Yakutsk"};
vector<string> paisesAustralia = {"Australia Oriental", "Indonesia", "Nueva Guinea", "Australia Occidental"};

// Variable global para el seguimiento del último ID asignado
int ultimoIdTerritorio = 0;

// Funciones del componente 1: Configuración del juego
bool inicializarJuego(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios){
    limpiarPantalla();
    cout << "Ingresando a la funcion inicializarJuego." << endl;
    
    if (!jugadores.empty() || !territorios.empty()) {
        cout << "El juego ya ha sido inicializado." << endl;
        return false;
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
    // Después de que todos los jugadores seleccionen un territorio
        cout<< endl;
        cout << "Todos los jugadores han seleccionado un territorio, ¿ Como desea continuar?" << endl;
        cout << "1. Seleccionar el resto de los territorios uno por uno." << endl;
        cout << "2. Seleccion aleatoria del resto de los territorios." << endl;
        int opcion;
        cin >> opcion;

        if (opcion == 1) {
        territoriosAsignados = 0; // Restablecer el contador para seleccionar más territorios
        }
        else if (opcion == 2){
            seleccionAleatoriaTerritorios(jugadores, territorios);
          // Salir del ciclo después de la selección aleatoria
          return 0;
        }

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

                cout << "Seleccione un pais (1-";
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
                            continente_seleccionado = "America del Norte";
                            paisValido = true;
                        }
                        break;
                    case 2: 
                        if (opcion_pais >= 1 && opcion_pais <= paisesAmericaDelSur.size()) {
                            pais_seleccionado = paisesAmericaDelSur[opcion_pais - 1];
                            continente_seleccionado = "America del Sur";
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
                            continente_seleccionado = "Africa";
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
                            continente_seleccionado = "Oceania";
                            paisValido = true;
                        }
                        break;
                    default:
                        cout << "Opcion de país no valida." << endl;
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
                    cout << "El pais <" << pais_seleccionado << "> ya ha sido seleccionado por otro jugador. Elige otro pais." << endl;
                    break;
                }
            }

            if (!paisYaSeleccionado) {
                paisValido = true; 
                Territorio territorio;
                territorio.nombre = pais_seleccionado;
                territorio.jugador = jugador.nombre;
                // Asignar el ID al territorio
                territorio.id = ++ultimoIdTerritorio;
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

                // Agregar el territorio como "enemigo" al otro jugador
                // Verificar si el territorio no es del jugador actual
                bool territorioNoEsDelJugadorActual = true;
                for (const Territorio& territorioDelJugador : jugador.territorio) {
                    if (territorioDelJugador.nombre == territorio.nombre) {
                        territorioNoEsDelJugadorActual = false;
                        break; // No es necesario buscar más
                    }
                }

                // Agregar el territorio como "enemigo" a otros jugadores
                for (Jugador& otroJugador : jugadores) {
                    
                    if (otroJugador.id != jugador.id) {
                        cout << "Iterando para el jugador " << otroJugador.nombre << endl;
                        cout << "Anadiendo enemigos para " << otroJugador.nombre << endl;
                        for (Territorio& otroTerritorio : otroJugador.territorio) {
                            VecinoEnemigo vecino;
                            vecino.nombre = territorio.nombre;
                            vecino.id = territorio.id;
                            otroTerritorio.vecinos_enemigos.push_back(vecino);
                            cout << "Territorio " << territorio.nombre << " anadido como enemigo a " << otroJugador.nombre << endl;
                        }
                    }
                }
                cout << "Territorio " << territorio.nombre << " tiene los siguientes enemigos: ";
                for (const VecinoEnemigo& vecino : territorio.vecinos_enemigos) {
                    if (vecino.esEnemigo) {
                            cout << vecino.nombre << ", ";
                    }
                }
                cout<< endl;
            }
        }
        territoriosAsignados++;
                

    } while (territoriosAsignados != 2);
    

    cout << "El juego se ha inicializado correctamente." << endl;
    //mostrarTerritoriosAsignados(jugadores);

    return true;
} 

// Función para seleccionar territorios aleatoriamente
void seleccionAleatoriaTerritorios(vector<Jugador>& jugadores, vector<Territorio>& territorios) {
    // Generar una semilla aleatoria basada en el tiempo
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    default_random_engine rng(seed);

    // Crear una lista de copias profundas de todos los territorios disponibles
    vector<string> todosLosPaises;
    todosLosPaises.insert(todosLosPaises.end(), paisesAmericaDelNorte.begin(), paisesAmericaDelNorte.end());
    todosLosPaises.insert(todosLosPaises.end(), paisesAmericaDelSur.begin(), paisesAmericaDelSur.end());
    todosLosPaises.insert(todosLosPaises.end(), paisesEuropa.begin(), paisesEuropa.end());
    todosLosPaises.insert(todosLosPaises.end(), paisesAfrica.begin(), paisesAfrica.end());
    todosLosPaises.insert(todosLosPaises.end(), paisesAsia.begin(), paisesAsia.end());
    todosLosPaises.insert(todosLosPaises.end(), paisesAustralia.begin(), paisesAustralia.end());

    vector<string> territoriosDisponibles = todosLosPaises;
    // Eliminar los territorios que ya han sido asignados en 'inicializarJuego'
    for (const Territorio& territorio : territorios) {
        auto it = find(territoriosDisponibles.begin(), territoriosDisponibles.end(), territorio.nombre);
        if (it != territoriosDisponibles.end()) {
            territoriosDisponibles.erase(it);
        }
    }

    // Recorrer los jugadores hasta que no tengan más piezas o no haya más territorios disponibles
    while (!territoriosDisponibles.empty()) {
        for (Jugador& jugador : jugadores) {
            if (jugador.numPiezas > 0 && !territoriosDisponibles.empty()) {
                // Seleccionar aleatoriamente un territorio disponible para el jugador actual
                uniform_int_distribution<int> distribution(0, territoriosDisponibles.size() - 1);
                int territorioAleatorioIndex = distribution(rng);
                string paisSeleccionado = territoriosDisponibles[territorioAleatorioIndex];

                // Encontrar el continente al que pertenece el país seleccionado
                string continenteAsignado;
                if (find(paisesAmericaDelNorte.begin(), paisesAmericaDelNorte.end(), paisSeleccionado) != paisesAmericaDelNorte.end()) {
                    continenteAsignado = "America del Norte";
                } else if (find(paisesAmericaDelSur.begin(), paisesAmericaDelSur.end(), paisSeleccionado) != paisesAmericaDelSur.end()) {
                    continenteAsignado = "America del Sur";
                } else if (find(paisesEuropa.begin(), paisesEuropa.end(), paisSeleccionado) != paisesEuropa.end()) {
                    continenteAsignado = "Europa";
                } else if (find(paisesAfrica.begin(), paisesAfrica.end(), paisSeleccionado) != paisesAfrica.end()) {
                    continenteAsignado = "Africa";
                } else if (find(paisesAsia.begin(), paisesAsia.end(), paisSeleccionado) != paisesAsia.end()) {
                    continenteAsignado = "Asia";
                } else if (find(paisesAustralia.begin(), paisesAustralia.end(), paisSeleccionado) != paisesAustralia.end()) {
                    continenteAsignado = "Australia";
                }

                
                // Asignar el territorio al jugador y asignar el continente
                Territorio territorio;
                territorio.nombre = paisSeleccionado;
                territorio.jugador = jugador.nombre;
                // Asignar el ID al territorio
                territorio.id = ++ultimoIdTerritorio;
                territorio.unidades_ejercito = 1; // Asignar 1 pieza al territorio
                territorio.continente = continenteAsignado;
                jugador.territorio.push_back(territorio);
                territorios.push_back(territorio);
                jugador.numPiezas--;
                //
                
                for (Territorio& t : territorios) {
                    if (t.continente == continenteAsignado  && t.nombre != paisSeleccionado) {
                        territorio.territorios_vecinos.push_back(t.id);
                    }
                }
                 bool territorioNoEsDelJugadorActual = true;
                for (const Territorio& territorioDelJugador : jugador.territorio) {
                    if (territorioDelJugador.nombre == territorio.nombre) {
                        territorioNoEsDelJugadorActual = false;
                        break; // No es necesario buscar más
                    }
                }

                // Agregar el territorio como "enemigo" a otros jugadores
                for (Jugador& otroJugador : jugadores) {
                    
                    if (otroJugador.id != jugador.id) {
                        cout << "Iterando para el jugador " << otroJugador.nombre << endl;
                        cout << "Anadiendo enemigos para " << otroJugador.nombre << endl;
                        for (Territorio& otroTerritorio : otroJugador.territorio) {
                            VecinoEnemigo vecino;
                            vecino.nombre = territorio.nombre;
                            vecino.id = territorio.id;
                            otroTerritorio.vecinos_enemigos.push_back(vecino);
                            cout << "Territorio " << territorio.nombre << " anadido como enemigo a " << otroJugador.nombre << endl;
                        }
                    }
                }
                cout << "Territorio " << territorio.nombre << " tiene los siguientes enemigos: ";
                for (const Jugador& otroJugador : jugadores) {
                    if (otroJugador.id != jugador.id) {
                        for (const Territorio& territorio : otroJugador.territorio){
                            cout << "Territorio ID " << territorio.id << " - " << territorio.nombre;
                        }
                    }
                }

                cout<< endl;
                cout << "Jugador: " << jugador.nombre << " asigno territorio: " << territorio.nombre << " en Continente: " << territorio.continente << " piezas "<< jugador.numPiezas << endl;
                // Eliminar el territorio de la lista de territorios disponibles
                territoriosDisponibles.erase(territoriosDisponibles.begin() + territorioAleatorioIndex); 
            }
        }
    }
    // Actualizar el número de piezas restantes de los jugadores después de la asignación
                int numPiezas;
                for (Jugador& jugador : jugadores) {
                    jugador.numPiezas = jugador.numPiezas -1; // Donde 'numPiezas' es el número correcto según la cantidad de jugadores
                }
    cout << "Todas las piezas han sido asignadas aleatoriamente." << endl;
    mostrarTerritoriosAsignados(jugadores);
}




void mostrarTerritoriosAsignados(const vector<Jugador>& jugadores) {
    cout << endl;
    cout << "Territorios asignados a cada jugador:" << endl;

    for (const Jugador& jugador : jugadores) {
        cout << "Jugador: " << jugador.nombre << " | Color: " << jugador.color << endl;
        cout << "Territorios asignados:" << endl;

        for (const Territorio& territorio : jugador.territorio) {
            cout << "  - Territorio: " << territorio.nombre << " | Continente: " << territorio.continente
                 << " | Piezas: " << territorio.unidades_ejercito << endl;
        }
        cout << "Total de piezas de " << jugador.nombre << ": " << jugador.numPiezas << endl;
        cout << "-----------------------------------------" << endl;
    }
}