//
// Created by PC on 25/11/2026.
//

#ifndef LAB09_2026_2_P2_FUNCIONESAUXILIARES_H
#define LAB09_2026_2_P2_FUNCIONESAUXILIARES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include "NodoDoble.h"
using namespace std;

void abrirArchLectura(const char* nombreArch, ifstream& archivo);

void insertarAlFinal(struct NodoDoble* &lista, char nuevoDato);

void leerPalabra(const char* nombreArch, struct NodoDoble* &lista);

bool esPalindromo(struct NodoDoble* lista);

void imprimirEnOrden(struct NodoDoble* lista);

void imprimirEnOrdenInverso(struct NodoDoble* lista);

void mostrarEnPantalla(struct NodoDoble* lista);

void eliminarLista(struct NodoDoble* &lista);

#endif //LAB09_2026_2_P2_FUNCIONESAUXILIARES_H
