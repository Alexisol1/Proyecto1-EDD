

// clase de la personaje que juega
#include <iostream>
#include "persona.h"

  void personas1::SetAll(std::string nombre){
    this->nombre = nombre;
   
}

  personas1::personas1(string nombre ) {
            this-> nombre = nombre;
         
    }

personas1::personas1()
{
    this->nombre = "";
 
}

personas1::~personas1()
{
    std::cout << "Persona " << this->nombre << " es destruida\n";
}

void personas1::ToString()
{
    std::cout << this->nombre ;
}