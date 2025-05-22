// --- Fecha.cpp ---
// Implementación de la clase Fecha para el sistema UdeAStay.
// Autor: [Tu Nombre/Equipo]
// Fecha de creación: 21 de Mayo del 2025

#include "Fecha.h"
#include <iostream>   // Para std::cerr (salida de errores)
#include <sstream>    // Para std::ostringstream (construcción de strings)
#include <iomanip>    // Para std::setw, std::setfill (formato de salida)
#include <stdexcept>  // Para std::invalid_argument (manejo de excepciones)

// Usamos el namespace std para evitar escribir 'std::' repetidamente.
using namespace std;

// --- Métodos Privados (Helpers) ---

/**
 * @brief Verifica si los componentes de una fecha (día, mes, año) forman una fecha válida.
 * Incluye la validación de años bisiestos para Febrero.
 * @param d Día.
 * @param m Mes.
 * @param a Año.
 * @return true si la fecha es válida, false en caso contrario.
 */
bool Fecha::esFechaValida(int d, int m, int a) const {
    // Considero años válidos a partir del 0 o 1 d.C. Ajustar si es necesario.
    if (a < 1) return false;
    if (m < 1 || m > 12) return false; // Meses deben estar entre 1 y 12.
    if (d < 1) return false;         // Días deben ser al menos 1.

    // Días por mes (0 es un placeholder para el índice 0).
    int diasEnMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Verificación de año bisiesto para Febrero.
    if (m == 2 && ((a % 4 == 0 && a % 100 != 0) || (a % 400 == 0))) {
        if (d > 29) return false; // Febrero en bisiesto tiene hasta 29 días.
    } else {
        if (d > diasEnMes[m]) return false; // Verificar contra días normales del mes.
    }
    return true; // Si pasó todas las validaciones, es válida.
}

/**
 * @brief Calcula el nombre del día de la semana para una fecha dada.
 * Utiliza la Congruencia de Zeller.
 * @param d Día del mes (1-31).
 * @param m Mes (1-12). Enero y Febrero se tratan como meses 13 y 14 del año anterior.
 * @param a Año.
 * @return string con el nombre del día de la semana en español.
 */
string Fecha::calcularNombreDiaSemana(int d, int m, int a) const {
    // Nombres de los días, Domingo es 0 según Zeller para esta variante.
    string nombresDia[] = {"Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};

    int anioZ = a;
    int mesZ = m;

    if (mesZ < 3) { // Enero (1) y Febrero (2) se consideran meses 13 y 14 del año anterior.
        mesZ += 12;
        anioZ--;
    }

    int K = anioZ % 100; // Año del siglo.
    int J = anioZ / 100; // Siglo.

    // Fórmula de Zeller (para el calendario Gregoriano):
    // h = (q + floor(13*(m+1)/5) + K + floor(K/4) + floor(J/4) - 2*J) mod 7
    // Donde q es el día, m es el mes (3=Marzo, ..., 12=Diciembre, 13=Enero, 14=Febrero),
    // K el año del siglo, J el siglo.
    // El resultado h: 0=Sábado, 1=Domingo, ..., 6=Viernes (si se usa la fórmula original directa)
    // Adaptaremos para que 0=Domingo, 1=Lunes, etc.
    // Mi variante: h = (d + floor((13*(mesZ+1))/5) + K + floor(K/4) + J + 5*J) mod 7
    // Resultado: 0=Domingo, 1=Lunes, ..., 6=Sábado.

    int h = (d + (13 * (mesZ + 1)) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;
    // Ajuste para que 0 sea Domingo, 1 Lunes, etc. según mi array `nombresDia`
    // Zeller original da 0=Sábado, 1=Domingo...
    // Si h=0 (Sábado), debe ser nombresDia[6]
    // Si h=1 (Domingo), debe ser nombresDia[0]
    // (h + 6) % 7 mapea 0->6, 1->0, 2->1 ...
    return nombresDia[(h + 6) % 7]; // Ajuste para que 0=Domingo, 1=Lunes...
}


// --- Constructores ---

/**
 * @brief Constructor por defecto. Inicializa a 01/01/1900.
 */
Fecha::Fecha() : dia(1), mes(1), anio(1900) {
    // Cuerpo del constructor por defecto. Ya inicializado en la lista.
}

/**
 * @brief Constructor con parámetros.
 * Valida la fecha; si es inválida, establece 01/01/1900 y muestra error.
 * @param d Día.
 * @param m Mes.
 * @param a Año.
 */
Fecha::Fecha(int d, int m, int a) {
    if (esFechaValida(d, m, a)) {
        this->dia = d;
        this->mes = m;
        this->anio = a;
    } else {
        // La fecha proporcionada no es válida.
        // Informamos y establecemos una fecha segura por defecto.
        cerr << "ADVERTENCIA [Fecha]: Fecha de construcción (" << d << "/" << m << "/" << a
             << ") inválida. Estableciendo a 01/01/1900." << endl;
        this->dia = 1;
        this->mes = 1;
        this->anio = 1900;
        // Podríamos lanzar std::invalid_argument aquí si quisiéramos ser más estrictos.
        // throw invalid_argument("Fecha de construcción inválida.");
    }
}

// --- Getters ---
int Fecha::getDia() const { return dia; }
int Fecha::getMes() const { return mes; }
int Fecha::getAnio() const { return anio; }

// --- Setters ---
/**
 * @brief Establece el día. Valida que la nueva fecha sea coherente.
 * @param d Nuevo día.
 * @return true si se pudo establecer, false si la fecha resultante sería inválida.
 */
bool Fecha::setDia(int d) {
    if (esFechaValida(d, this->mes, this->anio)) {
        this->dia = d;
        return true;
    }
    cerr << "ADVERTENCIA [Fecha]: Intento de establecer día (" << d << ") inválido para "
         << this->mes << "/" << this->anio << "." << endl;
    return false;
}

bool Fecha::setMes(int m) {
    if (esFechaValida(this->dia, m, this->anio)) {
        this->mes = m;
        return true;
    }
    cerr << "ADVERTENCIA [Fecha]: Intento de establecer mes (" << m << ") inválido para "
         << this->dia << "/" << this->anio << "." << endl;
    return false;
}

bool Fecha::setAnio(int a) {
    if (esFechaValida(this->dia, this->mes, a)) {
        this->anio = a;
        return true;
    }
    cerr << "ADVERTENCIA [Fecha]: Intento de establecer año (" << a << ") inválido para "
         << this->dia << "/" << this->mes << "." << endl;
    return false;
}

/**
 * @brief Establece la fecha completa.
 * @param d Nuevo día.
 * @param m Nuevo mes.
 * @param a Nuevo año.
 * @return true si se pudo establecer, false si la fecha resultante sería inválida.
 */
bool Fecha::setFecha(int d, int m, int a) {
    if (esFechaValida(d, m, a)) {
        this->dia = d;
        this->mes = m;
        this->anio = a;
        return true;
    }
    cerr << "ADVERTENCIA [Fecha]: Intento de establecer fecha (" << d << "/" << m << "/" << a
         << ") inválida." << endl;
    return false;
}

// --- Métodos de Utilidad ---

/**
 * @brief Convierte la fecha a un string en formato "dd/mm/aaaa".
 * @return string con la fecha formateada.
 */
string Fecha::toString() const {
    ostringstream oss;
    oss << setw(2) << setfill('0') << dia << "/"
        << setw(2) << setfill('0') << mes << "/"
        << anio;
    return oss.str();
}

/**
 * @brief Convierte la fecha a un string en formato largo: "NombreDia, DD de NombreMes del AAAA".
 * Cumple con el formato especificado en el desafío.
 * @return string con la fecha en formato largo.
 */
string Fecha::toStringFormatoLargo() const {
    string nombresMes[] = {
        "", "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
        "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"
    };

    // Obtenemos el nombre del día de la semana.
    string nombreDia = calcularNombreDiaSemana(this->dia, this->mes, this->anio);

    ostringstream oss;
    oss << nombreDia << ", " << dia << " de " << nombresMes[mes] << " del " << anio;
    return oss.str();
}

/**
 * @brief Compara si esta fecha es anterior a otraFecha.
 * @param otraFecha La fecha con la que se compara.
 * @return true si esta fecha es estrictamente menor.
 */
bool Fecha::esMenor(const Fecha& otraFecha) const {
    if (this->anio < otraFecha.anio) return true;
    if (this->anio > otraFecha.anio) return false;
    // Años iguales, se compara el mes.
    if (this->mes < otraFecha.mes) return true;
    if (this->mes > otraFecha.mes) return false;
    // Meses iguales, se compara el día.
    return this->dia < otraFecha.dia;
}

/**
 * @brief Compara si esta fecha es igual a otraFecha.
 * @param otraFecha La fecha con la que se compara.
 * @return true si ambas fechas son idénticas.
 */
bool Fecha::esIgual(const Fecha& otraFecha) const {
    return this->anio == otraFecha.anio &&
           this->mes == otraFecha.mes &&
           this->dia == otraFecha.dia;
}

/**
 * @brief Calcula la fecha resultante después de sumar un número de noches a la fecha actual.
 * Maneja correctamente el cambio de meses y años, incluyendo años bisiestos.
 * @param noches Número de noches a sumar (debe ser no negativo).
 * @return Un nuevo objeto Fecha con la fecha resultante.
 */
Fecha Fecha::calcularFechaMasDuracion(int noches) const {
    if (noches < 0) {
        cerr << "ERROR [Fecha]: No se pueden sumar noches negativas en calcularFechaMasDuracion." << endl;
        return *this; // Devolver la fecha actual o manejar el error de otra forma.
    }

    Fecha nuevaFecha = *this; // Se trabaja sobre una copia.

    int diasEnMes[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    for (int i = 0; i < noches; ++i) {
        // Actualizar días en Febrero si es necesario para el año actual de nuevaFecha
        if ((nuevaFecha.anio % 4 == 0 && nuevaFecha.anio % 100 != 0) || (nuevaFecha.anio % 400 == 0)) {
            diasEnMes[2] = 29;
        } else {
            diasEnMes[2] = 28;
        }

        nuevaFecha.dia++;
        if (nuevaFecha.dia > diasEnMes[nuevaFecha.mes]) {
            nuevaFecha.dia = 1; // Reiniciar día a 1.
            nuevaFecha.mes++;
            if (nuevaFecha.mes > 12) {
                nuevaFecha.mes = 1; // Reiniciar mes a Enero.
                nuevaFecha.anio++;  // Incrementar año.
            }
        }
    }
    // Es importante asegurar que la nuevaFecha final sea válida, aunque el bucle debería garantizarlo.
    // Sin embargo, si 'noches' es muy grande, podrían surgir problemas no previstos.
    // Por ahora, confiamos en que la lógica incremental es correcta.
    return nuevaFecha;
}


/**
 * @brief Verifica si la fecha actual (this) se encuentra dentro de un rango [inicio, fin], inclusivo.
 * @param inicio Fecha de inicio del rango.
 * @param fin Fecha de fin del rango.
 * @return true si this está en el rango [inicio, fin].
 */
bool Fecha::fechaEnRango(const Fecha& inicio, const Fecha& fin) const {
    // this >= inicio Y this <= fin
    // Lo que es equivalente a: !(this < inicio) Y !(fin < this)
    return !this->esMenor(inicio) && !fin.esMenor(*this);
}

/**
 * @brief Compara si esta fecha es mayor o igual a otraFecha.
 * @param otraFecha La fecha con la que se compara.
 * @return true si esta fecha es mayor o igual.
 */
bool Fecha::esMayorOIgual(const Fecha& otraFecha) const {
    return this->esIgual(otraFecha) || !this->esMenor(otraFecha);
}
