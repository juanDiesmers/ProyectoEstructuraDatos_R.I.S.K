# ProyectoEstructuraDatos_R.I.S.K

## RISK IN C++

[Click here to visit the Wiki and meet the members ](https://github.com/juanDiesmers/ProyectoEstructuraDatos_R.I.S.K/wiki)

[If you want to read the documentation in English](https://github.com/juanDiesmers/ProyectoEstructuraDatos_R.I.S.K/blob/NewFuncion/DOC/Documentation%20English/Readme_English.md)

[Si quieres saber de las versiones del programa y que se puede hacer en cada una](https://github.com/juanDiesmers/ProyectoEstructuraDatos_R.I.S.K/blob/NewFuncion/DOC/Releases%20Español/v.00.md)

## Español:

El presente documento muestra el uso y compilado del programa en C++ para el juego RISK.
Este programa esta basado con c++ v.11

# compilación del programa
### Windows
Si desea realizar la compilación por Windows, debe de tener instalado el **minGW** en su sistema.
1.  Si esta seguro de que cuneta con este, puede entrar el **cmd** y escribir el siguiente comando:
```sh
g++ --version
```
2.   Después de comprobar de que si tiene **minGW** instalado correctamente, podemos iniciar con la compilación del programa.
Debemos de saber en qué carpeta se encuentra nuestro programa pues debemos de acceder a ella con el siguiente comando en la **terminal** **(cmd)**
```sh
cd *nombre_carpeta_contenedora_del_programa*\ProyectoEstructuraDatos_R.I.S.K
```
3. Después de ingresar debidamente a la carpeta contenedora del proyecto debemos de ingresar a la carpeta contenedora del `main.cpp`, en esto usamos el mismo comando anterior:
```sh
cd nombre_carpeta_contenedora_del_proyecto\ProyectoEstructuraDatos_R.I.S.K\src
```
4. Estando en la carpeta contenedora el `main.cpp` podemos hacer la compilación del proyecto, con el siguiente comando:
```sh
g++ -std=c++11 -o *nombre* main.cpp risk.cxx Turno/turno.cxx Turno/funcionesTurno.cxx asignacion/asignacion.cxx
```
g++: Este comando invoca el compilador de C++ (GNU Compiler Collection para C++) para compilar el código fuente.
-std=c++11: Esta opción le indica al compilador que utilice el estándar de C++11 durante la compilación. C++11 es una versión específica del lenguaje C++ con características y mejoras adicionales.
-o nombre_del_ejecutable: Esta opción establece el nombre del archivo ejecutable resultante después de la compilación. Reemplaza nombre_del_ejecutable con el nombre que deseas darle al archivo ejecutable.
main.cpp: Es el nombre del archivo fuente que contiene la función main(). Esta función es el punto de entrada de cualquier programa en C++.
risk.cxx: Es el nombre del archivo fuente que contiene las definiciones de las funciones relacionadas con el juego Risk. Estas funciones deben ser definidas y utilizadas en tu programa.
Turno/turno.cxx y Turno/funcionesTurno.cxx: Son los nombres de los archivos fuente que contienen las definiciones y funciones relacionadas con la gestión de los turnos en el juego.
asignacion/asignacion.cxx: Es el nombre del archivo fuente que contiene las definiciones y funciones relacionadas con la asignación de territorios a los jugadores.
```sh
.\*nombreEjecutable*.exe
```
### Linux
1. Debe de clonar el repositorio con el uso de `git clone`:
desde la terminal de **linux** ingresamos a la carpeta la cual queremos clonar:
```sh
cd *rutaDescarga*
```
2. Pasamos a clonar nuestro repositorio a la carpeta seleccionada
```sh
git clone https://github.com/juanDiesmers/ProyectoEstructuraDatos_R.I.S.K.git
```
3. Una vez clonado el repositorio, ingresamos al directorio del proyecto **"src"** usando el comando `cd`.
```sh
cd ProyectoEstructuraDatos_R.I.S.K/src
```
#### Compilacion 

4. Ya estando en directorio `Game` procedemos a la compilación mediante **g++**.
```sh
g++ -std=c++11 -o *nombre* main.cpp risk.cxx Turno/turno.cxx Turno/funcionesTurno.cxx asignacion/asignacion.cxx
```
Esto compilara el programa y creara un archivo ejecuatable con el nombre que se le haya asignado *nombre* 

5. Ya estando compilado se puede ejecutar escribiendo:
```sh
./*nombreEjecutable*
```