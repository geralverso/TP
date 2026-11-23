//
// Created by PC on 21/11/2026.
//

#ifndef EJERCICIO01_LISTA_DOBLE_RESUELTO_POR_MI_FUNCIONES_H
#define EJERCICIO01_LISTA_DOBLE_RESUELTO_POR_MI_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "NodoDoble.h"
using namespace std;


void abrirArchLectura(const char* nombreArch, ifstream& archivo);

void insertarAlInicio(struct NodoDoble* &lista, int nuevoDato);

void insertarAlFinal(struct NodoDoble* &lista, int nuevoDato);

void insertarOrdenado(struct NodoDoble* &lista, int nuevoDato);

void cargarNumeros(const char* nombreArch, struct NodoDoble* &lista);

void eliminarDeLaLista(struct NodoDoble* &lista, int datoAEliminar);

void eliminarMenores(struct NodoDoble* &lista, int datoMinimo);

void imprimirEnOrden(ofstream &salida, struct NodoDoble *lista);

void imprimirEnOrdenInverso(ofstream &salida, struct NodoDoble *lista);

void abrirArchEscritura(const char* nombreArch, ofstream& archivo);

void generarReporte(const char* nombreArch, struct NodoDoble* lista);

void eliminarLista(struct NodoDoble* &lista);


#endif //EJERCICIO01_LISTA_DOBLE_RESUELTO_POR_MI_FUNCIONES_H
