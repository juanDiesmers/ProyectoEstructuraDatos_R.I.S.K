## English:

The present document shows the use and compilation of the program in c++ for the game RISK.

[command list](https://github.com/juanDiesmers/ProyectoEstructuraDatos_R.I.S.K/blob/NewFuncion/DOC/Documentation%20English/Releases%20English/v.00.md)

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