# #Version 1.0
## TAD Inicializacion de Juego
### TAD Asignación
#### Asignacion.h
#### Conjunto mínimo de datos:
#### Estructura Territorios
- Identificador (Id), numérico, numero de territorio único.
- Nombre (nombre), cadena, nombre del territorio.
- Jugador (jugador), cadena, jugador que tiene el territorio.
- Ejercito (Unidades_Ejercito), numérico, asocia la cantidad de unidades que tiene el territorio.
- Territorios Vecinos (territorios_vecinos), vector numerico, representa la cantidad de territorios cercanos al territorio de referencia. 
#### Estructura Jugador
- Identificador (Id), numérico, numero de referencia del jugador.
- Nombre (nombre), cadena, nombre del jugador.
- Color (color), cadena, representa el color que llevara el jugador toda la partida.
- Territorios (territorio), vector de tipo territorio, asocia los territorios que tiene el jugador.
- Tarjetas (tarjetas), vector de tipo numérico, representa la cantidad de tarjetas de infanteria que tiene el jugador.
#### Asignación.cxx
#### Operaciones del objeto:
inicializarJuego(jugadores referencia a vector de Jugador, territorios referencia a vector de Territorio):
Booleano, función para asignar paises, identificadores, colores y territorios a cada jugador, además de vincular los vectores de territorio a cada continente, se asegura de verificar la inicializacion y que la entrada de los datos no sea erronea.