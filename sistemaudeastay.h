/*#ifndef SISTEMA_UDEASTAY_H
#define SISTEMA_UDEASTAY_H

#include <string>
#include "Fecha.h" // Necesario para parámetros y tipos de retorno
#include "Alojamiento.h"
#include "Reservacion.h" // Asumiendo un Reservacion.h básico
#include "Anfitrion.h"   // Asumiendo un Anfitrion.h básico
#include "Huesped.h"     // Asumiendo un Huesped.h básico

class SistemaUdeAStay {
private:
    // --- Colecciones Dinámicas ---
    Alojamiento* todosAlojamientos;
    int cantidadAlojamientos;
    int cupoAlojamientos; // Capacidad actual del arreglo dinámico

    Reservacion* todasReservaciones;
    int cantidadReservaciones;
    int cupoReservaciones;

    Anfitrion* todosAnfitriones;
    int cantidadAnfitriones;
    int cupoAnfitriones;

    Huesped* todosHuespedes;
    int cantidadHuespedes;
    int cupoHuespedes;

    // --- Estado de Sesión ---
    Anfitrion* anfitrionLogueado; // Puntero al anfitrión actual, o nullptr
    Huesped* huespedLogueado;     // Puntero al huésped actual, o nullptr

    // --- Contadores para Medición de Recursos
    unsigned long long contadorIteraciones;
    size_t memoriaConsumidaActualObjetos; // Para sizeof(Objetos)

    // --- Métodos Privados de Ayuda (Helpers) ---
    void redimensionarAlojamientos();
    void redimensionarReservaciones();
    void redimensionarAnfitriones();
    void redimensionarHuespedes();

    // Helpers para carga y guardado
    void cargarAlojamientos();
    void guardarAlojamientos() const;
    void cargarReservaciones(); // Carga solo las vigentes
    void guardarReservaciones() const; // Guarda solo las vigentes
    void cargarAnfitriones();
    void guardarAnfitriones() const;
    void cargarHuespedes();
    void guardarHuespedes() const;

    void cargarArchivoHistorico(); // Solo para consulta o añadir, no se cargan a todasReservaciones
    void agregarAReservacionesHistoricas(const Reservacion& reservacion) const;

    // Helpers para búsqueda interna
    Anfitrion* buscarAnfitrionPorID(const std::string& id) const;
    Huesped* buscarHuespedPorID(const std::string& id) const;
    Alojamiento* buscarAlojamientoInternoPorCodigo(const std::string& codigo) const;
    int encontrarIndiceReservacion(const std::string& codigoReservacion) const;

    // Para la medición de recursos
    void resetearContadoresRecursos();

public:
    // --- Constructor y Destructor ---
    SistemaUdeAStay();
    ~SistemaUdeAStay();

    // --- Gestión Principal del Sistema ---
    void iniciar(); // Podría contener el bucle principal del menú

    // --- Carga y Guardado General de Datos
    void cargarTodosLosDatos(); // Llama a los cargadores individuales
    void guardarTodosLosDatos() const; // Llama a los guardadores individuales

    // --- Login y Sesión
    bool loginAnfitrion(const std::string& documento, const std::string& contrasena);
    bool loginHuesped(const std::string& documento, const std::string& contrasena);
    void logout();
    bool hayAnfitrionLogueado() const;
    bool hayHuespedLogueado() const;
    Anfitrion* getAnfitrionLogueado() const; // solo devolver punteros const
    Huesped* getHuespedLogueado() const;

    // --- Funcionalidades de Huésped
    // Muestra alojamientos y devuelve un arreglo de IDs o punteros para seleccionar
    void buscarYMostrarAlojamientosDisponibles(Fecha fecha, const std::string& municipio, int noches,
                                               double costoMax = -1.0, double puntMinAnf = -1.0);
    Alojamiento* buscarAlojamientoPorCodigo(const std::string& codigo) const; // Para la opción de búsqueda directa
    bool realizarNuevaReservacion(const std::string& codigoAlojamiento, Fecha fechaInicio, int noches,
                                  const std::string& metodoPago, const std::string& anotaciones);

    // --- Funcionalidades de Anfitrión ---
    void consultarReservacionesPropias(Fecha fechaDesde, Fecha fechaHasta) const;
    bool actualizarHistoricoReservaciones(Fecha fechaCorte);

    // --- Funcionalidades Comunes ---
    bool anularReservacion(const std::string& codigoReservacion);

    // --- Verificaciones y Validaciones ---
    bool verificarDisponibilidadAlojamiento(const std::string& codigoAlojamiento, Fecha inicio, int noches) const;
    bool verificarTraslapeReservasHuesped(const std::string& docHuesped, Fecha inicio, int noches) const;

    // --- Medición de Recursos
    void mostrarConsumoRecursos() const; // Muestra los contadores
    // Estos se llamarán internamente para actualizar los contadores
    void incrementarIteraciones(unsigned long long cantidad = 1);
    void anadirMemoriaConsumida(size_t bytes);
    void restarMemoriaConsumida(size_t bytes);



};

#endif // SISTEMA_UDEASTAY_H
*/
