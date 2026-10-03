//
// Created by PC on 30/09/2026.
//

#ifndef LAB04_2026_2_FUNCIONESAUXILIARES_H
#define LAB04_2026_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define CAPACIDAD_VEHICULOS 300
#define CAPACIDAD_CAPTURAS 591
#define ANCHO 62

void leerAniosRevision(ifstream &entrada, int anioRevision);

void cargarVehiculosTXT(const char* nombre, int *codigosVehiculos, char *categoriasVehiculos, int &numVehiculos);

void cargarCapturasCSV(const char* nombre, int *codigosVehiculosCapturas, double *velocidadesCapturas,
    int *carrilesCapturas, int *kilometrosCapturas, int *diasCapturas, int *mesCapturas, int *aniosCapturas,
    int *codigosCamarasCapturas, int &numCapturas);

void separador(ofstream &salida, char c, int n);

void encabezado1(ofstream &salida);

void encabezado2(const char* titulo, ofstream &salida);

int buscarPosicionMayorVelocidadEnCapturasCSV(double *velocidadesCapturas, int numCapturas);

void buscarValidosEInvalidos(ofstream &salida, int codigoVehiculo, char categoria, int *codigosVehiculosCapturas,
    double *velocidadesCapturas, int *carrilesCapturas, int *kilometrosCapturas, int *diasCapturas, int *mesCapturas,
    int *aniosCapturas, int *codigosCamarasCapturas, int numCapturas, double &montoLocalInfraccM,
    double &montoLocalInfraccG, int &cantCapturasRegistradasLocal, int &posicionMayorVel);

void imprimirInfoDeCadaVehiculo(ofstream &salida, int codigoVehiculo, char categoria, double *montoInfraccM,
        double *montoInfraccG, int cantCapturasRegistradasLocal, double *velocidadesCapturas, int posicionMayorVel,
        int *diasCapturas, int *mesCapturas, int *aniosCapturas, int i);

void resumenGeneral(ofstream &salida, int numVehiculos, int cantVehiculosInfractores, int cantCapturasValidas,
    double montoTotalInfraccM, double montoTotalInfraccG);

void generarReportes(const char* nombre1, const char* nombre2, int *codigosVehiculos, char *categoriasVehiculos,
    int numVehiculos, int *codigosVehiculosCapturas, double *velocidadesCapturas, int *carrilesCapturas,
    int *kilometrosCapturas, int *diasCapturas, int *mesCapturas, int *aniosCapturas, int *codigosCamarasCapturas,
    int numCapturas, double *montoInfraccM, double *montoInfraccG);

#endif //LAB04_2026_2_FUNCIONESAUXILIARES_H
