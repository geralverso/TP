//
// Created by PC on 30/10/2026.
//

#ifndef EJERCICIO_TEXT_MINING_FUNCIONES_H
#define EJERCICIO_TEXT_MINING_FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

#define ANCHO_REPORTE 60
#define CAP_OTROS 350
#define CAP_PALABRAS 1500
#define CAP_PALABRA 20
#define CAP_DESCONOCIDOS 100

//FUNCIONES PARA CARGAR Y LEER:
void abrirArchLectura(const char* nombreArch, ifstream& archivo);
char* leerCadena(ifstream &entrada, char delimitador);
void llenarDiccionario(ifstream &entrada, char**dic);
void cargarDiccionario(const char* nombreArch, char**dic, int &num);
void leerTexto(const char* nombreArch, char **dicOtros, char **dicPalabras, char** dicDesconocidas, int numOtros,
    int numPalabras, int &numDesconocidas, int *cantAparicionesOtros, int *cantAparicionesPalabras,
    int *cantAparicionesDesconocidas);
int buscarPalabra(char **dic, const char* palabraBuscada, int num);
int buscarBinariaPalabra(char **dic, const char* palabraBuscada, int num);

//FUNCIONES PARA ORDENAR:
void intercambiarEntero(int &a, int&b);
void intercambiarCadena(char*& a, char*& b);
void ordenarDiccionario(char** dic, int num);
void ordenarDesconocidas(char **dicDesconocidas, int numDesconocidas, int *cantAparicionesDesconocidas);
void ordenarHistograma(int numPalabras, int *cantAparicionesPalabras, char **dicPalabras);
void ordenarRankingGeneral(char** dicCompleto, int *cantApariciones, char** categorias, int numElementos);

//FUNCIONES PARA TOKENIZAR:
void normalizarPalabra(char *cad);
void pasarAMinuscula(char* cad);
void eliminarSignos(char* cad);

//FUNCIONES PARA CALCULAR O ARMAR:
void copiarDatos(int num, char **dicDestino, char **dicFuente, int *cantDestino, const int *cantFuente, char **cat,
    const char *nombre, int &k);
void calcularCantPalabras(ifstream &entrada, int &num);
int calcularCantTokens(const int *cantApariciones, int num);
int calcularCantDistintas(const int *cantApariciones, int num);

//FUNCIONES PARA IMPRIMIR:
void imprimirSeparador(ofstream& salida, char c, int n);
void imprimirEncabezadoResumenGeneral(ofstream &salida);
void imprimirInfoCategoria(ofstream &salida, const char *categoria, int cant, int total, int *cantApariciones, int num);
void imprimirResumenGeneral(ofstream &salida, int cantPalabras, int total, int *cantAparicionesPalabras, int numPalabras,
    int cantOtros, int *cantAparicionesOtros, int numOtros, int cantDesconocidas, int *cantAparicionesDesconocidas,
    int numDesconocidas);
void imprimirConteo(ofstream &salida, char c, int n);
void imprimirEncabezadoRankingGeneral(ofstream &salida);

//FUNCIONES PARA GENERAR REPORTES:
void abrirArchEscritura(const char* nombreArch, ofstream& archivo);
void generarReporteSimple(const char *nombreArch, char **dicOtros, char **dicPalabras, int numOtros, int numPalabras);
void generarListaDesconocidas(const char *nombreArch, char **dicDesconocidas, int numDesconocidas,
    const int *cantAparicionesDesconocidas);
void generarResumenGeneral(const char* nombreArch, int numOtros, int numPalabras, int numDesconocidas,
    int *cantAparicionesOtros, int *cantAparicionesPalabras, int *cantAparicionesDesconocidas);
void generarHistograma(const char *nombreArch, int numPalabras, int *cantAparicionesPalabras, char **dicPalabras);
void generarRankingGeneral(const char* nombreArch, int numOtros, int numPalabras, int *cantAparicionesOtros,
    int *cantAparicionesPalabras, char **dicOtros, char **dicPalabras);

//FUNCIONES PARA LIBERAR RECURSOS:
void liberarMemoria(char** dicOtros, char** dicPalabras, char** dicDesconocidas, int numOtros, int numPalabras,
    int numDesconocidas);


#endif //EJERCICIO_TEXT_MINING_FUNCIONES_H
