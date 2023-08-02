# ProyectoEstructuraDatos_R.I.S.K

## RISK IN C++

[Click here to visit the Wiki and meet the members ](https://github.com/juanDiesmers/ProyectoEstructuraDatos_R.I.S.K/wiki)

## Español:

El presente documento muestra el uso y compilado del programa en C++ para el juego RISK.
Este programa esta vasado con c++ v.11

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
cd nombre_carpeta_contenedora_del_programa\ProyectoEstructuraDatos_R.I.S.K
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
g++ -std=c++11 -o ejecutable main.cpp risk.cxx
```
Este comando realiza la compilacion de un porgarama escrito en c++ utilizado el compilador `g++`, `std=c++11`: Es una bandera o opcion que se le pasa al compilador para especificar el estadar de c++ que se va a utilizar, `-o ejecutbale`: Es otra bandera que indica el nombre que se le dara al archivo ejecutable resultante. En este caso se le asigno el nombre de `ejecutable` cabe destacar que se le puede asignar el nombre que se desee, `main.cpp`: Es el nombre del archivo que contiene la funcion `main()`, que es el punto de entrada del programa, `risk.cxx`: Es el nomnbre del archivo que contiene las definiciones de las funciones relacionadas con el juego RISK

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

## Ingles:

The present document shows the use and compilation of the program in c++ for the game RISK.

### Program compilation
### Windows
If you want to compile for windows, yo must have **minGW** intalled on your system.
1. if you are sure you have it, you cant enter **cmd** and type the following command:
```sh
g++ --version
```
2. After checking if you hace *mingGW* intalled correctly, you can start compiling the program.
We must knok in whitch folder our program is located because we must access to it whit the followin comand in the **terminal** **(cmd)**.
```sh
cd project_folder_containing\ProyectoEstructuraDatos_R.I.S.K
```
3. After entering properly to the folder containing the project we must enter to the folder containing the `main.cpp`, in this we use the same command above:
```sh
cd Game
```
or we can directly enter the folder containing the `main()` program if we do not want to do it separately.
```sh
cd project_folder_containing\ProyectoEstructuraDatos_R.I.S.K\Game
```
4. Once the `main.cpp` is in the folder containing the `main.cpp` we can compile the project, with the following command:
```sh
g++ -std=c++11 -o executable main.cpp risk.cxx
```
This command performs the compilation of a program written in c++ using the `g++` compiler, `std=c++11`: Is a flag or option that is passed to the compiler to specify the c++ standard to be used, `-o executable`: Is another flag that indicates the name that will be given to the resulting executable file. In this case it was assigned the name `executable`, it should be noted that it can be assigned any name you want, `main.cpp`: Is the name of the file containing the `main()` function, which is the entry point of the program, `risk.cxx`: Is the name of the file containing the definitions of the functions related to the RISK game.

In summary this command compiles the files "**main.cpp**" and "**risk.cxx**" using the g++ compiler and produces an executable file with the set name. If the compilation is successful, the program can be executed using the following command entered into `cmd`:
In case you execute the commands without any changes, you can apply the following to run the program.
```sh
.\ejecutable.exe
```
### Linux
1. You must clone the repository using `git clone`:
from the **linux** terminal enter the folder you want to clone:
```sh
cd *downloadPath
```
2. We clone our repository to the selected folder
```sh
git clone https://github.com/juanDiesmers/ProyectoEstructuraDatos_R.I.S.K.git
```
3. Once the repository has been cloned, we enter the **"Game "** project directory using the `cd` command.
```sh
cd ProyectoEstructuraDatos_R.I.S.K\Game
```
#### Compile 

4. Once in the `Game` directory we proceed to the compilation using **g++**.
```sh
g++ -std=c++11 -o executable main.cpp risk.cxx
```
This will compile the program and generate a file called ``executable``.

5. Once compiled you can run it by typing:
```sh
./executable
```


## Comandos del programa
Los siguientes comandos pueden ser ingresados de forma comleta ya sea `ayuda` o `a`.
```sh
ayuda
```
```sh
a
```
Este comado genera todos los comandos disponibles para usar en el juego.
1. InicializarJuego
```sh
inicializarJuego
```
```sh
i
```
Este comando tiene la fnuncion para iniciar el juego.

2. TurnoJugador
```sh
turnoJugador
```
```sh
tj
```
El jugador toma opciones con su turno.

3. Salir
```sh
salir
```
```sh
s
```
Comando para salir del juego sin guardar.

4. GuardarPartida
```sh
guardarPartida
```
```sh
gp
```
Comando para realizar un guardado normal del juego.

5. GuardarPartidaComprimida
```sh
guardarPartidaComprimida
```
```sh
gpc
```
Comando para guardar la partida en formato comprimida utilizando Codificación de Huffman.

6. Inicializar
```sh
inicializar
```
```sh
ip
```
Comando para inicializar un partida guardada.

7. ConstoConquista
```sh
constoConquista
```
```sh
cc
```
Comando para verificar el costo de conquista de otro territorio nombrado.

8. ConquistaMasBarata
```sh
conquistaMasBarata
```
```sh
cmb
```
Comando que muestra el territorio que puede ser conquistado con el menor costo. 







