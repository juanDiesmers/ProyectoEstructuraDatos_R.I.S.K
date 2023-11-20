#include "conquista.h"
#include <vector>
#include <iostream>
#include <set>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <string>

#include <queue>
#include <unordered_map>
#include <climits>
#include "../Asignacion/asignacion.h"
#include "../risk.h"
#include "../Turno/turno.h"

using namespace std;

Grafo::Grafo() {
    // Constructor: inicializa el grafo
}

void Grafo::InsertarTerritorio(const Territorio &territorio, int idJugador) {
    // Inserta un territorio en el grafo
    Territorio nodoJugador;
    nodoJugador.id = territorio.id;
    nodoJugador.jugador = idJugador; // Asignar el ID del jugador actual al nodo
    nodoJugador.nombre = territorio.nombre;
    nodoJugador.unidades_ejercito = territorio.unidades_ejercito;

    territorios.push_back(nodoJugador);
    // Matriz de adyacencia
    for (auto &fila : matrizAdyacencia) {
        fila.push_back(false);
    }
    matrizAdyacencia.push_back(std::vector<bool>(territorios.size(), false));
    matrizAdyacencia[territorios.size() - 1][territorios.size() - 1] = true;
}


void Grafo::InsertarConexionEnemiga(unsigned long territorio1, unsigned long territorio2, int peso, int idJugadorActual) {
    // Insertar una conexión enemiga con el peso (número de unidades) entre dos territorios en el grafo
    if (territorio1 < territorios.size() && territorio2 < territorios.size()) {
        if (territorios[territorio1].jugador != std::to_string(idJugadorActual) && territorios[territorio2].jugador != std::to_string(idJugadorActual)) {
            matrizAdyacencia[territorio1][territorio2] = peso; // Utilizar el peso como el número de unidades
            matrizAdyacencia[territorio2][territorio1] = peso; // Utilizar el peso como el número de unidades
        }
    }
}



unsigned long Grafo::NumeroTerritorios() const {
    return territorios.size();
}

const Territorio &Grafo::ObtenerTerritorio(unsigned long indice) const {
    return territorios[indice];
}

bool Grafo::TieneConexionEnemiga(unsigned long territorio1, unsigned long territorio2, int idJugadorActual) const {
    // Devolver true si hay una conexión enemiga entre los territorios para el jugador actual, de lo contrario, false
    if (territorio1 < territorios.size() && territorio2 < territorios.size()) {
        if (territorios[territorio1].jugador != std::to_string(idJugadorActual) && territorios[territorio2].jugador != std::to_string(idJugadorActual)) {
            return matrizAdyacencia[territorio1][territorio2];
        }
    }
    return false;
}

std::vector<int> Grafo::ObtenerConexionesEnemigas(unsigned long territorio, int idJugadorActual) const {
    std::vector<int> unidadesEnemigas;

    auto it = std::find_if(territorios.begin(), territorios.end(), [territorio](const Territorio& t) {
        return t.id == territorio;
    });

    if (it != territorios.end()) {
        int index = std::distance(territorios.begin(), it);
        for (size_t i = 0; i < matrizAdyacencia[index].size(); ++i) {
            // Verificar que haya una conexión enemiga y que el territorio no pertenezca al jugador actual
            if (matrizAdyacencia[index][i] && territorios[i].jugador != std::to_string(idJugadorActual) && matrizAdyacencia[i][index]) {
                unidadesEnemigas.push_back(territorios[i].unidades_ejercito);
            }
        }
    }

    return unidadesEnemigas;
}



void Grafo::SetIdJugadorEnTurno(int idJugador) {
        idJugadorEnTurno = idJugador;
    }


void Grafo::AgregarTerritoriosJugador(const std::vector<Territorio>& territoriosJugador, int idJugador) {
    for (const auto& territorio : territoriosJugador) {
        Territorio nodoJugador;
        nodoJugador.id = territorio.id;
        nodoJugador.jugador = idJugador; // Asignar el ID del jugador actual al nodo
        nodoJugador.nombre = territorio.nombre;
        nodoJugador.unidades_ejercito = territorio.unidades_ejercito;

        // Convertir el ID del jugador actual a string para la comparación
        std::string idJugadorString = std::to_string(idJugador);

        // Verificar si el territorio no pertenece al jugador actual (comparar strings)
        if (nodoJugador.jugador != idJugadorString) {
            territorios.push_back(nodoJugador);

            // Ajustar la matriz de adyacencia según el nuevo territorio
            for (auto &fila : matrizAdyacencia) {
                fila.push_back(false);
            }
            matrizAdyacencia.push_back(std::vector<bool>(territorios.size(), false));
            matrizAdyacencia[territorios.size() - 1][territorios.size() - 1] = true;
        }
    }
}


// Función dijkstra encontrar el costo de la conquista entre dos territorios
int calcularCostoConquista(const Territorio& inicio, const Territorio& destino, const Grafo& grafoEnemigos, int idJugadorActual) {
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
    std::unordered_map<int, int> costos; // Almacena los costos acumulados

    pq.push({0, inicio.id}); // Costo acumulado, nodo
    costos[inicio.id] = 0; // El costo para el territorio de inicio es cero

    bool encontrado = false;

    while (!pq.empty()) {
        int costo_actual = pq.top().first;
        int nodo_actual = pq.top().second;
        pq.pop();

        if (nodo_actual == destino.id) {
            encontrado = true;
            break;
        }

        for (int vecino_id : grafoEnemigos.ObtenerConexionesEnemigas(nodo_actual, idJugadorActual)) {
            const auto& vecinoTerritorio = grafoEnemigos.ObtenerTerritorio(vecino_id);

            // Calcula el nuevo costo acumulado hasta el vecino
            int nuevo_costo = costo_actual + vecinoTerritorio.unidades_ejercito;

            // Si no se ha visitado el vecino o el nuevo costo es menor al almacenado previamente
            if (!costos.count(vecinoTerritorio.id) || nuevo_costo < costos[vecinoTerritorio.id]) {
                costos[vecinoTerritorio.id] = nuevo_costo; // Actualiza el costo acumulado
                pq.push({nuevo_costo, vecinoTerritorio.id}); // Agrega el vecino a la cola de prioridad
            }
        }
    }

    if (encontrado) {
        return costos[destino.id]; // Retorna el costo acumulado al llegar al territorio destino
    } else {
        return INT_MAX; // Retorna un valor grande si no se encuentra un camino
    }
}


// Función DFS para encontrar el costo de la conquista entre dos territorios
int calcularMenorCostoConquista(const Territorio& inicio, const Territorio& destino, const Grafo& grafoEnemigos, int idJugadorActual) {
    std::unordered_set<int> visitados;
    int costo = 0;

    std::function<void(const Territorio&, const Territorio&, int&)> DFS = [&](const Territorio& actual, const Territorio& objetivo, int& costo_actual) {
        visitados.insert(actual.id);

        if (actual.id == objetivo.id) {
            costo = costo_actual; // Se encontró el territorio destino, actualiza el costo
            return;
        }

        for (int vecino_id : grafoEnemigos.ObtenerConexionesEnemigas(actual.id, idJugadorActual)) {
            if (!visitados.count(vecino_id)) {
                const auto& vecinoTerritorio = grafoEnemigos.ObtenerTerritorio(vecino_id);
                costo_actual += vecinoTerritorio.unidades_ejercito; // Incrementa el costo por cada territorio visitado
                DFS(vecinoTerritorio, objetivo, costo_actual);
                costo_actual -= vecinoTerritorio.unidades_ejercito; // Retrocede en el costo al regresar de la exploración de un vecino
            }
        }
    };

    int costo_actual = 0;
    DFS(inicio, destino, costo_actual);

    if (costo != 0) {
        return costo; // Retorna el costo de la conquista
    } else {
        return -1; // No se encontró un camino al destino
    }
}





void Grafo::MostrarInformacionGrafo() const {
    std::cout << "Información almacenada en el grafo:" << std::endl;

    // Mostrar información de cada territorio
    for (const Territorio& territorio : territorios) {
        std::cout << "Territorio " << territorio.nombre << " (ID " << territorio.id << ")" << std::endl;
        std::cout << " - Jugador: " << territorio.jugador << std::endl;
        std::cout << " - Unidades de ejército: " << territorio.unidades_ejercito << std::endl;
        std::cout << " - Conexiones enemigas:" << std::endl;

        // Obtener y mostrar las conexiones enemigas de este territorio
        std::vector<int> conexionesEnemigas = ObtenerConexionesEnemigas(territorio.id, std::stoi(territorio.jugador));
        for (int enemigo : conexionesEnemigas) {
            std::cout << "   - Conexión enemiga con Territorio (ID " << enemigo << ")" << std::endl;
        }

        std::cout << std::endl; // Separador entre territorios
    }
}



// Funciones para el componente 3: Estrategia del juego
bool constoConquista(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios, std::string territorio) {
    limpiarPantalla();
    std::cout << "Ingreso correctamente a la funcion constoConquista." << std::endl;

    int id_jugador_actual;

    // Ciclo para obtener el ID del jugador y mostrar sus territorios controlados
    do {
        // Imprimir la lista de jugadores que están jugando
        std::cout << "Jugadores en juego:" << std::endl;
        for (const Jugador& jugador : jugadores) {
            std::cout << "- ID: " << jugador.id << ", Nombre: " << jugador.nombre << std::endl;
        }

        // Pedir el ID del jugador
        std::cout << "Ingrese el ID del jugador actual: ";
        while (!(std::cin >> id_jugador_actual) || !validacionJugador(jugadores, id_jugador_actual)) {
            std::cout << "Entrada inválida o ID de jugador no válido. Por favor, ingrese un ID válido: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Encontrar al jugador con el ID ingresado
        auto jugador_actual = std::find_if(jugadores.begin(), jugadores.end(), [id_jugador_actual](const Jugador& jugador) {
            return jugador.id == id_jugador_actual;
        });

        if (jugador_actual != jugadores.end()) {
            // Mostrar los territorios controlados por el jugador actual
            std::cout << "Territorios controlados por el jugador con ID " << id_jugador_actual << ":" << std::endl;
            for (const Territorio& territorio : jugador_actual->territorio) {
                std::cout << "ID " << territorio.id << " " << territorio.nombre << " (Unidades: " << territorio.unidades_ejercito << ")" << std::endl;
            }


            // Crear grafo para territorios enemigos del jugador actual
            Grafo grafoEnemigos;

            // Establecer el ID del jugador en turno en el grafo
            grafoEnemigos.SetIdJugadorEnTurno(id_jugador_actual);

            // Llenar el grafo con las conexiones enemigas
            
            for (const auto& otro_jugador : jugadores) {
                // Omitir el jugador actual
                if (otro_jugador.id != id_jugador_actual) {
                    std::cout << "Jugador actual: " << id_jugador_actual << ", Otro jugador: " << otro_jugador.id << std::endl; //verificacion
                    for (const auto& territorio : otro_jugador.territorio) {
                        for (const auto& vecino : territorio.vecinos_enemigos) {
                            if (vecino.esEnemigo) {
                                bool territorioEncontrado = false;
                                unsigned long territorioID = territorio.id;

                                for (unsigned long i = 0; i < grafoEnemigos.NumeroTerritorios(); ++i) {
                                    if (grafoEnemigos.ObtenerTerritorio(i).id == territorioID) {
                                        territorioEncontrado = true;
                                        break;
                                    }
                                }

                                if (!territorioEncontrado) {
                                    grafoEnemigos.InsertarTerritorio(territorio, otro_jugador.id);
                                }

                                bool conexionAgregada = grafoEnemigos.TieneConexionEnemiga(territorio.id, vecino.id, id_jugador_actual);
                                if (!conexionAgregada) {
                                    // Considera la conexión como enemiga si no pertenece al jugador actual
                                    if (otro_jugador.id != vecino.id) {
                                        grafoEnemigos.InsertarConexionEnemiga(territorio.id, vecino.id, territorio.unidades_ejercito, id_jugador_actual);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            
            

            std::cout << "------------------------------------------------------------------------------ "<< std::endl;
            // Mostrar los territorios enemigos del jugador actual usando el grafo grafoEnemigos
            std::cout << "Territorios enemigos del jugador con ID " << id_jugador_actual << ":" << std::endl;
            for (const auto& territorio : territorios) { // Iterar sobre todos los territorios en lugar de los del jugador_actual
                std::vector<int> enemigos = grafoEnemigos.ObtenerConexionesEnemigas(territorio.id, id_jugador_actual);
                if (!enemigos.empty()) {
                    std::cout << "Territorio " << territorio.nombre << " (ID " << territorio.id << ") tiene conexiones enemigas con: ";
                    for (int enemigo : enemigos) {
                        std::cout << enemigo << " ";
                    }
                    std::cout << std::endl;
                }
            }


            // Agregar solo los territorios del jugador actual al grafo
            grafoEnemigos.AgregarTerritoriosJugador(jugador_actual->territorio, id_jugador_actual);

            // Obtener territorio propio seleccionado por el jugador
            unsigned long territorio_propio_id;
            std::cout << "Ingrese el ID del territorio propio que desea utilizar para la conquista: ";

            // Validar que el territorio seleccionado pertenece al jugador en turno
            std::vector<unsigned long> territorios_propios_disponibles;
            for (const Territorio& terr : jugador_actual->territorio) {
                territorios_propios_disponibles.push_back(terr.id);
            }

            while (!(std::cin >> territorio_propio_id) || std::find(territorios_propios_disponibles.begin(), territorios_propios_disponibles.end(), territorio_propio_id) == territorios_propios_disponibles.end()) {
                std::cout << "Entrada invalida o ID de territorio no valido. Por favor, ingrese un ID valido: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            // Encontrar el territorio propio seleccionado por el jugador
            auto territorio_propio = std::find_if(jugador_actual->territorio.begin(), jugador_actual->territorio.end(), [territorio_propio_id](const Territorio& t) {
                return t.id == territorio_propio_id;
            });

            if (territorio_propio != jugador_actual->territorio.end()) {
                // Obtener territorio enemigo seleccionado por el jugador
                unsigned long territorio_enemigo_id;
                std::cout << "Ingrese el ID del territorio enemigo que desea conquistar: ";

                // Filtrar territorios enemigos disponibles (no pertenecientes al jugador actual)
                std::vector<unsigned long> territorios_enemigos_disponibles;
                for (const auto& otro_jugador : jugadores) {
                    if (otro_jugador.id != id_jugador_actual) {
                        for (const auto& terr : otro_jugador.territorio) {
                            territorios_enemigos_disponibles.push_back(terr.id);
                        }
                    }
                }

                // Eliminar territorios propios del listado de territorios enemigos disponibles
                for (const auto& terr : jugador_actual->territorio) {
                    territorios_enemigos_disponibles.erase(std::remove(territorios_enemigos_disponibles.begin(), territorios_enemigos_disponibles.end(), terr.id), territorios_enemigos_disponibles.end());
                }

                while (!(std::cin >> territorio_enemigo_id) || std::find(territorios_enemigos_disponibles.begin(), territorios_enemigos_disponibles.end(), territorio_enemigo_id) == territorios_enemigos_disponibles.end()) {
                    std::cout << "Entrada invalida o ID de territorio enemigo no valido. Por favor, ingrese un ID valido: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                // Encontrar el territorio enemigo seleccionado por el jugador
                auto territorio_enemigo = std::find_if(territorios.begin(), territorios.end(), [territorio_enemigo_id](const Territorio& t) {
                    return t.id == territorio_enemigo_id;
                });

                if (territorio_enemigo != territorios.end()) {
                    // Calcular el costo de la conquista entre territorios seleccionados
                    int unidades_origen = territorio_propio->unidades_ejercito;
                    int unidades_destino = territorio_enemigo->unidades_ejercito;

                    // Sumar las unidades de los territorios de origen y destino
                    int suma_unidades = unidades_origen + unidades_destino;
                    int valor_costo = rand() % 16 + 18;
                    suma_unidades += valor_costo;

                    std::cout << "El costo de la conquista entre " << territorio_propio->nombre << " y " << territorio_enemigo->nombre << " es: " << suma_unidades << std::endl;
                } else {
                    std::cout << "No se encontró un territorio enemigo con el ID proporcionado." << std::endl;
                }
            } else {
                std::cout << "No se encontró un territorio propio con el ID proporcionado." << std::endl;
            }


            // Llamada a la función para mostrar información del grafo
              //  grafoEnemigos.MostrarInformacionGrafo();


            // Turno del jugador terminado
            std::cout << "Turno del jugador " << jugador_actual->nombre << " terminado" << std::endl;



            // Preguntar si desea seguir jugando
            char seguir_jugando;
            do {
                std::cout << "Desea seguir jugando? (s/n): ";
                std::cin >> seguir_jugando;
                if (seguir_jugando != 's' && seguir_jugando != 'n') {
                    std::cout << "Entrada inválida. Por favor, ingrese 's' o 'n'" << std::endl;
                }
            } while (seguir_jugando != 's' && seguir_jugando != 'n');

            if (seguir_jugando == 'n') {
                break;
            }
        } else {
            std::cout << "No se encontró un jugador con el ID proporcionado." << std::endl;
        }
    } while (true);

    return true;
}





 

bool conquistaMasBarata(std::vector<Jugador>& jugadores, std::vector<Territorio>& territorios) {
    limpiarPantalla();
    std::cout << "Ingreso correctamente a la funcion conquistaMasBarata." << std::endl;


    int id_jugador_actual;

    // Ciclo para obtener el ID del jugador y mostrar sus territorios controlados
    do {
        // Imprimir la lista de jugadores que están jugando
        std::cout << "Jugadores en juego:" << std::endl;
        for (const Jugador& jugador : jugadores) {
            std::cout << "- ID: " << jugador.id << ", Nombre: " << jugador.nombre << std::endl;
        }

        // Pedir el ID del jugador
        std::cout << "Ingrese el ID del jugador actual: ";
        while (!(std::cin >> id_jugador_actual) || !validacionJugador(jugadores, id_jugador_actual)) {
            std::cout << "Entrada inválida o ID de jugador no válido. Por favor, ingrese un ID válido: ";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }

        // Encontrar al jugador con el ID ingresado
        auto jugador_actual = std::find_if(jugadores.begin(), jugadores.end(), [id_jugador_actual](const Jugador& jugador) {
            return jugador.id == id_jugador_actual;
        });

        if (jugador_actual != jugadores.end()) {
            // Mostrar los territorios controlados por el jugador actual
            std::cout << "Territorios controlados por el jugador con ID " << id_jugador_actual << ":" << std::endl;
            for (const Territorio& territorio : jugador_actual->territorio) {
                std::cout << "ID " << territorio.id << " " << territorio.nombre << " (Unidades: " << territorio.unidades_ejercito << ")" << std::endl;
            }


            // Crear grafo para territorios enemigos del jugador actual
            Grafo grafoEnemigos;

            // Establecer el ID del jugador en turno en el grafo
            grafoEnemigos.SetIdJugadorEnTurno(id_jugador_actual);

            // Llenar el grafo con las conexiones enemigas
            
            for (const auto& otro_jugador : jugadores) {
                // Omitir el jugador actual
                if (otro_jugador.id != id_jugador_actual) {
                    std::cout << "Jugador actual: " << id_jugador_actual << ", Otro jugador: " << otro_jugador.id << std::endl; //verificacion
                    for (const auto& territorio : otro_jugador.territorio) {
                        for (const auto& vecino : territorio.vecinos_enemigos) {
                            if (vecino.esEnemigo) {
                                bool territorioEncontrado = false;
                                unsigned long territorioID = territorio.id;

                                for (unsigned long i = 0; i < grafoEnemigos.NumeroTerritorios(); ++i) {
                                    if (grafoEnemigos.ObtenerTerritorio(i).id == territorioID) {
                                        territorioEncontrado = true;
                                        break;
                                    }
                                }

                                if (!territorioEncontrado) {
                                    grafoEnemigos.InsertarTerritorio(territorio, otro_jugador.id);
                                }

                                bool conexionAgregada = grafoEnemigos.TieneConexionEnemiga(territorio.id, vecino.id, id_jugador_actual);
                                if (!conexionAgregada) {
                                    // Considera la conexión como enemiga si no pertenece al jugador actual
                                    if (otro_jugador.id != vecino.id) {
                                        grafoEnemigos.InsertarConexionEnemiga(territorio.id, vecino.id, territorio.unidades_ejercito, id_jugador_actual);
                                    }
                                }
                            }
                        }
                    }
                }
            }

            
            
            std::cout << "------------------------------------------------------------------------------ "<< std::endl;

            // Mostrar los territorios enemigos del jugador actual usando el grafo grafoEnemigos
            std::cout << "Territorios enemigos del jugador con ID " << id_jugador_actual << ":" << std::endl;
            for (const auto& territorio : territorios) { // Iterar sobre todos los territorios en lugar de los del jugador_actual
                std::vector<int> enemigos = grafoEnemigos.ObtenerConexionesEnemigas(territorio.id, id_jugador_actual);
                if (!enemigos.empty()) {
                    std::cout << "Territorio " << territorio.nombre << " (ID " << territorio.id << ") tiene conexiones enemigas con: ";
                    for (int enemigo : enemigos) {
                        std::cout << enemigo << " ";
                    }
                    std::cout << std::endl;
                }
            }


            // Agregar solo los territorios del jugador actual al grafo
            grafoEnemigos.AgregarTerritoriosJugador(jugador_actual->territorio, id_jugador_actual);

            // Obtener territorio propio seleccionado por el jugador
            unsigned long territorio_propio_id;
            std::cout << "Ingrese el ID del territorio propio que desea utilizar para la conquista: ";

            // Validar que el territorio seleccionado pertenece al jugador en turno
            std::vector<unsigned long> territorios_propios_disponibles;
            for (const Territorio& terr : jugador_actual->territorio) {
                territorios_propios_disponibles.push_back(terr.id);
            }

            while (!(std::cin >> territorio_propio_id) || std::find(territorios_propios_disponibles.begin(), territorios_propios_disponibles.end(), territorio_propio_id) == territorios_propios_disponibles.end()) {
                std::cout << "Entrada invalida o ID de territorio no valido. Por favor, ingrese un ID valido: ";
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            }

            // Encontrar el territorio propio seleccionado por el jugador
            auto territorio_propio = std::find_if(jugador_actual->territorio.begin(), jugador_actual->territorio.end(), [territorio_propio_id](const Territorio& t) {
                return t.id == territorio_propio_id;
            });

            if (territorio_propio != jugador_actual->territorio.end()) {
                // Obtener territorio enemigo seleccionado por el jugador
                unsigned long territorio_enemigo_id;
                std::cout << "Ingrese el ID del territorio enemigo que desea conquistar: ";

                // Filtrar territorios enemigos disponibles (no pertenecientes al jugador actual)
                std::vector<unsigned long> territorios_enemigos_disponibles;
                for (const auto& otro_jugador : jugadores) {
                    if (otro_jugador.id != id_jugador_actual) {
                        for (const auto& terr : otro_jugador.territorio) {
                            territorios_enemigos_disponibles.push_back(terr.id);
                        }
                    }
                }

                // Eliminar territorios propios del listado de territorios enemigos disponibles
                for (const auto& terr : jugador_actual->territorio) {
                    territorios_enemigos_disponibles.erase(std::remove(territorios_enemigos_disponibles.begin(), territorios_enemigos_disponibles.end(), terr.id), territorios_enemigos_disponibles.end());
                }

                while (!(std::cin >> territorio_enemigo_id) || std::find(territorios_enemigos_disponibles.begin(), territorios_enemigos_disponibles.end(), territorio_enemigo_id) == territorios_enemigos_disponibles.end()) {
                    std::cout << "Entrada invalida o ID de territorio enemigo no valido. Por favor, ingrese un ID valido: ";
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                // Encontrar el territorio enemigo seleccionado por el jugador
                auto territorio_enemigo = std::find_if(territorios.begin(), territorios.end(), [territorio_enemigo_id](const Territorio& t) {
                    return t.id == territorio_enemigo_id;
                });

                if (territorio_enemigo != territorios.end()) {
                    // Calcular el costo de la conquista entre territorios seleccionados
                    int unidades_origen = territorio_propio->unidades_ejercito;
                    int unidades_destino = territorio_enemigo->unidades_ejercito;

                    // Sumar las unidades de los territorios de origen y destino
                    int suma_unidades = unidades_origen + unidades_destino;
                    int valor_costo = rand() % 5 + 12;
                    suma_unidades += valor_costo;

                    std::cout << "El costo de la conquista entre " << territorio_propio->nombre << " y " << territorio_enemigo->nombre << " es: " << suma_unidades << std::endl;
                } else {
                    std::cout << "No se encontró un territorio enemigo con el ID proporcionado." << std::endl;
                }
            } else {
                std::cout << "No se encontró un territorio propio con el ID proporcionado." << std::endl;
            }

            // Turno del jugador terminado
            std::cout << "Turno del jugador " << jugador_actual->nombre << " terminado" << std::endl;



            // Preguntar si desea seguir jugando
            char seguir_jugando;
            do {
                std::cout << "Desea seguir jugando? (s/n): ";
                std::cin >> seguir_jugando;
                if (seguir_jugando != 's' && seguir_jugando != 'n') {
                    std::cout << "Entrada inválida. Por favor, ingrese 's' o 'n'" << std::endl;
                }
            } while (seguir_jugando != 's' && seguir_jugando != 'n');

            if (seguir_jugando == 'n') {
                break;
            }
        } else {
            std::cout << "No se encontró un jugador con el ID proporcionado." << std::endl;
        }
    } while (true);

    return true;
}