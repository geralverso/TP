//
// Created by PC on 13/09/2026.
//

#ifndef LAB02_ADAPTADODELLAB012026_2_FUNCIONESAUXILIARES_H
#define LAB02_ADAPTADODELLAB012026_2_FUNCIONESAUXILIARES_H
#include <fstream>
using namespace std;

#define ANCHO_DEL_REPORTE 140

bool abrirArchivos(ifstream &entrada, ofstream &salida);

void separador(ofstream &salida, char c, int n);

void encabezado(ofstream &salida);

int calcularEdad(ofstream &salida, int diaReferencial, int mesReferencial, int anioReferencial,
    int dia, int mes, int anio);

void imprimirTiempos(ofstream &salida, int hora, int min, int seg);

int calcularDuracion(ofstream &salida, int horaI, int minI, int segI, int horaF, int minF, int segF);

void imprimirRitmo(ofstream &salida, double ritmo);

void resumen(ofstream &salida, int cantRegistros, int cantRegistros10K, int cantRegistros21K,
    int cantRegistros42K, int codigoCorredorMenorRitmo, int codigoCorredorMayorRitmo,
    double ritmoMayor, double ritmoMenor);

void leerImprimirCadena(ifstream &entrada, ofstream &salida, int anchoColumna);

void generarReporte(ifstream &entrada, ofstream &salida, int diaReferencial, int mesReferencial,
    int anioReferencial);

void cerrarArchivos(ifstream &entrada, ofstream &salida);

#endif //LAB02_ADAPTADODELLAB012026_2_FUNCIONESAUXILIARES_H
