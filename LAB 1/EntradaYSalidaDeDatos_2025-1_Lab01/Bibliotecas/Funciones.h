//
// Created by PC on 6/09/2026.
//

#ifndef ENTRADAYSALIDADEDATOS_2025_1_LAB01_FUNCIONES_H
#define ENTRADAYSALIDADEDATOS_2025_1_LAB01_FUNCIONES_H

#define ANCHO_DEL_REPORTE 200

#define MONTO_LEVE 158.33
#define MONTO_GRAVE 516.75
#define MONTO_MUY_GRAVE 3920.25

#define INCREMENTO_MULTA_P 0.027
#define INCREMENTO_MULTA_M 0.117
#define INCREMENTO_MULTA_C 0.153

#define INCREMENTO_MULTA_ANTES_FECHAINICIAL 0.1075
#define INCREMENTO_MULTA_ENTRE_FECHAINICIALFINAL 0.0725
#define INCREMENTO_MULTA_LUEGO_FECHAFINAL 0.000

#define INCREMENTO_MULTA_MAÑANA 0.085
#define INCREMENTO_MULTA_TARDE 0.058
#define INCREMENTO_MULTA_NOCHE 0.037

void separador(char c, int n);

void leerImprimirNombres();

void encabezadoPrincipal(int ddi, int mmi, int aai, int ddf, int mmf, int aaf);

bool infoVehiculosInfraccionados(int fechaInicial, int fechaFinal, double &multaTotalDeLaCompania,
    double &monto1Total,double &monto2Total, double &monto3Total, double &multaTotalAPagarTotal,bool seMuestraLaInfo);

void encabezadoPagoTotal(double multaTotalDeLaCompania, double monto1Total, double monto2Total, double monto3Total,
    double multaTotalAPagarTotal);

void resumenFinal(double multaTotalDeTodasLasCompanias, int DNI_companiaMayorPagoInfracciones,
    double mayorMontoTotalPagadoCompania, int DNI_companiaMenorPagoInfracciones, double menorMontoTotalPagadoCompania);

void generarReporte(int ddi, int mmi, int aai, int ddf,int mmf,int aaf);


#endif //ENTRADAYSALIDADEDATOS_2025_1_LAB01_FUNCIONES_H
