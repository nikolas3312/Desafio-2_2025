// --- main_prueba_login.cpp ---
#include <iostream>
#include <string>
#include <limits>
#include "GestorUdeaStay.h" // Tu clase principal

using namespace std;

void limpiarBufferEntrada() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    cout << "Creando instancia de GestorUdeaStay..." << endl;
    GestorUdeaStay gestor; // Llama al constructor y a inicializarSistema()
        // Asegúrate que los cout de depuración estén activos en tus métodos de carga.
    cout << "Instancia creada y datos iniciales (se supone) cargados." << endl;

    // --- PASO 1 de Depuración: Inspeccionar Datos Cargados ---
    // Descomenta la siguiente línea si implementaste inspeccionarDatosCargadosParaDebug()
    // gestor.inspeccionarDatosCargadosParaDebug();
    // O revisa la salida de los cout que pusiste directamente en los métodos de carga.

    cout << "\n--- PRUEBA DE LOGIN ANFITRIÓN ---" << endl;
    string idAnfitrionPrueba = "ANF001"; // El ID que sabes que debe funcionar
    string passAnfitrionPrueba = "carlos024"; // La contraseña correcta

    cout << "Intentando login para Anfitrión ID: [" << idAnfitrionPrueba
         << "] con Pass: [" << passAnfitrionPrueba << "]" << endl;

    if (gestor.intentarLoginAnfitrion(idAnfitrionPrueba, passAnfitrionPrueba)) {
        cout << "RESULTADO PRUEBA: Login de Anfitrión [" << idAnfitrionPrueba << "] EXITOSO." << endl;
        if (gestor.getAnfitrionActual() != nullptr) {
            cout << "Anfitrión logueado: " << gestor.getAnfitrionActual()->getNombre() << endl;
        }
        gestor.cerrarSesion(); // Cerrar sesión para la siguiente prueba
    } else {
        cout << "RESULTADO PRUEBA: Login de Anfitrión [" << idAnfitrionPrueba << "] FALLIDO." << endl;
    }

    cout << "\n--- PRUEBA DE LOGIN HUÉSPED ---" << endl;
    string idHuespedPrueba = "HUE001"; // El ID que sabes que debe funcionar
    string passHuespedPrueba = "maria2025"; // La contraseña correcta (revisa tu CSV Huespedes)
        // En el huesped.cpp que me pasaste, el toFileString no incluía la contraseña.
        // Asegúrate que la contraseña se carga y se obtiene con getContrasena().

    cout << "Intentando login para Huésped ID: [" << idHuespedPrueba
         << "] con Pass: [" << passHuespedPrueba << "]" << endl;

    if (gestor.intentarLoginHuesped(idHuespedPrueba, passHuespedPrueba)) {
        cout << "RESULTADO PRUEBA: Login de Huésped [" << idHuespedPrueba << "] EXITOSO." << endl;
        if (gestor.getHuespedActual() != nullptr) {
            cout << "Huésped logueado: " << gestor.getHuespedActual()->getNombre() << endl;
        }
        gestor.cerrarSesion();
    } else {
        cout << "RESULTADO PRUEBA: Login de Huésped [" << idHuespedPrueba << "] FALLIDO." << endl;
    }

    cout << "\n--- PRUEBA DE LOGIN CON CREDENCIALES INCORRECTAS (ANFITRIÓN) ---" << endl;
    idAnfitrionPrueba = "ANF001";
    passAnfitrionPrueba = "contrasenaincorrecta";
    cout << "Intentando login para Anfitrión ID: [" << idAnfitrionPrueba
         << "] con Pass: [" << passAnfitrionPrueba << "]" << endl;
    if (gestor.intentarLoginAnfitrion(idAnfitrionPrueba, passAnfitrionPrueba)) {
        cout << "ERROR EN PRUEBA: Login de Anfitrión con pass incorrecta fue EXITOSO (no debería)." << endl;
        gestor.cerrarSesion();
    } else {
        cout << "RESULTADO PRUEBA: Login de Anfitrión con pass incorrecta FALLIDO (esperado)." << endl;
    }

    cout << "\n--- PRUEBA DE LOGIN CON ID INCORRECTO (ANFITRIÓN) ---" << endl;
    idAnfitrionPrueba = "ID_INEXISTENTE";
    passAnfitrionPrueba = "carlos024";
    cout << "Intentando login para Anfitrión ID: [" << idAnfitrionPrueba
         << "] con Pass: [" << passAnfitrionPrueba << "]" << endl;
    if (gestor.intentarLoginAnfitrion(idAnfitrionPrueba, passAnfitrionPrueba)) {
        cout << "ERROR EN PRUEBA: Login de Anfitrión con ID incorrecto fue EXITOSO (no debería)." << endl;
        gestor.cerrarSesion();
    } else {
        cout << "RESULTADO PRUEBA: Login de Anfitrión con ID incorrecto FALLIDO (esperado)." << endl;
    }

    cout << "\n--- Fin de las Pruebas de Login ---" << endl;

    // Al salir, el destructor de gestor se llamará y guardará datos.
    return 0;
}
