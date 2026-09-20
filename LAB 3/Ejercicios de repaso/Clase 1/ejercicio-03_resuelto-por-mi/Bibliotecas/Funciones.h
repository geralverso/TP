//
// Created by PC on 15/09/2026.
//

#ifndef EJERCICIO_03_RESUELTO_POR_MI_FUNCIONES_H
#define EJERCICIO_03_RESUELTO_POR_MI_FUNCIONES_H

#include <fstream>
using namespace std;
#define ANCHO_REPORTE 48

bool abrirArchivos1(ifstream& csv, ofstream& json);

void imprimirFechaHora(ofstream& json, long long fechaHora);

bool validarFechasHoras(int dia, int mes, int anio, int hora, int min, int seg);

bool esAnioBisiesto(int anio);

int diasDelMes(int mes, int anio);

long long calcularFechaHora(int dia, int mes, int anio, int hora, int min, int seg);

void generarReporteJSON(ifstream& csv, ofstream& json);

void cerrarArchivos1(ifstream& csv, ofstream& json);

////////////////////////////////////////////////////////////////////////////////////////////

bool abrirArchivos2(ifstream &entrada, ofstream &salida);

void separador(ofstream &salida, char c, int n);

void encabezado(ofstream &salida);

void resumen(ofstream &salida, int cantVentasValidas, int cantVentasInvalidas, double totalImporte,
    double importeMayor, int IDmayorImporte, long long fechaHoraMayorImporte, double importeMenor,
    int IDmenorImporte, long long fechaHoraMenorImporte);

void leerFechaHora(ifstream &entrada, int &dia, int &mes, int &anio, int &hora, int &min, int &seg);

void imprimirIDyFechaHoraVenta(ofstream &salida, int ID, long long fechaHora);

void generarReporteTXT(ifstream& entrada, ofstream& salida);

void cerrarArchivos2(ifstream &entrada, ofstream &salida);

#endif //EJERCICIO_03_RESUELTO_POR_MI_FUNCIONES_H
