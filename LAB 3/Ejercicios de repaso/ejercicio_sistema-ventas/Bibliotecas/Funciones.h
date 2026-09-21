//
// Created by PC on 21/09/2026.
//

#ifndef EJERCICIO_SISTEMA_VENTAS_FUNCIONES_H
#define EJERCICIO_SISTEMA_VENTAS_FUNCIONES_H

#include <fstream>
using namespace std;
#define ANCHO 45

bool abrirArchivos(ifstream &ventas, ifstream &inven, ifstream &config, ofstream &txt, ofstream &json,
    ofstream &csv);

void separador(ofstream &salida, char c, int n);

void encabezado(ofstream &txt);

void buscarInfoVentas(ifstream &ventas, ofstream &txt, char codigoProducto, int &cantUnidadesVendidasPorProducto,
    double &ingresoTotalPorProducto);

void escribirEnTXT(ofstream &txt, int cantUnidadesVendidasPorProducto, double ingresoTotalPorProducto,
    int stockRestante, char alerta);

void escribirEnJSON(ofstream &json, char codigoProducto, int cantUnidadesVendidasPorProducto,
    double ingresoTotalPorProducto, int stockRestante, char alerta);

void escribirEnTCSV(ofstream &csv, char codigoProducto, int cantUnidadesVendidasPorProducto,
    double ingresoTotalPorProducto, int stockRestante, char alerta);

void resumenTXT(ofstream &txt, double ingresoTotalDeLaTienda, double montoDeImpuesto, double ingresoNeto,
    double porcentajeDeCumpDeMeta, double ingresoPromedioPorEmpleado);

void generarReportes(ifstream &ventas, ifstream &inven, ifstream &config, ofstream &txt, ofstream &json,
    ofstream &csv);

void resumenJSON(ofstream &json, double ingresoTotalDeLaTienda, double montoDeImpuesto, double ingresoNeto,
    double porcentajeDeCumpDeMeta, double ingresoPromedioPorEmpleado);

void resumenCSV(ofstream &csv, char codigo, int cantUnidadesVendidasTotalDeLaTienda, double ingresoTotalDeLaTienda,
    int stock, char alerta);

void cerrarArchivos(ifstream &ventas, ifstream &inven, ifstream &config, ofstream &txt, ofstream &json,
    ofstream &csv);

#endif //EJERCICIO_SISTEMA_VENTAS_FUNCIONES_H
