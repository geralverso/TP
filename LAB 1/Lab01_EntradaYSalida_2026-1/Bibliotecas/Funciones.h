//
// Created by PC on 2/09/2026.
//

#ifndef LAB01_ENTRADAYSALIDA_2026_1_FUNCIONES_H
#define LAB01_ENTRADAYSALIDA_2026_1_FUNCIONES_H

#define ANCHO_DEL_REPORTE 180
#define COSTO_POR_3600SEC 575.00

void separador(char c, int n);

void encabezado(int di, int mi, int ai, int df, int mf, int af);

void secciones();

bool infoSecciones(int &cantAtenciones, int &cantPacientesNivelNormal, int &cantPacientesNivelHiper2,
    int &n1MayorPreArtMed, int &n2MayorPreArtMed, int &n3MayorPreArtMed,double &mayorPreArtMed, int &tiempoTotalAtencionesSec,
    double &costoTotalAtenciones, bool seMuestraLaInfo);

double calcularCostoPorAtencion(int duracionAtencionSec);

double calcularPresArtMedia(int sistolica, int diastolica);

void leerImprimirID(int n1, int n2, int n3);

void leerImprimirNombre(bool seMuestraLaInfo);

void resumenDelCanal(int cantAtenciones, int cantPacientesNivelNormal, int cantPacientesNivelHiper2,
    int n1MayorPreArtMed, int n2MayorPreArtMed, int n3MayorPreArtMed, double mayorPreArtMed, int tiempoTotalAtencionesSec,
    double costoTotalAtenciones);

void resumenFinal(int cantAtencionesDeTodosLosCanales, int tiempoTotalTodasLasAtencionesSec,
    double costoTotalTodasLasAtenciones);

void generarReporte(int di, int mi, int ai, int df, int mf, int af);

#endif //LAB01_ENTRADAYSALIDA_2026_1_FUNCIONES_H
