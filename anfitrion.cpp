#include "anfitrion.h"
#include <iostream>
using namespace std;

Anfitrion::Anfitrion(const string& doc, int antig, float punt)
    : documento(doc), antiguedadMeses(antig), puntuacion(punt){
    capacidad = 2;
    cantidad = 0;
    codigosAlojamiento = new string[capacidad];
}

Anfitrion::~Anfitrion() {
    delete[] codigosAlojamiento;
}

string Anfitrion::getDocumento() const {
    return documento;
}

float Anfitrion::getPuntuacion() const {
    return puntuacion;
}

void Anfitrion::agregarCodigoAlojamiento(const string &codigoAlo) {
    if (cantidad == capacidad) {
        capacidad *= 2;
        string* nuevo = new string[capacidad];
        for (int i = 0; i < cantidad; i++) {
            nuevo[i] = codigosAlojamiento[i];
        }
        delete[] codigosAlojamiento;
        codigosAlojamiento = nuevo;
    }
    codigosAlojamiento[cantidad++] = codigoAlo;
}

void Anfitrion::mostrarDetalles() const {
    cout << "Anfitrion: " << documento << endl;
    cout << "antiguedad (meses): " << antiguedadMeses << endl;
    cout << "Puntuacion: " << puntuacion << endl;
    cout << "Alojamiento administrados (" << cantidad << "): " << endl;
    for (int i = 0; i < cantidad; ++i) {
        cout << " - " << codigosAlojamiento[i] << endl;
    }
}
