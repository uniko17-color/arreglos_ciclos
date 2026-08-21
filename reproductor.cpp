#include "reproductor.h"

#include <iostream>

void mostrar_cancion(Cancion& cancion) {
    std::cout << cancion.titulo << " - " << cancion.artista
               << " (" << cancion.genero << ", "
               << cancion.reproducciones << " reproducciones)" << std::endl;
}

void registrar_reproduccion(Cancion& cancion) {
    cancion.reproducciones = cancion.reproducciones + 1;
}

std::string clasificar_por_reproducciones(int reproducciones) {
    if (reproducciones >= 1000000) {
        return "Viral";
    } else if (reproducciones >= 100000) {
        return "Popular";
    } else if (reproducciones >= 10000) {
        return "Emergente";
    } else {
        return "Nueva";
    }
}

bool es_recomendable(int reproducciones, double calificacion) {
    return reproducciones > 50000 && calificacion > 4.0;
}

std::string interpretar_calificacion(int calificacion_redondeada) {
    switch (calificacion_redondeada) {
        case 5:
            return "Excelente";
        case 4:
            return "Buena";
        case 3:
            return "Regular";
        case 2:
            return "Baja";
        case 1:
            return "Muy baja";
        default:
            return "Calificacion invalida";
    }
}

// TODO: recorre reproducciones_semana y nombres_dias con un ciclo for clasico
// (dia = 0; dia < 7; dia++) e imprime "nombre_dia: reproducciones" por cada dia.
// Ver seccion 2 (Recorrer un arreglo con un ciclo definido).
void mostrar_reproducciones_semana(int reproducciones_semana[7], std::string nombres_dias[7]) {

}

// TODO: calcula el total con sumar_reproducciones_semana, y llena porcentajes[dia]
// con (reproducciones_semana[dia] * 100.0) / total para cada dia.
// Ver seccion 3 (Transformacion).
void calcular_porcentaje_diario(int reproducciones_semana[7], double porcentajes[7]) {

}

// TODO: acumula la suma de las 7 posiciones en una variable inicializada en 0.
// Ver seccion 4 (Acumulacion).
int sumar_reproducciones_semana(int reproducciones_semana[7]) {
    return 0;
}

// TODO: reutiliza sumar_reproducciones_semana y divide entre 7.0 (no entre 7).
// Ver seccion 4 (Acumulacion).
double promedio_reproducciones_semana(int reproducciones_semana[7]) {
    return 0;
}

// TODO: recorre el arreglo y suma 1 a un contador (inicializado en 0) cada vez
// que reproducciones_semana[dia] > umbral.
// Ver seccion 5 (Conteo).
int contar_dias_pico(int reproducciones_semana[7], int umbral) {
    return 0;
}

// TODO: declara un std::vector<std::string> vacio y agrega con push_back el
// nombre de cada dia donde reproducciones_semana[dia] > umbral.
// Ver seccion 6 (Filtrado).
std::vector<std::string> filtrar_dias_pico(
    int reproducciones_semana[7], std::string nombres_dias[7], int umbral) {
    return {};
}
