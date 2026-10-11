//
// Created by PC on 9/10/2026.
//

#ifndef INC_2026_2__EXTRAS__FUNCIONES_H
#define INC_2026_2__EXTRAS__FUNCIONES_H

#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

#define ANCHO_REPORTE1 62
#define ANCHO_REPORTE2 55
#define CAPACIDAD_CURSOS 50


// ---------------------------------------------- REPORTE 1:

void imprimirSeparador(ofstream &salida, char c, int n);

bool abrirArchivos(ifstream &cursos, ifstream &registro, ofstream &salida);

void buscarCursosDelEstudiante(ifstream &registro, ifstream &cursos, ofstream &salida, int &cantCursosPorEstudiante,
    int &totalCreditosPorEstudiante, double &promedioGeneralEstudiante);

void buscarNombreYCreditosDelCurso(ifstream &cursos, ofstream &salida, int codigoCurso, int &sumaCreditos,
    double &notasPorCreditos, double nota);

double calcularPromedioPonderado();

void leerEImprimirNombre(ifstream &entrada, ofstream &salida, bool seMuestra);

void imprimirEncabezado1(ofstream &salida, int codigoEstudiante) ;

void imprimirResumen(ofstream &salida, int cantCursosPorEstudiante, int totalCreditosPorEstudiante, double promPonderado);

void generarReporte1(ifstream &cursos, ifstream &registro, ofstream &salida);

void cerrarArchivos(ifstream &cursos, ifstream &registro, ofstream &salida);


// ---------------------------------------------- REPORTE 2:

void cargarCursos(const char* nombreArchivo, int *codigosCursos, int &numCursos);

int insertarOrdenadoCursos(int *codigosCursos, int codCursoNuevo, int &numCursos, int capacidad);

void cargarRegistroNotas(const char *nombreArchivo, int *codigosCursos, int numCursos, int *cantEstudiantesCursos,
    int *cantAprobadosCursos, int *cantDesaprobadosCursos, double *promediosCursos, int &numAlumnos);

int buscarBinariaCurso(int *codigosCursos, int numCursos, int codigoBuscado);

void intercambiarInt(int &a, int &b);

void intercambiarDouble(double &a, double &b);

void ordenarCantEstudiantesAprobadosYPromedios_Burbuja(int *codigosCursos, int numCursos, int *cantEstudiantesCursos,
    int *cantAprobadosCursos, int *cantDesaprobadosCursos, double *promediosCursos);

void imprimirEncabezado2(ofstream &salida);

void generarReporte2(const char* nombreArchivo, int *codigosCursos, int numCursos, int *cantEstudiantesCursos,
    int *cantAprobadosCursos, int *cantDesaprobadosCursos, double *promediosCursos);


#endif //INC_2026_2__EXTRAS__FUNCIONES_H
