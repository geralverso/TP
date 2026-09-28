//
// Created by PC on 27/09/2026.
//

#include "Funciones.h"

void cargarAlumnosCSV(const char *nombreArchivo, int *codigosAlumnos, int *ciclosAlumnos, int &numAlumnos) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    numAlumnos=0;
    int codigoAlumno, cicloAlumno;
    char c;
    while (entrada >> codigoAlumno) {
        entrada >> c >> cicloAlumno;
        codigosAlumnos[numAlumnos] = codigoAlumno;
        ciclosAlumnos[numAlumnos] = cicloAlumno;
        numAlumnos++;
    }
}

void cargarNotasCSV(const char *nombreArchivo, int *codigosNotas, double *notas, int &numNotas) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    numNotas=0;
    int codigoAlumnoNota;
    double nota;
    char c;
    while (entrada >> codigoAlumnoNota) {
        entrada >> c >> nota;
        codigosNotas[numNotas] = codigoAlumnoNota;
        notas[numNotas] = nota;
        numNotas++;
    }
}

void cargarConsultasTXT(const char *nombreArchivo, int *codigosConsultas, int &numConsultas) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    numConsultas=0;
    int codigoAlumnoConsulta;
    while (entrada >> codigoAlumnoConsulta) {
        codigosConsultas[numConsultas] = codigoAlumnoConsulta;
        numConsultas++;
    }
}

int buscarPosAlumnoConsultasEnAlumnosCSV(int *codigosAlumnos, int codAlumnoBuscado, int numAlumnos) {
    for (int i = 0; i < numAlumnos; i++) {
        if (codigosAlumnos[i] == codAlumnoBuscado) {
            return i;
        }
    }
    return -1;
}

int calcularCantidadNotas(int *codigosNotas, int codigoAlumnoBuscado, int numNotas) {
    int cantNotas=0;
    for (int i=0; i < numNotas; i++) {
        if (codigosNotas[i] == codigoAlumnoBuscado) {
            cantNotas++;
        }
    }
    return cantNotas;
}

void generarReporte(const char *nombreArchivo, int *codigosAlumnos, int *ciclosAlumnos, int numAlumnos,
    int *codigosNotas, double *notas, int numNotas, int *codigosConsultas, int numConsultas) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "No se pudo abrir el archivo" << endl;
        exit(1);
    }

    salida << "REGISTROS DE CONSULTAS" << endl;
    salida << left << setw(11) << "CODIGO" << setw(22) << "¿ESTÁ REGISTRADO?" << setw(8)
            << "CICLO" << setw(12) << "CANT. NOTAS" << endl;

    for (int i = 0; i < numConsultas; i++) {
        int codigoAlumnoConsulta=codigosConsultas[i];
        salida << left << setw(11) << codigoAlumnoConsulta;

        int posicion=buscarPosAlumnoConsultasEnAlumnosCSV(codigosAlumnos, codigoAlumnoConsulta, numAlumnos);
        if (posicion>=0) salida << setw(20) << "si" << setw(8) << ciclosAlumnos[posicion];
        else salida << setw(20) << "no" << setw(8) << "-";

        int cantNotas=calcularCantidadNotas(codigosNotas, codigoAlumnoConsulta, numNotas);
        salida << setw(12) << cantNotas << endl;
    }
}
