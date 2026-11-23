//
// Created by PC on 17/11/2026.
//

#ifndef EJERCICIO_DE_LISTAS_SOBRE_PRODUCTOS_FUNCIONES_H
#define EJERCICIO_DE_LISTAS_SOBRE_PRODUCTOS_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include "Nodo.h"
#include "Producto.h"
using namespace std;

#define ANCHO_REPORTE 72
#define CAP_BUFFER 100

//FUNCIONES PARA LEER, CARGAR, CREAR, MODIFICAR:
void abrirArchLectura(const char* nombreArch, ifstream& archivo);
char* leerCadenaExacta(ifstream& archivo, char delimitador);
void insertarOrdenado(struct Nodo*& lista, struct Producto prodNuevo);
void crearCatalogo(const char* nombreArch, struct Nodo*&lista);
struct Nodo* buscarCodigo(struct Nodo* lista, int codigoBuscado);
void eliminarDeLaLista(struct Nodo* &lista, int codigoBuscado);
void eliminarSinVentas(struct Nodo* &lista);
void agregarProdNuevos(const char* nombreArch, struct Nodo*& lista);
void retirarProductos(const char* nombreArch, struct Nodo*& lista);
void cargarVentas(const char* nombreArch, struct Nodo*& lista);

//FUNCIONES PARA IMPRIMIR:
void imprimirSeparador(ofstream& archivo, char c, int n);
void imprimirEncabezado(ofstream &archivo, const char *titulo);
void imprimirFecha(ofstream &archivo, int fecha);
void imprimirVentas(struct Nodo *puntero, ofstream &salida);
void imprimirResumenFinal(ofstream &salida, int cantProdTotal, int cantUnidadesTotal, double montoTotal);

//FUNCIONES PARA GENERAR REPORTES:
void abrirArchEscritura(const char* nombreArch, ofstream& archivo);
void generarReporte(const char *nombreArch, struct Nodo *lista, int tipoReporte);

//FUNCIONES PARA LIBERAR MEMORIA:
void liberarMemoria(struct Nodo *&lista);

#endif //EJERCICIO_DE_LISTAS_SOBRE_PRODUCTOS_FUNCIONES_H
