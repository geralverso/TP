//
// Created by PC on 28/09/2026.
//

#ifndef EJERCICIO04_RESUELTO_POR_MI_FUNCIONES_H
#define EJERCICIO04_RESUELTO_POR_MI_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define ANCHO 55
#define CAPACIDAD_CONSULTAS 6
#define CAPACIDAD_CATEGORIAS 5
#define CAPACIDAD_PRODUCTOS 15

void cargarConsultasTXT(const char* nombreArchivo, int *codigosConsultas, int &numConsultas);

void cargarCategoriasTXT(const char* nombreArchivo, char *categoriasEnCategorias, int &numCategorias);

void cargarProductosCSV(const char* nombreArchivo, int *codigosProductos, char *categoriasProductos,
    double *preciosProductos, int *stocksProductos, bool *importadosProductos, int &numProductos);

void separador(ofstream &salida, char c, int n);

void encabezado1(ofstream &salida);

void encabezado2(ofstream &salida);

void encabezado3(ofstream &salida);

void encabezado4(ofstream &salida);

int buscarPosicionConsultaEnProductosCSV(int codigoBuscado, int *codigosProductos, int numProductos);

int contarProdPorCategoriasEnProductosCSV(char categoriaBuscada, char *categoriasProductos, int numProductos);

int buscarPosicionProdMasBaratoEnProductosCSV(char categoriaBuscada, char *categoriasProductos,
    double *preciosProductos, int numProductos, int *stocksProductos);

int buscarPosicionMayorStockEnProductosCSV(int *stocksProductos, int numProductos);

void masBaratoDisponiblePorCat(ofstream &salida, int numCategorias, char *categoriasEnCategorias,
    char* categoriasProductos, double *preciosProductos, int numProductos, int *stocksProductos, int *codigosProductos);

void consultasPorCodigo(ofstream &salida, int numConsultas, int *codigosConsultas, int *codigosProductos,
        char *categoriasProductos, double *preciosProductos, int *stocksProductos, int numProductos);

void productoConMayorStock(ofstream &salida, int *stocksProductos, int numProductos, int *codigosProductos);

void productosAgotados(ofstream &salida, int numProductos, int *codigosProductos, int *stocksProductos);

void generarReporte(const char* nombreArchivo, int *codigosConsultas, int numConsultas, char *categoriasEnCategorias,
    int numCategorias, int *codigosProductos, char *categoriasProductos, double *preciosProductos,
    int *stocksProductos, bool *importadosProductos, int numProductos);

#endif //EJERCICIO04_RESUELTO_POR_MI_FUNCIONES_H
