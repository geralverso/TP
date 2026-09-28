//
// Created by PC on 27/09/2026.
//

#ifndef EJERCICIO02_RESUELTO_POR_MI_FUNCIONES_H
#define EJERCICIO02_RESUELTO_POR_MI_FUNCIONES_H

#define CAPACIDAD_ALUMNOS 10
#define CAPACIDAD_NOTAS 15
#define CAPACIDAD_CONSULTAS 15

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

void cargarAlumnosCSV(const char* nombreArchivo, int *codigosAlumnos, int *ciclosAlumnos, int &numAlumnos);

void cargarNotasCSV(const char* nombreArchivo, int *codigosNotas, double *notas, int &numNotas);

void cargarConsultasTXT(const char* nombreArchivo, int *codigosConsultas, int &numConsultas);

int buscarPosAlumnoConsultasEnAlumnosCSV(int *codigosAlumnos, int codAlumnoBuscado, int numAlumnos);

int calcularCantidadNotas(int *codigosNotas, int codigoAlumnoBuscado, int numNotas);

void generarReporte(const char *nombreArchivo, int *codigosAlumnos, int *ciclosAlumnos, int numAlumnos,
    int *codigosNotas, double *notas, int numNotas, int *codigosConsultas, int numConsultas);

#endif //EJERCICIO02_RESUELTO_POR_MI_FUNCIONES_H
