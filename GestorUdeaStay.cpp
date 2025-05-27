// --- GestorUdeaStay.cpp ---
// Implementación de la clase GestorUdeaStay, el núcleo del sistema UdeaStay.

#include "GestorUdeaStay.h"
#include <iostream>     // Para std::cout, std::cin, std::endl
#include <fstream>      // Para std::ifstream, std::ofstream (manejo de archivos)
#include <sstream>      // Para std::istringstream, std::ostringstream (parseo de líneas)
#include <string>       // Para std::string, std::getline
#include <limits>       // Para std::numeric_limits (limpiar buffer de cin)
#include <algorithm>    // Para std::remove si se usa para limpiar strings (opcional)

// Usamos el namespace std para este archivo .cpp
using namespace std;

// --- Constructor y Destructor ---

/**
 * @brief Constructor de GestorUdeaStay.
 * Inicializa todos los punteros de arreglos dinámicos a nullptr,
 * las cantidades a 0 y los cupos a un valor inicial.
 * Llama a inicializarSistema() para cargar los datos.
 */
GestorUdeaStay::GestorUdeaStay() :
    todosAlojamientos(nullptr), cantidadAlojamientos(0), cupoAlojamientos(0),
    todasReservaciones(nullptr), cantidadReservaciones(0), cupoReservaciones(0),
    todosAnfitriones(nullptr), cantidadAnfitriones(0), cupoAnfitriones(0),
    todosHuespedes(nullptr), cantidadHuespedes(0), cupoHuespedes(0),
    anfitrionLogueado(nullptr),
    huespedLogueado(nullptr),
    contadorIteracionesGlobal(0)
// Los const std::string para nombres de archivo ya se inicializan en el .h
{
    cout << "Inicializando GestorUdeaStay..." << endl; // Mensaje de prueba
    // Establecer un cupo inicial para los arreglos dinámicos
    // Podríamos empezar con un cupo pequeño, por ejemplo 10, y redimensionar según sea necesario.
    // O dejar que los métodos de carga manejen la primera asignación.
    // Por ahora, los métodos de carga se encargarán de la primera asignación si son nullptr.

    inicializarSistema(); // Carga todos los datos al crear el objeto
}

/**
 * @brief Destructor de GestorUdeaStay.
 * Se asegura de guardar los datos necesarios (principalmente reservaciones).
 * Libera toda la memoria dinámica utilizada por los arreglos.
 */
GestorUdeaStay::~GestorUdeaStay() {
    cout << "Finalizando GestorUdeaStay y guardando datos..." << endl; // Mensaje de prueba
    finalizarSistema(); // Guarda los datos necesarios (ej. reservaciones)

    // Liberar memoria de los arreglos dinámicos
    delete[] todosAlojamientos;
    delete[] todasReservaciones;
    delete[] todosAnfitriones;
    delete[] todosHuespedes;

    // Los punteros anfitrionLogueado y huespedLogueado no son dueños de la memoria,
    // solo apuntan a objetos dentro de todosAnfitriones o todosHuespedes,
    // así que no se hace delete sobre ellos aquí.
    cout << "Memoria liberada." << endl;
}

// --- Gestión principal y Menús ---

/**
 * @brief Método principal que contiene el bucle del menú y maneja la interacción del usuario.
 * Este método será bastante extenso y se desarrollará progresivamente.
 */
void GestorUdeaStay::ejecutar() {
    // TODO: Implementar el bucle principal del menú, login, y llamadas a funcionalidades.
    // Por ahora, un placeholder.
    cout << "Sistema UdeaStay ejecutándose (menú principal por implementar)." << endl;
    // Ejemplo de cómo se podría estructurar:
    // int opcionPrincipal = 0;
    // do {
    //     mostrarMenuPrincipal();
    //     cin >> opcionPrincipal;
    //     // ... manejar opcionPrincipal ...
    //         // Si login anfitrion es exitoso:
    //         // do {
    //         //    mostrarMenuAnfitrion();
    //         //    cin >> opcionAnfitrion;
    //         //    // ... manejar opcionAnfitrion ...
    //         //    // Aquí iría la opción de llamar a mostrarEstadoRecursosActual()
    //         // } while (opcionAnfitrion != SALIR_MENU_ANFITRION);
    //         // cerrarSesion();
    //
    //     // Limpiar buffer de cin si es necesario
    //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
    //
    // } while (opcionPrincipal != SALIR_DEL_SISTEMA);
}


// --- Carga y Guardado de Datos (Implementaciones iniciales/esqueletos) ---

/**
 * @brief Carga todos los datos iniciales del sistema desde los archivos CSV.
 * Llama a los métodos de carga individuales para cada tipo de entidad.
 */
void GestorUdeaStay::inicializarSistema() {
    cout << "Cargando datos del sistema..." << endl;
    // En orden, por si hay dependencias (aunque aquí no debería haber muchas directas)
    cargarAlojamientosDesdeArchivo();
    cargarAnfitrionesDesdeArchivo();
    cargarHuespedesDesdeArchivo();
    cargarReservacionesActivasDesdeArchivo();
    // No cargamos el histórico a memoria por defecto, solo se usa para añadir o consultar específicamente.
    cout << "Datos cargados." << endl;
}

/**
 * @brief Guarda los datos modificables del sistema en los archivos CSV.
 * Principalmente, guarda las reservaciones activas.
 * Los datos de alojamientos, anfitriones y huéspedes no se reescriben
 * según la decisión de no tener toFileString() y asumir que son estáticos post-carga.
 */
void GestorUdeaStay::finalizarSistema() const {
    cout << "Guardando datos modificados del sistema..." << endl;
    guardarReservacionesActivasEnArchivo();
    // No se guardan alojamientos, anfitriones, huéspedes porque se asumen estáticos post-carga.
    // Si esta lógica cambia (ej. puntuaciones actualizadas deben persistir), se añadirían aquí.
    cout << "Datos guardados." << endl;
}

// --- Implementaciones de los Métodos de Carga (Esqueletos) ---
// Estos se llenarán con la lógica de lectura de archivos y parseo de CSV.
int GestorUdeaStay::parsearLineaCSVInterno(const string& linea, string campos[], int numCamposEsperados) {
    incrementarContadorIteraciones(); // Contar la llamada a esta función de parseo

    stringstream ssLinea(linea);
    string segmento;
    int indiceCampo = 0;
    char caracter;
    string campoActual = "";
    bool dentroDeComillas = false;

    for (int i = 0; i < linea.length() && indiceCampo < numCamposEsperados; ++i) {
        incrementarContadorIteraciones(); // Por cada caracter procesado
        caracter = linea[i];

        if (caracter == '"') {
            // Si encontramos una comilla, verificamos si es una comilla de escape ("")
            // o el inicio/fin de un campo entrecomillado.
            if (dentroDeComillas && i + 1 < linea.length() && linea[i+1] == '"') {
                campoActual += '"'; // Es una comilla doble de escape, añadir una comilla simple
                i++; // Saltar la siguiente comilla
            } else {
                dentroDeComillas = !dentroDeComillas; // Cambiar estado de "dentro de comillas"
            }
        } else if (caracter == ',' && !dentroDeComillas) {
            // Si es una coma y no estamos dentro de comillas, es un delimitador
            if (indiceCampo < numCamposEsperados) {
                campos[indiceCampo++] = campoActual;
            }
            campoActual = ""; // Resetear para el siguiente campo
        } else {
            // Cualquier otro caracter se añade al campo actual
            campoActual += caracter;
        }
    }

    // Añadir el último campo si existe
    if (indiceCampo < numCamposEsperados && !campoActual.empty()) {
        campos[indiceCampo++] = campoActual;
    } else if (indiceCampo < numCamposEsperados && linea.back() == ',') {
        // Caso de un último campo vacío después de una coma
        campos[indiceCampo++] = "";
    }


    return indiceCampo; // Devuelve el número de campos efectivamente leídos
}

// --- Métodos de Carga de Datos ---
void GestorUdeaStay::cargarAlojamientosDesdeArchivo() {
    incrementarContadorIteraciones();
    ifstream archivo(archivoAlojamientos);
    string linea;

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de alojamientos: " << archivoAlojamientos << endl;
        return;
    }

    if (getline(archivo, linea)) { // Omitir cabecera
        incrementarContadorIteraciones();
    } else {
        cerr << "Error: Archivo de alojamientos vacío o cabecera ilegible." << endl;
        archivo.close();
        return;
    }

    const int NUM_CAMPOS = 9; // CodigoID,Nombre,Direccion,Depto,Mun,Tipo,Amen,Precio,AnfID
    string campos[NUM_CAMPOS];

    while (getline(archivo, linea)) {
        incrementarContadorIteraciones();
        if (linea.empty()) continue;

        int camposLeidos = parsearLineaCSVInterno(linea, campos, NUM_CAMPOS);

        if (camposLeidos == NUM_CAMPOS) {
            asegurarCapacidadAlojamientos();
            double precio;
            try {
                precio = stod(campos[7]);
                incrementarContadorIteraciones();
            } catch (const exception& e) {
                cerr << "Error al convertir precio en línea (Alojamiento): " << linea << ". Error: " << e.what() << endl;
                incrementarContadorIteraciones();
                continue;
            }
            todosAlojamientos[cantidadAlojamientos++] = Alojamiento(campos[0], campos[1], campos[2], campos[3], campos[4], campos[5], campos[6], precio, campos[8]);
            incrementarContadorIteraciones();
        } else {
            cerr << "Advertencia: Línea con formato incorrecto en alojamientos: " << linea << endl;
            incrementarContadorIteraciones();
        }
    }
    archivo.close();
    cout << "Alojamientos cargados: " << cantidadAlojamientos << endl;
}

void GestorUdeaStay::cargarAnfitrionesDesdeArchivo() {
    incrementarContadorIteraciones();
    ifstream archivo(archivoAnfitriones);
    string linea;

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de anfitriones: " << archivoAnfitriones << endl;
        return;
    }

    if (getline(archivo, linea)) { // Omitir cabecera
        incrementarContadorIteraciones();
    } else {
        cerr << "Error: Archivo de anfitriones vacío o cabecera ilegible." << endl;
        archivo.close();
        return;
    }

    const int NUM_CAMPOS = 6; // AnfitrionID,NombreCompleto,Documento,ContrasenaLogin,AntiguedadMeses,Puntuacion
    string campos[NUM_CAMPOS];

    while (getline(archivo, linea)) {
        incrementarContadorIteraciones();
        if (linea.empty()) continue;

        int camposLeidos = parsearLineaCSVInterno(linea, campos, NUM_CAMPOS);

        if (camposLeidos == NUM_CAMPOS) {
            asegurarCapacidadAnfitriones();
            int antiguedad;
            float puntuacion;
            try {
                antiguedad = stoi(campos[4]);
                puntuacion = stof(campos[5]);
                incrementarContadorIteraciones(2); // Dos conversiones
            } catch (const exception& e) {
                cerr << "Error al convertir datos numéricos en línea (Anfitrión): " << linea << ". Error: " << e.what() << endl;
                incrementarContadorIteraciones();
                continue;
            }
            // Asumiendo que Anfitrion tiene un constructor que toma: id, nombre, doc, clave, antig, punt
            todosAnfitriones[cantidadAnfitriones++] = Anfitrion(campos[0], campos[1], campos[2], campos[3], antiguedad, puntuacion);
            incrementarContadorIteraciones();
        } else {
            cerr << "Advertencia: Línea con formato incorrecto en anfitriones: " << linea << endl;
            incrementarContadorIteraciones();
        }
    }
    archivo.close();
    cout << "Anfitriones cargados: " << cantidadAnfitriones << endl;
}

void GestorUdeaStay::cargarHuespedesDesdeArchivo() {
    incrementarContadorIteraciones();
    ifstream archivo(archivoHuespedes);
    string linea;

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de huéspedes: " << archivoHuespedes << endl;
        return;
    }

    if (getline(archivo, linea)) { // Omitir cabecera
        incrementarContadorIteraciones();
    } else {
        cerr << "Error: Archivo de huéspedes vacío o cabecera ilegible." << endl;
        archivo.close();
        return;
    }

    const int NUM_CAMPOS = 6; // HuespedID,NombreCompleto,Documento,CredencialLogin,AntiguedadMeses,Puntuacion
    string campos[NUM_CAMPOS];

    while (getline(archivo, linea)) {
        incrementarContadorIteraciones();
        if (linea.empty()) continue;

        int camposLeidos = parsearLineaCSVInterno(linea, campos, NUM_CAMPOS);

        if (camposLeidos == NUM_CAMPOS) {
            asegurarCapacidadHuespedes();
            int antiguedad;
            float puntuacion;
            try {
                antiguedad = stoi(campos[4]);
                puntuacion = stof(campos[5]);
                incrementarContadorIteraciones(2);
            } catch (const exception& e) {
                cerr << "Error al convertir datos numéricos en línea (Huésped): " << linea << ". Error: " << e.what() << endl;
                incrementarContadorIteraciones();
                continue;
            }
            // Asumiendo que Huesped tiene un constructor que toma: id, nombre, doc, clave, antig, punt
            todosHuespedes[cantidadHuespedes++] = Huesped(campos[0], campos[1], campos[2], campos[3], antiguedad, puntuacion);
            incrementarContadorIteraciones();
        } else {
            cerr << "Advertencia: Línea con formato incorrecto en huéspedes: " << linea << endl;
            incrementarContadorIteraciones();
        }
    }
    archivo.close();
    cout << "Huéspedes cargados: " << cantidadHuespedes << endl;
}
void GestorUdeaStay::cargarReservacionesActivasDesdeArchivo() {
    incrementarContadorIteraciones();
    ifstream archivo(archivoReservaciones);
    string linea;

    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo de reservaciones: " << archivoReservaciones << endl;
        return;
    }

    if (!getline(archivo, linea) || linea.empty()) { // Omitir cabecera y verificar si el archivo está vacío después
        cerr << "Error: Archivo de reservaciones vacío o cabecera ilegible." << endl;
        archivo.close();
        return;
    }
    incrementarContadorIteraciones(); // Por leer la cabecera

    // Formato CSV esperado:
    // CodigoReservacion,CodigoAlojamiento,DocumentoHuesped,FechaEntrada,DuracionNoches,MetodoPago,FechaPago,MontoPagado,Anotaciones,Activa
    const int NUM_CAMPOS = 10;
    string campos[NUM_CAMPOS];

    while (getline(archivo, linea)) {
        incrementarContadorIteraciones(); // Por leer una línea de datos
        if (linea.empty()) continue; // Saltar líneas vacías

        int camposLeidos = parsearLineaCSVInterno(linea, campos, NUM_CAMPOS);

        if (camposLeidos == NUM_CAMPOS) {
            // Campos de string directos
            string codigoRes = campos[0];
            string codigoAloja = campos[1];
            string docHuesped = campos[2];
            string metodoPago = campos[5];
            string anotaciones = campos[8]; // El constructor de Reservacion maneja el truncamiento

            // Campos que necesitan conversión
            Fecha fechaEntrada;
            int duracionNoches;
            Fecha fechaPago;
            int montoPagado; // Basado en el constructor de Reservacion que usa 'int valortotal'
            bool activa;

            try {
                fechaEntrada = parsearStringAFechaInterno(campos[3]); // Usa el helper
                duracionNoches = stoi(campos[4]);
                fechaPago = parsearStringAFechaInterno(campos[6]);   // Usa el helper
                montoPagado = stoi(campos[7]); // Si es int, o stod si es double
                activa = (campos[9] == "1" || campos[9] == "true"); // Asumiendo 1/true para activa
                incrementarContadorIteraciones(3); // Por stoi, stoi/stod, y la comparación bool
            } catch (const std::exception& e) {
                cerr << "Error [GestorUdeaStay]: Error al convertir datos para reservación en línea: " << linea << ". Error: " << e.what() << endl;
                incrementarContadorIteraciones(); // Por manejo de excepción
                continue; // Saltar esta línea
            }

            // Solo cargar si la reservación está marcada como activa en el archivo
            if (activa) {
                asegurarCapacidadReservaciones(); // Llama al método de redimensionamiento

                // Crear el objeto Reservacion usando el constructor parametrizado
                // El constructor de Reservacion que me mostraste es:
                // Reservacion(cod, codigoAloja, docHues, metPago, entrada, duracionNoche, pago, valortotal, anot)
                // y 'activa' se establece a true internamente en ese constructor.
                todasReservaciones[cantidadReservaciones++] = Reservacion(
                    codigoRes, codigoAloja, docHuesped, metodoPago,
                    fechaEntrada, duracionNoches, fechaPago, montoPagado,
                    anotaciones
                    );
                incrementarContadorIteraciones(); // Por la creación y asignación del objeto
            } else {
                // Si la reservación en el archivo NO está activa, no la cargamos en la lista de activas.
                // Podría considerarse para cargarla directamente en una lista de históricas si fuera necesario aquí.
                incrementarContadorIteraciones(); // Por la decisión de no cargarla
            }
        } else {
            cerr << "Advertencia [GestorUdeaStay]: Línea con formato incorrecto en " << archivoReservaciones << ": " << linea
                 << " (Esperados " << NUM_CAMPOS << " campos, encontrados " << camposLeidos << ")" << endl;
            incrementarContadorIteraciones(); // Por el manejo de la línea incorrecta
        }
    }

    archivo.close();
    cout << "Reservaciones activas cargadas: " << cantidadReservaciones << endl;
}
void GestorUdeaStay::guardarReservacionesActivasEnArchivo() const {
    // TODO: Abrir archivoReservaciones en modo escritura, iterar por todasReservaciones,
    //       llamar a Reservacion::toFileString() (¡DEBE EXISTIR!) y escribir la línea.
    cout << "Guardando reservaciones activas (por implementar)..." << endl;
}

void GestorUdeaStay::agregarReservacionAHistoricoEnArchivo(const Reservacion& reservacion) const {
    // TODO: Abrir archivoHistorico en modo append (añadir),
    //       llamar a reservacion.toFileString() y escribir la línea.
    cout << "Agregando reservación al histórico (por implementar)..." << endl;
}


// --- Implementaciones de los Métodos de Redimensionamiento (Esqueletos) ---
// Estos manejarán el crecimiento de los arreglos dinámicos.

void GestorUdeaStay::asegurarCapacidadAlojamientos() {
    // Incrementar contador de iteraciones por la llamada a esta función de gestión
    incrementarContadorIteraciones();

    if (cupoAlojamientos == 0) { // Primera vez que se añade algo, el arreglo no existe
        cupoAlojamientos = 10; // Establecer un cupo inicial (puedes ajustar este número)
        todosAlojamientos = new Alojamiento[cupoAlojamientos];
        // Incrementar iteraciones por la creación del arreglo (considera N iteraciones si hay un bucle implícito o coste)
        // Aquí es más un coste de asignación. Para ser simple, una iteración por la lógica.
        incrementarContadorIteraciones();
    } else if (cantidadAlojamientos == cupoAlojamientos) { // Arreglo lleno, necesita redimensionar
        int nuevoCupo = cupoAlojamientos * 2;
        Alojamiento* nuevoArreglo = new Alojamiento[nuevoCupo];
        incrementarContadorIteraciones(); // Por la asignación del nuevo arreglo

        for (int i = 0; i < cantidadAlojamientos; ++i) {
            nuevoArreglo[i] = todosAlojamientos[i]; // Se usa el operador de asignación de Alojamiento
            incrementarContadorIteraciones(); // Por cada copia de elemento
        }

        delete[] todosAlojamientos; // Liberar memoria del arreglo antiguo
        todosAlojamientos = nuevoArreglo; // Apuntar al nuevo arreglo
        cupoAlojamientos = nuevoCupo;     // Actualizar el cupo
        // No se incrementan iteraciones por delete o asignación de puntero, ya contamos la creación y copia.
    }
}
void GestorUdeaStay::asegurarCapacidadAnfitriones() {
    incrementarContadorIteraciones();

    if (cupoAnfitriones == 0) {
        cupoAnfitriones = 10; // Cupo inicial
        todosAnfitriones = new Anfitrion[cupoAnfitriones];
        incrementarContadorIteraciones();
    } else if (cantidadAnfitriones == cupoAnfitriones) {
        int nuevoCupo = cupoAnfitriones * 2;
        Anfitrion* nuevoArreglo = new Anfitrion[nuevoCupo];
        incrementarContadorIteraciones();

        for (int i = 0; i < cantidadAnfitriones; ++i) {
            nuevoArreglo[i] = todosAnfitriones[i]; // Copia usando el operador= de Anfitrion
            incrementarContadorIteraciones();
        }

        delete[] todosAnfitriones;
        todosAnfitriones = nuevoArreglo;
        cupoAnfitriones = nuevoCupo;
    }
}

void GestorUdeaStay::asegurarCapacidadHuespedes() {
    incrementarContadorIteraciones();

    if (cupoHuespedes == 0) {
        cupoHuespedes = 10; // Cupo inicial
        todosHuespedes = new Huesped[cupoHuespedes];
        incrementarContadorIteraciones();
    } else if (cantidadHuespedes == cupoHuespedes) {
        int nuevoCupo = cupoHuespedes * 2;
        Huesped* nuevoArreglo = new Huesped[nuevoCupo];
        incrementarContadorIteraciones();

        for (int i = 0; i < cantidadHuespedes; ++i) {
            nuevoArreglo[i] = todosHuespedes[i]; // Copia usando el operador= de Huesped
            incrementarContadorIteraciones();
        }

        delete[] todosHuespedes;
        todosHuespedes = nuevoArreglo;
        cupoHuespedes = nuevoCupo;
    }
}
void GestorUdeaStay::asegurarCapacidadReservaciones() {
    incrementarContadorIteraciones();

    if (cupoReservaciones == 0) {
        cupoReservaciones = 10; // Cupo inicial
        todasReservaciones = new Reservacion[cupoReservaciones];
        incrementarContadorIteraciones();
    } else if (cantidadReservaciones == cupoReservaciones) {
        int nuevoCupo = cupoReservaciones * 2;
        Reservacion* nuevoArreglo = new Reservacion[nuevoCupo];
        incrementarContadorIteraciones();

        for (int i = 0; i < cantidadReservaciones; ++i) {
            nuevoArreglo[i] = todasReservaciones[i]; // Copia usando el operador= de Reservacion
            incrementarContadorIteraciones();
        }

        delete[] todasReservaciones;
        todasReservaciones = nuevoArreglo;
        cupoReservaciones = nuevoCupo;
    }
}
void GestorUdeaStay::mostrarEstadoRecursosActual() const {
    cout << "\n--- Estado Actual de Recursos ---" << endl;
    cout << "Iteraciones acumuladas: " << contadorIteracionesGlobal << endl;

    size_t memoriaTotalObjetos = 0;
    // Cálculo de memoria (aproximación basada en cantidad de objetos)
    if (todosAlojamientos != nullptr) {
        memoriaTotalObjetos += (size_t)cantidadAlojamientos * sizeof(Alojamiento);
    }
    if (todosAnfitriones != nullptr) {
        memoriaTotalObjetos += (size_t)cantidadAnfitriones * sizeof(Anfitrion);
        // Si Anfitrion tiene arreglos dinámicos internos (ej. codigosAlojamiento),
        // se debería sumar también esa memoria aquí iterando por cada anfitrión.
        // for (int i = 0; i < cantidadAnfitriones; ++i) {
        //    memoriaTotalObjetos += todosAnfitriones[i].getMemoriaInternaDinamica(); // Método hipotético
        // }
    }
    if (todosHuespedes != nullptr) {
        memoriaTotalObjetos += (size_t)cantidadHuespedes * sizeof(Huesped);
        // Similar para Huesped si tiene arreglos dinámicos internos (codigosDeSusReservaciones)
    }
    if (todosReservaciones != nullptr) {
        memoriaTotalObjetos += (size_t)cantidadReservaciones * sizeof(Reservacion);
    }

    cout << "Memoria aproximada por objetos principales en colecciones: " << memoriaTotalObjetos << " bytes" << endl;
    cout << "Nota: Esta es una estimación y no incluye toda la memoria dinámica (ej. std::string, arreglos internos de objetos)." << endl;
    cout << "---------------------------------\n" << endl;
}
/**
 * @brief Incrementa el contador global de iteraciones.
 * Es llamado por otros métodos del gestor cuando realizan operaciones significativas.
 * @param cantidad Número de iteraciones a sumar (por defecto 1).
 */
void GestorUdeaStay::incrementarContadorIteraciones(unsigned long long cantidad) {
    contadorIteracionesGlobal += cantidad;
}


// TODO: Implementar el resto de los métodos declarados en GestorUdeaStay.h
// (Login, búsquedas, crear reserva, anular, actualizar histórico, etc.)
