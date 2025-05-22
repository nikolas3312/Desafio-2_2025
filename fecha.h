#ifndef FECHA_H
#define FECHA_H

#include <string> // Usaremos std::string para los métodos que devuelven cadenas.

// Evitamos 'using namespace std;' en los archivos de encabezado (.h)
// para no contaminar el espacio de nombres global de quien incluya este archivo.
// Es una buena práctica mantenerlo así en los .h.

class Fecha {
private:
    int dia;
    int mes;
    int anio;

    // --- Helpers Privados ---
    // Valida si los componentes d, m, a forman una fecha calendárica correcta.
    bool esFechaValida(int d, int m, int a) const;

    // Calcula el nombre del día de la semana (e.g., "Lunes", "Martes").
    // Este método es usado internamente por toStringFormatoLargo().
    std::string calcularNombreDiaSemana(int d, int m, int a) const;

public:
    // --- Constructores ---
    Fecha(); // Constructor por defecto (ej: 01/01/1900).
    Fecha(int d, int m, int a); // Constructor con parámetros.

    // --- Getters ---
    // Devuelven los componentes individuales de la fecha.
    int getDia() const;
    int getMes() const;
    int getAnio() const;

    // --- Setters ---
    // Permiten modificar los componentes de la fecha.
    // Devuelven 'true' si la modificación resultó en una fecha válida, 'false' en caso contrario.
    bool setDia(int d);
    bool setMes(int m);
    bool setAnio(int a);
    bool setFecha(int d, int m, int a); // Establece la fecha completa.

    // --- Métodos de Utilidad y Conversión ---
    // Convierte la fecha a un string simple (ej: "dd/mm/aaaa").
    std::string toString() const;

    // Convierte la fecha al formato largo especificado en el desafío
    // (ej: "Lunes, 12 de Mayo del 2025").
    std::string toStringFormatoLargo() const;

    // --- Métodos de Comparación ---
    // Compara si esta fecha es estrictamente anterior a 'otraFecha'.
    bool esMenor(const Fecha& otraFecha) const;
    // Compara si esta fecha es idéntica a 'otraFecha'.
    bool esIgual(const Fecha& otraFecha) const;
    // Compara si esta fecha es posterior o igual a 'otraFecha'.
    // Útil, por ejemplo, para validar la "fecha de corte" del histórico.
    bool esMayorOIgual(const Fecha& otraFecha) const;

    // --- Métodos de Cálculo ---
    // Calcula y devuelve una nueva fecha resultante de sumar 'noches' a la fecha actual.
    Fecha calcularFechaMasDuracion(int noches) const;

    // Verifica si la fecha actual (this) está dentro del rango [inicio, fin], inclusivo.
    bool fechaEnRango(const Fecha& inicio, const Fecha& fin) const;
};

#endif // FECHA_H
