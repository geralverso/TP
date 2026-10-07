//
// Created by PC on 6/10/2026.
//

#ifndef LAB05_2026_2_FUNCIONESAUXILIARES_H
#define LAB05_2026_2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define CAPACIDAD_CLIENTES 100
#define CAPACIDAD_MOV 20
#define CAPACIDAD_CUOTAS 200
#define ANCHO_REPORTE 78

//PARA LEER, ACUMULAR, VALIDAR Y ALMACENAR EN ARREGLOS:
void cargarClientesTXT(const char* nombreArchivo, int *codigosClientes, char *tiposDeCreditosClientes,
    double *montosDesembolsadosClientes, int &numClientes);
int buscarCliente(int *codigosClientes, int codigoBuscado, int numClientes);
void cargarMovimientosTXT(const char *nombreArchivo, int *codigosClientes, char *tiposDeCreditosClientes,
    double *montosDesembolsadosClientes,  int &numClientes);
bool eliminarDatos(int *codigosClientes, char *tiposDeCreditosClientes, double *montosDesembolsadosClientes,
    int &numClientes, int posicion);
int insertarOrdenado(int *codigosClientes, char *tiposDeCreditosClientes, double *montosDesembolsadosClientes,
    int codigoNuevo, char tipoCreditoCodNuevo, double montoDesembCodNuevo, int &numClientes, int capacidad);
void cargarCuotasCSV(const char* nombreArchivo, int *codigosClientesCuotas, double *montosCuotas,
    double *montosPagadosCuotas, int *cantDiasDeAtrasoCuotas, int *fechasDeVencimientoCuotas, int &numCuotas);
int buscarMayorDiasAtraso(int *codigosClientesCuotas, int *cantDiasDeAtrasoCuotas, int codigoBuscado, int numCuotas,
    int *fechasDeVencimientoCuotas);
void acumularDatosClasificacion(int codigo, int numCuotas, int *codigosClientesCuotas, int *cantDiasDeAtrasoCuotas,
    int &posicionMayorCantDiasAtraso, double &saldoPendienteTotal, double *montosCuotas, double *montosPagadosCuotas,
    int *fechasDeVencimientoCuotas);

//PARA ORDENAR:
void intercambiarInt(int &a, int &b);
void intercambiarDouble(double &a, double &b);
void intercambiarChar(char &a, char &b);
void imprimirTotalClientes(ofstream &salida, int numClientes);
void ordenarPorCodigoConBurbuja(int *codigosClientes, char *tiposDeCreditosClientes,
    double *montosDesembolsadosClientes, int numClientes);
void ordenarPorDiasAtrasoConSeleccion(int *cantDiasDeAtrasoCuotas, int *codigosClientes, char *tiposDeCreditosClientes,
    int *fechasDeVencimientoCuotas, int numClientes, int *codigosClientesCuotas, int numCuotas) ;

//PARA IMPRIMIR:
void imprimirSeparador(ofstream &salida, char c, int n);
void imprimirEncabezado1y2(ofstream &salida, const char *titulo);
void imprimirEncabezado3(ofstream &salida);
void imprimirFecha(ofstream &salida, int fecha);

//PARA GENERAR REPORTES:
void emitirReporteClientes(const char* nombreArchivo, int *codigosClientes, char *tiposDeCreditosClientes,
    double *montosDesembolsadosClientes, int numClientes);
void emitirReporteClientesMov(const char *nombreArchivo, int *codigosClientes, char *tiposDeCreditosClientes,
    double *montosDesembolsadosClientes, int numClientes);
void emitirReporteClasificacionCartera(const char* nombreArchivo, int *codigosClientesCuotas, double *montosCuotas,
    double *montosPagadosCuotas, int *cantDiasDeAtrasoCuotas, int *fechasDeVencimientoCuotas, char *tiposDeCreditosClientes,
    int *codigosClientes, int numCuotas, int numClientes);

#endif //LAB05_2026_2_FUNCIONESAUXILIARES_H
