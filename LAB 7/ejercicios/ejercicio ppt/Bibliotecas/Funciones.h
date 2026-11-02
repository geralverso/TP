//
// Created by PC on 1/11/2026.
//

#ifndef EJERCICIO_PPT_FUNCIONES_H
#define EJERCICIO_PPT_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

#define CAP_PERSONAL 200
#define CAP_BUFFER 150

//FUNCIONES PARA LEER Y CARGAR:
void abrirArchLectura(const char* nombreArch, ifstream& arch);
char* leerCadenaExacta(ifstream& arch, char delimitador);
void cargarPersonal(const char* nombreArch, int* &dnis, char** &nombres, double* &sueldos, int &numPersonal);
int insertarOrdenado(char** bufferNombres, int *bufferDNI, double* bufferSueldo, char* nombreNuevo, int dniNuevo,
    double sueldoNuevo, int &numPersonal);

//FUNCIONES PARA ORDENAR:
void intercambiarCadena(char*&a, char*&b);
void intercambiarEntero(int &a, int &b);
void intercambiarDecimal(double &a, double &b);
void ordenarPersonal(int* dnis, char** nombres, double* sueldos, int numPersonal);

//FUNCIONES PARA GENERAR REPORTES:
void abrirArchEscritura(const char* nombreArch, ofstream& arch);
void generarReporte(const char *nombreArch, const int *dnis, char **nombres, const double *sueldos, int numPersonal);

//FUNCIONES PARA LIBERAR RECURSOS:
void liberarMemoria(const int *dnis, char **nombres, const double *sueldos, int numPersonal);


#endif //EJERCICIO_PPT_FUNCIONES_H
