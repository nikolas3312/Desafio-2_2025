// --- main_prueba_alojamiento.cpp ---
// Archivo para probar la funcionalidad de la clase Alojamiento.

#include <iostream> // Para std::cout, std::endl, std::fixed, std::boolalpha
#include <string>   // Para std::string
#include <iomanip>  // Para std::setprecision (usado internamente por Alojamiento)
#include "Alojamiento.h" // La clase que vamos a probar

// Usamos el namespace std para cout, endl, etc. en este archivo de prueba.
using namespace std;

// Función auxiliar para imprimir un separador visual
void imprimirSeparador(const string& titulo = "") {
    cout << "\n--- " << titulo << " ---" << endl;
}

int main() {
    cout << boolalpha; // Para que los booleanos se impriman como "true" o "false"
    // Asegura que los doubles se impriman con punto decimal y no en notación científica
    cout << fixed << setprecision(2);

    imprimirSeparador("PRUEBAS DE CONSTRUCTORES Y mostrarDetalles()");

    // Prueba 1: Constructor por defecto
    cout << "Alojamiento 1 (por defecto):" << endl;
    Alojamiento al1;
    al1.mostrarDetalles();
    cout << "toFileString: " << al1.toFileString() << endl;

    // Prueba 2: Constructor con parámetros (datos válidos)
    imprimirSeparador("Alojamiento 2 (con parámetros válidos)");
    Alojamiento al2("AL001", "Cabaña El Mirador", "Vereda Las Nubes Km 2",
                    "Antioquia", "Guatape", "Casa",
                    "Piscina;WiFi;Aire Acondicionado;Parqueadero", 350000.00, "ANF001");
    al2.mostrarDetalles();
    cout << "toFileString: " << al2.toFileString() << endl;

    // Prueba 3: Constructor con algunos datos potencialmente problemáticos (precio negativo)
    imprimirSeparador("Alojamiento 3 (con precio negativo)");
    Alojamiento al3("AL002", "Apartamento Económico", "Calle Falsa 123",
                    "Cundinamarca", "Bogota", "Apartamento",
                    "WiFi", -150000.00, "ANF002"); // Precio negativo
    al3.mostrarDetalles(); // El constructor debería haber corregido el precio a 0.0
    cout << "toFileString: " << al3.toFileString() << endl;

    // Prueba 4: Constructor con strings vacíos (para ver advertencias)
    imprimirSeparador("Alojamiento 4 (con strings vacíos)");
    Alojamiento al4("", "", "Direccion X",
                    "Valle", "Cali", "Apartamento",
                    "", 100000.00, "");
    al4.mostrarDetalles();
    cout << "toFileString: " << al4.toFileString() << endl;


    imprimirSeparador("PRUEBAS DE GETTERS (usando al2)");
    cout << "ID: " << al2.getCodigoID() << endl;
    cout << "Nombre: " << al2.getNombre() << endl;
    cout << "Direccion: " << al2.getDireccion() << endl;
    cout << "Departamento: " << al2.getDepartamento() << endl;
    cout << "Municipio: " << al2.getMunicipio() << endl;
    cout << "Tipo: " << al2.getTipoAlojamiento() << endl;
    cout << "Amenidades: " << al2.getAmenidades() << endl;
    cout << "Precio/Noche: " << al2.getPrecioPorNoche() << endl;
    cout << "ID Anfitrión: " << al2.getAnfitrionResponsableID() << endl;

    imprimirSeparador("PRUEBAS DE SETTERS (usando al1)");
    cout << "al1 antes de setters:" << endl;
    al1.mostrarDetalles();

    al1.setNombre("Villa Serena Actualizada");
    al1.setDireccion("Carrera Principal # 10-20");
    al1.setDepartamento("Santander");
    al1.setMunicipio("Barichara");
    al1.setTipoAlojamiento("Casa");
    al1.setAmenidades("WiFi;Piscina Privada;Jardín");
    al1.setPrecioPorNoche(450000.00);
    // No hay setters para codigoID ni anfitrionResponsableID según nuestro diseño actual en Alojamiento.h

    cout << "\nal1 después de setters:" << endl;
    al1.mostrarDetalles();
    cout << "toFileString actualizado: " << al1.toFileString() << endl;

    // Prueba de setters con valores "inválidos" (según la lógica de Alojamiento.cpp)
    imprimirSeparador("Prueba de setters con valores 'inválidos' en al1");
    al1.setNombre(""); // Intento de poner nombre vacío
    al1.setPrecioPorNoche(-50.0); // Intento de poner precio negativo
    cout << "\nal1 después de intentos de set inválidos:" << endl;
    al1.mostrarDetalles(); // Debería mostrar advertencias y no cambiar los valores


    imprimirSeparador("PRUEBA ADICIONAL toFileString con comillas (simulando nombre con coma)");
    Alojamiento alConComa("ALC01", "Casa Grande, Con Jardín", "Calle Sol #1, Apto 2",
                          "Bolivar", "Cartagena", "Casa",
                          "Aire;Ventilador", 500000.00, "ANF00X");
    cout << "toFileString para alConComa: " << alConComa.toFileString() << endl;
    // La salida debería tener "Casa Grande, Con Jardín" y "Calle Sol #1, Apto 2" entre comillas dobles.

    cout << "\n--- FIN DE LAS PRUEBAS DE ALOJAMIENTO ---" << endl;
    return 0;
}
