//
// Created by PC on 9/09/2026.
//

#ifndef LAB01_2026_2_FUNCIONES_H
#define LAB01_2026_2_FUNCIONES_H

#define ANCHO_DEL_REPORTE 141

void separador(char c, int n);

void encabezado();

void leerImprimirCadena(int anchoColumna);

void resumen(int cantRegistrosProcesados, int cantRegisProcesados10K, int cantRegisProcesados21K,
    int cantRegisProcesados42K, int codigoCorredorMenorRitmo, int codigoCorredorMayorRitmo,
    double ritmoMenor, double ritmoMayor);

void generarReporte();

#endif //LAB01_2026_2_FUNCIONES_H
