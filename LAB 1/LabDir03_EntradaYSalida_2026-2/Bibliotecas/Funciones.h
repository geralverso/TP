//
// Created by PC on 6/09/2026.
//

#ifndef LABDIR03_ENTRADAYSALIDA_2026_2_FUNCIONES_H
#define LABDIR03_ENTRADAYSALIDA_2026_2_FUNCIONES_H

#define ANCHO_DEL_REPORTE  137

void separador(char c, int n);

// ///////////////////////////////////////////////////////////////////////////////// PARTE 1
void encabezado1();
bool leerImprimirDNI();
void leerImprimirNyA_reporte1();
void leerImprimirAseguradoras();
void leerimprimirCodigoCliente();
void leerImprimirFechas();
void leerImprimirMonto();
void leerImprimirEdad_reporte1();
void leerImprimirDAtos();
void leerEscribirAsegurados();

// ///////////////////////////////////////////////////////////////////////////////// PARTE 2
void generarReportePolizas(int dFijo, int mFijo, int aFijo);
void encabezado2();
bool leerImprimirNyA_reporte2();
void leerImprimirInfo_reporte2(int dd, int mm, int aa, int dFijo, int mFijo, int aFijo);
int convertirADias(int dd, int mm, int aa);
void ignorarCampo();

#endif //LABDIR03_ENTRADAYSALIDA_2026_2_FUNCIONES_H
