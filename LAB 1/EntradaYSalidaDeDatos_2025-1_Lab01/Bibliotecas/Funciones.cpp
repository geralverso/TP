//
// Created by PC on 6/09/2026.
//

#include "Funciones.h"
using namespace std;
#include <iostream>
#include <iomanip>

void separador(char c, int n) {
    for (int i = 0; i < n; i++) cout <<c;
    cout << endl;
}

void leerImprimirNombres() {
    char c;
    int cantCaracteres=0;
    cin >> ws;
    while (true) {
        c=cin.get();
        if (c==' ') break;
        if (c=='/' or c=='-') c=' ';
        if (c>='a' and c<='z') c=c-32;
        cout << c;
        cantCaracteres++;
    }
    int anchoDeLaCajaDeNombre=50;
    cout << setw(anchoDeLaCajaDeNombre-cantCaracteres) << " ";
}

void encabezadoPrincipal(int ddi, int mmi, int aai, int ddf, int mmf, int aaf) {
    cout << right << setw((ANCHO_DEL_REPORTE+25)/2) << "MINISTERIO DE TRANSPORTE" << endl;
    cout << right << setw((ANCHO_DEL_REPORTE+35)/2) << "MULTAS IMPUESTAS A LAS COMPANIAS" << endl;
    cout
        << setw((ANCHO_DEL_REPORTE+10)/2) << "RANGO DE FECHAS A CONSIDERAR: DEL "
        << right << setw(2) << setfill('0') << ddi << "/" << setw(2) << mmi << "/" << aai
        << " AL " << right <<  setw(2) << ddf << "/" << setw(2) << mmf << "/" << aaf << setfill(' ') << endl;
    separador('=', ANCHO_DEL_REPORTE);
}

bool infoVehiculosInfraccionados(int fechaInicial, int fechaFinal, double &multaTotalDeLaCompania,
    double &monto1Total, double &monto2Total, double &monto3Total,  double &multaTotalAPagarTotal,
    bool seMuestraLaInfo) {

    char c, n1;
    int n2=0, n3; // PLACA: n1n2-n3

    /////////////////////////////////////////////////////////////////////////////////////////////////// PARTE IMPORTANTE
    c=cin.get();
    while (c==' ') c=cin.get();
    if (c=='\n') return false;

    //c=cin.get() YA ATRAPÓ EL 1ER CARACTER DE LA PLACA, EL CUAL ES P DEL P599-629:
    n1=c; //ES DECIR n1=P

    while (cin.get(c) and c!='-') {
        n2=(n2*10)+c-'0';  //1ra vuelta: n2= (0*10)+(5-0) = 5
    }                      //2da vuelta: n2= (5*10)+(9-0) = 59
                            //3ra vuelta: n2= (59*10)+(9-0) = 599
                             //4ta vuelta: NO HAY, porque ahora aparece el '-'

    cin >> n3; //se lee normalmente el ultimo numero que falta de P599-629
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //SE LEE LA FECHA:
    int dd, mm, aa;
    cin >> ws >> dd >> c >> mm >> c >> aa;
    int fechaActual=(aa*10000)+(mm*100)+dd;

    //SE LEE LA HORA
    int hora, min, sec;
    cin >> hora >> c >> min >> c >> sec;
    int tiempoEnSec=(hora*3600)+(min*60)+sec;

    //SE LEE LA GRAVEDAD DE LA MULTA:
    char tipoGravedad;
    cin >> ws >> tipoGravedad;

    //SE HACEN SELECTIVAS PARA EL TIPO DE CARRO (pequeño, mediano, grande):
    if (n1=='P') {
        cout << "- PEQUEÑO" << setw(18-9) << " ";
    }
    else if (n1=='M') {
        cout << "- MEDIANO" << setw(18-9) << " ";
    }
    else if (n1=='C') {
        cout << "- GRANDE" << setw(18-8) << " ";
    }

    //SE IMPRIME LA PLACA:
    cout << n1 << n2 << "-" << n3 << setw(18-8) << " ";

    //SE IMPRIME LA FECHA:
    cout << right << setw(2) << setfill('0') << dd << "/" << setw(2) << mm << "/" << aa << setfill(' ');
    cout << setw(18-10) << " ";

    //SE IMPRIME LA HORA:
    cout << right << setw(2) << setfill('0') << hora << ":" << setw(2) << min << ":";
    cout << setw(2) << sec << setfill(' ') << setw(18-8) << " ";

    //SE CALCULA PARA LA PROXIMA SELECTIVA:
    int inicioManana=(4*3600)+(30*60), finManana=(11*3600)+(25*60);
    int inicioTarde=(11*3600)+(25*60), finTarde=(20*3600)+(40*60);
    int inicioNoche=(20*3600)+(40*60), finNoche=(28*3600)+(30*60);

    double montoTotalAPagar, monto1, monto2, monto3, multa;

    //SE HACEN SELECTIVAS PARA EL TIPO DE GRAVEDAD (leve, grave, muy grave):
    if (tipoGravedad=='L') {
        multa=MONTO_LEVE;
        cout << "LEVE" << setw(18-4) << " " << left << setw(18) << fixed << setprecision(2) << MONTO_LEVE;

        //SELECTIVA PARA EL INCREMENTO POR TIPO DE VEHICULO:
        if (n1=='P') {
            monto1=MONTO_LEVE*INCREMENTO_MULTA_P;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto1;
        }
        else if (n1=='M') {
            monto1=MONTO_LEVE*INCREMENTO_MULTA_M;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto1;
        }
        else if (n1=='C') {
            monto1=MONTO_LEVE*INCREMENTO_MULTA_C;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto1;
        }

        //SELECTIVA PARA EL INCREMENTO POR FECHAS:
        if (fechaActual<fechaInicial) {
            monto2=MONTO_LEVE*INCREMENTO_MULTA_ANTES_FECHAINICIAL;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto2;
        }
        else if (fechaActual>=fechaInicial and fechaActual<=fechaFinal) {
            monto2=MONTO_LEVE*INCREMENTO_MULTA_ENTRE_FECHAINICIALFINAL;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto2;
        }
        else if (fechaActual>fechaFinal) {
            monto2=MONTO_LEVE*INCREMENTO_MULTA_LUEGO_FECHAFINAL;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto2;
        }

        //SELECTIVA PARA EL INCREMENTO POR HORA:
        if (tiempoEnSec>=inicioManana and tiempoEnSec<finManana) {
            monto3=MONTO_LEVE*INCREMENTO_MULTA_MAÑANA;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto3;
        }
        else if (tiempoEnSec>=inicioTarde and tiempoEnSec<finTarde) {
            monto3=MONTO_LEVE*INCREMENTO_MULTA_TARDE;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto3;
        }
        else{
            monto3=MONTO_LEVE*INCREMENTO_MULTA_NOCHE;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto3;
        }

        montoTotalAPagar=MONTO_LEVE+monto1+monto2+monto3;

    }
    else if (tipoGravedad=='G') {;
        multa=MONTO_GRAVE;
        cout << "GRAVE" << setw(18-5) << " " << left << setw(18) << fixed << setprecision(2) << MONTO_GRAVE;

        //SELECTIVA PARA EL INCREMENTO POR TIPO DE VEHICULO:
        if (n1=='P') {
            monto1=MONTO_GRAVE*INCREMENTO_MULTA_P;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto1;
        }
        else if (n1=='M') {
            monto1=MONTO_GRAVE*INCREMENTO_MULTA_M;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto1;
        }
        else if (n1=='C') {
            monto1=MONTO_GRAVE*INCREMENTO_MULTA_C;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto1;
        }

        //SELECTIVA PARA EL INCREMENTO POR FECHAS:
        if (fechaActual<fechaInicial) {
            monto2=MONTO_GRAVE*INCREMENTO_MULTA_ANTES_FECHAINICIAL;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto2;
        }
        else if (fechaActual>=fechaInicial and fechaActual<=fechaFinal) {
            monto2=MONTO_GRAVE*INCREMENTO_MULTA_ENTRE_FECHAINICIALFINAL;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto2;
        }
        else if (fechaActual>fechaFinal) {
            monto2=MONTO_GRAVE*INCREMENTO_MULTA_LUEGO_FECHAFINAL;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto2;
        }

        //SELECTIVA PARA EL INCREMENTO POR HORA:
        if (tiempoEnSec>=inicioManana and tiempoEnSec<finManana) {
            monto3=MONTO_GRAVE*INCREMENTO_MULTA_MAÑANA;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto3;
        }
        else if (tiempoEnSec>=inicioTarde and tiempoEnSec<finTarde) {
            monto3=MONTO_GRAVE*INCREMENTO_MULTA_TARDE;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto3;
        }
        else{
            monto3=MONTO_GRAVE*INCREMENTO_MULTA_NOCHE;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto3;
        }

        montoTotalAPagar=MONTO_GRAVE+monto1+monto2+monto3;

    }
    else if (tipoGravedad=='M') {
        multa=MONTO_MUY_GRAVE;
        cout << "MUY GRAVE" << setw(18-9) << " " << left << setw(18) << fixed << setprecision(2) << MONTO_MUY_GRAVE;

        //SELECTIVA PARA EL INCREMENTO POR TIPO DE VEHICULO:
        if (n1=='P') {
            monto1=MONTO_MUY_GRAVE*INCREMENTO_MULTA_P;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto1;
        }
        else if (n1=='M') {
            monto1=MONTO_MUY_GRAVE*INCREMENTO_MULTA_M;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto1;
        }
        else if (n1=='C') {
            monto1=MONTO_MUY_GRAVE*INCREMENTO_MULTA_C;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto1;
        }

        //SELECTIVA PARA EL INCREMENTO POR FECHAS:
        if (fechaActual<fechaInicial) {
            monto2=MONTO_MUY_GRAVE*INCREMENTO_MULTA_ANTES_FECHAINICIAL;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto2;
        }
        else if (fechaActual>=fechaInicial and fechaActual<=fechaFinal) {
            monto2=MONTO_MUY_GRAVE*INCREMENTO_MULTA_ENTRE_FECHAINICIALFINAL;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto2;
        }
        else if (fechaActual>fechaFinal) {
            monto2=MONTO_MUY_GRAVE*INCREMENTO_MULTA_LUEGO_FECHAFINAL;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto2;
        }

        //SELECTIVA PARA EL INCREMENTO POR HORA:
        if (tiempoEnSec>=inicioManana and tiempoEnSec<finManana) {
            monto3=MONTO_MUY_GRAVE*INCREMENTO_MULTA_MAÑANA;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto3;
        }
        else if (tiempoEnSec>=inicioTarde and tiempoEnSec<finTarde) {
            monto3=MONTO_MUY_GRAVE*INCREMENTO_MULTA_TARDE;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto3;
        }
        else{
            monto3=MONTO_MUY_GRAVE*INCREMENTO_MULTA_NOCHE;
            cout << left << setw(18)<<  fixed << setprecision(2) <<monto3;
        }

        montoTotalAPagar=MONTO_MUY_GRAVE+monto1+monto2+monto3;

    }
    cout <<fixed << setprecision(2) << montoTotalAPagar << endl;

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // LUEGO DE LEER TODO LO ANTERIOR:
    multaTotalDeLaCompania=multaTotalDeLaCompania+multa;
    monto1Total=monto1Total+monto1;
    monto2Total=monto2Total+monto2;
    monto3Total=monto3Total+monto3;
    multaTotalAPagarTotal=multaTotalAPagarTotal+montoTotalAPagar;
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    return true;
}

void encabezadoPagoTotal(double multaTotalDeLaCompania, double monto1Total, double monto2Total, double monto3Total,
    double multaTotalAPagarTotal) {
    cout << "PAGO TOTAL:" << setw(18*4 + 7) << " ";
    cout
        << left << setw(18) << fixed << setprecision(2) << multaTotalDeLaCompania
        << left << setw(18) << fixed << setprecision(2) << monto1Total
        << left << setw(18) << fixed << setprecision(2) << monto2Total
        << left << setw(18) << fixed << setprecision(2) << monto3Total
        << left << setw(18) << fixed << setprecision(2) << multaTotalAPagarTotal << endl;
    separador('=', ANCHO_DEL_REPORTE);
}

void resumenFinal(double multaTotalDeTodasLasCompanias, int DNI_companiaMayorPagoInfracciones,
    double mayorMontoTotalPagadoCompania, int DNI_companiaMenorPagoInfracciones, double menorMontoTotalPagadoCompania) {

    cout << "TOTAL RECAUDADO POR INFRACCIONES: " << fixed << setprecision(2) << multaTotalDeTodasLasCompanias << endl;
    separador('=', ANCHO_DEL_REPORTE);
    cout << endl;

    //CUADRO:
    separador('/', 50);
    cout << "// COMPANIA CON MAYOR PAGO POR INFRACCIONES" << setw(5) << " " << "//" << endl;
    cout << left << setw(24) << "// DNI:" << setw(23) << DNI_companiaMayorPagoInfracciones << " //" << endl;
    cout
        << left << setw(24) << "// TOTAL PAGADO:" << setw(24)
        << fixed << setprecision(2) << mayorMontoTotalPagadoCompania << "//" << endl;
    separador('/', 50);
    cout << "// COMPANIA CON MENOR PAGO POR INFRACCIONES" << setw(5) << " " << "//" << endl;
    cout << left << setw(24) << "// DNI:" << setw(23) << DNI_companiaMenorPagoInfracciones << " //" << endl;
    cout
        << left << setw(24) << "// TOTAL PAGADO:" << setw(24)
        << fixed << setprecision(2) << menorMontoTotalPagadoCompania << "//" << endl;
    separador('/', 50);
}

void generarReporte(int ddi, int mmi, int aai, int ddf, int mmf, int aaf) {
    char c;
    int DNI, cantCompanias=0;

    encabezadoPrincipal(ddi, mmi, aai, ddf, mmf, aaf);

    //HALLAMOS EL RANGO DE FECHAS:
    int fechaInicial=(aai*10000)+(mmi*100)+ddi;
    int fechaFinal=(aaf*10000)+(mmf*100)+ddf;

    //DATOS PARA EL RESUMEN FINAL:
    double multaTotalDeTodasLasCompanias=0.0, mayorMontoTotalPagadoCompania=-1.0;
    long long menorMontoTotalPagadoCompania=999999.0;
    int DNI_companiaMayorPagoInfracciones=0, DNI_companiaMenorPagoInfracciones=0;

    while (cin >> DNI) {
        cantCompanias++;

        ///////////////////////////////////////////////////////////////////////// ENCABEZADO 1
        cout << "COMPANIA No. " << cantCompanias << endl;
        cout << "REPRESENTANTE LEGAL: ";
        leerImprimirNombres();
        cout << "DNI: " << DNI << endl;
        separador('-', ANCHO_DEL_REPORTE);
        //////////////////////////////////////////////////////////////////////////////////////

        // (...)

        ///////////////////////////////////////////////////////////////////////// ENCABEZADO 2
        cout << "VEHICULOS INFRACCIONADOS:" << endl;
        cout //1ra linea
            << left << setw(ANCHO_DEL_REPORTE/11) << " "
            << left << setw(ANCHO_DEL_REPORTE/11) << " "
            << left << setw(ANCHO_DEL_REPORTE/11) << " "
            << left << setw(ANCHO_DEL_REPORTE/11) << " "
            << left << setw(ANCHO_DEL_REPORTE/11) << " "
            << left << setw(ANCHO_DEL_REPORTE/11) << " "
            << left << setw(ANCHO_DEL_REPORTE/11) << "INCREMENTOS"
            << left << setw(ANCHO_DEL_REPORTE/11) << "INCREMENTOS"
            << left << setw(ANCHO_DEL_REPORTE/11) << "INCREMENTOS"
            << left << setw(ANCHO_DEL_REPORTE/11) << " " << endl;
        cout //2da linea
            << left << setw(ANCHO_DEL_REPORTE/11) << "  TIPO"
            << left << setw(ANCHO_DEL_REPORTE/11) << "PLACA"
            << left << setw(ANCHO_DEL_REPORTE/11) << "FECHA"
            << left << setw(ANCHO_DEL_REPORTE/11) << "HORA"
            << left << setw(ANCHO_DEL_REPORTE/11) << "GRAVEDAD"
            << left << setw(ANCHO_DEL_REPORTE/11) << "MULTA"
            << left << setw(ANCHO_DEL_REPORTE/11) << "POR TIPO"
            << left << setw(ANCHO_DEL_REPORTE/11) << "POR FECHA"
            << left << setw(ANCHO_DEL_REPORTE/11) << "POR HORA"
            << left << setw(ANCHO_DEL_REPORTE/11) << "TOTAL A PAGAR" << endl;
        //////////////////////////////////////////////////////////////////////////////////////

        // (...)

        ///////////////////////////////////////////////////////////////////////// ENCABEZADO 3
        // DATOS INICIALES:
        double multaTotalDeLaCompania=0.0, monto1Total=0.0, monto2Total=0.0, monto3Total=0.0;
        double multaTotalAPagarTotal=0.0;
        int DNIcompania=0;

        while (infoVehiculosInfraccionados(fechaInicial, fechaFinal, multaTotalDeLaCompania, monto1Total,
            monto2Total,monto3Total, multaTotalAPagarTotal, true));
        separador('-', ANCHO_DEL_REPORTE);
        //////////////////////////////////////////////////////////////////////////////////////

        // (...)

        ///////////////////////////////////////////////////////////////////////// ENCABEZADO 4
        encabezadoPagoTotal(multaTotalDeLaCompania, monto1Total,monto2Total,monto3Total,
            multaTotalAPagarTotal);

        multaTotalDeTodasLasCompanias=multaTotalDeTodasLasCompanias+multaTotalAPagarTotal;

        //SELECTIVAS PARA EL CUADRO:
        if (multaTotalAPagarTotal>mayorMontoTotalPagadoCompania) {
            mayorMontoTotalPagadoCompania=multaTotalAPagarTotal;
            DNI_companiaMayorPagoInfracciones=DNI;
        }
        if (multaTotalAPagarTotal<menorMontoTotalPagadoCompania) {
            menorMontoTotalPagadoCompania=multaTotalAPagarTotal;
            DNI_companiaMenorPagoInfracciones=DNI;
        }
        //////////////////////////////////////////////////////////////////////////////////////

    }
    resumenFinal(multaTotalDeTodasLasCompanias, DNI_companiaMayorPagoInfracciones, mayorMontoTotalPagadoCompania,
        DNI_companiaMenorPagoInfracciones,menorMontoTotalPagadoCompania);
}
