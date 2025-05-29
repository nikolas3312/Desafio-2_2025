#include "reservacion.h"
#include <iostream>
using namespace std;

Reservacion::Reservacion() :
    codigo(""), codigoAlojamiento(""), documentoHuesped(""),
    metodoPago(""), fechaEntrada(), duracionNoche(0),
    fechaPago(), valorTotal(0), activa(false), anotaciones("") {
    // Inicializa los miembros a valores seguros o vacíos.
    // La clase Fecha ya tiene un constructor por defecto.
}
Reservacion::Reservacion(const string& cod, const string& codigoAloja, const string& docHues, const string& metPago,
                         Fecha entrada, int duracionNoche, Fecha pago, int valortotal,
                         const string& anot)
    :   codigo(cod), codigoAlojamiento(codigoAloja), documentoHuesped(docHues),
        metodoPago(metPago), fechaEntrada(entrada), duracionNoche(duracionNoche),
        fechaPago(pago), valorTotal(valortotal), activa(true){
    if (anot.length() > 1000) {
        anotaciones = anot.substr(0,1000);
    } else {
        anotaciones = anot;
    }
}

string Reservacion::getCodigo() const{
    return codigo;
}

Fecha Reservacion::getFechaEntrada() const {
    return fechaEntrada;
}

Fecha Reservacion::getFechaSalida() const {
    return fechaEntrada.calcularFechaMasDuracion(duracionNoche);
}

bool Reservacion::EstaActiva() const {
    return activa;
}

string Reservacion::getAnotaciones() const {
    return anotaciones;
}

void Reservacion::setAnotaciones(const string& notas) {
    if (notas.length() > 1000) {
        anotaciones = notas.substr(0,1000);
    } else {
        anotaciones = notas;
    }
}

void Reservacion::mostrarComprobante() const {
    cout <<"   Comprobante de reservacion    " << endl;
    cout << "Codigo:" << codigo << endl;
    cout << "Codigo de Alojamiento: " << codigoAlojamiento << endl;
    cout << "Documento del huesped: " << documentoHuesped << endl;
    cout << "Metodo de pago: " << metodoPago << endl;
    cout << "Fecha de entrada: " << fechaEntrada.toStringFormatoLargo() << endl;
    cout << "Fecha de salida: " << getFechaSalida().toStringFormatoLargo() << endl;
    cout << "Valor total pagado: " << valorTotal << endl;
    cout << "Estado: " << (activa ? "Activa" : "Cancelada") << endl;
    cout << "Anotaciones: " << anotaciones << endl;
}

void Reservacion::anular() {
    activa = false;
}

string Reservacion::toFileString() const {
    ostringstream oss;
    oss << codigo << ","
        << codigoAlojamiento << ","
        << documentoHuesped << ","
        << fechaEntrada.toString() << ","
        << duracionNoche << ","
        << metodoPago << ","
        << fechaPago.toString() << ","
        << valorTotal << ","
        << "\"" << anotaciones << "\","
        << (activa ? "1" : "0");                //1 si es verdadero, 0 si es falso
    return oss.str();
}
