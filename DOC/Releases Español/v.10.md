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
- Numero de Piezas (numPiezas), numérico, referencia al numero de tropas que tiene cada jugador según el numero de participantes del juego actual.
- Nombre (nombre), cadena, nombre del jugador.
- Color (color), cadena, representa el color que llevara el jugador toda la partida.
- Territorios (territorio), vector de tipo territorio, asocia los territorios que tiene el jugador.
- Tarjetas (tarjetas), vector de tipo numérico, representa la cantidad de tarjetas de infanteria que tiene el jugador.
#### Asignación.cxx
#### Operaciones del objeto:

inicializarJuego(jugadores referencia a vector de Jugador, territorios referencia a vector de Territorio):
- Booleano, función para asignar paises, identificadores, colores y territorios a cada jugador, además de vincular los vectores de territorio a cada continente, se asegura de verificar la inicializacion y que la entrada de los datos no sea erronea.

### TAD Turno
#### Turno.h
#### Conjunto mínimo de datos:
- Estructuras Territorios y Jugador.
#### Turno.cxx
#### Operaciones del objeto:

turnoJugador(jugadores referencia a vector de Jugador, territorios referencia a vector de Territorio):
- Función para establecer turnos en el juego para atacar, realizar ataques o fortificaciones a territorios.

validacionJugador(jugadores referencia a vector de Jugador, identificador del jugador actual):
- Booleana, que se ejecuta para comprobar la identificacion del jugador y si esta participando en el juego, además de asignar y verificar el turno siguiente durante la partida.

obtenerNuevasUnidades(jugadores referencia a vector de Jugador, territorios referencia a vector de Territorio, identificador del jugador actual):
- Función que calcula la ganancia de tropas según los casos del juego, donde el control de continentes o mas territorios añade mas soldados.

realizarFortificaciones(jugadores referencia a vector de Jugador, territorios referencia a vector de Territorio, identificador del jugador actual):
- Función que ofrece al usuario la elección de reforzar con tropas entre los territorios que posee y verificando las condiciones necesarias para realizarlas.

realizarAtaques(jugadores referencia a vector de Jugador, territorios referencia a vector de Territorio, identificador del jugador actual):
- Función que interactua con el usuario para atacar territorios vecinos y conquistarlos, con la comparación de dados y el establecimiento de las unidades perdidas si se conquista o no la región.
