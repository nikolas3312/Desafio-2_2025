#ifndef ANFITRION_H
#define ANFITRION_H
#include <string>
using namespace std;

class Anfitrion
{
private:
    string id;
    string nombre;
    string documento;
    string contraseñaLogin;

    int antiguedadMeses;
    float puntuacion;
    string* codigosAlojamiento;
    int cantidad;
    int capacidad;
public:
    //constructor
    Anfitrion();
    Anfitrion& operator=(const Anfitrion& otro);
    Anfitrion(const string& doc, int antig, float punt = 0.0);
    Anfitrion(const string& id_, const string& nom_, const string& doc_, const string& clave,
              int antig, float punt);
    //Destructor
    ~Anfitrion();

    //Getters
    string getId() const;
    string getNombre()const;
    string getDocumento() const;
    string getContrasena() const; // para poder crear el login
    float getPuntuacion() const;
    //Setters
    void setPuntuacion(float nueva);

    //agregar codigo de alojamiento
    void agregarCodigoAlojamiento(const string& codigoAlo);

    //informacion del anfitrion
    void mostrarDetalles() const;

};

#endif // ANFITRION_H
