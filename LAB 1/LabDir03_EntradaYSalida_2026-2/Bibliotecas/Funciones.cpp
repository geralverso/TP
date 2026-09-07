//
// Created by PC on 6/09/2026.
//

#include <iostream>
#include <iomanip>
using namespace std;
#include "Funciones.h"


void separador(char c, int n) {
    for (int i=1;i<=n;i++) cout << c;
    cout << endl;
}

// ///////////////////////////////////////////////////////////////////////////////// INICIO PARTE 1

void encabezado1() {
    cout
        << left << setw(12) << "DNI"
        << left << setw(30) << "NOMBRE Y APELLIDOS"
        << left << setw(20) << "ASEGURADORA"
        << left << setw(8) << "CÓDIGO"
        << right << setw(25) << "INICIO DE LA POLIZA"
       << right << setw(20) << "FIN DE LA POLIZA"
        << right << setw(10) << "MONTO"
        << right <<  setw(12) << "EDAD" << endl;
    separador('-', ANCHO_DEL_REPORTE);
}

bool leerImprimirDNI() {
    int DNI;
   if (cin>>DNI) {
       cout << left << setw(12) << DNI;
       return true;
   }
    return false;
}

void leerImprimirNyA_reporte1() {
    char c;
    int cantCaracteres=0;
    cin >> ws;

    while (true) {
        c=cin.get();
        if (c==' ') break;
        if (c=='_') c=' ';
        if (c>='a' and c<='z') c=c-('a'-'A');
        cout << c;
        cantCaracteres++;
    }

    //PARA RELLENAR ESPACIOS HASTA LLEGAR A UN ANCHO FIJO.
    int anchoColumnaNyA=30;
    cout << setw(anchoColumnaNyA-cantCaracteres) << " ";
}

void leerImprimirAseguradoras() { // CASI LO MISMO QUE leerImprimirNyA_reporte1()
    char c;
    int cantCaracteres=0;
    cin >> ws;

    while (true) {
        c=cin.get();
        if (c==' ') break;
        if (c=='_') c=' ';
        cout << c;
        cantCaracteres++;
    }

    //PARA RELLENAR ESPACIOS HASTA LLEGAR A UN ANCHO FIJO.
    int anchoColumnaAseg=20;
    cout << setw(anchoColumnaAseg-cantCaracteres) << " ";
}

void leerimprimirCodigoCliente() {  //LO MISMO QUE leerImprimirAseguradoras()
    char c;
    cin >> ws;
    while (true) {
        c=cin.get();
        if (c==' ') break;
        cout << c;
    }
    cout << "       ";
}

void leerImprimirFechas() {
    int dd, mm, aa;
    char c;
    cin >> ws;
    cin >> dd >> c >> mm >> c >> aa;

    aa=aa+2000; //se actualiza el año 26->2026
    cout
         << right << setw(2) << setfill('0') << dd << "/"
        << setw(2) << mm << "/"
        << setfill(' ') << aa;
}

void leerImprimirMonto() {
    double monto;
    cin >> ws;
    cin >> monto;
    cout << left << setw(13) << fixed << setprecision(3) << monto;
}

void leerImprimirEdad_reporte1() {
    int edad;
    char car;
    cin >> ws;
    cin >> edad;
    cout << left << setw(3) << edad;

    while (true) {
        car=cin.get();
        if (car =='\n') break;
    }
}

void leerImprimirDAtos() {
    while (leerImprimirDNI()) {
        leerImprimirNyA_reporte1();
        leerImprimirAseguradoras();
        leerimprimirCodigoCliente();
        leerImprimirFechas();
        cout << "             ";
        leerImprimirFechas();
        cout << "           ";
        leerImprimirMonto();
        leerImprimirEdad_reporte1();
        cout << endl;
    }
}

void leerEscribirAsegurados() {
    encabezado1();
    leerImprimirDAtos();
}

// ///////////////////////////////////////////////////////////////////////////////// FIN PARTE 1


// (..)


// ///////////////////////////////////////////////////////////////////////////////// INICIO PARTE 2

void generarReportePolizas(int dFijo, int mFijo, int aFijo) {

    // int dd, mm, aa;
    // encabezado2();
    // leerImprimirNyA_reporte2();
    // leerImprimirInfo_reporte2(dd, mm, aa, 31, 8, 2026);

    int dd, mm, aa;
    encabezado2();
                        //CONDICIONAL
    while (leerImprimirNyA_reporte2()) { //LAS FUNCIONES BOOL PUEDEN IR DENTRO DE WHILEs
        leerImprimirInfo_reporte2(dd, mm, aa, 31, 8, 2026);
    }

}

void encabezado2() {
    cout << left << setw(30) << "NOMBRE Y APELLIDOS";
    cout << left << setw(8) << "EDAD";
    cout << left << setw(17) << "ESTADO";
    cout << left << setw(25) << "DIAS" << endl;
    separador('-', 80);
}

bool leerImprimirNyA_reporte2() {

    // char c;
    // int dni, cantCaracteres=0;
    // cin >> dni;
    // cin >> ws;                               GENERALMENTE EN LOS LABS1
    //                                          SE USA COMO LO QUE ESTÁ COMENTADO
    // while (true) {                                   (lineas 174-189)
    //     c=cin.get();
    //     if (c==' ') break;
    //     if (c=='_') c=' ';
    //     cout << c;
    //     cantCaracteres++;
    // }
    //
    // //PARA RELLENAR ESPACIOS HASTA LLEGAR A UN ANCHO FIJO.
    // int anchoColumnaNyA=30;
    // cout << setw(anchoColumnaNyA-cantCaracteres) << " ";

    int dni;
    if (cin>>dni) {
        cin >> ws;
        char c;
        int cantCaracteres=0;

        while (true) {
            c=cin.get();
            if (c==' ' or c=='\n') break;
            if (c=='_') c=' ';
            cout << c;
            cantCaracteres++;
        }

        //PARA RELLENAR ESPACIOS HASTA LLEGAR A UN ANCHO FIJO.
        int anchoColumnaNyA=30;
        cout << setw(anchoColumnaNyA-cantCaracteres) << " ";
        return true;
    }

    return false;
}

void leerImprimirInfo_reporte2(int dd, int mm, int aa, int dFijo, int mFijo, int aFijo) {

    ignorarCampo(); //se salta ASEGURADORAS
    ignorarCampo(); //se salta CODIGO
    ignorarCampo(); //se salta FECHA INICIO POLIZA
    double monto;
    int edad;
    char c;
    cin >> ws;
    cin >> dd >> c >> mm >> c >> aa; //FECHA FIN POLIZA
    aa=aa+2000; //se actualiza el año 26->2026

    cin >> monto >> edad;
    cout << left << setw(8) << edad;

    //convertir fechaFinPoliza a diasFinPoliza
    int fechaFinPoliza=(aa*10000)+(mm*100)+dd;
    int diasFinPoliza=convertirADias(dd, mm, aa);

    //convertir fechafija 31/08/2026 a diasFechaFija
    int fechaFija=(aFijo*10000)+(mFijo*100)+dFijo;
    int diasFechaFija=convertirADias(31, 8, 2026);

    if (fechaFinPoliza>=fechaFija) {
        int diasParaVencer=diasFinPoliza-diasFechaFija;
        cout << "Poliza vigente   " << diasParaVencer << " dias para vencer" <<  endl;
    }
    else{
        int diasDeVencido=diasFechaFija-diasFinPoliza;
        cout << "Poliza vencida   " << diasDeVencido << " dias vencida" << endl;
    }

}

int convertirADias(int dd, int mm, int aa) {
    int diasMeses=0;

    if (mm==1) diasMeses=0;             //enero:31
    if (mm==2) diasMeses=31;             //febrero:28
    if (mm==3) diasMeses=59;             //marzo:31
    if (mm==4) diasMeses=90;             //abril:30
    if (mm==5) diasMeses=120;             //mayo:31
    if (mm==6) diasMeses=151;             //junio:30
    if (mm==7) diasMeses=181;             //julio:31
    if (mm==8) diasMeses=212;             //agosto:31
    if (mm==9) diasMeses=243;             //septiembre:30
    if (mm==10) diasMeses=274;             //octubre:31
    if (mm==11) diasMeses=304;             //noviembre:30
    if (mm==12) diasMeses=334;             //diciembre:31

                                    //AÑOS BISIESTOS
    return (aa*365)+diasMeses+dd + (aa/4);
}

void ignorarCampo() {
    char c;
    cin >> ws;

    while (true) {
        c=cin.get();
        if (c==' ') break;
        if (c=='_') c=' '; //no hay cout
    }
}

// ///////////////////////////////////////////////////////////////////////////////// FIN PARTE 2
