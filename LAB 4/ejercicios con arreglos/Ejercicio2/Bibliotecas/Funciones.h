//
// Created by PC on 25/09/2026.
//

#ifndef EJERCICIO2_FUNCIONES_H
#define EJERCICIO2_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define ANCHO_REPORTE 75
#define CAPACIDAD_TEORIA 300
#define CAPACIDAD_PRACTICA 300

void cargarTeoria(const char* nombreArchivo, int *codigosNotasTeo, char *secciones, double *notas_teoricas,
    int &numNotasTeoricas);

void cargarPractica(const char* nombreArchivo, int *codigosNotasPrac, double *notas_practica, int &numNotasPracticas);

void separador(ofstream &archivo, char c, int n);

void encabezadoPrincipal(ofstream &archivo);

void encabezadoResumen(ofstream &archivo);

void resumenPorSeccion(ofstream &archivo, char seccion, int cantEstudiantes, double promedioNotasTeo,
    double promedioNotasPrac, double promedioNotasFinal, int cantAprobados, int cantDesaprobados,
    double *notas_finales, char *secciones, int numNotasTeoricas, int *codigosNotasTeo);

void resumenTotales(ofstream &archivo, double promedioGeneralCurso, int cantEstudiantes);

int buscarCodigoCoincidenteEnPractica(int *codigosNotasPrac, int codigoNotaPrac, int numNotasPracticas);

int buscarPosNotaFinalMasAltaDeCadaSeccion(char seccionBuscada, double *notas_finales, char *secciones,
    int numNotasTeoricas);

double calcularNotaFinal(double notaTeoria, double notaPractica);

void resumen(ofstream &archivo, int numNotasTeoricas, int cantEstudiantesA, int cantAprobadosA, int cantDesaprobadosA,
    double *notas_finales, char *secciones, int *codigosNotasTeo, int cantEstudiantesB, int cantAprobadosB,
    int cantDesaprobadosB, int cantEstudiantesC, int cantAprobadosC, int cantDesaprobadosC, double sumaNotasTeoricasA,
    double sumaNotasPracticasA, double sumaNotasFinalesA, double sumaNotasTeoricasB, double sumaNotasPracticasB,
    double sumaNotasFinalesB, double sumaNotasTeoricasC, double sumaNotasPracticasC, double sumaNotasFinalesC);

void generarReporte(const char* nombreArchivo, int *codigosNotasTeo, char *secciones, double *notas_teoricas,
    int numNotasTeoricas, int *codigosNotasPrac, double *notas_practica, int numNotasPracticas, double *notas_finales);

#endif //EJERCICIO2_FUNCIONES_H
