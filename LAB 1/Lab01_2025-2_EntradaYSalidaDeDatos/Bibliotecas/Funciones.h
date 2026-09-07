//
// Created by PC on 6/09/2026.
//

#ifndef LAB01_2025_2_ENTRADAYSALIDADEDATOS_FUNCIONES_H
#define LAB01_2025_2_ENTRADAYSALIDADEDATOS_FUNCIONES_H

#define ANCHO_DEL_REPORTE 110
#define INGRESO_POR_1000REPROD 3.25

void separador(char c, int n);

void encabezadoPrincipal(int ddi, int mmi, int aai, int ddf, int mmf, int aaf);

void leerImprimirNombre();

bool infoUltimasReproducciones(int &duracionTotalReprodSec, int &fechaUltimaPublicacion, int &numTotalReprod,
    double &ingresosPublicidad, bool seMuestraLaInfo, int &cantTotalStreamsCanales,
    int &duracionTotalStreamsCanalesSec);

void resumenDelCanal(int duracionTotalReprodSec, int fechaUltimaPublicacion,int numTotalReprod,
    double ingresosPublicidad);

double calcularIngresoPorPublicidad(int num);

void resumenFinal(int cantTotalStreamsCanales, int duracionTotalStreamsCanalesSec, double ingresosTotalesCanales,
    char n1CodigoCanalMayorIngreso, int n2CodigoCanalMayorIngreso, double mayorIngreso);

void generarReporte(int ddi, int mmi, int aai, int ddf, int mmf, int aaf);

#endif //LAB01_2025_2_ENTRADAYSALIDADEDATOS_FUNCIONES_H
