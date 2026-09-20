//
// Created by PC on 15/09/2026.
//

#include "Funciones.h"
#include <iomanip>

bool abrirArchivos(ifstream &entrada, ofstream &salida) {
    entrada.open("ArchivosDeDatos/sensores.json");
    salida.open("ArchivosDeReportes/Reporte.txt");
    return entrada.is_open() && salida.is_open();
}

void separador(ofstream &salida, char c, int n) {
    for (int i = 0; i < n; i++) salida << c;
    salida << endl;
}

void encabezado(ofstream &salida) {
    separador(salida, '-', 73);
    salida << "REPORTE DE SENSORES A / B" << endl;
    separador(salida, '-', 73);
    salida << left << setw(ANCHO_REPORTE/10) << "Sensor"
            << right << setw(ANCHO_REPORTE/6) << "Lecturas"
            << right << setw(ANCHO_REPORTE/6) << "Promedio"
            << right << setw(ANCHO_REPORTE/6) << "Minimo"
            << right << setw(ANCHO_REPORTE/6) << "Maximo"
            << right << setw(ANCHO_REPORTE/7) << "Rango" << endl;
    separador(salida, '-', 73);
}

void acumularDatos(double lectura, double &lecturaMinima, double &lecturaMaxima, int &cantLecturas, //CONSTRUYE LOS RESULTADOS
    double &sumaLecturas) {
    if (lectura<lecturaMinima) lecturaMinima = lectura;
    if (lectura>lecturaMaxima) lecturaMaxima = lectura;
    cantLecturas++;
    sumaLecturas+=lectura;
}

void imprimirInfoSensores(ofstream& salida, char sensor, int cantLecturasSensor, double sumaLecturas, //RECIBE LOS RESULTADOS
                          double lecturaMinima, double lecturaMaxima) {
    double promedio=(cantLecturasSensor>0) ? sumaLecturas / cantLecturasSensor : 0.0;
    double rango=lecturaMaxima-lecturaMinima;
    salida << left << setw(ANCHO_REPORTE/10) << sensor
            << right << setw(ANCHO_REPORTE/6) << cantLecturasSensor
            << right << setw(ANCHO_REPORTE/6) << fixed << setprecision(2) << promedio
            << right << setw(ANCHO_REPORTE/6) << fixed << setprecision(2) << lecturaMinima
            << right << setw(ANCHO_REPORTE/6) << fixed << setprecision(2) << lecturaMaxima
            << right << setw(ANCHO_REPORTE/7) << fixed << setprecision(2) << rango << endl;
}

void generarReporte(ifstream &entrada, ofstream &salida) {
    char sensor;
    int numID, cantLineasIgnoradas=0, cantLecturasSensorA=0, cantLecturasSensorB=0;
    double lectura, sumaLecturasSensorA=0.0, sumaLecturasSensorB=0.0;
    double lecturaMinimaA=999.9, lecturaMaximaA=-100.0;
    double lecturaMinimaB=999.9, lecturaMaximaB=-100.0;

    while (entrada.peek()=='{') {
        entrada.ignore(100,':');
        entrada >> numID;
        entrada.ignore(100,':');
        entrada.ignore(100,'"');
        entrada >> sensor;
        entrada.ignore(100,':');
        entrada >> lectura;
        entrada.ignore(100,'\n');

        if (sensor=='A') {
            acumularDatos(lectura, lecturaMinimaA, lecturaMaximaA, cantLecturasSensorA, sumaLecturasSensorA);
        }
        else if (sensor=='B') {
            acumularDatos(lectura, lecturaMinimaB, lecturaMaximaB, cantLecturasSensorB, sumaLecturasSensorB);
        }
        else { //sensor=='C'
            cantLineasIgnoradas++; //no se hace ningún cálculo con sensor=='C'
        }
    }

    encabezado(salida);

    //PARA EL SENSOR A:
    imprimirInfoSensores(salida, 'A', cantLecturasSensorA,  sumaLecturasSensorA,
    lecturaMinimaA, lecturaMaximaA);

    //PARA EL SENSOR B:
    imprimirInfoSensores(salida, 'B', cantLecturasSensorB,  sumaLecturasSensorB,
    lecturaMinimaB, lecturaMaximaB);

    separador(salida, '-', 73);
    salida << "Lineas ignoradas: " << cantLineasIgnoradas << endl;
    separador(salida, '-', 73);
}

void cerrarArchivos(ifstream &entrada, ofstream &salida) {
    entrada.close();
    salida.close();
}