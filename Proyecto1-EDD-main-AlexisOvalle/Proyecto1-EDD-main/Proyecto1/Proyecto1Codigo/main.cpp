#include <iostream>
#include <string>
#include <ctime>
#include <stdlib.h>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <chrono>
#include <fstream>
#include "persona.h"
#include "partida.h"
using namespace std;
// VARIABLES GLOBALES
chrono::steady_clock sc; // Para determinar el tiempo de ejecucion
// simon
int cantidadMovimientos = 0;

personas1 *personasArregloFinal;
std::vector<personas1> personasArrayFinal;
std::vector<Partida> partidasArreglo;

// Para matriz
string **punteroMatriz;

// matriz base
string **matrixOriginal;


int *elementos, nElementos;
int numeroFilas, numeroColumnas;

void SetAll(std::string nombre, int cantidadPunteo, int pasosTotales, double tiempoPartida)
{
}

void ToString() {}

void ingresoNombre()
{
    string nombre;
    cout << "ingrese su nombre de usuario" << endl;
    cin >> nombre;
}

//-------------------PARA JUGAR---------------------------------------------------------



// INGRESO DE USUARIOS
// metodo para el ingreso de usuarios
void ingresarUsuarios()
{
    cout << "-----Ingrese el nombre de usuario-------\n";
    string nombre;
    cin >> nombre;
    bool nombreIngresadoPrevio = false;
    // personasArregloFinal = new personas1[cantidadArreglo+1];
    for (size_t i = 0; i < personasArrayFinal.size(); i++)
    {
        if (nombre == personasArrayFinal[i].getNombre())
        {
            nombreIngresadoPrevio = true;
            break;
        }
    }
    if (!nombreIngresadoPrevio)
    {
        personas1 personaTempo(nombre);
        personasArrayFinal.push_back(personaTempo);

        cout << "se ha ingreso a " << nombre << " exitosamente" << endl;
    }
}
// vista para los jugadores
// Metodo para la muestra de jugadores
void mostrarJugadores()
{
    cout << "-----Usuarios ingresasos-------\n";
    for (size_t i = 0; i < personasArrayFinal.size(); i++)
    {
        cout << " " << i << " " << personasArrayFinal[i].getNombre() << endl;
    }
}
// Menu para los usuarios
void generacionUsuario()
{
    int seleccion;
    do
    {
        std::cout << "Para comenzar el juego debe se seleccionar su usario o crear uno\n";
        std::cout << "1. Crear Usuario" << std::endl
                  << " 2. Ver usuarios" << std::endl
                  << " 3. Regresar\n";
        std::cin >> seleccion;
        switch (seleccion)
        {
        case 1:
            ingresarUsuarios();
            break;
        case 2:
            // Ver Reportes
            mostrarJugadores();
            break;
        case 3:
            // FIn juego
            cout << "Regresando al menu de juego" << endl;
            break;
        default:
            // presiona algo mas
            cout << "No existe esta opcion" << endl;
            break;
        }
    } while (seleccion != 3);
}

// return numero del usuario

// METODOS Y FUNCIONALIDES DEL JUEGO
// movimientos con las teclas
enum EMove
{
    keUp = 'w',
    keDown = 's',
    keLeft = 'a',
    keRight = 'd',
    terminateGame = 'x'
};

void InitializeBoard(string[4][4]);
void PrintBoard(string[4][4]);
void LocateSpace(int &, int &, string[4][4]);
void Randomize(string[4][4]);
void movimiento(string[4][4], const EMove);

void ingresoManual();
void aleatorio(string **);
void moverEspacios(string **, const EMove);

// Metodo que inicia con el tablero basico
void InitializeBoard(string caaBoard[4][4])
{
    const string kcaaInitial[4][4] = {
        {"1", "2", "3", "4"},
        {"5", "6", "7", "8"},
        {"9", "10", "11", "12"},
        {"13", "14", "15", "X"}};
    for (int iRow = 0; iRow < 4; ++iRow)
    {

        for (int iCol = 0; iCol < 4; ++iCol)
        {
            caaBoard[iRow][iCol] = kcaaInitial[iRow][iCol];
        }
    }
}
///-----------------------------INGRESO MANUAL
// Metodo que determina un ordenamiento del arreglo
void ordenamiento(string **arreglo, int *array)
{
   
    int contadorOrden =1;
    for (size_t i = 0; i < numeroFilas; i++)
    {
        for (size_t j = 0; j < numeroColumnas; j++)
        {
            if (numeroColumnas-1 == j && numeroFilas-1 == i) 
            {
            arreglo[numeroFilas-1][numeroColumnas-1] = "X";
                
            } else {
                arreglo[i][j] = to_string(array[contadorOrden]);
                contadorOrden++;
            }

        }
        
    }

    
}
// Determina la cantidad de puntos del aleatorio
int comprobarGanadorDinamico(string **arreglo, string **arreglo2)
{
    int cantidadPuntos = 0;
    for (size_t i = 0; i < numeroFilas; i++)
    {
        for (size_t j = 0; j < numeroColumnas; j++)
        {
            if (arreglo[i][j] == arreglo2[i][j])
            {
                cantidadPuntos = cantidadPuntos + 2;
            }
        }
    }
    return cantidadPuntos;
}


//METODO DE INGRESO DE DATOS MANUAL
void ingresoManual()
{
    cout << "INgrese la cantidad de numeros que tendra el juego";
    cin >> numeroFilas;
    cout << "Ingrese la cantidad de columnas";
    cin >> numeroColumnas;

    int cantidadTablero = numeroFilas * numeroColumnas;

    nElementos = cantidadTablero;
    elementos = new int[nElementos];
    int contador=0;


    punteroMatriz = new string *[numeroFilas];
    matrixOriginal = new string *[numeroFilas];
    for (size_t i = 0; i < numeroFilas; i++)
    {
        punteroMatriz[i] = new string[numeroColumnas];
        matrixOriginal[i] = new string[numeroColumnas];
    }
    // INGRESANDO ELEMENTOS A LA MATRIZ
    for (size_t i = 0; i < numeroFilas; i++)
    {
        for (size_t j = 0; j < numeroColumnas; j++)
        {
            if (j == numeroColumnas - 1 && i == numeroFilas - 1)
            {
                punteroMatriz[i][j] = "X";
                matrixOriginal[i][j] = "X";
                elementos[contador] = 0;

                break;
            }
            else
            {
                cout << "Ingrese el numero en la posicion: " << i + 1 << "--" << j + 1 << "de la matriz";
                int numero;


                cin >> punteroMatriz[i][j];

                elementos[contador] = stoi(punteroMatriz[i][j]);
                contador++;
                matrixOriginal[i][j] = punteroMatriz[i][j];
                //  arregloOrden[contador] = numero;
                // contador++;
            }
        }
    }
}
// Metodo que imprime la matriz dinamica
void imprimir(string **punteroMatriz)
{

    for (size_t i = 0; i < numeroFilas; i++)
    {
        cout << "\n-------------------------" << endl;

        for (size_t j = 0; j < numeroColumnas; j++)
        {
            cout << "| " << punteroMatriz[i][j] << " |";
        }
        cout << "\n";
    }
}

// Metodo que imprime la matriz basica
void PrintBoard(string caaBoard[4][4])
{
    using namespace std;
    for (int iRow = 0; iRow < 4; ++iRow)
    {
        cout << "\n-------------------------" << endl;
        for (int iCol = 0; iCol < 4; ++iCol)
        {
            cout << "| " << caaBoard[iRow][iCol] << " |";
        }
        cout << endl;
    }
}

// Metodo que determina el movimiento del pivote X en matriz estatica
void determinarEspacio(int &fila, int &columna, string **matriz)
{
    for (size_t i = 0; i < numeroFilas; i++)
    {
        for (size_t j = 0; j < numeroColumnas; j++)
        {
            if (matriz[i][j] == "X")
            {
                fila = i;
                columna = j;
            }
        }
    }
}
// Meetodo que determina la posicion de nuestro pivote X, en matriz basica
void LocateSpace(int &irRow, int &irCol, string caaBoard[4][4])
{
    for (int iRow = 0; iRow < 4; ++iRow)
    {
        for (int iCol = 0; iCol < 4; ++iCol)
        {
            if (caaBoard[iRow][iCol] == "X")
            {
                irRow = iRow;
                irCol = iCol;
            }
        }
    }
}

// Metood de movimiento en matriz dinamica
void moverEspacios(string **matriz, const EMove keMove)
{
    int iRowSpace;
    int iColSpace;

    determinarEspacio(iRowSpace, iColSpace, matriz);
    int iRowMove(iRowSpace);
    int iColMove(iColSpace);

    switch (keMove)
    {
    case keDown:
    {
        iRowMove = iRowSpace + 1;
        cantidadMovimientos++;
        break;
    }
    case keUp:
    {
        iRowMove = iRowSpace - 1;
        cantidadMovimientos++;
        break;
    }
    case keRight:
    {
        iColMove = iColSpace + 1;
        cantidadMovimientos++;
        break;
    }
    case keLeft:
    {
        iColMove = iColSpace - 1;
        cantidadMovimientos++;
        break;
    }
    }
    // Make sure that the square to be moved is in bounds
    if (iRowMove >= 0 && iRowMove < numeroFilas && iColMove >= 0 && iColMove < numeroColumnas)
    {
        matriz[iRowSpace][iColSpace] = matriz[iRowMove][iColMove];
        matriz[iRowMove][iColMove] = "X";
    }
}
// Metodo Aleatorio en matriz basica
void Randomize(string caaBoard[4][4])
{
    using namespace std;
    srand((unsigned int)time(0));
    for (int iIndex = 0; iIndex < 1000000; ++iIndex)
    {
        const int kiNextMove = (rand() % 4);
        switch (kiNextMove)
        {
        case 0:
        {
            movimiento(caaBoard, keUp);
            break;
        }
        case 1:
        {
            movimiento(caaBoard, keDown);
            break;
        }
        case 2:
        {
            movimiento(caaBoard, keLeft);
            break;
        }
        case 3:
        {
            movimiento(caaBoard, keRight);
            break;
        }
        }
    }
}
// Metodo de movimiento en matriz basica
void movimiento(string caaBoard[4][4], const EMove keMove)
{
    int iRowSpace;
    int iColSpace;
    LocateSpace(iRowSpace, iColSpace, caaBoard);
    int iRowMove(iRowSpace);
    int iColMove(iColSpace);
    switch (keMove)
    {
    case keDown:
    {
        iRowMove = iRowSpace + 1;
        cantidadMovimientos++;
        break;
    }
    case keUp:
    {
        iRowMove = iRowSpace - 1;
        cantidadMovimientos++;
        break;
    }
    case keRight:
    {
        iColMove = iColSpace + 1;
        cantidadMovimientos++;
        break;
    }
    case keLeft:
    {
        iColMove = iColSpace - 1;
        cantidadMovimientos++;
        break;
    }
    }
    // Make sure that the square to be moved is in bounds
    if (iRowMove >= 0 && iRowMove < 4 && iColMove >= 0 && iColMove < 4)
    {
        caaBoard[iRowSpace][iColSpace] = caaBoard[iRowMove][iColMove];
        caaBoard[iRowMove][iColMove] = "X";
    }
}
// Metodo para determinar el puntaje de la matriz Basica
int comprobarPuntaje(string caaBoard[4][4])
{
    int cantidadPuntos = 0;
    const string matriz[4][4] = {
        {"1", "2", "3", "4"},
        {"5", "6", "7", "8"},
        {"9", "10", "11", "12"},
        {"13", "14", "15", "X"}};

    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            if ((caaBoard[i][j] == (matriz[i][j])))
            {
                cantidadPuntos = cantidadPuntos + 2;
            }
        }
    }
    return cantidadPuntos;
}

// Metodo para la impresion de la matriz basica
void imprimirMatriz(string matriz[4][4])
{
    for (size_t i = 0; i < 4; i++)
    {
        for (size_t j = 0; j < 4; j++)
        {
            cout << matriz[i][j];
        }
    }
}

// Metodo para genenrar el orden aleatorio en la matriz dinamica
void shufelingMatrix(string **matriz)
{
    int rowindex = rand() % numeroFilas;
    int colindex = rand() % numeroColumnas;
    string auxiliar;
    for (size_t i = 0; i < numeroFilas; i++)
    {

        for (size_t j = 0; j < numeroColumnas; j++)
        {
            auxiliar = matriz[i][j];
            matriz[i][j] = matriz[rowindex][colindex];
            matriz[rowindex][colindex] = auxiliar;
        }
    }
}


void ordenarNumeros(int *elemento,int nElementos){
        int aux;

        //Ordenamiento por metodo burbuja con punteros
        for(int i=0;i<nElementos;i++){
                for(int j=0;j<nElementos-1;j++){
                        if(*(elemento+j) > *(elemento+j+1)){
                                aux = *(elemento+j);
                                *(elemento+j) = *(elemento+j+1);
                                *(elemento+j+1) = aux;
                        }
                }
        }
}

void mostrarArregloOrdenado(int *elemento,int nElementos){//Mostrando Arreglo ordenado
        cout<<"\n\nMostrando Arreglo Ordenado: ";
        for(int i=0;i<nElementos;i++){
                cout<<*(elemento+i)<<" ";
        }
}


void ingresoAleatorioNumeros()
{
    cout << "INgrese la cantidad de Filas";
    cin >> numeroFilas;
    cout << "Ingrese la cantidad de columnas";
    cin >> numeroColumnas;
    int cantidadTablero = (numeroFilas * numeroColumnas);

    nElementos = cantidadTablero;
    elementos = new int[nElementos];

    punteroMatriz = new string *[numeroFilas];
    matrixOriginal = new string *[numeroFilas];

    int contador=0;
    for (size_t i = 0; i < numeroFilas; i++)
    {
        punteroMatriz[i] = new string[numeroColumnas];
        matrixOriginal[i] = new string[numeroColumnas];
    }
    // INGRESANDO ELEMENTOS A LA MATRIZ
    for (size_t i = 0; i < numeroFilas; i++)
    {
        for (size_t j = 0; j < numeroColumnas; j++)
        {
            if (j == numeroColumnas - 1 && i == numeroFilas - 1)
            {
                punteroMatriz[i][j] = "X";
                matrixOriginal[i][j] = "X";
                elementos[contador] = 0;

                break;
            }
            else
            {
                int numero;
                // desde 1 al numero final de tablero
                numero = (rand() % cantidadTablero + 1);
                elementos[contador] = numero;
                contador++;

                punteroMatriz[i][j] =to_string(numero);
                matrixOriginal[i][j] = to_string(numero);
            }
        }
    }

 
    
}

void creacionTableroArchivo(string* text) {

}

//metodo split
void split(string str)
{
    string word = "";
    for (auto x : str) 
    {
        if (x == ',')
        {
            cout << word << endl;
            word = "";
        }
        else {
            word = word + x;
        }
    }
    cout << word << endl;
}

// Metoto para determinar el archivo de texto
void ingresoArchivoTexto()
{
    string archivoTotal;
    fstream file;
    file.open("ingreso.txt", ios::in);
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            archivoTotal = archivoTotal + line;

        }
        file.close();
    }

    cout << archivoTotal;
}

// metodo de juego (manual - Insertando datos -  Aleatorio)
void jugarManual(int seleccion)
{
    cantidadMovimientos = 0;
    // Aqui eestablezco el juego
    auto start = sc.now(); // Comienza a contar el tiempo
    // le solicito al usuario que seleccione con que "usuario" jugara
    cout << "Escriba el numero del usuario con el que jugara" << endl;
    mostrarJugadores();
    int seleccionJugador;
    cin >> seleccionJugador;
    bool jugadorEncontrado = false;

    for (size_t i = 0; i < personasArrayFinal.size(); i++)
    {
        if (seleccionJugador == i)
        {
            cout << "Jugara con el usuario: " << personasArrayFinal[i].getNombre();
            jugadorEncontrado = true;
            break;
        }
    }

    if (jugadorEncontrado)
    {

        if (seleccion == 2)
        {
            ingresoManual();
        }
        else if (seleccion == 3)
        {
            ingresoAleatorioNumeros();
        }
        cout << "La matriz generada es:\n";
        imprimir(punteroMatriz);
        shufelingMatrix(punteroMatriz);
        cout<<"Seleccione que modo quiere jugar: \n"<<
                "1. Orden descendente\n"<<
                "2. Orden estipulado por el programa/Usuario";
        int seleccionModo;
        cin>>seleccionModo;
        if (seleccionModo ==1)
        {
            /**Continua*/
        } else if (seleccionModo ==2) {
        cout << "La matriz generada es:\n";
        ordenarNumeros(elementos, nElementos);
        ordenamiento(matrixOriginal, elementos);
        imprimir(matrixOriginal);
        }
        
        bool continuacion = true;
        do
        {
            imprimir(punteroMatriz);
            // imprimir(punteroMatriz, numeroFilas, numeroColumnas);
            int pasos = cantidadMovimientos;

            cout << "Nombre del jugador: " << personasArrayFinal[seleccionJugador].getNombre() << "\t";
            cout << "Cantidad de Movimientos: " << pasos << endl;
            cout << endl
                 << "w = Arriba - s = Abajo - a = Izquierda - d = Derecha - x = Terminar" << endl;
            char cNextMove;
            cin >> cNextMove;

            if (cNextMove == 'x' || comprobarGanadorDinamico(punteroMatriz, matrixOriginal) == 2 * (numeroColumnas * numeroFilas))
            {
                imprimir(punteroMatriz);
                cout << "Su puntaje fue de:" << comprobarGanadorDinamico(punteroMatriz, matrixOriginal)
                     << "\n";
                // Generacion de Tiempo en Partida
                auto end = sc.now();
                auto time_span = static_cast<chrono::duration<double>>(end - start);
                cout << "Tiempo de Juego: " << time_span.count() << " segundos\n";

                // CREACION Y ASIGNACION DE VARIABLES DE PARTIDAS

                Partida partidaTempo(personasArrayFinal[seleccionJugador].getNombre(), comprobarGanadorDinamico(punteroMatriz, matrixOriginal), pasos, time_span.count());

                // agrega la partida
                partidasArreglo.push_back(partidaTempo);
                // eLIMINACION DE PUNTEROS
                for (size_t i = 0; i < numeroFilas; i++)
                {
                    delete[] punteroMatriz[i];
                    delete[] matrixOriginal[i];
                }
                // eliminacion de puntero
                delete[] punteroMatriz;
                delete[] matrixOriginal;
                delete[] elementos;

                continuacion = false;
                break;
            }
            else
            {
                EMove eNextMove = (EMove)cNextMove;
                moverEspacios(punteroMatriz, eNextMove);
                cout << endl;
            }

        } while (continuacion == true);
    }
    else
    {
        cout << "Error Jugador no existente o sin jugadores";
    }
}

// Metodo de juego (basico para solo 15 numeros)
void jugar()
{
    cantidadMovimientos = 0;

    // Aqui eestablezco el juego
    auto start = sc.now(); // Comienza a contar el tiempo
    // le solicito al usuario que seleccione con que "usuario" jugara
    cout << "Escriba el numero del usuario con el que jugara" << endl;
    mostrarJugadores();
    int seleccionJugador;
    cin >> seleccionJugador;
    bool jugadorEncontrado = false;

    for (size_t i = 0; i < personasArrayFinal.size(); i++)
    {
        if (seleccionJugador == i)
        {
            cout << "Jugara con el usuario: " << personasArrayFinal[i].getNombre();
            jugadorEncontrado = true;
            break;
        }
    }

    if (jugadorEncontrado)
    {
        string caaBoard[4][4];
        InitializeBoard(caaBoard);
        Randomize(caaBoard);
        bool continuacion = true;
        do
        {
            PrintBoard(caaBoard);
            int pasos = cantidadMovimientos - 1000000;
            cout << "Nombre del jugador: " << personasArrayFinal[seleccionJugador].getNombre() << "\t";
            cout << "Cantidad de Movimientos: " << pasos << endl;
            cout << endl
                 << "w = Arriba - s = Abajo - a = Izquierda - d = Derecha - x = Terminar" << endl;
            char cNextMove;
            cin >> cNextMove;
            if (cNextMove == 'x' || comprobarPuntaje(caaBoard) == 32)
            {
                imprimirMatriz(caaBoard);
                cout << "Su puntaje fue de:" << comprobarPuntaje(caaBoard) << "\n";
                auto end = sc.now();
                auto time_span = static_cast<chrono::duration<double>>(end - start);
                cout << "Tiempo de Juego: " << time_span.count() << " segundos\n";

                // CREACION Y ASIGNACION DE VARIABLES DE PARTIDAS
                Partida partidaTempo(personasArrayFinal[seleccionJugador].getNombre(), comprobarPuntaje(caaBoard),
                                     (cantidadMovimientos - 1000000), time_span.count());
                partidasArreglo.push_back(partidaTempo);
                continuacion = false;
                break;
            }
            else
            {
                EMove eNextMove = (EMove)cNextMove;
                movimiento(caaBoard, eNextMove);
                cout << endl;
            }

        } while (continuacion == true);
    }
    else
    {
        cout << "Error Jugador no existente o sin jugadores";
    }
}

//-------------------------------------Metodo de seleccion de opciones de matriz
void menuMatrizEspecifico()
{
    int seleccion;
    do
    {
        std::cout << "Seleccione una opcion\n";
        std::cout << "1. Jugar basico (15 numeros)" << std::endl
                  << "2. Ingreso Manual" << std::endl
                  << "3. Ingreso Aleatorio" << std::endl
                  << "4. Ingreso Archivo" << std::endl
                  << "5. Regresar\n";
        std::cin >> seleccion;
        switch (seleccion)
        {
        case 1:
            jugar();
            break;
        case 2:
            jugarManual(seleccion);

            break;
        case 3:
            jugarManual(seleccion);
        case 4:
            // Ingreso por archivo
            ingresoArchivoTexto();
            break;
        case 5:
            // FIn
            cout << "Regresando al menu de Juego" << endl;
            break;

        default:
            // presiona algo mas
            cout << "No existe esta opcion" << endl;
            break;
        }
    } while (seleccion != 5);
}

// Metodo del juego en general
void menuEspecificoJuego()
{
    int seleccion;
    do
    {
        std::cout << "Seleccione una opcion\n";
        std::cout << "1. Jugar" << std::endl
                  << " 2. Usuarios" << std::endl
                  << " 3. Regresar\n";
        std::cin >> seleccion;
        switch (seleccion)
        {
        case 1:
            menuMatrizEspecifico();
            break;
        case 2:
            // Ver Reportes
            generacionUsuario();
            break;
        case 3:
            // FIn juego
            cout << "Regresando al menu principal" << endl;
            break;
        default:
            // presiona algo mas
            cout << "No existe esta opcion" << endl;
            break;
        }
    } while (seleccion != 3);
}

// APARTADO DE REPORTES Y VISTAS*-----------------------------------------------------------------

void mostrarReporte()
{
    cout << "-----Partidas Jugadas-------\n";
    for (size_t i = 0; i < partidasArreglo.size(); i++)
    {
        cout << "--------------------------------------------------------\n";
        cout << "Nombre: " << partidasArreglo[i].getNombre() << "\n";
        cout << "Puntos: " << partidasArreglo[i].getCantidadPunteo() << "\n";
        cout << "Pasos: " << partidasArreglo[i].getPasosTotales() << "\n";
        cout << "Tiempo: " << partidasArreglo[i].getTiempoPartida() << "\n";
    }
}
// METODO DEL MENU DE REPORTE
void menuReporte()
{
    int seleccion;
    do
    {
        std::cout << "Seleccione una opcion\n";
        std::cout << "1. Ver reporte" << std::endl
                  << " 2. Regresar";
        std::cin >> seleccion;
        switch (seleccion)
        {
        case 1:
            mostrarReporte();
            break;

        case 2:
            // FIn juego
            cout << "Regresando al menu principal" << endl;
            break;
        default:
            // presiona algo mas
            cout << "No existe esta opcion" << endl;
            break;
        }
    } while (seleccion != 2);
}

// Metodo inicial de Menu
int main()
{
    // puntero

    personas1 *persona = new personas1();

    int seleccion;

    do
    {
        std::cout << "1. Jugar" << std::endl
                  << " 2. Reportes" << std::endl
                  << " 3. Salir\n";
        std::cin >> seleccion;

        switch (seleccion)
        {
        case 1:
            menuEspecificoJuego();

        case 2:
            menuReporte();
            break;
        case 3:
            // FIn juego

            cout << "Gracias por jugar" << endl;
            return 0;
        default:
            // presiona algo mas
            cout << "No existe esta opcion" << endl;
            break;
        }
        // en caso venga el 2, se termina todo
    } while (seleccion != 3);
}