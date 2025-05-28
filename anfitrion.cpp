#include "anfitrion.h"
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;

Anfitrion::Anfitrion(const string& id_, const string& nom_,  const string& doc, const string& clave, int antig, float punt)
    : id(id_), nombre(nom_), documento(doc), contraseñaLogin(clave), antiguedadMeses(antig), puntuacion(punt){
    capacidad = 2;
    cantidad = 0;
    codigosAlojamiento = new string[capacidad];
}

Anfitrion& Anfitrion::operator=(const Anfitrion& otro) {
    if (this != &otro) {
        // Liberar memoria previa
        delete[] codigosAlojamiento;

        // Copiar los datos
        id = otro.id;
        nombre = otro.nombre;
        documento = otro.documento;
        contraseñaLogin = otro.contraseñaLogin;
        antiguedadMeses = otro.antiguedadMeses;
        puntuacion = otro.puntuacion;
        cantidad = otro.cantidad;
        capacidad = otro.capacidad;

        codigosAlojamiento = new string[capacidad];
        for (int i = 0; i < cantidad; ++i) {
            codigosAlojamiento[i] = otro.codigosAlojamiento[i];
        }
    }
    return *this;
}


Anfitrion::Anfitrion() {
    id = "";
    nombre = "";
    documento = "";
    contraseñaLogin = "";
    antiguedadMeses = 0;
    puntuacion = 0.0;
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
string Anfitrion::getContrasena() const {
    return contraseñaLogin;
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
    cout << "Contrasena login" << contraseñaLogin << endl;
    cout << "antiguedad (meses): " << antiguedadMeses << endl;
    cout << "Puntuacion: " << puntuacion << endl;
    cout << "Alojamiento administrados (" << cantidad << "): " << endl;
    for (int i = 0; i < cantidad; ++i) {
        cout << " - " << codigosAlojamiento[i] << endl;
    }
}
