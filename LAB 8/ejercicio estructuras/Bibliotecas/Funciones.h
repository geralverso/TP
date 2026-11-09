//
// Created by aml on 7/11/2026.
//

#ifndef EJERCICIO_ESTRUCTURAS_FUNCIONES_H
#define EJERCICIO_ESTRUCTURAS_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Vehiculo.h"
#include "Captura.h"
using namespace std;

#define ANCHO_REPORTE 115
#define CAP_VEHICULOS 350
#define CAP_CAPTURAS 600
#define CAP_BUFFER 30
#define NO_ENCONTRADO (-1)
#define MONTO_M 963.00
#define MONTO_G 428.00
#define PUNTOS_M 100
#define PUNTOS_G 50


//FUNCIONES PARA CARGAR Y LEER:
void abrirArchLectura(const char* nombreArch, ifstream& archivo);
char* leerCadenaExacta(ifstream& archivo, char delimitador);
void cargarAniosRevisiones(ifstream &archivo, struct Vehiculo &vehiculo);
void cargarVehiculos(const char* nombreArch, struct Vehiculo*&vehiculos, int&numVehiculos);
int buscarVehiculo(const struct Vehiculo *vehiculos, int numVehiculos, int codVehiculoBuscado);
void agregarCaptura(struct Captura *arrCapturas, int &cantCapturas, struct Captura &capturaAux);
void cargarCapturas(const char *nombreArch, struct Vehiculo *vehiculos, int numVehiculos);
void acumularInfraccionesM(struct Vehiculo *vehiculos, int i, int carril, double vel, int km);
void acumularInfraccionesG(struct Vehiculo *vehiculos, int i, char cat, int carril);
void identificarInfracciones(struct Vehiculo *vehiculos, int numVehiculos);

//FUNCIONES PARA ORDENAR:
void intercambiarVehiculo(struct Vehiculo &a, struct Vehiculo &b);
void intercambiarCaptura(struct Captura &a, struct Captura &b);
void ordenarCapturas(struct Captura *captura, int numCap);
void ordenarVehiculos(struct Vehiculo *vehiculos, int numVehiculos);

//FUNCIONES PARA IMPRIMIR:
void imprimirSeparador(ofstream& archivo, char c, int n);
void imprimirEncabezado(ofstream &archivo);
void imprimirCabeceraTabla(ofstream &salida, const struct Vehiculo *vehiculos, int i);
void imprimirInfoInfracciones(ofstream &archivo, const struct Vehiculo *vehiculos, int i);
void imprimirFecha(ofstream &archivo, int fecha);
void imprimirCapturas(ofstream &salida, const char* titulo, const struct Captura *capturas, int i, int numCap);
void imprimirCapValidasEInvalidas(ofstream &salida, const struct Vehiculo *vehiculos, int i);

//FUNCIONES PARA GENERAR REPORTES:
void abrirArchEscritura(const char* nombreArch, ofstream& archivo);
void generarReporte(const char* nombreArch, const struct Vehiculo*vehiculos, int numVehiculos);


#endif //EJERCICIO_ESTRUCTURAS_FUNCIONES_H
