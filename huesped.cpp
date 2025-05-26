#include "huesped.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;


Huesped::Huesped(const string& id_, const string& nom_, const string& doc, const string& clave, int antig, float punt)
    : id(id_), nombre(nom_), documento(doc), credencialLogin(clave), antiguedadMeses(antig), puntuacion(punt){
    capacidad = 2;
    cantidad = 0;
    codigosDeSusReservaciones = new string[capacidad];
}

Huesped::~Huesped() {
    delete[] codigosDeSusReservaciones;
}

float Huesped::getPuntuacion() const {
    return puntuacion;
}

void Huesped::setPuntuacion(float nueva) {
    if (nueva >= 0.0 && nueva <= 5.0) {
        puntuacion = nueva;
    }
}

void Huesped::agregarCodigoReservacion(const string &codigoRes) {
    if (cantidad == capacidad) {
        capacidad *= 2;
        string* nueva = new string[capacidad];
        for (int i = 0; i < cantidad; ++i) {
            nueva[i] = codigosDeSusReservaciones[i];
        }
        delete[] codigosDeSusReservaciones;
        codigosDeSusReservaciones = nueva;
    }
    codigosDeSusReservaciones[cantidad++] = codigoRes;
}

void Huesped::eliminarCodigoReservacion(const string &codigoRes) {
    for (int i = 0; i < cantidad; ++i) {
        if (codigosDeSusReservaciones[i] == codigoRes) {
            for (int j = i; j < cantidad - 1; ++j) {
                codigosDeSusReservaciones[j] = codigosDeSusReservaciones[j + 1];
            }
            cantidad--;
            break;
        }
    }
}

void Huesped::mostrarDetalles() const {
    cout << "ID: " << id << endl;
    cout << "Nombre completo: " << nombre << endl;
    cout << "documento: " << documento << endl;
    cout << "Antiguedad (meses): " << antiguedadMeses << endl;
    cout << "Puntuacion: " << puntuacion << endl;
    cout << "Reservaciones (" << cantidad << "): " << endl;
    for (int i = 0; i < cantidad; ++i) {
        cout << " - " << codigosDeSusReservaciones[i] << endl;
    }
}

string Huesped::toFileString() const {
    ostringstream oss;
    oss << id << ","
        << "\"" << nombre << "\","
        << documento << ","
        << "\"" << credencialLogin << "\","
        << antiguedadMeses << ","
        << fixed << setprecision(1) << puntuacion;
    return oss.str();
}
