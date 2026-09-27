//
// Created by PC on 25/09/2026.
//

#include "Funciones.h"

void cargarTeoria(const char *nombreArchivo, int *codigosNotasTeo, char *secciones, double *notas_teoricas,
    int &numNotasTeoricas) {

    ifstream entrada(nombreArchivo);
    if(!entrada) {
        cerr << "No se pudo abrir el archivo." << endl;
        exit(1);
    }

    numNotasTeoricas=0;
    int codigoNotaTeo;
    char seccion;
    double notaTeorica;
    while (entrada >> codigoNotaTeo) {
        entrada >> seccion >> notaTeorica;
        codigosNotasTeo[numNotasTeoricas]=codigoNotaTeo;
        secciones[numNotasTeoricas]=seccion;
        notas_teoricas[numNotasTeoricas]=notaTeorica;
        numNotasTeoricas++;
    }
}

void cargarPractica(const char *nombreArchivo, int *codigosNotasPrac, double *notas_practica, int &numNotasPracticas) {

    ifstream entrada(nombreArchivo);
    if(!entrada) {
        cerr << "No se pudo abrir el archivo." << endl;
        exit(1);
    }

    numNotasPracticas=0;
    int codigoNotaPrac;
    double notaPractica;
    while (entrada >> codigoNotaPrac) {
        entrada >> notaPractica;
        codigosNotasPrac[numNotasPracticas]=codigoNotaPrac;
        notas_practica[numNotasPracticas]=notaPractica;
        numNotasPracticas++;
    }
}

void separador(ofstream &archivo, char c, int n) {
    for (int i=0; i<n; i++) archivo << c;
    archivo << endl;
}

void encabezadoPrincipal(ofstream &archivo) {
    separador(archivo, '=', ANCHO_REPORTE);
    archivo << right << setw((ANCHO_REPORTE+67)/2) << "REPORTE DE NOTAS FINALES (TEORIA + PRACTICA) - INSTITUTO SAN MARCOS" << endl;
    separador(archivo, '=', ANCHO_REPORTE);
    archivo << left << setw(ANCHO_REPORTE/6) << "CODIGO" << setw(ANCHO_REPORTE/6) << "SECCION" << setw(ANCHO_REPORTE/6) << "TEORIA"
            << setw(ANCHO_REPORTE/6) << "PRACTICA" << setw(ANCHO_REPORTE/6) << "NOTA FINAL" << setw(ANCHO_REPORTE/6) << "CONDICION" << endl;
    separador(archivo, '-', ANCHO_REPORTE);
}

void encabezadoResumen(ofstream &archivo) {
    separador(archivo, '=', ANCHO_REPORTE);
    archivo << right << setw((ANCHO_REPORTE+19)/2) << "RESUMEN POR SECCION" << endl;
    separador(archivo, '=', ANCHO_REPORTE);
}

void resumenPorSeccion(ofstream &archivo, char seccion, int cantEstudiantes, double promedioNotasTeo,
    double promedioNotasPrac,double promedioNotasFinal, int cantAprobados, int cantDesaprobados,
    double *notas_finales, char *secciones, int numNotasTeoricas, int *codigosNotasTeo) {
    archivo << "Seccion " << seccion << ":" << endl;
    archivo << left << setw(29) << "  Total de estudiantes" << ": " << cantEstudiantes << endl;
    archivo << left << setw(29) << "  Promedio teoria" << ": " << fixed << setprecision(2) << promedioNotasTeo << endl;
    archivo << left << setw(29) << "  Promedio practica" << ": " << fixed << setprecision(2) << promedioNotasPrac << endl;
    archivo << left << setw(29) << "  Promedio nota final" << ": " << fixed << setprecision(2) << promedioNotasFinal << endl;
    archivo << left << setw(29) << "  Aprobados" << ": " << cantAprobados << endl;
    archivo << left << setw(29) << "  Desaprobados" << ": " << cantDesaprobados << endl;

    int posicionNotaFinalMayor=buscarPosNotaFinalMasAltaDeCadaSeccion(seccion, notas_finales, secciones, numNotasTeoricas);
    if (posicionNotaFinalMayor!=-1) {
        archivo << left << setw(29) << "  Nota final mas alta" << ": " << fixed << setprecision(2)
                << notas_finales[posicionNotaFinalMayor] << " (Codigo: " << codigosNotasTeo[posicionNotaFinalMayor]
                << ")" << endl;
    }
}

void resumenTotales(ofstream &archivo, double promedioGeneralCurso, int cantEstudiantes) {
    separador(archivo, '=', ANCHO_REPORTE);
    archivo << "PROMEDIO GENERAL DEL CURSO: " << fixed << setprecision(2) << promedioGeneralCurso << endl;
    archivo << "TOTAL DE ESTUDIANTES: " << cantEstudiantes << endl;
    separador(archivo, '=', ANCHO_REPORTE);
}

int buscarCodigoCoincidenteEnPractica(int *codigosNotasPrac, int codigoNotaPrac, int numNotasPracticas) {
    for (int i=0; i<numNotasPracticas; i++) {
        if (codigosNotasPrac[i] == codigoNotaPrac) {
            return i;
        }
    }
    return -1;
}

int buscarPosNotaFinalMasAltaDeCadaSeccion(char seccionBuscada, double *notas_finales, char *secciones,
    int numNotasTeoricas) {
    if (numNotasTeoricas==0) return -1;
    int posicionMayorNotaFinal=0;
    for (int i=0; i<numNotasTeoricas; i++) {
        if (secciones[i]==seccionBuscada) {  //PARA BUSCAR RESPECTIVAMENTE DENTRO DE CADA SECCION
            if (notas_finales[i]>notas_finales[posicionMayorNotaFinal]) {
                posicionMayorNotaFinal=i;
            }
        }
    }
    return posicionMayorNotaFinal;
}

double calcularNotaFinal(double notaTeoria, double notaPractica) {
    return (notaTeoria*0.6) + (notaPractica*0.4);
}

void resumen(ofstream &archivo, int numNotasTeoricas, int cantEstudiantesA, int cantAprobadosA, int cantDesaprobadosA,
    double *notas_finales, char *secciones, int *codigosNotasTeo, int cantEstudiantesB, int cantAprobadosB,
    int cantDesaprobadosB, int cantEstudiantesC, int cantAprobadosC, int cantDesaprobadosC, double sumaNotasTeoricasA,
    double sumaNotasPracticasA, double sumaNotasFinalesA, double sumaNotasTeoricasB, double sumaNotasPracticasB,
    double sumaNotasFinalesB, double sumaNotasTeoricasC, double sumaNotasPracticasC, double sumaNotasFinalesC) {

    encabezadoResumen(archivo);
    //CALCULAMOS LOS PROMEDIOS:
    double promedioNotasTeoA=(cantEstudiantesA>0)?(sumaNotasTeoricasA/cantEstudiantesA):0.0;
    double promedioNotasPracA=(cantEstudiantesA>0)?(sumaNotasPracticasA/cantEstudiantesA):0.0;
    double promedioNotasFinalA=(cantEstudiantesA>0)?(sumaNotasFinalesA/cantEstudiantesA):0.0;
    double promedioNotasTeoB=(cantEstudiantesB>0)?(sumaNotasTeoricasB/cantEstudiantesB):0.0;
    double promedioNotasPracB=(cantEstudiantesB>0)?(sumaNotasPracticasB/cantEstudiantesB):0.0;
    double promedioNotasFinalB=(cantEstudiantesB>0)?(sumaNotasFinalesB/cantEstudiantesB):0.0;
    double promedioNotasTeoC=(cantEstudiantesC>0)?(sumaNotasTeoricasC/cantEstudiantesC):0.0;
    double promedioNotasPracC=(cantEstudiantesC>0)?(sumaNotasPracticasC/cantEstudiantesC):0.0;
    double promedioNotasFinalC=(cantEstudiantesC>0)?(sumaNotasFinalesC/cantEstudiantesC):0.0;
    double promedioGeneralCurso=(promedioNotasFinalA+promedioNotasFinalB+promedioNotasFinalC)/3;

    resumenPorSeccion(archivo, 'A', cantEstudiantesA,  promedioNotasTeoA, promedioNotasPracA,
        promedioNotasFinalA, cantAprobadosA, cantDesaprobadosA, notas_finales, secciones, numNotasTeoricas, codigosNotasTeo);
    resumenPorSeccion(archivo, 'B', cantEstudiantesB,  promedioNotasTeoB, promedioNotasPracB,
            promedioNotasFinalB, cantAprobadosB, cantDesaprobadosB, notas_finales, secciones, numNotasTeoricas, codigosNotasTeo);
    resumenPorSeccion(archivo, 'C', cantEstudiantesC,  promedioNotasTeoC, promedioNotasPracC,
            promedioNotasFinalC, cantAprobadosC, cantDesaprobadosC, notas_finales, secciones, numNotasTeoricas, codigosNotasTeo);
    resumenTotales(archivo, promedioGeneralCurso, numNotasTeoricas);
}

void generarReporte(const char *nombreArchivo, int *codigosNotasTeo, char *secciones, double *notas_teoricas,
    int numNotasTeoricas, int *codigosNotasPrac, double *notas_practica, int numNotasPracticas, double *notas_finales) {

    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "No se pudo abrir el archivo." << endl;
        exit(1);
    }

    encabezadoPrincipal(salida);
    double sumaNotasTeoricasA=0.0, sumaNotasTeoricasB=0.0, sumaNotasTeoricasC=0.0;
    double sumaNotasPracticasA=0.0, sumaNotasPracticasB=0.0, sumaNotasPracticasC=0.0;
    double sumaNotasFinalesA=0.0, sumaNotasFinalesB=0.0, sumaNotasFinalesC=0.0;
    int cantEstudiantesA=0, cantEstudiantesB=0, cantEstudiantesC=0;
    int cantAprobadosA=0, cantAprobadosB=0, cantAprobadosC=0;
    int cantDesaprobadosA=0, cantDesaprobadosB=0, cantDesaprobadosC=0;

    for (int i=0; i<numNotasTeoricas; i++) {
        //EN EL ARCHIVO teoria.txt
        int codigo=codigosNotasTeo[i];
        char seccion=secciones[i];
        double notaTeoria=notas_teoricas[i];
        int posicion=buscarCodigoCoincidenteEnPractica(codigosNotasPrac, codigo, numNotasPracticas);

        salida << left << setw(ANCHO_REPORTE/6) << codigo << setw(ANCHO_REPORTE/6) << seccion
                << setw(ANCHO_REPORTE/6) << fixed << setprecision(2) << notaTeoria;

        double notaPractica, notaFinal;
        //EN EL ARCHIVO practica.txt
        if (posicion >= 0) { //si se encontró su posicion correspondiente
            notaPractica=notas_practica[posicion]; //SOLO SE ALINEA notas_practica con posicion y no con i
            notaFinal=calcularNotaFinal(notaTeoria, notaPractica);
        }
        else{
            notaPractica=0.0;
            notaFinal=calcularNotaFinal(notaTeoria, notaPractica);
        }
        notas_finales[i]=notaFinal; //SE LE ASIGNAN VALORES AL ARREGLO PARA ARMARLO

        salida << left << setw(ANCHO_REPORTE/6) << fixed << setprecision(2) <<  notaPractica
                    << setw(ANCHO_REPORTE/6) << fixed << setprecision(2) <<  notaFinal;

        if (notaFinal>=13) {
            salida << setw(ANCHO_REPORTE/6) << "APROBADO" << endl;
            if (seccion=='A') cantAprobadosA++;
            if (seccion=='B') cantAprobadosB++;
            if (seccion=='C') cantAprobadosC++;
        }
        else {
            salida << "DESAPROBADO" << endl;
            if (seccion=='A') cantDesaprobadosA++;
            if (seccion=='B') cantDesaprobadosB++;
            if (seccion=='C') cantDesaprobadosC++;
        }

        if (seccion=='A') {
            cantEstudiantesA++;
            sumaNotasTeoricasA+=notaTeoria;
            sumaNotasPracticasA+=notaPractica;
            sumaNotasFinalesA+=notaFinal;
        }
        else if (seccion=='B') {
            cantEstudiantesB++;
            sumaNotasTeoricasB+=notaTeoria;
            sumaNotasPracticasB+=notaPractica;
            sumaNotasFinalesB+=notaFinal;
        }
        else if (seccion=='C') {
            cantEstudiantesC++;
            sumaNotasTeoricasC+=notaTeoria;
            sumaNotasPracticasC+=notaPractica;
            sumaNotasFinalesC+=notaFinal;
        }
    }

    resumen(salida, numNotasTeoricas, cantEstudiantesA, cantAprobadosA, cantDesaprobadosA, notas_finales, secciones,
        codigosNotasTeo, cantEstudiantesB, cantAprobadosB, cantDesaprobadosB, cantEstudiantesC, cantAprobadosC,
        cantDesaprobadosC, sumaNotasTeoricasA, sumaNotasPracticasA, sumaNotasFinalesA, sumaNotasTeoricasB,
        sumaNotasPracticasB, sumaNotasFinalesB, sumaNotasTeoricasC, sumaNotasPracticasC, sumaNotasFinalesC);
}
