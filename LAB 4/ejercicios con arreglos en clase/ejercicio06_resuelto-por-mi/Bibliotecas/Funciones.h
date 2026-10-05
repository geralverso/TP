//
// Created by PC on 28/09/2026.
//

#ifndef EJERCICIO06_RESUELTO_POR_MI_FUNCIONES_H
#define EJERCICIO06_RESUELTO_POR_MI_FUNCIONES_H

#include <iostream>
using namespace std;
#include <fstream>
#include <iomanip>

#define ANCHO 62
#define CAPACIDAD_NUEVOS 10
#define CAPACIDAD_PRODUCTOS 50


//PARA LEER Y ARMAR LOS DATOS DE LOS ARCHIVOS CON ORDEN
void cargarNuevosCSV(const char* nombreArchivo, int *codigosNuevos, char *categoriasDeNuevos, double *preciosNuevos,
    int *stocksNuevos, bool *importadosNuevos, int &numNuevos);
void cargarProductosCSV(const char* nombreArchivo, int *codigosProductos, char *categoriasDeProductos,
    double *preciosProductos, int *stocksProductos, bool *importadosProductos, int &numProductos);
int buscarPosicionProductoQueYaExisteEnProductosCSV(int *codigosProductos, int codigoBuscado, int numProductos);
int buscarPosicionOrdenadaParaProductosCSV(int *codigosProductos, int codigoProdNuevo, int numProductos);
int insertarOrdenado(int *codigosProductos, char *categoriasDeProductos, double *preciosProductos, int *stocksProductos,
    bool *importadosProductos, int codigoProdNuevo, char catProdNuevo, double precioProdNuevo, int stockProdNuevo,
    bool importadoProdNuevo, int &numProductos, int capacidad);
int buscarPosicionProdMayorPrecioEnProductosCSV(double *preciosProductos, int numProductos, char *categoriasDeProductos,
    char categoriaBuscada);

//PARA IMPRIMIR EL REPORTE
void separador(ofstream &salida, char c, int n);
void encabezado1(ofstream &salida);
void encabezado2(ofstream &salida);
void encabezado3(ofstream &salida);
void insersionDeProductosNuevos(ofstream &salida, int numNuevos, int *codigosNuevos, char *categoriasDeNuevos,
    double *preciosNuevos, int *stocksNuevos, bool *importadosNuevos, int *codigosProductos, char *categoriasDeProductos,
    double *preciosProductos, int *stocksProductos, bool *importadosProductos, int &numProductos);
void productosOrdenadosPorCodigo(ofstream &salida, int numProductos, int *codigosProductos, char *categoriasDeProductos,
    double *preciosProductos, int *stocksProductos, bool *importadosProductos, int &cantProductosA, int &cantUnidadesA,
    double &valorUnidadesA, double &sumaPreciosA, int &cantProductosB, int &cantUnidadesB, double &valorUnidadesB,
    double &sumaPreciosB, int &cantProductosC, int &cantUnidadesC, double &valorUnidadesC, double &sumaPreciosC,
    int &cantProductosD, int &cantUnidadesD, double &valorUnidadesD, double &sumaPreciosD);
void lineaDeDatosPorCategoria(ofstream &salida, char categoria, int cantProductos, int cantUnidades, double valor,
    double promPrecio, int *codigosProductos, char *categoriasDeProductos, double *preciosProductos, int numProductos);
void resumenPorCategoria(ofstream &salida, int *codigosProductos, char *categoriasDeProductos, double *preciosProductos,
        int numProductos, int cantProductosA, int cantUnidadesA, double valorUnidadesA, double sumaPreciosA, int cantProductosB,
        int cantUnidadesB, double valorUnidadesB, double sumaPreciosB, int cantProductosC, int cantUnidadesC,
        double valorUnidadesC, double sumaPreciosC, int cantProductosD, int cantUnidadesD, double valorUnidadesD,
        double sumaPreciosD);
void generarReporte(const char* nombreArchivo, int *codigosNuevos, char *categoriasDeNuevos, double *preciosNuevos,
    int *stocksNuevos, bool *importadosNuevos, int numNuevos, int *codigosProductos, char *categoriasDeProductos,
    double *preciosProductos, int *stocksProductos, bool *importadosProductos, int &numProductos);


#endif //EJERCICIO06_RESUELTO_POR_MI_FUNCIONES_H
