// --- main_prueba_fecha.cpp ---
// Archivo para probar la funcionalidad de la clase Fecha.

#include <iostream> // Para std::cout, std::endl, std::boolalpha
#include "Fecha.h"  // La clase que vamos a probar

// Usamos el namespace std para cout, endl, etc. en este archivo de prueba.
using namespace std;

// Función auxiliar para imprimir un separador visual
void imprimirSeparador(const string& titulo = "") {
    cout << "\n--- " << titulo << " ---" << endl;
}

int main() {
    cout << boolalpha; // Para que los booleanos se impriman como "true" o "false"

    imprimirSeparador("PRUEBAS DE CONSTRUCTORES Y toString()");
    Fecha f1; // Constructor por defecto
    Fecha f2(21, 5, 2025); // Fecha específica (¡hoy!)
    Fecha f3(29, 2, 2024); // Año bisiesto
    Fecha f4(29, 2, 2023); // Año no bisiesto (debería ajustarse o marcar error en constructor)
    Fecha f5(31, 12, 2022);
    Fecha fInvalida(32, 1, 2023); // Fecha inválida

    cout << "Fecha f1 (por defecto): " << f1.toString() << endl;
    cout << "Fecha f2 (21/05/2025): " << f2.toString() << endl;
    cout << "Fecha f3 (29/02/2024 - bisiesto): " << f3.toString() << endl;
    cout << "Fecha f4 (29/02/2023 - no bisiesto, constructor debería corregir): " << f4.toString() << endl;
    cout << "Fecha f5 (31/12/2022): " << f5.toString() << endl;
    cout << "Fecha fInvalida (32/01/2023, constructor debería corregir): " << fInvalida.toString() << endl;

    imprimirSeparador("PRUEBAS DE GETTERS");
    cout << "Getter f2: Dia=" << f2.getDia() << ", Mes=" << f2.getMes() << ", Anio=" << f2.getAnio() << endl;

    imprimirSeparador("PRUEBAS DE SETTERS");
    Fecha fParaSetters(1, 1, 2023);
    cout << "fParaSetters inicial: " << fParaSetters.toString() << endl;
    cout << "setDia(15): " << fParaSetters.setDia(15) << " -> " << fParaSetters.toString() << endl;
    cout << "setMes(6): " << fParaSetters.setMes(6) << " -> " << fParaSetters.toString() << endl;
    cout << "setAnio(2024): " << fParaSetters.setAnio(2024) << " -> " << fParaSetters.toString() << endl;
    cout << "setDia(31) (válido para Junio): " << fParaSetters.setDia(30) << " -> " << fParaSetters.toString() << endl;
    cout << "setDia(31) (inválido para Junio 2024): " << fParaSetters.setDia(31) << " -> " << fParaSetters.toString() << endl;
    cout << "setFecha(29, 2, 2024) (bisiesto): " << fParaSetters.setFecha(29, 2, 2024) << " -> " << fParaSetters.toString() << endl;
    cout << "setFecha(29, 2, 2025) (no bisiesto): " << fParaSetters.setFecha(29, 2, 2025) << " -> " << fParaSetters.toString() << endl;


    imprimirSeparador("PRUEBAS DE toStringFormatoLargo()");
    cout << "f1: " << f1.toStringFormatoLargo() << endl;
    cout << "f2 (21/05/2025): " << f2.toStringFormatoLargo() << endl;
    cout << "f3 (29/02/2024): " << f3.toStringFormatoLargo() << endl;
    cout << "Fecha (15/08/2023): " << Fecha(15,8,2023).toStringFormatoLargo() << endl;
    cout << "Fecha (01/01/2000): " << Fecha(1,1,2000).toStringFormatoLargo() << endl; // Sábado
    cout << "Fecha (06/01/1992): " << Fecha(6,1,1992).toStringFormatoLargo() << endl; // Lunes

    imprimirSeparador("PRUEBAS DE COMPARACIÓN (esMenor, esIgual, esMayorOIgual)");
    Fecha comp1(10, 5, 2025);
    Fecha comp2(21, 5, 2025); // f2
    Fecha comp3(10, 5, 2025); // igual a comp1

    cout << comp1.toString() << " esMenor que " << comp2.toString() << ": " << comp1.esMenor(comp2) << endl; // true
    cout << comp2.toString() << " esMenor que " << comp1.toString() << ": " << comp2.esMenor(comp1) << endl; // false
    cout << comp1.toString() << " esMenor que " << comp3.toString() << ": " << comp1.esMenor(comp3) << endl; // false

    cout << comp1.toString() << " esIgual que " << comp2.toString() << ": " << comp1.esIgual(comp2) << endl; // false
    cout << comp1.toString() << " esIgual que " << comp3.toString() << ": " << comp1.esIgual(comp3) << endl; // true

    cout << comp1.toString() << " esMayorOIgual que " << comp2.toString() << ": " << comp1.esMayorOIgual(comp2) << endl; // false
    cout << comp2.toString() << " esMayorOIgual que " << comp1.toString() << ": " << comp2.esMayorOIgual(comp1) << endl; // true
    cout << comp1.toString() << " esMayorOIgual que " << comp3.toString() << ": " << comp1.esMayorOIgual(comp3) << endl; // true

    imprimirSeparador("PRUEBAS DE calcularFechaMasDuracion()");
    Fecha baseSuma(25, 2, 2024); // Bisiesto
    cout << "Fecha base: " << baseSuma.toStringFormatoLargo() << endl;
    cout << "+ 3 noches: " << baseSuma.calcularFechaMasDuracion(3).toStringFormatoLargo() << endl;   // Debería ser 28/02/2024
    cout << "+ 5 noches: " << baseSuma.calcularFechaMasDuracion(5).toStringFormatoLargo() << endl;   // Debería ser 01/03/2024

    Fecha baseSuma2(25, 12, 2023);
    cout << "Fecha base: " << baseSuma2.toStringFormatoLargo() << endl;
    cout << "+ 10 noches: " << baseSuma2.calcularFechaMasDuracion(10).toStringFormatoLargo() << endl; // Debería ser 04/01/2024

    Fecha baseSuma3(1,1,2024);
    cout << "Fecha base: " << baseSuma3.toStringFormatoLargo() << endl;
    cout << "+ 365 noches (año no bisiesto a bisiesto): " << baseSuma3.calcularFechaMasDuracion(365).toStringFormatoLargo() << endl; // Debería ser 31/12/2024
    cout << "+ 366 noches: " << baseSuma3.calcularFechaMasDuracion(366).toStringFormatoLargo() << endl; // Debería ser 01/01/2025

    Fecha inicioAnio(1,1,2023);
    cout << "Fecha base: " << inicioAnio.toStringFormatoLargo() << endl;
    cout << "+ 59 noches (a fin de Feb no bisiesto): " << inicioAnio.calcularFechaMasDuracion(58).toStringFormatoLargo() << endl; // Debería ser 28/02/2023
    cout << "+ 60 noches (a inicio de Mar no bisiesto): " << inicioAnio.calcularFechaMasDuracion(59).toStringFormatoLargo() << endl; // Debería ser 01/03/2023


    imprimirSeparador("PRUEBAS DE fechaEnRango()");
    Fecha rangoInicio(1, 6, 2025);
    Fecha rangoFin(15, 6, 2025);
    Fecha dentro(10, 6, 2025);
    Fecha antes(20, 5, 2025);
    Fecha despues(20, 6, 2025);

    cout << "Rango: [" << rangoInicio.toString() << " - " << rangoFin.toString() << "]" << endl;
    cout << dentro.toString() << " en rango: " << dentro.fechaEnRango(rangoInicio, rangoFin) << endl;   // true
    cout << antes.toString() << " en rango: " << antes.fechaEnRango(rangoInicio, rangoFin) << endl;    // false
    cout << despues.toString() << " en rango: " << despues.fechaEnRango(rangoInicio, rangoFin) << endl; // false
    cout << rangoInicio.toString() << " en rango (límite inferior): " << rangoInicio.fechaEnRango(rangoInicio, rangoFin) << endl; // true
    cout << rangoFin.toString() << " en rango (límite superior): " << rangoFin.fechaEnRango(rangoInicio, rangoFin) << endl;       // true

    imprimirSeparador("PRUEBAS ADICIONALES calcularNombreDiaSemana()");
    // Puedes añadir más fechas específicas aquí si quieres verificar el cálculo del día.
    Fecha diaEspecifico1(25, 12, 2023); // Lunes
    Fecha diaEspecifico2(4, 7, 1776);   // Jueves (Declaración Independencia USA)
    cout << diaEspecifico1.toStringFormatoLargo() << endl;
    cout << diaEspecifico2.toStringFormatoLargo() << endl;


    cout << "\n--- FIN DE LAS PRUEBAS ---" << endl;
    return 0;
}
