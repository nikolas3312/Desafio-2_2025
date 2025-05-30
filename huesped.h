#ifndef HUESPED_H
#define HUESPED_H
#include <string>
using namespace std;

class Huesped
{
private:
    string id;
    string nombre;
    string documento;
    string credencialLogin;

    int antiguedadMeses;
    float puntuacion;
    string* codigosDeSusReservaciones;
    int cantidad;
    int capacidad;
public:
    Huesped();
    Huesped(const Huesped& otro);                     // Constructor por copia
    Huesped& operator=(const Huesped& otro);          // Operador de asignación
    Huesped(const string& doc, int antig, float punt = 0.0);
    Huesped(const string& id_, const string& nom_, const string& doc_,
            const string& clave, int antig, float punt);
    ~Huesped();

    //Getters
    string getId() const;
    string getNombre() const;
    string getDocumento() const;
    float getPuntuacion() const;
    string getContrasena() const; //se agrego para poder crear el login
    int getCantidadReservaciones() const;
    string getCodigoReservacion(int i) const;

    //Setters
    void setPuntuacion(float nueva);

    //Metodos de utilidad
    void agregarCodigoReservacion(const string& codigoRes);
    void eliminarCodigoReservacion(const string& codigoRes);
    void mostrarDetalles() const;

};

#endif // HUESPED_H
