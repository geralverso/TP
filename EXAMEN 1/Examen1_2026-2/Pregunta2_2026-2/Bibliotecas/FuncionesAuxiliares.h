//
// Created by PC on 16/10/2026.
//

#ifndef PREGUNTA2_2026_2_FUNCIONESAUXILIARES_H
#define PREGUNTA2_2026_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define ANCHO_REPORTE 85

bool abrirArchivos(ifstream &cat, ifstream &prod, ofstream &salida);

void imprimirSeparador(ofstream &salida, char c, int n);

void leerEImprimirNombre(ifstream &entrada, ofstream &salida, bool seMuestra);

void buscarProductos(ifstream &prod, ofstream &salida, char categoria, int &cantProductos, int &cantProdSinStock,
    int &codProdMayorPrecio, int &codProdMenorPrecio, double &valorTotalInventario, double &mayorPrecio,
    double &menorPrecio);

void buscarCategoria(ifstream &cat, ofstream &salida, char categoriaMayorValorInv);

void imprimirEncabezado(ofstream &salida);

void imprimirTituloPorCategoria(ofstream &salida, ifstream &cat, char categoria);

void imprimirResumenPorCategoria(ofstream &salida, int cantProductos, int cantProdSinStock, double valorTotalInventario,
    int codProdMayorPrecio, double mayorPrecio, int codProdMenorPrecio, double menorPrecio);

void imprimirResumenGeneral(ofstream &salida, ifstream &cat, int cantTotalProductos, int cantTotalProdSinStock,
    double valorTotalInventarioCompleto, char categoriaMayorValorInv, double mayorValorTotalInventario);

void generarReporte(ifstream &cat, ifstream &prod, ofstream &salida);

void cerrarArchivos(ifstream &cat, ifstream &prod, ofstream &salida);

#endif //PREGUNTA2_2026_2_FUNCIONESAUXILIARES_H
