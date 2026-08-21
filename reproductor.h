#pragma once

#include <string>
#include <vector>

// Representa una cancion del catalogo de Sonora.
struct Cancion {
    std::string titulo;
    std::string artista;
    std::string genero;
    int duracion_segundos;
    int reproducciones;
    double calificacion;
};

/**
 * Imprime los datos principales de una cancion en una sola linea.
 *
 * @param cancion Cancion a mostrar.
 */
void mostrar_cancion(Cancion& cancion);

/**
 * Suma una reproduccion al contador de la cancion recibida.
 *
 * @param cancion Cancion cuyo contador de reproducciones se incrementa.
 */
void registrar_reproduccion(Cancion& cancion);

/**
 * Clasifica una cancion segun su numero de reproducciones.
 *
 * @param reproducciones Numero de reproducciones de la cancion.
 * @return "Viral", "Popular", "Emergente" o "Nueva" segun el umbral que alcance.
 */
std::string clasificar_por_reproducciones(int reproducciones);

/**
 * Decide si una cancion es recomendable segun sus reproducciones y calificacion.
 *
 * @param reproducciones Numero de reproducciones de la cancion.
 * @param calificacion Calificacion de la cancion (0.0 a 5.0).
 * @return true si reproducciones > 50000 y calificacion > 4.0.
 */
bool es_recomendable(int reproducciones, double calificacion);

/**
 * Interpreta una calificacion entera de 1 a 5 como una etiqueta de texto.
 *
 * @param calificacion_redondeada Calificacion entera (1 a 5).
 * @return Etiqueta de texto, o "Calificacion invalida" fuera de ese rango.
 */
std::string interpretar_calificacion(int calificacion_redondeada);

// --- Arreglos estaticos y ciclos ---
// reproducciones_semana[7] guarda el total de reproducciones del catalogo
// completo para cada dia (0 = Lunes, 6 = Domingo). nombres_dias[7] guarda
// el nombre de cada dia, en el mismo orden.

/**
 * Imprime las reproducciones de cada dia de la semana.
 *
 * @param reproducciones_semana Arreglo con 7 posiciones, una por dia.
 * @param nombres_dias Arreglo con el nombre de cada dia, en el mismo orden.
 */
void mostrar_reproducciones_semana(int reproducciones_semana[7], std::string nombres_dias[7]);

/**
 * Calcula que porcentaje del total semanal representa cada dia.
 *
 * @param reproducciones_semana Arreglo con las reproducciones de cada dia.
 * @param porcentajes Arreglo de salida donde se guarda el porcentaje de cada dia.
 */
void calcular_porcentaje_diario(int reproducciones_semana[7], double porcentajes[7]);

/**
 * Suma las reproducciones de los 7 dias de la semana.
 *
 * @param reproducciones_semana Arreglo con las reproducciones de cada dia.
 * @return Total de reproducciones de la semana.
 */
int sumar_reproducciones_semana(int reproducciones_semana[7]);

/**
 * Calcula el promedio diario de reproducciones de la semana.
 *
 * @param reproducciones_semana Arreglo con las reproducciones de cada dia.
 * @return Promedio de reproducciones por dia.
 */
double promedio_reproducciones_semana(int reproducciones_semana[7]);

/**
 * Cuenta cuantos dias superaron un umbral de reproducciones.
 *
 * @param reproducciones_semana Arreglo con las reproducciones de cada dia.
 * @param umbral Numero minimo de reproducciones para considerarse un dia pico.
 * @return Cantidad de dias que superaron el umbral.
 */
int contar_dias_pico(int reproducciones_semana[7], int umbral);

/**
 * Filtra los nombres de los dias que superaron un umbral de reproducciones.
 *
 * @param reproducciones_semana Arreglo con las reproducciones de cada dia.
 * @param nombres_dias Arreglo con el nombre de cada dia (mismo orden que reproducciones_semana).
 * @param umbral Numero minimo de reproducciones para considerarse un dia pico.
 * @return Vector con los nombres de los dias que superaron el umbral.
 */
std::vector<std::string> filtrar_dias_pico(
    int reproducciones_semana[7], std::string nombres_dias[7], int umbral);
