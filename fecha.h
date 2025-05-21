#ifndef FECHA_H
#define FECHA_H

#include <string>

class Fecha {
private:
    int dia;
    int mes;
    int anio;
    // Helper para validar si una fecha es correcta (ej. no 30 de febrero)
    bool esFechaValida(int d, int m, int a) const;

public:
    // --- Constructores ---
    Fecha(); // Constructor por defecto
    Fecha(int d, int m, int a);

    // --- Getters ---
    int getDia() const;
    int getMes() const;
    int getAnio() const;

    // --- Setters ---
    // Devuelven bool para indicar si la fecha se pudo establecer (si era válida)
    bool setDia(int d);
    bool setMes(int m);
    bool setAnio(int a);
    bool setFecha(int d, int m, int a);

    // --- Métodos de Utilidad ---
    std::string toString() const; // Para mostrar la fecha, ej. "dd/mm/aaaa"

    std::string toStringFormatoLargo() const;
    bool esMenor(const Fecha& otraFecha) const;
    bool esIgual(const Fecha& otraFecha) const;
    // Calcula la fecha resultante después de sumar N noches
    Fecha calcularFechaMasDuracion(int noches) const;
    // Verifica si la fecha actual está dentro de un rango [inicio, fin]
    bool fechaEnRango(const Fecha& inicio, const Fecha& fin) const;
    //  para validar la "fecha de corte"
    bool esMayorOIgual(const Fecha& otraFecha) const;
};

#endif // FECHA_H
