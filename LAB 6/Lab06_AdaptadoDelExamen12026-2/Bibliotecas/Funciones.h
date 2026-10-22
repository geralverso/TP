//
// Created by PC on 16/10/2026.
//

#ifndef LAB06_ADAPTADODELEXAMEN12026_2_FUNCIONES_H
#define LAB06_ADAPTADODELEXAMEN12026_2_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define CAPACIDAD_PRODUCTOS 150
#define ANCHO_REPORTE 120


//PARA LEER Y ARMAR:

void cargarProductos(const char* nombreArchivo, char* &categorias, int* &codigosProductos, int* &stocksIniciales,
    double* &preciosUnitarios, int &numProductos);

int insertarOrdenadoProductos(char *categorias, int *codigosProductos, int *stocksIniciales, double *preciosUnitarios,
    char catNuevo, int codProdNuevo, int stockInicialNuevo, double precioNuevo, int &numProductos, int capacidad);

void cargarMovimientos(const char *nombreArchivo, int* codigosProductos, int *&totalIngresos, int *&totalEgresos,
    int numProductos);

int buscarBinariaProductos(int *codigosProductos, int codigoBuscado, int numProductos);

void armarStocksFinales(int* &stocksFinales, int* stocksIniciales, int* totalIngresos, int* totalEgresos, int numProductos);

void armarMontosTotales(double* &montosTotales, double* preciosUnitarios, int* stocksFinales, int numProductos);


//PARA ORDENAR:

void intercambiarInt(int &a, int &b);

void intercambiarDouble(double &a, double &b);

void intercambiarChar(char &a, char &b);

void ordenarCatYStockFinalPorSeleccion(char *categorias, int *codigosProductos, int *stocksIniciales, int* totalIngresos,
    int* totalEgresos, double* preciosUnitarios, int* stocksFinales, double* montosTotales, int numProductos);


//PARA IMPRIMIR:

void imprimirSeparador(ofstream &salida, char c, int n);

void imprimirEncabezadoRepSimple(ofstream &salida);

void imprimirEncabezadoKardex(ofstream &salida);


//PARA GENERAR REPORTES:

void generarReporteSimple(const char* nombreArchivo, char* categorias, int* codigosProductos, int* stocksIniciales,
    double* preciosUnitarios, int numProductos);

void generarListado(const char* nombreArchivo, char* categorias, int* codigosProductos, int numProductos, int* stocksFinales);

void generarReporte(const char* nombreArchivo, char *categorias, int *codigosProductos, int *stocksIniciales, int* totalIngresos,
    int* totalEgresos, double* preciosUnitarios, int* stocksFinales, double* montosTotales, int numProductos);

#endif //LAB06_ADAPTADODELEXAMEN12026_2_FUNCIONES_H
