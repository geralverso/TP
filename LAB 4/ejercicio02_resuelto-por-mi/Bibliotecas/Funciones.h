//
// Created by PC on 2/10/2026.
//

#ifndef EJERCICIO02_RESUELTO_POR_MI_FUNCIONES_H
#define EJERCICIO02_RESUELTO_POR_MI_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define ANCHO 54
#define CAPACIDAD_ALUMNOS 50
#define CAPACIDAD_NOTAS 250

void cargarAlumnosCSV(const char *nombre, int *codigosAlumnos, int *ciclosAlumnos, int &numAlumnos);

void cargarAlumnosEDITADO(const char *nombre, int *codigosAlumnos, char *nombresAlumnos, int *ciclosAlumnos,
    int &numAlumnosEDITADO);

void cargarNotasCSV(const char *nombre, int *codigosAlumnosNotas, double *notasAlumnosNotas, int &numNotas);

void encabezado(ofstream &salida);

void encabezado2(ofstream &salida);

double calcularPromedioDeNotas(double *notasAlumnosNotas, int numNotas, int *codigosAlumnosNotas, int codigoBuscado);

void armarArregloPromediosNotas(int numAlumnos, int *codigosAlumnos, double *promedios, double *notasAlumnosNotas,
    int numNotas, int *codigosAlumnosNotas);

void generarReporte(const char *nombre, int *codigosAlumnos, int *ciclosAlumnos, int numAlumnos, double *promedios);

void generarReporte2(const char *nombre, int *codigosAlumnos, char *nombresAlumnos, int *ciclosAlumnos,
    int numAlumnosEDITADO, int *codigosAlumnosNotas, double *notasAlumnosNotas, int numNotas);


//---------------------FUNCIONES DE ORDENAMIENTO

void intercambiarDouble(double &a, double &b);
void intercambiarInt(int &a, int &b);

//ORDENAR POR PROMEDIOS
void ordenarPorPromediosPorIntercambio(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos);
void ordenarPorPromediosPorSeleccion(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos);
void ordenarPorPromediosPorBubble(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos);

//ORDENAR POR CICLO
void ordenarPorCicloPorIntercambio(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos);
void ordenarPorCicloPorSeleccion(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos);
void ordenarPorCicloPorBubble(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos);

//ORDENAR POR PROMEDIO Y CICLO AL MISMO TIEMPO
void ordenarPromediosyCiclosPorBubble(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos);
void ordenarPromediosyCiclosPorSeleccion(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos);
void ordenarPromediosyCiclosPorIntercambio(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos);

#endif //EJERCICIO02_RESUELTO_POR_MI_FUNCIONES_H
