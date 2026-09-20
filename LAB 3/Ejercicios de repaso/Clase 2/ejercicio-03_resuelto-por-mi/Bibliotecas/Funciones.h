//
// Created by PC on 19/09/2026.
//

#ifndef EJERCICIO_03_RESUELTO_POR_MI_FUNCIONES_H
#define EJERCICIO_03_RESUELTO_POR_MI_FUNCIONES_H

#include <fstream>
using namespace std;
#define ANCHO 47

bool abrirArchivos1(ifstream &csv, ofstream &json);

bool esAnioBisiesto(int anio);

int calcularDiasDelMes(int mes, int anio);

bool validarFechaHora(int dia, int mes, int anio, int hora, int min, int seg);

long long calcularFechaHora(int dia, int mes, int anio, int hora, int min, int seg);

void transformarFechaHoraISO(ofstream &json, long long fechaHora);

void resumenJSON(ofstream &json, int cantReservasValidas, int cantReservasInvalidas, double importesTotales,
    double mayorImporte, int IDmayorImporte, long long fechaHoraMayorImporte, double menorImporte,
    int IDmenorImporte, long long fechaHoraMenorImporte);

void generarJSON(ifstream &csv, ofstream &json);

void cerrarArchivos1(ifstream &csv, ofstream &json);

bool abrirArchivos2(ifstream &entrada, ofstream &salida);

void separador(ofstream &salida, char c, int n);

void encabezadoTXT(ofstream &salida);

bool esLineaDeReservaHab(ifstream &entrada);

long long leerYPasarFechaHoraISO(ifstream &entrada);

void resumenTXT(ofstream &salida, int cantReservasValidas, int cantReservasInvalidas, double importeTotal,
    double mayorImporte, int IDmayorImporte, long long fechaHoraMayorImporte, double menorImporte,
    int IDmenorImporte, long long fechaHoraMenorImporte);

void imprimirDatosMayorImporteTXT(ofstream &salida, int id, long long fecha);

void generarTXT(ifstream &entrada, ofstream &salida);

void cerrarArchivos2(ifstream &entrada, ofstream &salida);


#endif //EJERCICIO_03_RESUELTO_POR_MI_FUNCIONES_H
