#ifndef RESERVACION_H
#define RESERVACION_H
#include <string>
#include <sstream>
#include "fecha.h"
using namespace std;

class Reservacion
{
private:
    string codigo;
    string codigoAlojamiento;
    string documentoHuesped;
    string metodoPago;
    Fecha fechaEntrada;
    int duracionNoche;
    Fecha fechaPago;
    string anotaciones;
    int valorTotal;
    bool activa;
public:
    //Constructores
    Reservacion();
    Reservacion(const string& cod, const string& codigoAloja, const string& docHues,
                const string& metPago, Fecha entrada, int duracionNoche, Fecha pago, int valortotal,
                const string& anot = "");
    //Getters
    string getCodigo() const;
    Fecha getFechaEntrada() const;
    Fecha getFechaSalida() const;
    bool EstaActiva() const;
    string getAnotaciones() const;
    string getCodigoAlojamiento() const;
    string getDocumentoHuesped() const;

    //Setters
    void setActiva(bool estado);
    void setAnotaciones(const string& notas);

    //Metodos de utilidad
    void mostrarComprobante() const;
    void anular();

    string toFileString() const;

};

#endif // RESERVACION_H
