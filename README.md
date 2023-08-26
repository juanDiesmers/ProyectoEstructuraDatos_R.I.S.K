# ProyectoEstructuraDatos_R.I.S.K

## RISK IN C++

[Click here to visit the Wiki and meet the members ](https://github.com/juanDiesmers/ProyectoEstructuraDatos_R.I.S.K/wiki)

[If you want to read the documentation in English](https://github.com/juanDiesmers/ProyectoEstructuraDatos_R.I.S.K/blob/NewFuncion/DOC/Documentation%20English/Readme_English.md)

[Si quiers saber de las versiones del programa y que se puede hacer en cada una](https://github.com/juanDiesmers/ProyectoEstructuraDatos_R.I.S.K/blob/NewFuncion/DOC/Releases%20Español/v.00.md)

## Español:

El presente documento muestra el uso y compilado del programa en C++ para el juego RISK.
Este programa esta basado con c++ v.11

# Compilacion del programa
### Windows
Si desea realizar la compilacion por Windows, debe de tener instalado el **minGW** en su sistema.
1.  Si esta seguro de que cuneta con este, puede entrar el **cmd** y escribir el siguiente comando:
```sh
g++ --version
```
2.   Despues de comprobar de que si tiene **minGW** instalado correctamente, podemos iniciar con la compilacion del programa.
Debemos de saber en que carpeta se encutra nuestro programa pues debemos de acceder a ella  con el siguiente comando en la **terminal** **(cmd)**
```sh
cd *nombre_carpeta_contenedora_del_programa*\ProyectoEstructuraDatos_R.I.S.K
```
3. Despues de ingresar debidamente a la carpeta contenedora del proyecto debemos de ingresar a la carpeta contenedora del `main.cpp`, en esto usamos el mismo comando anterior:
```sh
cd Game
```
o en su caso podemos de una ingresar directamente a la carpeta contenedora del programa `main()` sin no queremos hacerlo por separado
```sh
cd nombre_carpeta_contenedora_del_proyecto\ProyectoEstructuraDatos_R.I.S.K\Game
```

4. Estando en la carpeta contenedora el `main.cpp` podemos hacer la compilacion del peoyecto, con el siguiete comando:
```sh
g++ -std=c++11 -o *nombreArchivo* main.cpp risk.cxx
```
Este comando realiza la compilacion de un porgarama escrito en c++ utilizado el compilador `g++`, `std=c++11`: Es una bandera o opcion que se le pasa al compilador para especificar el estadar de c++ que se va a utilizar, `-o *nombreArchivo*`: Es otra bandera que indica el nombre que se le dara al archivo ejecutable resultante. Cabe destacar que se le puede asignar el nombre que se desee, `main.cpp`: Es el nombre del archivo que contiene la funcion `main()`, que es el punto de entrada del programa, `risk.cxx`: Es el nomnbre del archivo que contiene las definiciones de las funciones relacionadas con el juego RISK

En resumen este comando compila los archivos "**main.cpp**" y "**risk.cxx**" utilizando el compilador de g++ y produce un archivo ejecutable con el nombre establecido. Si la compilacion es exitosa, se podra ejecutar el programa utilizadno el siguiente comando introducido al `cmd`:
En caso de ejecutar los comandos sin ningun cambio, puede aplicar el siguiente para correr el programa.
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
3. Una vez clonado el repositorio, ingresamos al directorio del proyecto **"Game"** usando el comando `cd`.
```sh
cd ProyectoEstructuraDatos_R.I.S.K/Game
```
#### Compilacion 

4. Ya estando en directorio `Game` procedemos a la compilacion mediante **g++**.
```sh
g++ -std=c++11 -o ejecutable main.cpp risk.cxx
```
Esto compilara el programa y generara un archivo llamado `"ejecutbale"`.

5. Ya estando compilado se puede ejecutar escribiendo:
```sh
./ejecutable
```