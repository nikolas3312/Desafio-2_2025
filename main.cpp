
// --- main_prueba_gestor.cpp ---
#include <iostream>
#include <string>
#include <limits> // Para limpiar el buffer de cin
#include "GestorUdeaStay.h" // Tu clase principal
#include "Fecha.h"          // Para crear objetos Fecha para las pruebas


using namespace std;

// Función para limpiar el buffer de entrada después de leer con cin >>
void limpiarBufferEntrada() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Función para mostrar un menú simple y obtener una opción
int mostrarMenuLogueo() {
    int opcion;
    cout << "\n--- UdeaStay - Menú Principal ---" << endl;
    cout << "1. Iniciar Sesión como Anfitrión" << endl;
    cout << "2. Iniciar Sesión como Huésped" << endl;
    cout << "3. Ver Estado de Recursos (Global)" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opción: ";
    cin >> opcion;
    limpiarBufferEntrada();
    return opcion;
}

int mostrarMenuAnfitrion(const Anfitrion* anfitrion) {
    int opcion;
    cout << "\n--- Menú Anfitrión: " << anfitrion->getNombre() << " ---" << endl; // Necesitas Anfitrion::getNombre()
    cout << "1. Actualizar Archivo Histórico" << endl;
    cout << "2. Ver Estado de Recursos" << endl;
    // TODO: Añadir más opciones de anfitrión aquí (ej. Consultar sus reservaciones)
    cout << "0. Cerrar Sesión" << endl;
    cout << "Seleccione una opción: ";
    cin >> opcion;
    limpiarBufferEntrada();
    return opcion;
}

int mostrarMenuHuesped(const Huesped* huesped) {
    int opcion;
    cout << "\n--- Menú Huésped: " << huesped->getNombre() << " ---" << endl; // Necesitas Huesped::getNombre()
    cout << "1. Ver Estado de Recursos" << endl;
    // TODO: Añadir más opciones de huésped aquí (ej. Buscar alojamiento, Crear reserva, Anular reserva)
    cout << "0. Cerrar Sesión" << endl;
    cout << "Seleccione una opción: ";
    cin >> opcion;
    limpiarBufferEntrada();
    return opcion;
}


int main() {

    cout << "Creando instancia de GestorUdeaStay..." << endl;
    GestorUdeaStay gestor; // Esto llamará al constructor y a inicializarSistema()
    cout << "Instancia de GestorUdeaStay creada y datos iniciales cargados." << endl;

    // Pequeña prueba de mostrar recursos al inicio
    gestor.mostrarEstadoRecursosActual();

    int opcionPrincipal;
    do {
        opcionPrincipal = mostrarMenuLogueo();
        string idLogin, contrasena;

        switch (opcionPrincipal) {
        case 1: // Iniciar Sesión Anfitrión
            cout << "Ingrese ID de Anfitrión: ";
            getline(cin, idLogin); // Usar el ID de login, no el documento, según lo último que hablamos
            cout << "Ingrese Contraseña: ";
            getline(cin, contrasena);
            if (gestor.intentarLoginAnfitrion(idLogin, contrasena)) {
                cout << "Login de Anfitrión exitoso!" << endl;
                gestor.incrementarContadorIteraciones(); // Por la operación de login
                int opcionAnfitrion;
                do {
                    opcionAnfitrion = mostrarMenuAnfitrion(gestor.getAnfitrionActual());
                    switch (opcionAnfitrion) {
                    case 1: { // Actualizar Histórico
                        int dia, mes, anio;
                        cout << "Ingrese fecha de corte (dd mm aaaa): ";
                        cin >> dia >> mes >> anio;
                        limpiarBufferEntrada();
                        Fecha fechaCorte(dia, mes, anio);
                        if (fechaCorte.getDia() == 0) { // Asumiendo que Fecha() por defecto es inválida o 0
                            cout << "Fecha de corte inválida." << endl;
                        } else {
                            gestor.actualizarArchivoHistorico(fechaCorte);
                        }
                        gestor.incrementarContadorIteraciones(); // Por la operación
                        break;
                    }
                    case 2: // Ver Estado de Recursos
                        gestor.mostrarEstadoRecursosActual();
                        break;
                    case 0: // Cerrar Sesión
                        gestor.cerrarSesion();
                        cout << "Sesión de Anfitrión cerrada." << endl;
                        break;
                    default:
                        cout << "Opción no válida." << endl;
                        break;
                    }
                } while (opcionAnfitrion != 0);
            } else {
                cout << "Login de Anfitrión fallido. Verifique ID y/o contraseña." << endl;
                gestor.incrementarContadorIteraciones(); // Contar intento fallido
            }
            break;

        case 2: // Iniciar Sesión Huésped
            cout << "Ingrese ID de Huésped: ";
            getline(cin, idLogin);
            cout << "Ingrese Contraseña: ";
            getline(cin, contrasena);
            if (gestor.intentarLoginHuesped(idLogin, contrasena)) {
                cout << "Login de Huésped exitoso!" << endl;
                gestor.incrementarContadorIteraciones();
                int opcionHuesped;
                do {
                    opcionHuesped = mostrarMenuHuesped(gestor.getHuespedActual());
                    switch (opcionHuesped) {
                    case 1: // Ver Estado de Recursos
                        gestor.mostrarEstadoRecursosActual();
                        break;
                    case 0: // Cerrar Sesión
                        gestor.cerrarSesion();
                        cout << "Sesión de Huésped cerrada." << endl;
                        break;
                    default:
                        cout << "Opción no válida." << endl;
                        break;
                    }
                } while (opcionHuesped != 0);
            } else {
                cout << "Login de Huésped fallido. Verifique ID y/o contraseña." << endl;
                gestor.incrementarContadorIteraciones();
            }
            break;

        case 3: // Ver Estado de Recursos (Global)
            gestor.mostrarEstadoRecursosActual();
            break;

        case 0: // Salir
            cout << "Saliendo del sistema UdeaStay..." << endl;
            break;

        default:
            cout << "Opción principal no válida. Intente de nuevo." << endl;
            break;
        }
        cout << endl;

    } while (opcionPrincipal != 0);

    // Al salir del main, el destructor de 'gestor' se llamará automáticamente,
    // el cual llama a finalizarSistema() para guardar datos.
    cout << "Programa finalizado." << endl;
    return 0;
}
