// --- GestorUdeaStay.cpp ---
// Implementación de la clase GestorUdeaStay, el núcleo del sistema UdeaStay.
#include "GestorUdeaStay.h"
#include <iostream>     // Para std::cout, std::cin, std::endl
#include <fstream>      // Para std::ifstream, std::ofstream (manejo de archivos)
#include <sstream>      // Para std::istringstream, std::ostringstream (parseo de líneas)
#include <string>       // Para std::string, std::getline
#include <limits>       // Para std::numeric_limits (limpiar buffer de cin)
#include <algorithm>    // Para std::remove si se usa para limpiar strings (opcional)
#include <cctype>
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
// --- Funciones de Ayuda Estáticas para Trimming ---
// Estas funciones operan directamente sobre el string (in-place)

// Recorta espacios del inicio (in-place)
static inline std::string& ltrim(std::string& s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
                return !std::isspace(ch);
            }));
    return s;
}

// Recorta espacios del final (in-place)
static inline std::string& rtrim(std::string& s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
                return !std::isspace(ch);
            }).base(), s.end());
    return s;
}

// Recorta espacios de ambos lados (in-place)
static inline std::string& trim(std::string& s) {
    return ltrim(rtrim(s));
}
// --- Fin Funciones de Trimming ---
void GestorUdeaStay::inspeccionarDatosCargadosParaDebug()  {
    cout << "\n--- DEBUG: Inspección de Datos Cargados ---" << endl;
    incrementarContadorIteraciones(); // Si este método es const y el contador no es mutable, esta línea daría error.
        // Para depuración, puedes quitar const de este método o hacer mutable el contador.
        // O no contar iteraciones aquí.

    cout << "\n--- Anfitriones en Memoria (" << cantidadAnfitriones << ") ---" << endl;
    for (int i = 0; i < cantidadAnfitriones; ++i) {
        // Asumiendo que Anfitrion tiene getId() y getContrasena()
        cout << "Índice " << i << ": ID=[" << todosAnfitriones[i].getId() << "], Pass=[" << todosAnfitriones[i].getContrasena()
             << "], Nombre=[" << todosAnfitriones[i].getNombre() << "]" << endl;
    }

    cout << "\n--- Huéspedes en Memoria (" << cantidadHuespedes << ") ---" << endl;
    for (int i = 0; i < cantidadHuespedes; ++i) {
        // Asumiendo que Huesped tiene getId() y getContrasena()
        cout << "Índice " << i << ": ID=[" << todosHuespedes[i].getId() << "], Pass=[" << todosHuespedes[i].getContrasena()
             << "], Nombre=[" << todosHuespedes[i].getNombre() << "]" << endl;
    }
    cout << "--- Fin Inspección ---" << endl;
}
// --- Gestión principal y Menús ---
void limpiarBufferEntrada() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void GestorUdeaStay::manejarMenuAnfitrion() {
    int opcion = -1;
    do {
        cout << "\n--- Menú Anfitrión: " << anfitrionLogueado->getNombre() << " ---" << endl;
        cout << "1. Actualizar archivo histórico" << endl;
        cout << "2. Consultar mis reservaciones" << endl; // Por implementar
        cout << "3. Anular una reservación" << endl;       // Por implementar
        cout << "4. Ver estado de recursos" << endl;
        cout << "0. Cerrar Sesión" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (cin.fail()) {
            cout << "Entrada inválida. Por favor ingrese un número." << endl;
            cin.clear();
            opcion = -1; // Resetear opción para evitar bucle infinito
        }
        limpiarBufferEntrada();

        switch (opcion) {
        case 1: { // Actualizar Histórico
            cout << "--- Actualizar Histórico ---" << endl;
            int dia, mes, anio;
            cout << "Ingrese la fecha de corte (formato dd mm aaaa): ";
            cin >> dia >> mes >> anio;
            limpiarBufferEntrada();

            Fecha fechaCorte(dia, mes, anio);
            // Asumiendo que el constructor de Fecha maneja la validez
            actualizarArchivoHistorico(fechaCorte);
            incrementarContadorIteraciones();
            break;
        }
        case 2:
            cout << "Funcionalidad 'Consultar mis reservaciones' por implementar." << endl;
            // Aquí iría la llamada a mostrarReservacionesDelAnfitrion(...)
            break;
        case 3:
            cout << "Funcionalidad 'Anular una reservación' por implementar." << endl;
            // Aquí iría la llamada a cancelarUnaReservacion(...)
            break;
        case 4:
            mostrarEstadoRecursosActual();
            break;
        case 0:
            cerrarSesion();
            cout << "Sesión de Anfitrión cerrada." << endl;
            break;
        default:
            cout << "Opción no válida. Intente de nuevo." << endl;
            break;
        }
    } while (opcion != 0);
}
void GestorUdeaStay::manejarMenuHuesped() {
    int opcion = -1;
    do {
        cout << "\n--- Menú Huésped: " << huespedLogueado->getNombre() << " ---" << endl;
        cout << "1. Buscar alojamiento disponible" << endl; // Por implementar
        cout << "2. Crear nueva reservación por código" << endl; // Por implementar
        cout << "3. Anular una de mis reservaciones" << endl;  // Por implementar
        cout << "4. Ver estado de recursos" << endl;
        cout << "0. Cerrar Sesión" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;

        if (cin.fail()) {
            cout << "Entrada inválida. Por favor ingrese un número." << endl;
            cin.clear();
            opcion = -1;
        }
        limpiarBufferEntrada();

        switch (opcion) {
        case 1:
            cout << "Funcionalidad 'Buscar alojamiento disponible' por implementar." << endl;
            // Aquí iría la llamada a mostrarAlojamientosDisponibles(...)
            break;
        case 2:
            cout << "Funcionalidad 'Crear nueva reservación por código' por implementar." << endl;
            // Aquí iría la llamada a crearNuevaReservacion(...)
            break;
        case 3:
            cout << "Funcionalidad 'Anular una de mis reservaciones' por implementar." << endl;
            // Aquí iría la llamada a cancelarUnaReservacion(...)
            break;
        case 4:
            mostrarEstadoRecursosActual();
            break;
        case 0:
            cerrarSesion();
            cout << "Sesión de Huésped cerrada." << endl;
            break;
        default:
            cout << "Opción no válida. Intente de nuevo." << endl;
            break;
        }
    } while (opcion != 0);
}
/**
 * @brief Método principal que contiene el bucle del menú y maneja la interacción del usuario.
 * Este método será bastante extenso y se desarrollará progresivamente.
 */
void GestorUdeaStay::ejecutar() {
    int opcionPrincipal = -1;
    do {
        cout << "\n--- UdeaStay - Menú Principal ---" << endl;
        cout << "1. Iniciar Sesión como Anfitrión" << endl;
        cout << "2. Iniciar Sesión como Huésped" << endl;
        cout << "3. Ver Estado de Recursos (Global)" << endl;
        cout << "0. Salir del sistema" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcionPrincipal;

        if (cin.fail()) {
            cout << "Entrada inválida. Por favor ingrese un número." << endl;
            cin.clear();
            opcionPrincipal = -1; // Resetear opción para evitar bucle infinito
        }
        limpiarBufferEntrada(); // Limpiar el buffer después de leer un número

        string id, contrasena;
        switch (opcionPrincipal) {
        case 1: // Login Anfitrión
            cout << "Ingrese ID de Anfitrión: ";
            getline(cin, id);
            cout << "Ingrese Contraseña: ";
            getline(cin, contrasena);
            if (intentarLoginAnfitrion(id, contrasena)) {
                cout << "Login de Anfitrión exitoso." << endl;
                manejarMenuAnfitrion(); // Llama al menú específico
            } else {
                cout << "Login de Anfitrión fallido. Verifique ID y/o contraseña." << endl;
            }
            break;
        case 2: // Login Huésped
            cout << "Ingrese ID de Huésped: ";
            getline(cin, id);
            cout << "Ingrese Contraseña: ";
            getline(cin, contrasena);
            if (intentarLoginHuesped(id, contrasena)) {
                cout << "Login de Huésped exitoso." << endl;
                manejarMenuHuesped(); // Llama al menú específico
            } else {
                cout << "Login de Huésped fallido. Verifique ID y/o contraseña." << endl;
            }
            break;
        case 3: // Ver Recursos
            mostrarEstadoRecursosActual();
            break;
        case 0: // Salir
            cout << "Saliendo del sistema..." << endl;
            break;
        default:
            cout << "Opción no válida. Intente de nuevo." << endl;
            break;
        }
        cout << endl;
    } while (opcionPrincipal != 0);
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
void GestorUdeaStay::finalizarSistema()  {
    cout << "Guardando datos modificados del sistema..." << endl;
    guardarReservacionesActivasEnArchivo();
    // No se guardan alojamientos, anfitriones, huéspedes porque se asumen estáticos post-carga.
    // Si esta lógica cambia (ej. puntuaciones actualizadas deben persistir), se añadirían aquí.
    cout << "Datos guardados." << endl;
}
Fecha GestorUdeaStay::parsearStringAFechaInterno(const string& strFecha) {
    incrementarContadorIteraciones();

    if (strFecha.length() != 10 || strFecha[2] != '/' || strFecha[5] != '/') {
        cerr << "Error [GestorUdeaStay]: Formato de fecha inválido '" << strFecha << "'. Se esperaba dd/mm/aaaa." << endl;
        return Fecha();
    }
    try {
        int dia = stoi(strFecha.substr(0, 2));
        int mes = stoi(strFecha.substr(3, 2));
        int anio = stoi(strFecha.substr(6, 4));
        incrementarContadorIteraciones(3);

        Fecha fechaObtenida(dia, mes, anio);
        return fechaObtenida;
    } catch (const std::exception& e) {
        cerr << "Error [GestorUdeaStay]: Excepción al convertir string a fecha '" << strFecha << "'. Error: " << e.what() << endl;
        incrementarContadorIteraciones();
        return Fecha();
    }
}

/**
 * Parsea una línea de texto en formato CSV.
 * Divide la línea en campos basados en el delimitador ',',
 * manejando campos que están encerrados entre comillas dobles
 * y eliminando espacios en blanco al inicio/final de cada campo.
 */
int GestorUdeaStay::parsearLineaCSVInterno(const string& linea, string campos[], int numCamposEsperados) {
    incrementarContadorIteraciones();

    if (linea.empty()) {
        return 0;
    }

    int indiceCampo = 0;
    string campoActual = "";
    bool dentroDeComillas = false;

    for (size_t i = 0; i < linea.length(); ++i) { // Usar size_t para 'i'
        incrementarContadorIteraciones();
        char caracter = linea[i];

        if (caracter == '"') {
            if (dentroDeComillas && i + 1 < linea.length() && linea[i+1] == '"') {
                campoActual += '"';
                i++;
            } else {
                dentroDeComillas = !dentroDeComillas;
            }
        } else if (caracter == ',' && !dentroDeComillas) {
            if (indiceCampo < numCamposEsperados) {
                string campoProcesado = campoActual; // Copia para hacer trim
                campos[indiceCampo++] = trim(campoProcesado);
            } else {
                // Se encontraron más comas de las esperadas para los campos, podría ser un error
                // o simplemente ignorar el resto de la línea.
                // Por ahora, si ya llenamos numCamposEsperados, paramos.
                break;
            }
            campoActual = "";
        } else {
            campoActual += caracter;
        }
    }

    // Añadir el último campo
    if (indiceCampo < numCamposEsperados) {
        string campoProcesado = campoActual; // Copia para hacer trim
        campos[indiceCampo++] = trim(campoProcesado);
    }

    return indiceCampo;
}
Huesped* GestorUdeaStay::encontrarHuespedPorID(const std::string& idLogin) {
    cout << "DEBUG_BUSQUEDA_HUE: Iniciando encontrarHuespedPorID..." << endl;
    cout << "  ID Buscado: [" << idLogin << "] (Longitud: " << idLogin.length() << ")" << endl;
    for (int i = 0; i < cantidadHuespedes; ++i) {
        // incrementarContadorIteraciones(); // Comentado porque es método const
        std::string idEnMemoria = todosHuespedes[i].getId(); // Usa el getter
        cout << "    Comparando con Huésped en memoria (Índice " << i << ") ID: [" << idEnMemoria << "] (Longitud: " << idEnMemoria.length() << ")" << endl;
        if (idEnMemoria == idLogin) {
            cout << "    ¡ID de Huésped Coincide en Índice " << i << "!" << endl;
            return &todosHuespedes[i];
        }
    }
    cout << "  ID de Huésped [" << idLogin << "] NO encontrado en la colección." << endl;
    return nullptr;
}
Anfitrion* GestorUdeaStay::encontrarAnfitrionPorID(const std::string& idLogin)  {
    cout << "DEBUG_BUSQUEDA_ANF: Iniciando encontrarAnfitrionPorID..." << endl;
    cout << "  ID Buscado: [" << idLogin << "] (Longitud: " << idLogin.length() << ")" << endl;
    for (int i = 0; i < cantidadAnfitriones; ++i) {
        incrementarContadorIteraciones(); // Si necesitas contar iteraciones
        std::string idEnMemoria = todosAnfitriones[i].getId();
        cout << "    Comparando con Anfitrion en memoria (Índice " << i << ") ID: [" << idEnMemoria << "] (Longitud: " << idEnMemoria.length() << ")" << endl;
        if (idEnMemoria == idLogin) {
            cout << "    ¡ID de Anfitrion Coincide en Índice " << i << "!" << endl;
            return &todosAnfitriones[i];
        }
    }
    cout << "  ID de Anfitrion [" << idLogin << "] NO encontrado en la colección." << endl;
    return nullptr;
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
                incrementarContadorIteraciones(2);
            } catch (const exception& e) {
                cerr << "Error al convertir datos numéricos en línea (Anfitrión): " << linea << ". Error: " << e.what() << endl;
                incrementarContadorIteraciones();
                continue;
            }

            // --- AGREGAR BLOQUE DE DEPURACIÓN ANTES DE INCREMENTAR cantidadAnfitriones ---
            cout << "DEBUG_CARGA_ANF: Procesando línea CSV para Anfitrión." << endl;
            cout << "  CSV Raw -> ID: [" << campos[0] << "], PassLeidaCSV: [" << campos[3] << "]" << endl;

            // Crear el objeto primero
            todosAnfitriones[cantidadAnfitriones] = Anfitrion(campos[0], campos[1], campos[2], campos[3], antiguedad, puntuacion);

            // Luego depurar el objeto creado
            Anfitrion& anfitrionActual = todosAnfitriones[cantidadAnfitriones];
            cout << "  OBJETO Anfitrion Creado -> ID via Getter: [" << anfitrionActual.getId()
                 << "], Pass via Getter: [" << anfitrionActual.getContrasena()
                 << "], Nombre via Getter: [" << anfitrionActual.getNombre() << "]" << endl;
            // --- FIN BLOQUE DEPURACIÓN ---

            cantidadAnfitriones++; // Incrementar después de la depuración
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

            // --- INICIO BLOQUE DEPURACIÓN CARGA HUÉSPED ---
            cout << "DEBUG_CARGA_HUE: Procesando línea CSV para Huésped." << endl;
            cout << "  CSV Raw -> ID: [" << campos[0] << "], PassLeidaCSV: [" << campos[3] << "]" << endl;
            // --- FIN BLOQUE DEPURACIÓN CARGA HUÉSPED ---

            // Asumiendo que Huesped tiene un constructor que toma: id, nombre, doc, clave, antig, punt
            todosHuespedes[cantidadHuespedes++] = Huesped(campos[0], campos[1], campos[2], campos[3], antiguedad, puntuacion);

            // --- INICIO BLOQUE DEPURACIÓN VERIFICACIÓN OBJETO ---
            // Verifica el objeto recién añadido (accediendo a cantidadHuespedes-1)
            cout << "  OBJETO Huésped Creado -> ID via Getter: [" << todosHuespedes[cantidadHuespedes-1].getId()
                 << "], Pass via Getter: [" << todosHuespedes[cantidadHuespedes-1].getContrasena() << "]" << endl;
            // --- FIN BLOQUE DEPURACIÓN VERIFICACIÓN OBJETO ---

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
void GestorUdeaStay::guardarReservacionesActivasEnArchivo()  {
    incrementarContadorIteraciones();
    ofstream archivo(archivoReservaciones);

    if (!archivo.is_open()) {
        cerr << "Error [GestorUdeaStay]: No se pudo abrir el archivo '" << archivoReservaciones
             << "' para guardar las reservaciones activas." << endl;
        incrementarContadorIteraciones();
        return;
    }

    archivo << "CodigoReservacion,CodigoAlojamiento,DocumentoHuesped,FechaEntrada,DuracionNoches,MetodoPago,FechaPago,MontoPagado,Anotaciones,Activa\n";
    incrementarContadorIteraciones();

    for (int i = 0; i < cantidadReservaciones; ++i) {
        incrementarContadorIteraciones();
        archivo << todasReservaciones[i].toFileString() << "\n";
        incrementarContadorIteraciones();
    }

    archivo.close();
}

void GestorUdeaStay::agregarReservacionAHistoricoEnArchivo(const Reservacion& reservacion) {
    incrementarContadorIteraciones();
    ofstream archivo(archivoHistorico, ios::app);

    if (!archivo.is_open()) {
        cerr << "Error [GestorUdeaStay]: No se pudo abrir o crear el archivo histórico '"
             << archivoHistorico << "' para añadir la reservación." << endl;
        incrementarContadorIteraciones();
        return;
    }
    // Asumiendo que Reservacion tiene el método toFileString() implementado por tu compañero
    archivo << reservacion.toFileString() << "\n";
    incrementarContadorIteraciones();

    archivo.close();
}
bool GestorUdeaStay::actualizarArchivoHistorico(Fecha fechaCorte) {
    incrementarContadorIteraciones();

    if (cantidadReservaciones == 0) {
        cout << "No hay reservaciones activas para procesar." << endl;
        return true;
    }

    Reservacion* nuevasReservacionesActivas = nullptr;
    int nuevaCantidadActivas = 0;
    int nuevoCupoActivas = cupoReservaciones;

    if (nuevoCupoActivas > 0) {
        nuevasReservacionesActivas = new Reservacion[nuevoCupoActivas];
        incrementarContadorIteraciones();
    } else {
        cout << "No hay reservaciones activas (cupo 0)." << endl;
        return true;
    }

    int movidasAlHistorico = 0;

    for (int i = 0; i < cantidadReservaciones; ++i) {
        incrementarContadorIteraciones();

        Fecha fechaSalida = todasReservaciones[i].getFechaSalida();
        incrementarContadorIteraciones();

        if (fechaSalida.esMenor(fechaCorte)) {
            agregarReservacionAHistoricoEnArchivo(todasReservaciones[i]);
            movidasAlHistorico++;
            incrementarContadorIteraciones();
        } else {
            if (nuevasReservacionesActivas != nullptr) {
                nuevasReservacionesActivas[nuevaCantidadActivas++] = todasReservaciones[i];
            }
            incrementarContadorIteraciones();
        }
    }

    delete[] todasReservaciones;
    incrementarContadorIteraciones();

    todasReservaciones = nuevasReservacionesActivas;
    cantidadReservaciones = nuevaCantidadActivas;
    cupoReservaciones = nuevoCupoActivas;

    cout << movidasAlHistorico << " reservaciones han sido movidas al archivo histórico." << endl;
    cout << cantidadReservaciones << " reservaciones permanecen activas." << endl;

    return true;
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
    if (todasReservaciones != nullptr) {
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


//LOGIN

bool GestorUdeaStay::intentarLoginAnfitrion(const string &idLogin, const string &contrasenaIngresada) {
    incrementarContadorIteraciones();
    cout << "DEBUG_LOGIN_ANF: Iniciando intentarLoginAnfitrion..." << endl;
    cout << "  ID Ingresado: [" << idLogin << "], Pass Ingresada: [" << contrasenaIngresada << "]" << endl;

    Anfitrion* anfitrionEncontrado = encontrarAnfitrionPorID(idLogin);

    if (anfitrionEncontrado != nullptr) {
        cout << "  Anfitrion con ID [" << idLogin << "] encontrado. Verificando contraseña..." << endl;
        std::string passAlmacenada = anfitrionEncontrado->getContrasena();
        cout << "    Pass Ingresada por Usuario: [" << contrasenaIngresada << "] (Longitud: " << contrasenaIngresada.length() << ")" << endl;
        cout << "    Pass Almacenada en Objeto: [" << passAlmacenada << "] (Longitud: " << passAlmacenada.length() << ")" << endl;

        if (passAlmacenada == contrasenaIngresada) {
            anfitrionLogueado = anfitrionEncontrado;
            cout << "    ¡Contraseña CORRECTA! Login exitoso." << endl;
            return true;
        } else {
            cout << "    Contraseña INCORRECTA." << endl;
            return false;
        }
    }
    // El mensaje de "NO encontrado" ya salió de encontrarAnfitrionPorID si es nullptr
    cout << "  Login FALLIDO: Anfitrión con ID [" << idLogin << "] no encontrado (reportado por intentarLoginAnfitrion)." << endl;
    return false;
}


bool GestorUdeaStay::intentarLoginHuesped(const string &idLogin, const string &contrasenaIngresada) {
    incrementarContadorIteraciones();
    cout << "DEBUG_LOGIN_HUE: Iniciando intentarLoginHuesped..." << endl;
    cout << "  ID Ingresado: [" << idLogin << "], Pass Ingresada: [" << contrasenaIngresada << "]" << endl;

    Huesped* huespedEncontrado = encontrarHuespedPorID(idLogin);

    if (huespedEncontrado != nullptr) {
        cout << "  Huésped con ID [" << idLogin << "] encontrado. Verificando contraseña..." << endl;
        std::string passAlmacenada = huespedEncontrado->getContrasena(); // Usa el getter
        cout << "    Pass Ingresada por Usuario: [" << contrasenaIngresada << "] (Longitud: " << contrasenaIngresada.length() << ")" << endl;
        cout << "    Pass Almacenada en Objeto: [" << passAlmacenada << "] (Longitud: " << passAlmacenada.length() << ")" << endl;

        if (passAlmacenada == contrasenaIngresada) {
            huespedLogueado = huespedEncontrado;
            cout << "    ¡Contraseña CORRECTA! Login exitoso." << endl;
            return true;
        } else {
            cout << "    Contraseña INCORRECTA." << endl;
            return false;
        }
    }
    cout << "  Login FALLIDO: Huésped con ID [" << idLogin << "] no encontrado (reportado por intentarLoginHuesped)." << endl;
    return false;
}
void GestorUdeaStay::cerrarSesion() {
    anfitrionLogueado = nullptr;
    huespedLogueado = nullptr;
}

bool GestorUdeaStay::haySesionHuespedActiva() const {
    return huespedLogueado != nullptr;
}

const Anfitrion* GestorUdeaStay::getAnfitrionActual() const {
    return anfitrionLogueado;
}

const Huesped* GestorUdeaStay::getHuespedActual() const {
    return huespedLogueado;
}

// TODO: Implementar el resto de los métodos declarados en GestorUdeaStay.h
// (Login, búsquedas, crear reserva, anular, actualizar histórico, etc.)
