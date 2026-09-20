//
// Created by PC on 15/09/2026.
//

#ifndef EJERCICIO_01_RESUELTO_POR_MI_FUNCIONES_H
#define EJERCICIO_01_RESUELTO_POR_MI_FUNCIONES_H
#include <fstream>
using namespace std;

#define ANCHO_DEL_REPORTE 50

bool abrirArchivos(ifstream& clientes, ifstream& pedidos, ofstream& salida);

void separador(ofstream& salida, char c, int n);

void encabezado(ofstream& salida);

void infoPedidos(ifstream& pedidos, ofstream& salida, int &cantPedidos,
    double &totalCostoPedidos, int numCliente);

void resumenFinal(ofstream& salida, int cantTotalClientes, int cantClientesSinPedidos,
    double TotalDeTotalesCostoPedidos, int numClienteMayorGasto, double mayorCostoTotalPedidos);

void generarReporte(ifstream& clientes, ifstream& pedidos, ofstream& salida);

void cerrarArchivos(ifstream& clientes, ifstream& pedidos, ofstream& salida);

#endif //EJERCICIO_01_RESUELTO_POR_MI_FUNCIONES_H
