//
// Created by PC on 16/10/2026.
//

#ifndef PREGUNTA3_2026_2_FUNCIONESAUXILIARES_H
#define PREGUNTA3_2026_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define ANCHO_REPORTE 120
#define CAPACIDAD_PRODUCTOS 150


//PARA CARGAR O ARMAR ARREGLOS:

void cargarProductos(const char* nombre, int *codigosProductos, char *categoriasProductos, int *stocksInicialesProductos,
    double *preciosUnitProductos, int &numProductos);

int insertarOrdenadoProductos(int *codigosProductos, char *categoriasProductos, int *stocksInicialesProductos,
    double *preciosUnitProductos, int &numProductos, int codigoProdNuevo, char catProdNuevo, int stockInProdNuevo,
    double precioUnitProdNuevo, int capacidad);

int buscarBinariaProducto(int *codigosProductos, int codigoBuscado, int numProductos);

void leerMovimientos(const char *nombre, int *codigosProductos, int *totalIngresosProductos, int *totalEgresosProductos,
    int numProductos);

void armarArregloStocksFinales(int *stocksFinalesProductos, int *stocksInicialesProductos, int *totalIngresosProductos,
    int *totalEgresosProductos, int numProductos);

void armarArregloMontoTotal(double *montosTotalesProductos, int *stocksFinalesProductos, double *preciosUnitProductos,
    int numProductos);


//PARA ORDENAR:

void intercambiarInt(int &a, int &b);

void intercambiarDouble(double &a, double &b);

void intercambiarChar(char &a, char &b);

void ordenarCategoriasYStockFinalConBubble(int numProductos, int *codigosProductos, char *categoriasProductos,
    int *stocksInicialesProductos, double *preciosUnitProductos, int *totalIngresosProductos, int *totalEgresosProductos,
    int *stocksFinalesProductos, double *montosTotalesProductos);


//PARA IMPRIMIR:

void imprimirSeparador(ofstream &salida, char c, int n);

void imprimirEncabezado(ofstream &salida);

void generarReporteSimple(const char *nombre, int *codigosProductos, char *categoriasProductos, int *stocksInicialesProductos,
    double *preciosUnitProductos, int numProductos);

void generarListado(const char* nombre, int *stocksFinalesProductos, int *codigosProductos, char *categoriasProductos,
    int numProductos);

void generarReporte(const char* nombre, int *codigosProductos, char *categoriasProductos, int *stocksInicialesProductos,
    double *preciosUnitProductos, int *totalIngresosProductos, int *totalEgresosProductos, int *stocksFinalesProductos,
    double *montosTotalesProductos, int numProductos);

#endif //PREGUNTA3_2026_2_FUNCIONESAUXILIARES_H
