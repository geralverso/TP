//
// Created by PC on 16/09/2026.
//

#ifndef LAB02_2026_2_FUNCIONES_H
#define LAB02_2026_2_FUNCIONES_H
#include <fstream>
using namespace std;

#define ANCHO_REPORTES 62

bool abrirArchivos(ifstream &entrada, ofstream &estadisticas, ofstream &alertas);

void separador(ofstream &salida, char c, int n);

void cerrarArchivos(ifstream &entrada, ofstream &estadisticas, ofstream &alertas);

void encabezadoEstadisticas(ofstream &estadisticas, int ddi, int mmi, int aai, int ddf, int mmf, int aaf);

double infoMedicionesTemp(ifstream &entrada, ofstream &alertas, int &cantMedicionesTemp, int &cantAlertasTemp, double &minimaTemp,
    double &maximaTemp, int &dia, int &mes, int &anio, double &medicionAlertaTemp);

double infoMedicionesVib(ifstream &entrada, ofstream &alertas, int &cantMedicionesVib, int &cantAlertasVel, double &minimaVel,
    double &maximaVel, int &dia, int &mes, int &anio, double &medicionAlertaVel);

void reporteEstadisticas(ofstream &estadisticas, int cantLecturasTemp, int cantAlertasTemp, double promedioTemp,
    double minimaTemp, double maximaTemp, int cantLecturasVel, int cantAlertasVel, double promedioVel,
    double minimaVel, double maximaVel, int cantLecturasDia, int cantLecturasNoche);

void generarEstadisticasYAlertas(ifstream &entrada, ofstream &alertas, ofstream &estadisticas, int ddi, int mmi, int aai, int ddf,
    int mmf, int aaf);

void encabezadoAlertas(ofstream &alertas);

void imprimirFecha(ofstream &alertas, int dia, int mes, int anio);

#endif //LAB02_2026_2_FUNCIONES_H
