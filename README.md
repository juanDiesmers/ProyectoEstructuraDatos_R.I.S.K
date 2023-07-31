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

4. Estando en la carpeta contenedora el `main.cpp` podemos hacer la compilacion del peoyecto, con el siguiete comando:
```sh
g++ -std=c++11 -o ejecutable main.cpp risk.cxx
```


## Ingles:

The present document shows the use and compilation of the program in c++ for the game RISK.
