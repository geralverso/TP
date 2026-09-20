//
// Created by PC on 15/09/2026.
//

#ifndef EJERCICIO_02_RESUELTO_POR_MI_FUNCIONES_H
#define EJERCICIO_02_RESUELTO_POR_MI_FUNCIONES_H
#include <fstream>
using namespace std;

#define ANCHO_REPORTE 80

bool abrirArchivos(ifstream& entrada, ofstream& salida);

void separador(ofstream& salida, char c, int n);

void encabezado(ofstream& salida);

void acumularDatos(double lectura, double &lecturaMinima, double &lecturaMaxima, int &cantLecturas,
    double &sumaLecturas);

void imprimirInfoSensores(ofstream& salida, char sensor, int cantLecturasSensor,double sumaLecturas,
    double lecturaMinima, double lecturaMaxima);

void generarReporte(ifstream& entrada, ofstream& salida);

void cerrarArchivos(ifstream& entrada, ofstream& salida);

#endif //EJERCICIO_02_RESUELTO_POR_MI_FUNCIONES_H
