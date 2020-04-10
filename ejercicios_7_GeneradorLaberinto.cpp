#include <iostream>
#include <iomanip>
#include <array>
#include <random>
#include <stdlib.h>
using namespace std;

static int caminos = 0;
static int X = 1;
static int Y = 0;

int generarEntradas(array<array<char, 24>,24> &);
int generarCaminos(array<array<char, 24>,24> &, int, int);
int numeroAleatorio(int, int);
int positivoNegativo();
void imprimirLaberinto(array<array<char, 24>,24> &);
int generarPared(array<array<char, 24>, 24> &);

int main() {
    // ====================================== INICIAR LABERINTO ======================================
    const int size_filas = 24;
    const int size_colum = 24;
    array<array<char, size_filas>, size_colum> laberinto = {"#"};

    for (int i = 0; i < 24; i++){
        for (int j = 0; j < 24; j++){
            laberinto[i][j] = 32;
            cout<<setw(2)<<laberinto[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
    ::Y = generarEntradas(laberinto); // Genera la entrada y salida del laberinto.
    // ====================================== LLAMADA A FUNCION ======================================
    generarCaminos(laberinto, ::Y, ::X);
    imprimirLaberinto(laberinto);
   return 0;
}

int generarCaminos(array<array<char, 24>,24> &laberinto, int Y, int X){ // Genera los caminos del laberinto.
    /*  . == 250
        # == 35
        S == 83   */
    int camino = 0;
    if (laberinto[Y][X] == 'S'){
        cout<<"El programa llego a la salida."<<endl;
        system("pause");
        return 7; // Si llega a su objetivo (S) retorna una lista de valores.
    }

    if (laberinto[Y][X] == 'O'){
        return 1; // Termina la recursividad. (Al ser un arbol, hay muchos caminos recursivos paralelos)
    }
    system ("CLS");
    laberinto[Y][X] = 42; // Hace la funcion de escavar.

    imprimirLaberinto(laberinto);

    if ((Y > 0) && (laberinto[Y-1][X] == ' ' || laberinto[Y-1][X] == 'S')){         // Norte
        cout<<"A\n\t\t|"<<endl<<endl;
        cout<<"Laberintos generados proceduralmente (al azar) mediante numeros pseudoaleatorios.\n"
              "Si el laberinto da vuelta a la derecha, siga la pared a su derecha.\n"
              "Mientras no quite su mano de la pared, finalmente llegará a la salida del laberinto.\n";
        camino = generarCaminos(laberinto, Y-1, X);
        if (camino){return generarCaminos(laberinto, Y-1, X);}
    }
    if ((X < 23) && (laberinto[Y][X + 1] == ' ' || laberinto[Y][X + 1] == 'S')){// Este
        cout<<"->"<<endl<<endl;
        cout<<"Laberintos generados proceduralmente (al azar) mediante numeros pseudoaleatorios.\n"
              "Si el laberinto da vuelta a la derecha, siga la pared a su derecha.\n"
              "Mientras no quite su mano de la pared, finalmente llegará a la salida del laberinto.\n";
        camino = generarCaminos(laberinto, Y, X+1);
        if (camino){return generarCaminos(laberinto, ::Y, ::X+1);}
    }
    if ((Y < 23) && (laberinto[Y+1][X] == ' ' || laberinto[Y+1][X] == 'S')){   // Sur
        cout<<"|\n\t\tV"<<endl<<endl;
        cout<<"Laberintos generados proceduralmente (al azar) mediante numeros pseudoaleatorios.\n"
              "Si el laberinto da vuelta a la derecha, siga la pared a su derecha.\n"
              "Mientras no quite su mano de la pared, finalmente llegará a la salida del laberinto.\n";
        camino = generarCaminos(laberinto, Y+1, X);
        if (camino){return generarCaminos(laberinto, Y+1, X);}
    }
    if ((Y > 0) && (laberinto[Y][X-1] == ' ' || laberinto[Y-1][X] == 'S')){         // Oeste
        cout<<"<-"<<endl<<endl;
        cout<<"Laberintos generados proceduralmente (al azar) mediante numeros pseudoaleatorios.\n"
              "Si el laberinto da vuelta a la derecha, siga la pared a su derecha.\n"
              "Mientras no quite su mano de la pared, finalmente llegará a la salida del laberinto.\n";
        camino = generarCaminos(laberinto, Y, X-1);
        if (camino){return generarCaminos(laberinto, Y, X-1);}
    }

    return 1;
    //return generarCaminos(laberinto, ::Y, ::X);
}

int generarPared(array<array<char, 24>, 24> &laberinto){
    int obstaculos_y = numeroAleatorio(1,23);
    int obstaculos_x = numeroAleatorio(1,23);
    if (obstaculos_x % 2 != 0 && obstaculos_y % 2 != 0){
        int pared_size = numeroAleatorio(1,9);
        int orientacion = positivoNegativo();
        for (unsigned int i = 1; i < pared_size; i++){
            if (orientacion == 1){
                laberinto[obstaculos_y][obstaculos_x+i] = 'O';
            }else{
                laberinto[obstaculos_y+i][obstaculos_x] = 'O';
            }
        }
        return 7;
    }
}

int generarEntradas(array<array<char, 24>, 24> &laberinto){ // Marca la entrada y salida del laberinto.
    int entrada = numeroAleatorio(1,23);
    int salida = 23 - entrada;
    int cantidad_paredes = 0;
    int comprobacion = 7;
    while (cantidad_paredes < 48){
        comprobacion = generarPared(laberinto);
        if (comprobacion == 7){
            cantidad_paredes++;
        }
    }
    laberinto[entrada][0] = 42;
    laberinto[entrada][1] = 42;

    laberinto[salida][23] = 83;
    return entrada;
}

int numeroAleatorio(int INICIO, int FINAL){ // Genera un numero aleatorio.
    static int mult = 57;
    mult *= 13;
    default_random_engine motor (static_cast<unsigned int>(time(0)*mult));
    uniform_int_distribution<unsigned int> intAleatorio(INICIO,FINAL);
    return intAleatorio(motor);
}

int positivoNegativo(){
    static int mult = 57;
    mult *= 13;
    default_random_engine motor (static_cast<unsigned int>(time(0)*mult));
    uniform_int_distribution<unsigned int> intAleatorio(1,2);
    switch(intAleatorio(motor)){
        case 1:
            return 1;
            break;
        case 2:
            return 2;
            break;
        default:
            cout<<"No deberia llegar aqui."<<endl;
            break;
    }
}
void imprimirLaberinto(array<array<char, 24>, 24> &laberinto){
    cout<<" ============== Recursive Backtracking Labyrinth | By:  cyberian_husky_ ============== "<<endl;
    for (int i = 0; i < 24; i++){
        cout<<" |                 |";
        for (int j = 0; j < 24; j++){
            cout<<setw(2)<<laberinto[i][j];
        }
        cout<<"|                | "<<endl;
    }
    cout<<" ===================================================================================== "<<endl;
    static int pasos = 0;
    pasos++;
    cout<<"Pasos: "<<pasos<<"\t";
}
