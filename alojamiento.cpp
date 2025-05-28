// --- Alojamiento.cpp ---
// Implementación de la clase Alojamiento para el sistema UdeAStay.
// Esta clase representa una propiedad disponible para ser rentada.
// Autor: [Nikolas ortega]
// Fecha de creación: 21 de Mayo del 2025

#include "Alojamiento.h"
#include <iostream> // Para std::cout (en mostrarDetalles y errores)
#include <sstream>  // Para std::ostringstream (en toFileString)
#include <limits>   // Para validaciones de precio (opcional)
#include <iomanip>
// Usamos el namespace std para evitar escribir 'std::' repetidamente.
using namespace std;

// --- Constructores ---

/**
 * @brief Constructor por defecto.
 * Inicializa el alojamiento con valores predeterminados o vacíos.
 * Es importante que un alojamiento creado por defecto sea identificable como tal
 * o se valide antes de su uso completo en el sistema.
 */
Alojamiento::Alojamiento() :
    codigoID("SIN_ID"),
    nombre("Alojamiento Desconocido"),
    direccion("No especificada"),
    departamento("No especificado"),
    municipio("No especificado"),
    tipoAlojamiento("No especificado"), // Podría ser "Casa" o "Apartamento"
    amenidades("Ninguna"),             // Ejemplo: "ascensor, piscina, etc."
    precioPorNoche(0.0),
    anfitrionResponsableID("SIN_ANFITRION") {
    // El constructor por defecto es útil, pero se debe tener cuidado
    // de que los objetos creados así se inicialicen correctamente
    // antes de ser usados plenamente en la lógica del sistema.
}

/**
 * @brief Constructor con parámetros.
 * Inicializa un alojamiento con todos sus atributos.
 * Realiza validaciones básicas en los parámetros, como el precio.
 * @param codID Código identificador único del alojamiento.
 * @param nom Nombre del alojamiento.
 * @param dir Dirección.
 * @param depto Departamento donde se ubica.
 * @param mun Municipio donde se ubica.
 * @param tipo Tipo de alojamiento (ej: "Casa", "Apartamento").
 * @param amen Lista de amenidades ofrecidas, separadas por algún delimitador.
 * @param precio Precio por noche.
 * @param anfitrionID ID del anfitrión responsable.
 */
Alojamiento::Alojamiento(const string& codID, const string& nom, const string& dir,
                         const string& depto, const string& mun, const string& tipo,
                         const string& amen, double precio, const string& anfitrionID) :
    codigoID(codID),
    nombre(nom),
    direccion(dir),
    departamento(depto),
    municipio(mun),
    tipoAlojamiento(tipo),
    amenidades(amen),
    precioPorNoche(precio),
    anfitrionResponsableID(anfitrionID) {

    // Validaciones básicas en el constructor
    if (codID.empty()) {
        cerr << "ADVERTENCIA [Alojamiento]: Código ID no puede estar vacío. Se asignó '" << this->codigoID << "' temporalmente." << endl;
        // Podríamos asignar un ID temporal o lanzar una excepción si la política es más estricta.
        // Por ahora, se mantiene el valor proporcionado, pero se advierte.
    }
    if (nom.empty()) {
        cerr << "ADVERTENCIA [Alojamiento]: Nombre del alojamiento no puede estar vacío para ID: " << this->codigoID << endl;
    }
    if (precio < 0.0) {
        cerr << "ADVERTENCIA [Alojamiento]: Precio por noche no puede ser negativo para ID: " << this->codigoID
             << ". Se establecerá a 0.0." << endl;
        this->precioPorNoche = 0.0;
    }
    if (anfitrionID.empty()) {
        cerr << "ADVERTENCIA [Alojamiento]: ID del anfitrión responsable no puede estar vacío para ID: " << this->codigoID << endl;
    }
    // Se podrían añadir más validaciones (ej. longitud de strings, formato de tipoAlojamiento, etc.)
}

// --- Getters ---
// Los getters proporcionan acceso de solo lectura a los atributos del alojamiento.
string Alojamiento::getCodigoID() const { return codigoID; }
string Alojamiento::getNombre() const { return nombre; }
string Alojamiento::getDireccion() const { return direccion; }
string Alojamiento::getDepartamento() const { return departamento; }
string Alojamiento::getMunicipio() const { return municipio; }
string Alojamiento::getTipoAlojamiento() const { return tipoAlojamiento; }
string Alojamiento::getAmenidades() const { return amenidades; }
double Alojamiento::getPrecioPorNoche() const { return precioPorNoche; }
string Alojamiento::getAnfitrionResponsableID() const { return anfitrionResponsableID; }

// --- Setters ---
// Los setters permiten modificar los atributos después de la creación del objeto.
// Es importante notar que el codigoID y anfitrionResponsableID usualmente no se modifican.

void Alojamiento::setNombre(const string& nom) {
    if (nom.empty()) {
        cerr << "ADVERTENCIA [Alojamiento]: Intento de establecer un nombre vacío para el alojamiento ID: " << this->codigoID << ". No se realizó el cambio." << endl;
        return;
    }
    this->nombre = nom;
}

void Alojamiento::setDireccion(const string& dir) {
    this->direccion = dir;
}

void Alojamiento::setDepartamento(const string& depto) {
    this->departamento = depto;
}

void Alojamiento::setMunicipio(const string& mun) {
    this->municipio = mun;
}

/**
 * @brief Establece el tipo de alojamiento.
 * Se podría validar contra una lista de tipos permitidos (ej: "Casa", "Apartamento").
 * @param tipo Nuevo tipo de alojamiento.
 */
void Alojamiento::setTipoAlojamiento(const string& tipo) {
    // Validación simple (se podría expandir para una lista específica de tipos)
    if (tipo.empty()) {
        cerr << "ADVERTENCIA [Alojamiento]: Tipo de alojamiento no puede ser vacío para ID: " << this->codigoID << ". No se realizó el cambio." << endl;
        return;
    }
    // Podríamos verificar si 'tipo' es uno de los valores esperados ("Casa", "Apartamento")
    // if (tipo != "Casa" && tipo != "Apartamento") {
    //     cerr << "ADVERTENCIA [Alojamiento]: Tipo de alojamiento '" << tipo << "' no reconocido para ID: " << this->codigoID << ". Se mantuvo el anterior." << endl;
    //     return;
    // }
    this->tipoAlojamiento = tipo;
}

void Alojamiento::setAmenidades(const string& amen) {
    this->amenidades = amen;
}

/**
 * @brief Establece el precio por noche.
 * Valida que el precio no sea negativo.
 * @param precio Nuevo precio por noche.
 */
void Alojamiento::setPrecioPorNoche(double precio) {
    if (precio < 0.0) {
        cerr << "ADVERTENCIA [Alojamiento]: Intento de establecer un precio negativo (" << precio
             << ") para el alojamiento ID: " << this->codigoID << ". No se realizó el cambio." << endl;
        return;
    }
    this->precioPorNoche = precio;
}

// --- Métodos de Utilidad ---

/**
 * @brief Muestra los detalles completos del alojamiento en la consola.
 * Formatea la salida para una fácil lectura por parte del usuario.
 */
void Alojamiento::mostrarDetalles() const {
    cout << "--- Detalles del Alojamiento ---" << endl;
    cout << "ID: " << codigoID << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Ubicación: " << direccion << ", " << municipio << ", " << departamento << endl;
    cout << "Tipo: " << tipoAlojamiento << endl;
    cout << "Precio por Noche: $" << fixed << setprecision(2) << precioPorNoche << endl;
    cout << "Amenidades: " << amenidades << endl;
    cout << "ID Anfitrión Responsable: " << anfitrionResponsableID << endl;
    cout << "------------------------------" << endl;
}

/**
 * @brief Convierte los datos del alojamiento a un string en formato CSV.
 * Facilita la escritura del objeto en un archivo de texto plano,
 * manteniendo el orden de campos definido para la carga.
 * @return string en formato CSV representando el alojamiento.
 */
string Alojamiento::toFileString() const {
    ostringstream oss;
    // El orden debe coincidir con el formato esperado por la función de carga de archivos.
    // Ejemplo de formato: CodigoID,Nombre,Direccion,Departamento,Municipio,Tipo,Amenidades,Precio,AnfitrionID
    oss << codigoID << ","
        << "\"" << nombre << "\"," // Usar comillas si el nombre puede tener comas
        << "\"" << direccion << "\","
        << departamento << ","
        << municipio << ","
        << tipoAlojamiento << ","
        << "\"" << amenidades << "\"," // Usar comillas si las amenidades usan comas internas, aunque usamos ';'
        << fixed << setprecision(2) << precioPorNoche << ","
        << anfitrionResponsableID;
    return oss.str();
}
