#ifndef ALOJAMIENTO_H
#define ALOJAMIENTO_H

#include <string>
// No incluimos Fecha.h aquí directamente si no es estrictamente necesario
// para la declaración de Alojamiento. La disponibilidad se gestiona a nivel SistemaUdeAStay.

class Alojamiento {
private:
    std::string codigoID;
    std::string nombre;
    std::string direccion;
    std::string departamento;
    std::string municipio;
    std::string tipoAlojamiento; // "casa" o "apartamento" [cite: 20]
    std::string amenidades;     // "ascensor, piscina, etc." [cite: 20]
    double precioPorNoche;
    std::string anfitrionResponsableID; // ID del Anfitrion

public:
    // --- Constructores ---
    Alojamiento();
    Alojamiento(const std::string& codID, const std::string& nom, const std::string& dir,
                const std::string& depto, const std::string& mun, const std::string& tipo,
                const std::string& amen, double precio, const std::string& anfitrionID);

    // --- Getters ---
    std::string getCodigoID() const;
    std::string getNombre() const;
    std::string getDireccion() const;
    std::string getDepartamento() const;
    std::string getMunicipio() const;
    std::string getTipoAlojamiento() const;
    std::string getAmenidades() const;
    double getPrecioPorNoche() const;
    std::string getAnfitrionResponsableID() const;

    // --- Setters ---
    // Generalmente, el codigoID y el anfitrionResponsableID no deberían cambiar una vez creados.
    void setNombre(const std::string& nom);
    void setDireccion(const std::string& dir);
    void setDepartamento(const std::string& depto);
    void setMunicipio(const std::string& mun);
    void setTipoAlojamiento(const std::string& tipo);
    void setAmenidades(const std::string& amen);
    void setPrecioPorNoche(double precio);

    // --- Métodos de Utilidad ---
    // Para mostrar la información del alojamiento de forma legible
    void mostrarDetalles() const;
    // Podrías tener un método para convertir sus datos a un string para guardar en archivo
    std::string toFileString() const;
};

#endif // ALOJAMIENTO_H
