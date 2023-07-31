# ProyectoEstructuraDatos_R.I.S.K

## RISK IN C++

## Español:

El presente documento muestra el uso y compilado del programa en C++ para el juego RISK.
Este programa esta vasado con c++ v.11

# Compilacion del programa
### Windows
Si desea realizar la compilacion por Windows, debe de tener instalado el *minGW* en su sistema.
1.  Si esta seguro de que cuneta con este, puede entrar el *cmd* y escribir el siguiente comando:
```sh
g++ --version
```
2.   Despues de comprobar de que si tiene *minGW* instalado correctamente, podemos iniciar con la compilacion del programa.
Debemos de saber en que carpeta se encutra nuestro programa pues debemos de acceder a ella  con el siguiente comando en la *terminal* *(cmd)*
```sh
cd nombre_carpeta_contenedora_del_programa\ProyectoEstructuraDatos_R.I.S.K
```
3. Despues de ingresar debidamente a la carpeta contenedora del proyecto debemos de ingresar a la carpeta contenedora del `main.cpp`, en esto usamos el mismo comando anterior:
```sh
cd Game
```
o en su caso podemos de una ingresar a la carpeta contenedora del programa `main()` 
```sh
cd cd nombre_carpeta_contenedora_del_proyecto\ProyectoEstructuraDatos_R.I.S.K\Game
```

4. Estando en la carpeta contenedora el `main.cpp` podemos hacer la compilacion del peoyecto, con el siguiete comando:
```sh
g++ -std=c++11 -o ejecutable main.cpp risk.cxx
```
Este comando realiza la compilacion de un porgarama escrito en c++ utilizado el compilador `g++`, `std=c++11`: Es una bandera o opcion que se le pasa al compilador para especificar el estadar de c++ que se va a utilizar, `-o ejecutbale`: Es otra bandera que indica el nombre que se le dara al archivo ejecutable resultante. En este caso se le asigno el nombre de `ejecutable` cabe destacar que se le puede asignar el nombre que se desee, `main.cpp`: Es el nombre del archivo que contiene la funcion `main()`, que es el punto de entrada del programa, `risk.cxx`: Es el nomnbre del archivo que contiene las definiciones de las funciones relacionadas con el juego RISK

En resumen este comando compila los archivos "main.cpp" y "risk.cxx" utilizando el compilador de g++ y produce un archivo ejecutable con el nombre establecido. Si la compilacion es exitosa, se podra ejecutar el programa utilizadno el siguiente comando introducido al `cmd`:
En caso de ejecutar los comandos sin ningun cambio, puede aplicar el siguiente para correr el programa.
```sh
./ejecutable
```

## Ingles:

The present document shows the use and compilation of the program in c++ for the game RISK.

### Program compilation
### Windos
If you want to compile for windows, yo must have *minGW* intalled on your system.
1. if you are sure you have it, you cant enter *cmd* and type the following command:
```sh
g++ --version
```
2. After checking if you hace *mingGW* intalled correctly, you can start compiling the program.
We must knok in whitch folder our program is located because we must access to it whit the followin comand in the *terminal* *(cmd)*.
```sh
cd project_folder_containing\ProyectoEstructuraDatos_R.I.S.K
```
3. After entering properly to the folder containing the project we must enter to the folder containing the `main.cpp`, in this we use the same command above:
```sh
cd Game
```
Or in your case we can enter the folder containing the `main()` program. 
```sh
cd project_folder_containing\ProyectoEstructuraDatos_R.I.S.K\Game
```
4. Once the `main.cpp` is in the folder containing the `main.cpp` we can compile the project, with the following command:
```sh
g++ -std=c++11 -o executable main.cpp risk.cxx
```
This command performs the compilation of a program written in c++ using the `g++` compiler, `std=c++11`: Is a flag or option that is passed to the compiler to specify the c++ standard to be used, `-o ejecutbale`: Is another flag that indicates the name that will be given to the resulting executable file. In this case it was assigned the name `ejecutable`, it should be noted that it can be assigned any name you want, `main.cpp`: Is the name of the file containing the `main()` function, which is the entry point of the program, `risk.cxx`: Is the name of the file containing the definitions of the functions related to the RISK game.

In summary this command compiles the files "main.cpp" and "risk.cxx" using the g++ compiler and produces an executable file with the set name. If the compilation is successful, the program can be executed using the following command entered into `cmd`:
In case you execute the commands without any changes, you can apply the following to run the program.
```sh
./executable
```