//
// Created by PC on 25/10/2026.
//

#ifndef EJERCICIO02_RESUELTO_POR_MI_FUNCIONES_H
#define EJERCICIO02_RESUELTO_POR_MI_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define CAPACIDAD_TEXTO 10000
#define CAPACIDAD_POR_LINEA 300
#define CAPACIDAD_PALABRA 50

//FUNCIONES PROPIAS:
int mi_strlen(const char* cadena);
void mi_strcpy(char* destino, const char* fuente);
void mi_strcat(char* cadena1, const char* cadena2);
void pasarAMinusculas(char* cadena);
bool corresponde(const char *cadena1, const char *cadena2);
char* mi_strstr(char* cadena1, const char* cadena2);
void reemplazar(char* texto, const char* cadenaBuscada, const char* cadenaReemplazada);

//FUNCIONES PARA CARGAR:
void abrirArchLectura(const char* nombre, ifstream &archivo);
void cargarTexto(const char* nombre, char* texto);
void cargarStopWords(const char* nombre, char* stopWords);

//FUNCIONES PARA NORMALIZAR TEXTO:
bool extraerCadena(char *&cursor, const char* delimitador, char* cadena);
void reemplazarEnTodoElTexto(char* texto, const char* cadenaBuscada, const char* cadenaReemplazada);
void aplicarEquivalencia(char* texto, char* equivalencia);
void aplicamosTodasLasEquivalencias(char* texto, char* equivalencias);
bool esMinuscula(char c);
bool esDigito(char c);
bool esCaracterValido(char c);
void quitarSignos(char* texto);
bool esStopWord(const char *palabra, char* stopWords);
void agregarPalabra(char *textoFinal, const char* palabra);
void filtrarLinea(char* linea, char* stopWords, char* textoFinal);
void quitarStopWords(char* texto, char* stopWords);
void normalizarTexto(char *texto, char *equivalencias, char *stopWords);

//FUNCIONES PARA GENERAR REPORTES:
void abrirArchEscritura(const char* nombre, ofstream &archivo);
void generarTextoNormalizado(const char* nombre, const char* texto);


#endif //EJERCICIO02_RESUELTO_POR_MI_FUNCIONES_H
