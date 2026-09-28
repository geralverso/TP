//
// Created by PC on 27/09/2026.
//

#ifndef EJERCICIO05_RESUELTO_POR_MI_FUNCIONES_H
#define EJERCICIO05_RESUELTO_POR_MI_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define ANCHO 55
#define CAPACIDAD 15

void cargarVentasCSV(const char *nombreArchivo, int *codigosVentas, int *cantidadesVentas, int &numVentas);

void cargarProductosCSV(const char *nombreArchivo, int *codigosProductos, char *categoriasProductos,
    double *preciosProductos, int *stocksProductos, bool *importadosProductos, int &numProductos);

void separador(ofstream &salida, char c, int n);

void encabezado1(ofstream &salida);

void encabezado2(ofstream &salida);

void encabezado3(ofstream &salida);

int buscarPosCodigoVentaEnProductosCSV(int codigoBuscado, int *codigosProductos, int numProductos);

void detalleDeVentas(ofstream &salida, int *codigosVentas, int *cantidadesVentas, int numVentas, int *codigosProductos,
    int *stocksProductos, int numProductos, int *cantProductosVendidos, double *ingresoProductosVendidos,
    double *preciosProductos, int &cantVentasAtendidasTotales, int &cantVentasSinStockTotales,
    int &cantVentasProdNoRegisTotales);

int buscarPosCodigoProductoMasVendido(int *cantProductosVendidos, int numProductos);

int buscarPosCodigoProductoMayorIngreso(double *ingresoProductosVendidos, int numProductos);

void ventasPorProducto(ofstream &salida, int numProductos, int *codigosProductos, double *preciosProductos,
    int *cantProductosVendidos, double *ingresoProductosVendidos, int *stocksProductos, int &cantProdSinVentas,
    double &ingresoTotal);

void resumen(ofstream &salida, int *codigosProductos, int numProductos, int *cantProductosVendidos,
    double *ingresoProductosVendidos, int cantVentasAtendidasTotales, int cantVentasSinStockTotales,
    int cantVentasProdNoRegisTotales, int cantProdSinVentas, double ingresoTotal);

void generarReporte(const char *nombreArchivo, int *codigosVentas, int *cantidadesVentas, int numVentas,
    int *codigosProductos, double *preciosProductos, int *stocksProductos, int numProductos, int *cantProductosVendidos,
    double *ingresoProductosVendidos);

#endif //EJERCICIO05_RESUELTO_POR_MI_FUNCIONES_H
