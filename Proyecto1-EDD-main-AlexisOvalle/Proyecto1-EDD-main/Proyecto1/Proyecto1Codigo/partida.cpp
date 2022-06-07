

#include <iostream>
#include "persona.h"
#include "partida.h"


// metodo constructor
Partida::Partida(std::string nombre, int cantidadPunteo, 
int pasosTotales, double tiempoPartida) :
personas1(nombre){
    this-> cantidadPunteo = cantidadPunteo;
    this->pasosTotales = pasosTotales;
    this->tiempoPartida = tiempoPartida;
}
 
// Overwrite del ToString
void Partida::ToString(){
    std::cout <<"Nombre: "<< this-> getNombre() <<
            " cantidad de puntos " << this-> cantidadPunteo << 
            " pasos totales" << this-> pasosTotales << 
            " tiempo de partida " << this-> tiempoPartida  << "\n";
}



 /* 
Partida::~Partida()
{
   // std::cout << "Persona " << this->nombre << " es destruida\n";
}

*/