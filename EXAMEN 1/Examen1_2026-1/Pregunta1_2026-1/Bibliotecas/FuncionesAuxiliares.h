//
// Created by PC on 7/10/2026.
//

#ifndef PREGUNTA1_2026_1_FUNCIONESAUXILIARES_H
#define PREGUNTA1_2026_1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
#define ANCHO_REPORTE 170


bool abrirArchivos(ifstream &atenciones, ifstream &medicos, ifstream &pacientes, ifstream &sedes, ofstream &salida);

void cerrarArchivos(ifstream &atenciones, ifstream &medicos, ifstream &pacientes, ifstream &sedes, ofstream &salida);

void imprimirSeparador(ofstream &salida, char c, int n);

void imprimirEncabezado(ofstream &salida);

void leerImprimirNombres(ifstream &entrada, ofstream &salida, int anchoColumna, bool seMuestra);

void imprimirEncabezadoSedes(ifstream &entrada, ofstream &salida, int numSede);

void buscarInfoAtenciones(ifstream &atenciones, ifstream &pacientes, ifstream &medicos, ofstream &salida, int numSede,
    int &cantAtencionesPorSede, int &tiempoTotalAtencionesPorSedeSec, double &pagoTotalPorSede);

double calcularPago(double costoPor1Hora, int tiempoSec);

void buscarPacientes(ifstream &pacientes, ofstream &salida, int n1, int n2, int n3);

void imprimirTiempo(ofstream &salida, int tiempo, int anchoColumna);

void buscarMedicos(ifstream &medicos, ofstream &salida, int codigoDoctor, int duracionSec, double &pago);

void imprimirResumenPorSede(ofstream &salida, int cantAtencionesPorSede, double pagoTotalPorSede, int tiempoTotalAtencionesPorSedeSec);

void imprimirResumenTotal(ofstream &salida, int cantSedes, double pagoTotal, int numSedeMayorPago, double mayorPagoPorSede);

void generarReporte(ifstream &atenciones, ifstream &medicos, ifstream &pacientes, ifstream &sedes, ofstream &salida);


#endif //PREGUNTA1_2026_1_FUNCIONESAUXILIARES_H
