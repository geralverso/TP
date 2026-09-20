//
// Created by PC on 16/09/2026.
//

#include "Funciones.h"
#include <iomanip>

bool abrirArchivos(ifstream &entrada, ofstream &estadisticas, ofstream &alertas) {
    entrada.open("ArchivosDeDatos/lecturas_sensores_planta.txt", ios::in);
    estadisticas.open("ArchivosDeReportes/estadisticas_sensores.txt", ios::out);
    alertas.open("ArchivosDeReportes/alertas_sensores.txt", ios::out);
    return entrada.is_open() and estadisticas.is_open() and alertas.is_open();
}

void separador(ofstream &salida, char c, int n) {
    for (int i = 0; i < n; i++) salida << c;
    salida << endl;
}

void cerrarArchivos(ifstream &entrada, ofstream &estadisticas, ofstream &alertas) {
    entrada.close();
    estadisticas.close();
    alertas.close();
}

void encabezadoEstadisticas(ofstream &estadisticas, int ddi, int mmi, int aai, int ddf, int mmf, int aaf) {
    separador(estadisticas, '=', ANCHO_REPORTES);
    estadisticas << "REPORTE DE MONITOREO DE SENSORES" << endl;
    separador(estadisticas, '=', ANCHO_REPORTES);
    estadisticas << "Periodo del reporte: " << right << setw(2) << setfill('0') << ddi << "/"
                    << setw(2) << mmi << "/" << setw(4) << aai << " al " << setw(2) << ddf << "/"
                    << setw(2) << mmf << "/" << setw(4) << aaf << setfill(' ') << endl;
    separador(estadisticas, '-', ANCHO_REPORTES);
}

double infoMedicionesTemp(ifstream &entrada,ofstream &alertas, int &cantMedicionesTemp, int &cantAlertasTemp,
    double &minimaTemp,double &maximaTemp, int &dia, int &mes, int &anio, double &medicionAlertaTemp) {
    double medicion, sumaMediciones=0.0;

    while (entrada.peek()!='\n') {
        if (entrada >> medicion) {
            sumaMediciones+=medicion;
            cantMedicionesTemp++;
            if (!(medicion>=0.0 and medicion<=90.0)) { //EN CASO HAYA UNA ALERTA
                cantAlertasTemp++;                      //SE IMPRIME EN alertas_sensores.txt
                medicionAlertaTemp=medicion;
                imprimirFecha(alertas, dia, mes, anio);
                alertas << left << setw(6) << "T" << setw(28) << "Temperatura (C)" << right << setw(15)
                                << fixed << setprecision(2) << medicionAlertaTemp << endl;
            }
            if (medicion<minimaTemp) minimaTemp=medicion;
            if (medicion>maximaTemp) maximaTemp=medicion;
        }
        else {
            entrada.clear();
            break;
        }
    }
    return sumaMediciones;
}

double infoMedicionesVib(ifstream &entrada, ofstream &alertas, int &cantMedicionesVib, int &cantAlertasVel,
    double &minimaVel,double &maximaVel, int &dia, int &mes, int &anio, double &medicionAlertaVel) {
    double medicion, sumaMediciones=0.0;

    while (entrada.peek()!='\n') {
        if (entrada >> medicion) {
            sumaMediciones+=medicion;
            cantMedicionesVib++;
            if (!(medicion>=0.0 and medicion<=15.0)) { //EN CASO HAYA UNA ALERTA
                cantAlertasVel++;                      //SE IMPRIME EN alertas_sensores.txt
                medicionAlertaVel=medicion;
                imprimirFecha(alertas, dia, mes, anio);
                alertas << left << setw(6) << "V" << setw(28) << "Velocidad (mm/s)" << right << setw(15)
                                << fixed << setprecision(2) << medicionAlertaVel << endl;
            }
            if (medicion<minimaVel) minimaVel=medicion;
            if (medicion>maximaVel) maximaVel=medicion;
        }
        else {
            entrada.clear();
            break;
        }
    }
    return sumaMediciones;
}

void reporteEstadisticas(ofstream &estadisticas, int cantLecturasTemp, int cantAlertasTemp, double promedioTemp,
    double minimaTemp, double maximaTemp, int cantLecturasVel, int cantAlertasVel, double promedioVel,
    double minimaVel, double maximaVel, int cantLecturasDia, int cantLecturasNoche) {

    //TEMPERATURA:
    estadisticas << "TEMPERATURA (T)   -   Lecturas: " << left << setw(5) << cantLecturasTemp
                << "Alertas: " << cantAlertasTemp << endl;
    separador(estadisticas, '-', ANCHO_REPORTES);
    estadisticas << left << setw(22) << "Medicion" << right << setw(12) << "Promedio"
                << setw(12) << "Minimo" << setw(12) << "Maximo" << endl;
    estadisticas << left << setw(22) << "Temperatura (C)" << right << setw(12)
                << fixed << setprecision(2) << promedioTemp
                << setw(12) << minimaTemp << setw(12) << maximaTemp << endl;
    separador(estadisticas, '-', ANCHO_REPORTES);

    //VIBRACION:
    estadisticas << "VIBRACION (V)   -   Lecturas: " << left << setw(5) << cantLecturasVel
                << "Alertas: " << cantAlertasVel << endl;
    separador(estadisticas, '-', ANCHO_REPORTES);
    estadisticas << left << setw(22) << "Medicion" << right << setw(12) << "Promedio"
                << setw(12) << "Minimo" << setw(12) << "Maximo" << endl;
    estadisticas << left << setw(22) << "Velocidad (mm/s)" << right << setw(12)
                << fixed << setprecision(2) << promedioVel
                << setw(12) << minimaVel << setw(12) << maximaVel << endl;
    separador(estadisticas, '-', ANCHO_REPORTES);

    //LECTURAS POR TURNO:
    estadisticas << "LECTURAS POR TURNO" << endl;
    separador(estadisticas, '-', ANCHO_REPORTES);
    estadisticas << left << setw(14) << "Turno" << right << setw(10) << "Lecturas" << endl;
    estadisticas << left << setw(14) << "Dia" << right << setw(10) << cantLecturasDia << endl;
    estadisticas << left << setw(14) << "Noche" << right << setw(10) << cantLecturasNoche << endl;
    separador(estadisticas, '-', ANCHO_REPORTES);

    //TOTAL:
    estadisticas << "Total de alertas registradas en el periodo: " << (cantAlertasTemp+cantAlertasVel) << endl;
    separador(estadisticas, '-', ANCHO_REPORTES);
}

void generarEstadisticasYAlertas(ifstream &entrada, ofstream &alertas, ofstream &estadisticas, int ddi, int mmi, int aai,
    int ddf,int mmf, int aaf) {

    encabezadoEstadisticas(estadisticas, ddi, mmi, aai, ddf, mmf, aaf);
    int fechaInicio=(aai*10000)+(mmi*100)+ddi;
    int fechaFin=(aaf*10000)+(mmf*100)+ddf;

    int dia, mes, anio, hora, min, seg, turnoDiaInicioSec=6*3600, turnoDiaFinSec=(17*3600)+(59*60)+59;
    char c, tipoSensor;

    //DATOS A ACUMULAR:
    int cantLecturasTemp=0, cantAlertasTemp=0, cantMedicionesTemp=0;
    double promedioTemp, minimaTemp=999.99, maximaTemp=-100.0, sumaMedicionesTemp=0;
    int cantLecturasVel=0, cantAlertasVel=0, cantMedicionesVib=0;
    double promedioVel, minimaVel=999.99, maximaVel=-1.0, sumaMedicionesVib=0;
    int cantLecturasNoche=0, cantLecturasDia=0;
    double medicionAlertaTemp, medicionAlertaVel;

    encabezadoAlertas(alertas); //PARA EL .txt DE ALERTAS

    while (entrada >> dia) {
        entrada >> c >> mes >> c >> anio >> hora >> c >> min >> c >> seg >> tipoSensor;
        int fecha=(anio*10000)+(mes*100)+dia;
        int tiempoSec=(hora*3600)+(min*60)+seg;

        if (fecha>=fechaInicio and fecha<=fechaFin) {
            if (tipoSensor=='T') {
                cantLecturasTemp++;
                sumaMedicionesTemp=infoMedicionesTemp(entrada, alertas, cantMedicionesTemp, cantAlertasTemp,
                    minimaTemp, maximaTemp, dia, mes, anio, medicionAlertaTemp);
            }
            else { //tipoSensor=='V'
                cantLecturasVel++;
                sumaMedicionesVib=infoMedicionesVib(entrada,alertas, cantMedicionesVib, cantAlertasVel,
                    minimaVel,maximaVel, dia, mes, anio, medicionAlertaVel);
            }
            //SELECTURAS TURNO DIA-NOCHE:
            if (tiempoSec>=turnoDiaInicioSec and tiempoSec<=turnoDiaFinSec) cantLecturasDia++;
            else cantLecturasNoche++;
        }
    }
    promedioTemp=(cantMedicionesTemp>0)?(sumaMedicionesTemp/cantMedicionesTemp):0.0;
    promedioVel=(cantMedicionesVib>0)?(sumaMedicionesVib/cantMedicionesVib):0.0;

    reporteEstadisticas(estadisticas, cantLecturasTemp, cantAlertasTemp, promedioTemp, minimaTemp, maximaTemp,
        cantLecturasVel, cantAlertasVel, promedioVel, minimaVel,maximaVel, cantLecturasDia, cantLecturasNoche);
}

void encabezadoAlertas(ofstream &alertas) {
    alertas << "LISTADO DE ALERTAS - LECTURAS FUERA DE RANGO" << endl;
    separador(alertas, '-', ANCHO_REPORTES);
    alertas << left << setw(13) << "Fecha" << setw(6) << "Tipo" << setw(28) << "Medicion"
            << right << setw(15) << "Valor" << endl;
    separador(alertas, '-', ANCHO_REPORTES);
}

void imprimirFecha(ofstream &alertas, int dia, int mes, int anio) {
    alertas << right << setw(2) << setfill('0') << dia << "/" << setw(2) << mes << "/"
    << setw(4) << anio << setfill(' ') << setw(3) << " ";
}
