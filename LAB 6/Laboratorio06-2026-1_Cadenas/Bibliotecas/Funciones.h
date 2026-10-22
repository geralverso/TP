//
// Created by PC on 16/10/2026.
//

#ifndef LABORATORIO06_2026_1_CADENAS_FUNCIONES_H
#define LABORATORIO06_2026_1_CADENAS_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

#define ANCHO_REPORTE 140
#define CAPACIDAD_MEDICOS 200
#define CAPACIDAD_ATENCIONES 500


//PARA LEER, CALCULAR, BUSCAR, ARMAR:

void cargarEspecMedicos(const char* nombreArchivo, int* &codigosMedicos, double* &tarifaMedicos, int &numMedicos);

int insertarOrdenadoEspecMedicos(int* codigosMedicos, double* tarifaMedicos, int codMedNuevo, double tarifaNueva,
    int &numMedicos, int capacidad);

void cargarAtenciones(const char *nombreArchivo, int *&codigosPacientes, int *&codigosSedesPacientes,
    int *&duracionAtencionesPacientes, double *&pagosTotalesPacientes, int &numAtenciones, int* codigosMedicos,
    double* tarifaMedicos, int numMedicos);

int leerYCalcularTiempo(ifstream &entrada);

int buscarBinariaMedico(int* codigosMedicos, int codigoBuscado, int numMedicos);

int buscarPacienteYSede(int *bufferCodigosPacientes, int *bufferCodigosSedesPacientes, int codPacienteBuscado,
    int codSedeBuscado, int numAtenciones);

void armarCadena(ifstream& entrada, char *cadena, char delimitador);

void armarTodasLasCadenas(ifstream &entrada, char *nombreRed, char* nombreClinica, char* nombreDireccion, char *nombreDistrito);

int buscarSede(int* codigosSedesPacientes, int codigoBuscado, int numAtenciones);

int calcularDuracion(int inicio, int fin);


//PARA ORDENAR:

void intercambiarInt(int &a, int &b);

void intercambiarDouble(double &a, double &b);

void ordenarSedeYPacientePorBurbuja(int* codigosPacientes, int* codigosSedesPacientes, int* duracionAtencionesPacientes,
    double* pagosTotalesPacientes, int numAtenciones);


//PARA IMPRIMIR:

void imprimirSeparador(ofstream& salida, char c, int n);

void imprimirTiempoOCodigo(char tipo, int tiempo, ofstream& salida, int ancho);

void imprimirDatosSede(ifstream &entrada, ofstream &salida, char *nombreRed, char *nombreClinica, char *nombreDireccion,
    char *nombreDistrito, int codigoSede);

void imprimirPacientesPorSede(ofstream &salida, int numAtenciones, int codigoSede, int *codigosSedesPacientes,
    int *codigosPacientes, int* duracionAtencionesPacientes, double* pagosTotalesPacientes, double &ingresoTotalPorSede);

void imprimirResumen(ofstream &salida, char *redMayorIngreso,  char *clinicaMayorIngreso,  char *direccionMayorIngreso,
    char *distritoMayorIngreso, double mayorIngresoTotal);


//PARA GENERAR REPORTES:

void generarReporteSimple1(const char* nombreArchivo, int* codigosMedicos, double* tarifaMedicos, int numMedicos);

void generarReporteSimple2(const char* nombreArchivo, int* codigosPacientes, int* codigosSedesPacientes,
    int* duracionAtencionesPacientes, double* pagosTotalesPacientes, int numAtenciones);

void generarReporte(const char* nombreArchivo1, const char* nombreArchivo2, int *codigosMedicos, int *codigosPacientes,
    int *codigosSedesPacientes, int *duracionAtencionesPacientes, double *pagosTotalesPacientes, int numAtenciones);


#endif //LABORATORIO06_2026_1_CADENAS_FUNCIONES_H
