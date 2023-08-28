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
Este comando realiza la compilación de un programa escrito en c++ utilizado el compilador `g++`, `std=c++11`: Es una bandera o opcion que se le pasa al compilador para especificar el estandar de c++ que se va a utilizar, `-o *nombreArchivo*`: Es otra bandera que indica el nombre que se le asignara al archivo ejecutable resultante. Cabe destacar que se le puede asignar el nombre que se desee, `main.cpp`: Es el nombre del archivo que contiene la función `main()`, que es el punto de entrada del programa, `risk.cxx`: Es el nombre del archivo que contiene las definiciones de las funciones relacionadas con el juego RISK

En resumen este comando compila los archivos "**main.cpp**" y "**risk.cxx**" utilizando el compilador de g++ y produce un archivo ejecutable con el nombre establecido. Si la compilación es exitosa, se podra ejecutar el programa utilizando el siguiente comando introducido al `cmd`:
En caso de ejecutar los comandos sin ningún cambio, puede aplicar el siguiente para correr el programa.
```sh
.\ejecutable.exe
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
Esto compilara el programa y generara un archivo llamado `"ejecutable"`.

5. Ya estando compilado se puede ejecutar escribiendo:
```sh
./ejecutable
```

