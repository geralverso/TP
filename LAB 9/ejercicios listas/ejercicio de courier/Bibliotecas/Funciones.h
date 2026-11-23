//
// Created by PC on 17/11/2026.
//

#ifndef EJERCICIO_COURIER_FUNCIONES_H
#define EJERCICIO_COURIER_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Resumen.h"
#include "TotalPorZona.h"
using namespace std;

#define ANCHO_REPORTE 100
#define CAP_BUFFER 50
#define RECARGO 0.15


void abrirArchLectura(const char* nombreArch, ifstream &archivo);

char* leerCadenaExacta(ifstream &archivo, char delimitador);

int calcularFecha(int dia, int mes, int anio);

bool esBisiesto(int anio);

int calcularDias(int mes, int anio);

bool validarFecha(int dia, int mes, int anio);

void insertarOrdenado(struct Nodo *&lista, struct Envio envioAux);

void cargarEnvios(const char* nombreArch, struct Nodo*& lista, struct Resumen& resumen);

struct Nodo * buscarDNI(struct Nodo *lista, int dniBuscado, char cliente);


void procesarClientes(const char* nombreArch, struct Nodo*& lista);

struct Nodo * buscarDistrito(struct Nodo *lista, int distritoBuscado);

void procesarDestinos(const char* nombreArch, struct Nodo*& lista, struct Resumen& resumen);


void eliminarSinCobertura(struct Nodo*& lista, char *cadena);

struct Nodo* buscarEnvio(struct Nodo* lista, char* codEnvioBuscado);

long long pasarFechaADias(struct Fecha f);

int calcularDiasDeDemora(struct Fecha fechaInicio, struct Fecha fechaFin);

int retornarFechaRegistro(struct Nodo *lista, char* codEnvio);

void registrarEntregas(const char* nombreArch, struct Nodo*& lista, struct Resumen& resumen);

void calcularCostos(struct Nodo*& lista);



void imprimirSeparador(ofstream& archivo, char c, int n);

void imprimirFecha(ofstream& archivo, int dd, int mm, int aa);

void imprimirEncabezado(ofstream &archivo);

void imprimirResumenZona(ofstream &salida, struct TotalPorZona totalPorZona, char zona);

void imprimirResumenZonas(ofstream &salida, struct TotalPorZona totalPorZona);


void abrirArchEscritura(const char* nombreArch, ofstream &archivo);

void generarReporte(const char* nombreArch, struct Nodo* lista, struct Resumen resumen,
    struct TotalPorZona &totalPorZona);


#endif //EJERCICIO_COURIER_FUNCIONES_H
