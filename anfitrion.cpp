#include "anfitrion.h"
#include <iostream>
using namespace std;

Anfitrion::Anfitrion(const string& id_, const string& nom_,  const string& doc, const string& clave, int antig, float punt)
    : id(id_), nombre(nom_), documento(doc), contraseñaLogin(clave), antiguedadMeses(antig), puntuacion(punt){
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
    cout << "ID: " << id << endl;
    cout << "Nombre completo: " << nombre << endl;
    cout << "Documento: " << documento << endl;
    cout << "Contraseña login" << contraseñaLogin << endl;
    cout << "antiguedad (meses): " << antiguedadMeses << endl;
    cout << "Puntuacion: " << puntuacion << endl;
    cout << "Alojamiento administrados (" << cantidad << "): " << endl;
    for (int i = 0; i < cantidad; ++i) {
        cout << " - " << codigosAlojamiento[i] << endl;
    }
}
