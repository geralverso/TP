//
// Created by PC on 25/11/2026.
//

#ifndef LAB09_2026_2_P1_FUNCIONESAUXILIARES_H
#define LAB09_2026_2_P1_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "Nodo.h"
#include "Distrito.h"
#include "Plato.h"
using namespace std;

#define ANCHO_REPORTE1 90
#define ANCHO_REPORTE2 112
#define CAP_BUFFER 50


//FUNCIONES PARA LEER, ACUMULAR, CARGAR, BUSCAR, INSERTAR:
void abrirArchLectura(const char* nombreArch, ifstream& archivo);
void leerPlatos(const char* nombreArch, struct Plato* &plato);
char* leerCadenaExacta(ifstream& archivo, char delimitador);
void leerDistritos(const char* nombreArch, struct Distrito* &distrito);
long long calcularTiempoSec(struct Hora tiempo);
void insertarOrdenado(struct Nodo* &lista, struct Pedido pedidoAux);
struct Plato* buscarPlato(struct Plato* plato, int codPlatoBuscado);
struct Distrito* buscarDistrito(struct Distrito* distrito, int codDistritoBuscado);
void acumularPlatos(ifstream &entrada, struct Plato* plato, struct Pedido &pedidoAux);
void leerPedidos(const char* nombreArch, struct Nodo* &lista, struct Plato* plato, struct Distrito* distrito);

//FUNCIONES PARA ELIMINAR DATOS:
void eliminarPedidos(struct Nodo* &lista, int horaL, int minL, int segL);

//FUNCIONES PARA IMPRIMIR:
void imprimirSeparador(ofstream& archivo, int n, char c);
void imprimirEncabezado1(ofstream &salida);
void imprimirEncabezado2(ofstream &salida, int horaL, int minL, int segL);
void imprimirResumen1(ofstream& salida, int totalPedidos, double costoTotal);
void imprimirResumen2(ofstream &salida, int totalPedidos, double costoTotal, double montoTotalDelivery,
        double montoTotalCobrar);

//FUNCIONES PARA GENERAR REPORTES:
void abrirArchEscritura(const char* nombreArch, ofstream& archivo);
void generarReporte1(const char* nombreArch, struct Nodo* lista);
void generarReporte2(const char *nombreArch, struct Nodo *lista, int horaL, int minL, int segL);

//FUNCIONES PARA LIBERAR MEMORIA:
void eliminarLista(struct Nodo *&lista, struct Distrito* &distrito);


#endif //LAB09_2026_2_P1_FUNCIONESAUXILIARES_H
