//
// Created by PC on 9/10/2026.
//

#ifndef EJERCICIO2_FUNCIONES_H
#define EJERCICIO2_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define ANCHO_REPORTE1 90
#define ANCHO_REPORTE2 66
#define CAPACIDAD_USUARIOS 50


// ----------------------------------------------------- REPORTE 1:

bool abrirArchivos(ifstream &planes, ifstream &usuarios, ifstream &llamadas, ofstream &salida);

void imprimirSeparador(ofstream &salida, char c, int n);

void leerEImprimirNombres(ifstream &entrada, ofstream &salida, bool seMuestra);

void imprimirTiempoOFecha(int a, int b, int c, char tipo, ofstream &salida);

int calcularDuracionSec(int hora1, int min1, int seg1, int hora2, int min2, int seg2);

double leerEImprimirPlan_Y_ObtenerPrecio(ifstream &usuarios, ifstream &planes, ofstream &salida);

void buscarLlamadas(ifstream &llamadas, ofstream &salida, int telefono, int &cantLlamadasPorNumero,
    int &tiempoDuracionSecTotal);

void imprimirResumenDeCadaUsuario(ofstream &salida, int tiempoDuracionSecTotal, int cantLlamadasPorNumero, double precio,
    double &monto);

void imprimirResumenFinal(ofstream &salida, int cantUsuarios, int cantLlamadas, double montoTotal);

void generarReporte1(ifstream &planes, ifstream &usuarios, ifstream &llamadas, ofstream &salida);

void cerrarArchivos(ifstream &planes, ifstream &usuarios, ifstream &llamadas, ofstream &salida);


// ----------------------------------------------------- REPORTE 2:

void cargarUsuarios(const char* nombreArchivo, int *dnisUsuarios, int *telefonosUsuarios, int &numUsuarios);

void cargarLlamadas(const char *nombreArchivo, int *telefonosUsuarios, int numUsuarios, int *cantLlamadasUsuarios,
    int *duracionTotalLlamadas, int *fechaUltimasLlamadas, int &numLlamadas);

int buscarPosTelefono(int *telefonosUsuarios, int telefonoBuscado, int numUsuarios);

void imprimirEncabezado(ofstream &salida);

void imprimirResumen(ofstream &salida, int numLlamadas, int duracionTotalSec);

void generarReporte2(const char* nombreArchivo,  int *dnisUsuarios, int *telefonosUsuarios, int &numUsuarios,
    int *cantLlamadasUsuarios, int *duracionTotalLlamadas, int *fechaUltimasLlamadas, int numLlamadas);

#endif //EJERCICIO2_FUNCIONES_H
