

#include <string>
using std::string;

class Partida : public personas1 {
private:
    int cantidadPunteo;
    int pasosTotales;
    double tiempoPartida;
public:
   
    
     
        void setPasosTotales(int pasosTotales){this->pasosTotales = pasosTotales;}
        int getPasosTotales(){return pasosTotales;}

        void setCantidadPunteo(int cantidadPunteo){this->cantidadPunteo = cantidadPunteo;}
        int getCantidadPunteo(){return cantidadPunteo;}
        
        void setTiempoPartida(double tiempoPartida){this->tiempoPartida = tiempoPartida;}
        double getTiempoPartida(){return tiempoPartida;}
    
    // The Dogs constructor
    Partida(std::string, int, int, double);
    
    // The default constructor calls Animals default
    // constructor
    Partida(): personas1(){};
   //  Partida();
    // ~Partida();
    // Overwrite ToString
    void ToString();
    
};

//-----------------------------------------------


