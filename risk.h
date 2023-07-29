#ifndef RISK_H
#define RISK_H

#include <string>
#include <vector>
#include <map>

//Declaraciones de las estructuras para paises y continentes
struct Pais{
    std::string nombre;
    std::string continente;
    int ejercitos;
};

struct Continente{
    std::string nombre;
    int bonusEjercito;
};

//Declaracion de la clase para el jugador
class Jugador{
public:
    std::string nombre;
    std::vector<Pais> paisesControlados;

    //

    //Declaraciòn de la funcion para que el jugador realice acciones
    void conquistaPais(Pais& pais, int ejercitos);
    void atacarPais(Pais& pais, int ejercitos);
    void reagruparEjercitos(Pais& origen, Pais& destino, int ejercitos);

};


#endif //risk.h