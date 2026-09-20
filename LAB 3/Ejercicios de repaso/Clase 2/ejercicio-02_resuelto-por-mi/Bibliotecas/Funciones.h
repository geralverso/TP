//
// Created by PC on 19/09/2026.
//

#ifndef EJERCICIO_02_RESUELTO_POR_MI_FUNCIONES_H
#define EJERCICIO_02_RESUELTO_POR_MI_FUNCIONES_H

#include <fstream>
using namespace std;
#define ANCHO 63

bool abrirArchivos(ifstream& entrada, ofstream& salida);

void separador(ofstream& salida, char c, int n);

void encabezado(ofstream& salida);

void acumularPacientes(int cantPacientes, int &cantRegistros, int &sumaPacientes, int &minCantPacientes,
    int &maxCantPacientes);

void generarReporte(ifstream& entrada, ofstream& salida);

void imprimirLineaConDatosPorTurno(ofstream& salida, char turno, int registros, int suma, double promedio,
    int minimo, int maximo);

void resumen(ofstream& salida, int totalRegistrosAmbosTurnos, int totalPacientesAmbosTurnos);

void cerrarArchivos(ifstream& entrada, ofstream& salida);

#endif //EJERCICIO_02_RESUELTO_POR_MI_FUNCIONES_H
