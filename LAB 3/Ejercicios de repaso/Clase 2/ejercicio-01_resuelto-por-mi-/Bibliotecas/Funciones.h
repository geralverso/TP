//
// Created by PC on 18/09/2026.
//

#ifndef EJERCICIO_01_RESUELTO_POR_MI_FUNCIONES_H
#define EJERCICIO_01_RESUELTO_POR_MI_FUNCIONES_H

#include <fstream>
using namespace std;
#define ANCHO 53

bool abrirArchivos(ifstream &movi, ifstream &prod, ofstream &salida);

void separador(ofstream &salida, char c, int n);

void encabezado(ofstream &salida);

void contarEntradasSalidasProductos(ifstream &movi, ofstream &salida,int &cantEntradasTotales,
    int &cantSalidasTotales);

void buscarMovimientosProducto(ifstream &movi, ofstream &salida, int IDproducto, int &stock, int &cantEntradasProducto,
    int &cantSalidasProducto);

void resumen(ofstream &salida, int cantProductosProcesados, int cantProductosSinMov,int cantEntradasTotales,
    int cantSalidasTotales,int IDproductoConMayorStock, int mayorStock);

void generarReporte(ifstream &movi, ifstream &prod, ofstream &salida);

void cerrarArchivos(ifstream &movi, ifstream &prod, ofstream &salida);

#endif //EJERCICIO_01_RESUELTO_POR_MI_FUNCIONES_H
