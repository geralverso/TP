//
// Created by PC on 8/10/2026.
//

#ifndef PREGUNTA2_2026_1_FUNCIONESAUXILIARES_H
#define PREGUNTA2_2026_1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define ANCHO_REPORTE 125
#define CAPACIDAD_MEDICOS 100


//PARA LEER, ACUMULAR Y ARMAR ARREGLOS:
void cargarAtenciones(const char* nombreArchivo, int *codigosMedicos, int *cantAtencionesMedicos,
    int *tiempoTotalAtencionesMedicos, int &numMedicos);
int leerYCalcularTiempoEnSec(ifstream &entrada);
int buscarMedico(int codigoBuscado, int *codigosMedicos, int numMedicos);
void cargarEspecialidades(const char* nombreArchivo, int *codigosEspecialidades, double *tarifasMedicos,
    int &numEspecialidades, int *codigosMedicos, int numMedicos);
double calcularPago(double tarifa, int tiempoSec);
void armarArregloPagos(double *pagosRecibidosMedicos, int numMedicos, double *tarifasMedicos,
    int *tiempoTotalAtencionesMedicos);
void armarArregloTiempoPromedio(int *tiempoPromAtencionesMedicos, int *tiempoTotalAtencionesMedicos, int numMedicos,
    int *cantAtencionesMedicos);
bool eliminarDatos(int *codigosMedicos, int *cantAtencionesMedicos, double *tarifasMedicos, int *codigosEspecialidades,
    int *tiempoPromAtencionesMedicos, int *tiempoTotalAtencionesMedicos, double *pagosRecibidosMedicos, int &numMedicos,
    int posicion);
void eliminarDatosDeLosArreglos(int *codigosMedicos, int *cantAtencionesMedicos, double *tarifasMedicos,
    int *codigosEspecialidades, int *tiempoPromAtencionesMedicos, int *tiempoTotalAtencionesMedicos,
    double *pagosRecibidosMedicos, int &numMedicos);

//PARA IMPRIMIR:
void imprimirSeparador(ofstream &salida, char c, int n);
void imprimirTiempo(ofstream &salida, int tiempo);
void imprimirEncabezado(ofstream &salida, int ancho, int cantCar1, int cantCar2, const char* titulo1, const char* titulo2);
void imprimirCabecerasCompletas(ofstream &salida, int tipo);
void imprimirResumen(ofstream &salida, int numMedicos, double pagoTotal);


//PARA GENERAR REPORTES:
void generarReportePrueba(const char* nombreArchivo, int *codigosMedicos, int *cantAtencionesMedicos,
    int *tiempoTotalAtencionesMedicos, int numMedicos);
void generarReporteAtencionesMedicos(const char* nombreArchivo, int *codigosMedicos, double *tarifasMedicos,
    int *codigosEspecialidades, int *cantAtencionesMedicos, int *tiempoTotalAtencionesMedicos, int numMedicos,
    int *tiempoPromAtencionesMedicos, double *pagosRecibidosMedicos, int tipo);


#endif //PREGUNTA2_2026_1_FUNCIONESAUXILIARES_H
