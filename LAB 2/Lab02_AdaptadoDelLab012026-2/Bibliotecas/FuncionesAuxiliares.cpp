//
// Created by PC on 13/09/2026.
//

#include "FuncionesAuxiliares.h"
#include <iomanip>

bool abrirArchivos(ifstream &entrada, ofstream &salida) {
    entrada.open("ArchivosDeDatos/registrosCarreras.txt");
    salida.open("ArchivosDeReporte/Reporte.txt");
    return entrada.is_open() and salida.is_open();
}

void separador(ofstream &salida, char c, int n) {
    for (int i = 0; i < n; i++) salida << c;
    salida << endl;
}

void encabezado(ofstream &salida) {
    salida << setw(80) << "RESULTADOS DE CARRERAS\n" << endl;
    salida
        << setw(25) << "CORREDOR" << setw(25) << "PAIS" << setw(19) << "NACIMIENTO"
        << setw(6) << "EDAD" << setw(15) << "TIPO_CARRERA" << setw(9) << "INICIO"
        << setw(13) << "FIN" << setw(16) << "DURACION" << setw(11) << "RITMO" << endl;
    separador(salida, '=', ANCHO_DEL_REPORTE);
}

int calcularEdad(ofstream &salida, int diaReferencial, int mesReferencial, int anioReferencial,
    int dia, int mes,int anio) {
    int fechaReferencial=(anioReferencial*10000)+(mesReferencial*100)+diaReferencial;
    int fechaNacimiento=(anio*10000)+(mes*100)+dia;
    return (fechaReferencial-fechaNacimiento)/10000;
}

void imprimirTiempos(ofstream &salida, int hora, int min, int seg) {
    salida << right << setw(2) << setfill('0') << hora << ":" << setw(2) << min << ":"
            << setw(2) << seg << setfill(' ') << setw(6) << " ";
}

int calcularDuracion(ofstream &salida, int horaI, int minI, int segI, int horaF, int minF, int segF) {
    int tiempoInicialSec=(horaI*3600)+(minI*60)+segI;
    int tiempoFinalSec=(horaF*3600)+(minF*60)+segF;
    if (tiempoInicialSec>tiempoFinalSec) tiempoFinalSec=tiempoFinalSec+(24*3600);
    return (tiempoFinalSec-tiempoInicialSec);
}

void imprimirRitmo(ofstream &salida,double ritmo) {
    int ritmoMinutos=(int)ritmo;
    int ritmoSegundos=(ritmo-ritmoMinutos)*60;
    salida << right << setw(2) << setfill('0') << ritmoMinutos << ":"
            << setw(2) << ritmoSegundos << setfill(' ') << endl;
}

void resumen(ofstream &salida, int cantRegistros, int cantRegistros10K, int cantRegistros21K,
    int cantRegistros42K, int codigoCorredorMenorRitmo, int codigoCorredorMayorRitmo,
    double ritmoMayor, double ritmoMenor) {
    separador(salida, '=', ANCHO_DEL_REPORTE);
    salida << "RESUMEN: " << endl;
    separador(salida, '-', 50);
    salida << "CANTIDAD DE REGISTROS PROCESADOS: " << cantRegistros << endl;
    separador(salida, '-', 50);
    salida << "CANTIDAD DE REGISTROS POR TIPO DE CARRERA: " << endl;
    salida << "10K - " << cantRegistros10K << endl;
    salida << "21K - " << cantRegistros21K << endl;
    salida << "42K - " << cantRegistros42K << endl;
    separador(salida, '-', 50);
    salida << "CORREDOR CON MENOR RITMO: " << right << setw(5) << setfill('0')
            << codigoCorredorMenorRitmo << " - " << setfill(' ');
    imprimirRitmo(salida, ritmoMenor);
    salida << "CORREDOR CON MAYOR RITMO: " << right << setw(5) << setfill('0')
            << codigoCorredorMayorRitmo << " - " << setfill(' ');
    imprimirRitmo(salida, ritmoMayor);
}

void leerImprimirCadena(ifstream &entrada, ofstream &salida, int anchoColumna) {
    char c;
    int cantCaracteres=0;
    while (true) {
        c=entrada.get();
        if (c==' ') break;
        if (c=='_') c=' ';
        if (c>='a' && c<='z') c=c-32;
        salida << c;
        cantCaracteres++;
    }
    salida << setw(anchoColumna-cantCaracteres) << " ";
}

void generarReporte(ifstream &entrada, ofstream &salida, int diaReferencial, int mesReferencial,
    int anioReferencial) {
    encabezado(salida);
    int tipoDeCarrera, codigoDelCorredor, dia, mes, anio, horaI, minI, segI, horaF, minF, segF;
    int cantRegistros=0, cantRegistros10K=0, cantRegistros21K=0, cantRegistros42K=0;
    int codigoCorredorMenorRitmo, codigoCorredorMayorRitmo;
    double ritmoMayor=-1.0, ritmoMenor=999999.9999;
    char c;

    while (entrada>>tipoDeCarrera) {
        cantRegistros++;
        entrada >> codigoDelCorredor >> ws;
        salida << right << setw(5) << setfill('0') << codigoDelCorredor << setfill(' ') << "  ";

        leerImprimirCadena(entrada, salida, 35+2); //PARA EL NOMBRE
        entrada >> ws;
        leerImprimirCadena(entrada, salida, 15); //PARA EL PAIS

        entrada
            >> ws >> dia >> c >> mes >> c >> anio >> horaI >> c >> minI >> c >> segI >> horaF
            >> c >> minF >> c >> segF;
        salida << right << setw(2) << setfill('0') << dia << "/" << setw(2) << mes << "/"
                << setw(4) << anio << setfill(' ');

        int edad=calcularEdad(salida, diaReferencial, mesReferencial, anioReferencial,dia, mes, anio);
        salida << right << setw(5) << edad;

        int distanciaKM;
        if (tipoDeCarrera==2) {
            salida << right << setw(12) << "10K";
            distanciaKM=10;
            cantRegistros10K++;
        }
        else if (tipoDeCarrera==3) {
            salida << right << setw(12) << "21K";
            distanciaKM=21;
            cantRegistros21K++;
        }
        else { //tipoDeCarrera==4
            salida << right << setw(12) << "42K";
            distanciaKM=42;
            cantRegistros42K++;
        }
        salida << setw(6) << " ";

        imprimirTiempos(salida, horaI, minI, segI);
        imprimirTiempos(salida, horaF, minF, segF);

        int duracionSec=calcularDuracion(salida, horaI, minI, segI, horaF, minF, segF);
        int horaDuracion=duracionSec/3600;
        int minduracion=(duracionSec%3600)/60;
        int segDuracion=duracionSec%60;
        imprimirTiempos(salida, horaDuracion, minduracion, segDuracion);

        double ritmo=((double)duracionSec/60)/distanciaKM;
        imprimirRitmo(salida, ritmo);
        if (ritmo<ritmoMenor) {
            ritmoMenor=ritmo;
            codigoCorredorMenorRitmo=codigoDelCorredor;
        }
        if (ritmo>ritmoMayor) {
            ritmoMayor=ritmo;
            codigoCorredorMayorRitmo=codigoDelCorredor;
        }
    }
    resumen(salida, cantRegistros, cantRegistros10K, cantRegistros21K, cantRegistros42K,
        codigoCorredorMenorRitmo, codigoCorredorMayorRitmo,ritmoMayor, ritmoMenor);
}

void cerrarArchivos(ifstream &entrada, ofstream &salida) {
    entrada.close();
    salida.close();
}
