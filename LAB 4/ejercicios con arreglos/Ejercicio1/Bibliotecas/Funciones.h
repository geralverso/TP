//
// Created by PC on 25/09/2026.
//

#ifndef EJERCICIO1_FUNCIONES_H
#define EJERCICIO1_FUNCIONES_H

#include <fstream>
#include <iomanip>
#include <iostream>
using namespace std;

#define ANCHO_REPORTE 65
#define CAPACIDAD_EMPLEADOS 200

void cargarEmpleadosTXT(const char* nombreArchivo, int *codigos, char *nombres, char *areasDeTrabajo,
    double *horasExtra, int &numEmpleados);

void separador(ofstream &archivo, char c, int n);

void encabezadoPrincipalArch1(ofstream &archivo1);

void encabezadoPrincipalArch2(ofstream &archivo2);

void encabezadoResumen(ofstream &archivo);

double calcularPago(char area, double horasExtra);

void imprimirDatosDelEmpleado(ofstream &archivo, int codigo, char area, double horasExtra, double pago);

void imprimirListadoDeEmpleados(ofstream &archivo, ofstream &archivo2, int *codigos, char *areasDeTrabajo,
    double *horasExtra, int numEmpleados, int &cantEmpleadosA, double &totalHorasExtraA, double &totalPagadoA,
    int &cantEmpleadosB, double &totalHorasExtraB, double &totalPagadoB, int &cantEmpleadosC, double &totalHorasExtraC,
    double &totalPagadoC);

void resumenPorArea(ofstream &archivo, char area, int cantEmpleados, double totalHorasExtra, double totalPagado,
    double* horasExtra, int *codigos, char *areasDeTrabajo, int numEmpleados);

void resumenDeTotales(ofstream &archivo, double totalPagadoTodasAreas, int numEmpleados);

int buscarPosicionMayorDeCadaArea(double *horasExtra, char *areasDeTrabajo, int numEmpleados, char areaBuscada);

void imprimirResumen(ofstream &archivo, int *codigos, char *areasDeTrabajo, double *horasExtra, int numEmpleados,
    int cantEmpleadosA, double totalHorasExtraA, double totalPagadoA, int cantEmpleadosB, double totalHorasExtraB,
    double totalPagadoB, int cantEmpleadosC, double totalHorasExtraC, double totalPagadoC);

void generarReportes(const char *nombreArchivo1, const char *nombreArchivo2, int *codigos, char *areasDeTrabajo,
    double *horasExtra, int numEmpleados);


//PARA EL REPORTE ORDENADO

void intercambiarInt(int &a, int &b);

void intercambiarChar(char &a, char &b);

void intercambiarDouble(double &a, double &b);

bool esMenor(double horasExtra1, char area1, double horasExtra2, char area2);

void ordenarEmpleados(int *codigos, char *areasDeTrabajo, double *horasExtra, int numEmpleados);


#endif //EJERCICIO1_FUNCIONES_H
