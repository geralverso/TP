//
// Created by PC on 9/10/2026.
//

#ifndef EJERCICIO1_FUNCIONES_H
#define EJERCICIO1_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define ANCHO_REPORTE1 60
#define ANCHO_REPORTE2 40
#define CAPACIDAD_CITAS 60


//-----------------------------------------------------------REPORTE 1:

bool abrirArchivos(ifstream &espec, ifstream &medicos, ofstream &salida);

void imprimirSeparador(ofstream &salida, char c, int n);

void leerEImprimirNombres(ifstream &entrada, ofstream &salida);

void buscarMedicos(ifstream &medicos, ofstream &salida, char letraCodigoEspecialidad, int numCodigoEspecialidad,
    int &cantMedicosPorEspecialidad);

void generarReporte1(ifstream &espec, ifstream &medicos, ofstream &salida);

void cerrarArchivos(ifstream &espec, ifstream &medicos, ofstream &salida);


//-----------------------------------------------------------REPORTE 2:

void cargarCitas(const char* nombreArchivo, int *fechasCitas, int* codigosCitas, int *dnisCitas, int *codigosMedicos,
    int &numCitas);

void imprimirEncabezado(ofstream &salida);

void imprimirFecha(int fecha, ofstream &salida);

void intercambiarInt(int &a, int &b);

void ordenarFechasYMedicosConBubble(int *fechasCitas, int* codigosCitas, int *dnisCitas, int *codigosMedicos,
    int numCitas);


void generarReporte2(const char* nombreArchivo, int *fechasCitas, int* codigosCitas, int *dnisCitas, int *codigosMedicos,
    int numCitas);



#endif //EJERCICIO1_FUNCIONES_H
