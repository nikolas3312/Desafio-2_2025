#ifndef GESTOR_UDEASTAY_H
#define GESTOR_UDEASTAY_H

#include <string>
#include "Fecha.h"
#include "Alojamiento.h"
#include "Reservacion.h"
#include "Anfitrion.h"
#include "Huesped.h"

class GestorUdeaStay {
private:
    Fecha parsearStringAFechaInterno(const std::string& strFecha);
    int parsearLineaCSVInterno(const std::string& linea, std::string campos[], int numCamposEsperados);
    // Colecciones de datos principales
    Alojamiento* todosAlojamientos;
    int cantidadAlojamientos;
    int cupoAlojamientos;
    Reservacion* todasReservaciones; // Solo reservaciones activas
    int cantidadReservaciones;
    int cupoReservaciones;

    Anfitrion* todosAnfitriones;
    int cantidadAnfitriones;
    int cupoAnfitriones;

    Huesped* todosHuespedes;
    int cantidadHuespedes;
    int cupoHuespedes;

    // Información de la sesión actual
    Anfitrion* anfitrionLogueado;
    Huesped* huespedLogueado;

    // Para medir el rendimiento
    unsigned long long contadorIteracionesGlobal; // Un contador general de operaciones
    // La memoria se calculará bajo demanda o se actualizará en puntos clave

    // Nombres de los archivos de datos
    const std::string archivoAlojamientos = ""C:/Users/Nikolas Ortega/Desktop/desafio#2_2025/Desafio-2_2025/build/Desktop_Qt_6_8_2_MinGW_64_bit-Debug/Alojamientos.csv"";
    const std::string archivoAnfitriones = "Anfitriones.csv";
    const std::string archivoHuespedes = "Huespedes.csv";
    const std::string archivoReservaciones = "Reservaciones.csv";
    const std::string archivoHistorico = "Historico.csv";

    // --- Métodos de ayuda internos ---
    // Para manejar el tamaño de los arreglos dinámicos
    void asegurarCapacidadAlojamientos();
    void asegurarCapacidadAnfitriones();
    void asegurarCapacidadHuespedes();
    void asegurarCapacidadReservaciones();

    // Para cargar datos desde los archivos CSV
    void cargarAlojamientosDesdeArchivo();
    void cargarAnfitrionesDesdeArchivo();
    void cargarHuespedesDesdeArchivo();
    void cargarReservacionesActivasDesdeArchivo();

    // Para guardar las reservaciones (activas y al histórico)
    void guardarReservacionesActivasEnArchivo();
    void agregarReservacionAHistoricoEnArchivo(const Reservacion& reservacion);

    // Para buscar entidades internamente
    Anfitrion* encontrarAnfitrionPorDocumento(const std::string& documento) const;
    Huesped* encontrarHuespedPorDocumento(const std::string& documento) const;
    Alojamiento* encontrarAlojamientoPorCodigo(const std::string& codigo) const; // Cambiado para uso público potencial
    Reservacion* encontrarReservacionActivaPorCodigo(const std::string& codigoReservacion); // Para modificarla
    int obtenerIndiceReservacionActiva(const std::string& codigoReservacion) const;

    std::string generarNuevoCodigoReservacion() const; // Crea un ID único

public:
    GestorUdeaStay();
    ~GestorUdeaStay();

    // --- Gestión principal y Menús (a ser llamados desde main.cpp) ---
    void ejecutar(); // Método principal que inicia el sistema y maneja el flujo de menús

    // --- Carga y Guardado de Datos (principalmente interno) ---
    void inicializarSistema(); // Carga todos los datos al inicio
    void finalizarSistema();   // Guarda los datos necesarios al salir

    // --- Login y Sesión ---
    bool intentarLoginAnfitrion(const std::string& documento, const std::string& contrasena);
    bool intentarLoginHuesped(const std::string& documento, const std::string& contrasena);
    void cerrarSesion();
    bool haySesionAnfitrionActiva() const;
    bool haySesionHuespedActiva() const;
    const Anfitrion* getAnfitrionActual() const; // Devuelve el anfitrión logueado
    const Huesped* getHuespedActual() const;     // Devuelve el huésped logueado

    // --- Funcionalidades para Huéspedes ---
    void mostrarAlojamientosDisponibles(Fecha fecha, const std::string& municipio, int noches,
                                        double costoMax = -1.0, double puntMinAnf = -1.0) const;
    // getAlojamientoPorCodigo se puede usar antes de reservar si el huésped busca por código
    bool crearNuevaReservacion(const std::string& codigoAlojamiento, Fecha fechaInicio, int noches,
                               const std::string& metodoPago, const std::string& anotacionesHuesped);

    // --- Funcionalidades para Anfitriones ---
    void mostrarReservacionesDelAnfitrion(Fecha fechaDesde, Fecha fechaHasta) const; // Muestra las del anfitrión logueado
    bool actualizarArchivoHistorico(Fecha fechaCorte);
    // --- Funcionalidades Comunes ---
    bool cancelarUnaReservacion(const std::string& codigoReservacion); // Verifica permisos antes de anular

    // --- Medición de Recursos (ahora son métodos públicos para ser llamados desde el menú) ---
    void mostrarEstadoRecursosActual() const; // Muestra iteraciones y memoria
    void incrementarContadorIteraciones(unsigned long long cantidad = 1); // Para ser llamado por otros métodos
    // La memoria se calcula dentro de mostrarEstadoRecursosActual

    // --- Métodos de Ayuda Públicos (si fueran necesarios por main.cpp) ---
    // Alojamiento* getAlojamientoPorCodigo(const std::string& codigo) const; // Ya está arriba
};

#endif // GESTOR_UDEASTAY_H
