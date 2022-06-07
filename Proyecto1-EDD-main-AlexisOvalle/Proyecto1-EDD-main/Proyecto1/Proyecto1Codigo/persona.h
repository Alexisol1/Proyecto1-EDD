#include <string>
using std::string;
class personas1 {
    private:

    string nombre;
    
    public:
      
        void ingresoNombre() {
        
        }
      
        // GETTERS Y SETTES DE LA CLASE
        void setNombre(string nombre) {this->nombre = nombre;}
        string getNombre() {return nombre;}
        
      
        
    void SetAll(string nombre);
    //constructor de clase
    personas1(string nombre);
    personas1();
     ~personas1();

  // Created to be overwritten
    void ToString();
// destructor en direccion de memoeria
};
