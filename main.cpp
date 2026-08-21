#include "reproductor.h"

#include <iostream>
#include <vector>

// ---------------------------------------------------------------------------
// Plantilla para las funciones de prueba de esta guia.
//
// Cada vez que un ejercicio te pida "prueba tal función", agrega una función
// nueva aqui arriba, con este mismo patron, y en main() comenta la llamada a
// iniciar_sonora() y descomenta la llamada a tu función de prueba.
//
// Estas funciones de prueba no van al header (reproductor.h): son solo para
// este ejercicio, para probar un concepto de forma aislada. En un programa
// real no existirian, por eso viven solo aqui, en main.cpp.
//
// void prueba_ejemplo() {
//     int reproducciones_semana[7] = {12000, 8500, 15300, 9800, 22000, 31000, 18500};
//     std::string nombres_dias[7] = {
//         "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"
//     };
//     mostrar_reproducciones_semana(reproducciones_semana, nombres_dias);
// }
// ---------------------------------------------------------------------------

// Todo el menu de Sonora vive aqui, en una funcion aparte de main().
void iniciar_sonora() {
    std::vector<Cancion> catalogo = {
        {"La Gota Fria", "Carlos Vives", "Vallenato", 245, 1250000, 4.6},
        {"La Rebelion", "Joe Arroyo", "Salsa", 260, 82000, 4.2},
        {"Rio", "Bomba Estereo", "Electronica", 210, 15300, 3.8},
    };

    // Arreglo estatico con las reproducciones del catalogo por dia,
    // y un arreglo paralelo con el nombre de cada dia. Ver seccion 1.
    int reproducciones_semana[7] = {12000, 8500, 15300, 9800, 22000, 31000, 18500};
    std::string nombres_dias[7] = {
        "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado", "Domingo"
    };

    bool ejecutando = true;
    while (ejecutando) {
        std::cout << "\n=== Sonora ===\n";
        std::cout << "1. Mostrar catalogo\n";
        std::cout << "2. Registrar una reproduccion\n";
        std::cout << "3. Clasificar una cancion por reproducciones\n";
        std::cout << "4. Ver si una cancion es recomendable\n";
        std::cout << "5. Interpretar una calificacion (1 a 5)\n";
        std::cout << "6. Mostrar reproducciones de la semana\n";
        std::cout << "7. Ver porcentaje de reproducciones por dia\n";
        std::cout << "8. Ver total y promedio semanal\n";
        std::cout << "9. Contar dias pico\n";
        std::cout << "10. Ver dias pico\n";
        std::cout << "11. Salir\n";
        std::cout << "Elige una opcion: ";

        int opcion = 0;
        std::cin >> opcion;

        switch (opcion) {
            case 1:
                for (Cancion& cancion : catalogo) {
                    mostrar_cancion(cancion);
                }
                break;
            case 2:
                std::cout << "Antes: " << catalogo[0].reproducciones << "\n";
                registrar_reproduccion(catalogo[0]);
                std::cout << "Despues: " << catalogo[0].reproducciones << "\n";
                break;
            case 3:
                for (Cancion& cancion : catalogo) {
                    std::cout << cancion.titulo << ": "
                               << clasificar_por_reproducciones(cancion.reproducciones)
                               << "\n";
                }
                break;
            case 4:
                for (Cancion& cancion : catalogo) {
                    bool recomendable = es_recomendable(cancion.reproducciones, cancion.calificacion);
                    std::cout << cancion.titulo << ": "
                               << (recomendable ? "Recomendable" : "No recomendable")
                               << "\n";
                }
                break;
            case 5: {
                std::cout << "Ingresa una calificacion entera de 1 a 5: ";
                int calificacion_ingresada = 0;
                std::cin >> calificacion_ingresada;
                std::cout << interpretar_calificacion(calificacion_ingresada) << "\n";
                break;
            }
            // case 6:
            //     // Se descomenta en la seccion 2 (recorrer con ciclo definido)
            //     mostrar_reproducciones_semana(reproducciones_semana, nombres_dias);
            //     break;
            // case 7: {
            //     // Se descomenta en la seccion 3 (transformacion)
            //     double porcentajes[7];
            //     calcular_porcentaje_diario(reproducciones_semana, porcentajes);
            //     for (int dia = 0; dia < 7; dia++) {
            //         std::cout << nombres_dias[dia] << ": " << porcentajes[dia] << "%\n";
            //     }
            //     break;
            // }
            // case 8:
            //     // Se descomenta en la seccion 4 (acumulacion)
            //     std::cout << "Total: " << sumar_reproducciones_semana(reproducciones_semana) << "\n";
            //     std::cout << "Promedio: " << promedio_reproducciones_semana(reproducciones_semana) << "\n";
            //     break;
            // case 9: {
            //     // Se descomenta en la seccion 5 (conteo); la validacion con
            //     // while del umbral se agrega en la seccion 7 (ciclos indefinidos)
            //     std::cout << "Ingresa el umbral de reproducciones: ";
            //     int umbral = 0;
            //     std::cin >> umbral;
            //     std::cout << "Dias pico: " << contar_dias_pico(reproducciones_semana, umbral) << "\n";
            //     break;
            // }
            // case 10: {
            //     // Se descomenta en la seccion 6 (filtrado); la validacion con
            //     // while del umbral se agrega en la seccion 7 (ciclos indefinidos)
            //     std::cout << "Ingresa el umbral de reproducciones: ";
            //     int umbral = 0;
            //     std::cin >> umbral;
            //     std::vector<std::string> dias_pico = filtrar_dias_pico(reproducciones_semana, nombres_dias, umbral);
            //     for (std::string& dia : dias_pico) {
            //         std::cout << dia << "\n";
            //     }
            //     break;
            // }
            case 11:
                ejecutando = false;
                break;
            default:
                std::cout << "Opcion invalida.\n";
                break;
        }
    }

    std::cout << "Hasta pronto.\n";
}

int main() {
    iniciar_sonora();
    // prueba_ejemplo();
    return 0;
}
