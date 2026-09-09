//
// Created by PC on 9/09/2026.
//

#include "Funciones.h"
using namespace std;
#include <iomanip>
#include <iostream>

void separador(char c, int n) {
    for (int i = 0; i < n; i++) cout << c;
    cout << endl;
}

void encabezado() {
    cout << setw(80) << "RESULTADOS DE CARRERAS" << endl;
    cout << endl;
    cout
        << setw(25) << "CORREDOR" << setw(25) << "PAIS" << setw(19) << "NACIMIENTO" << setw(6) << "EDAD"
        << setw(15) << "TIPO_CARRERA" << setw(9) << "INICIO" << setw(13) << "FIN" << setw(16) << "DURACION"
         << setw(11) << "RITMO" << endl;
    separador('=', ANCHO_DEL_REPORTE);
}

void leerImprimirCadena(int anchoColumna) {
    char c;
    int cantCaracteres=0;
    while (true) {
        c=cin.get();
        if (c==' ') break;
        if (c=='_') c=' ';
        if (c>='a' and c<='z') c=c-32;
        cout << c;
        cantCaracteres++;
    }
    cout  << setw(anchoColumna-cantCaracteres) << " ";
}

void resumen(int cantRegistrosProcesados, int cantRegisProcesados10K, int cantRegisProcesados21K,
    int cantRegisProcesados42K, int codigoCorredorMenorRitmo, int codigoCorredorMayorRitmo, double ritmoMenor,
    double ritmoMayor) {
    separador('=', ANCHO_DEL_REPORTE);
    cout << "RESUMEN:" << endl;
    separador('-', 45);
    cout << "CANTIDAD DE REGISTROS PROCESADOS: " << cantRegistrosProcesados << endl;
    separador('-', 45);
    cout << "CANTIDAD DE REGISTROS POR TIPO DE CARRERA: " << endl;
    cout << "10K - " << cantRegisProcesados10K << endl;
    cout << "21K - " << cantRegisProcesados21K << endl;
    cout << "42K - " << cantRegisProcesados42K << endl;
    separador('-', 45);

    //RITMO MENOR:
    int ritmoMenorMin=(int)ritmoMenor;
    int ritmoMenorSec=(ritmoMenor-ritmoMenorMin)*60;

    //RITMO MAYOR:
    int ritmoMayorMin=(int)ritmoMayor;
    int ritmoMayorSec=(ritmoMayor-ritmoMayorMin)*60;

    cout
        << "CORREDOR CON MENOR RITMO: " << right << setw(5) <<  setfill('0') << codigoCorredorMenorRitmo
        << " - " << right << setw(2) << ritmoMenorMin << ":" << setw(2) << ritmoMenorSec
        << setfill(' ') << endl;
    cout
        << "CORREDOR CON MAYOR RITMO: " <<right << setw(5) << setfill('0') << codigoCorredorMayorRitmo
        << " - " << right << setw(2) << setfill('0') << ritmoMayorMin << ":" << setw(2) << ritmoMayorSec
        << setfill(' ');
}

void generarReporte() {
    encabezado();
    char c;
    int tipoDeCarrera, codigoDelCorredor;

    //DATOS INICIALES PARA EL RESUMEN:
    int cantRegistrosProcesados=0, cantRegisProcesados10K=0, cantRegisProcesados21K=0;
    int cantRegisProcesados42K=0, codigoCorredorMenorRitmo=0, codigoCorredorMayorRitmo=0;
    double ritmoMenor=999999, ritmoMayor=-1;

    while (cin>>tipoDeCarrera) {
        cantRegistrosProcesados++;
        cin>>codigoDelCorredor;
        cout << setw(5) << setfill('0') << codigoDelCorredor << setfill(' ') << "  ";

        cin>>ws;
        leerImprimirCadena(37); //PARA EL NOMBRE
        cin>>ws;
        leerImprimirCadena(15); //PARA EL PAIS

        int dd, mm, aa, ddA=7, mmA=9, aaA=2026; // dia actual = 07/09/2026
        int fechaActual=(aaA*10000)+(mmA*100)+ddA;
        cin >> ws >> dd >> c >> mm >> c >> aa;
        cout
            << right << setw(2) << setfill('0') << dd << "/" << setw(2) << mm << "/"
            << setw(4) << aa << setfill(' ');

        int fechaNacimiento=(aa*10000)+(mm*100)+dd;
        int edad=(fechaActual-fechaNacimiento)/10000;

        cout << right << setw(5) << edad;

        if (tipoDeCarrera==2) {
            cout << setw(12) << "10K";
            cantRegisProcesados10K++;
        }
        else if (tipoDeCarrera==3) {
            cout << setw(12) << "21K";
            cantRegisProcesados21K++;
        }
        else if (tipoDeCarrera==4) {
            cout << setw(12) << "42K";
            cantRegisProcesados42K++;
        }
        cout << setw(6) << " ";

        cin >>ws;
        int hhi, mmi, ssi, hhf, mmf, ssf;
        cin>>hhi >> c >> mmi >> c >> ssi >> hhf >> c>>mmf >> c>>ssf;
        cout
            << right << setw(2) << setfill('0') << hhi << ":" << setw(2) << mmi << ":"
            << setw(2) << ssi << setfill(' ')<< setw(6) << " ";
        cout
            << right << setw(2) << setfill('0') << hhf << ":" << setw(2) << mmf << ":"
            << setw(2) << ssf << setfill(' ')<< setw(6) << " ";

        int tiempoInicioSec=(hhi*3600)+(mmi*60)+ssi;
        int tiempoFinSec=(hhf*3600)+(mmf*60)+ssf;

        if (tiempoFinSec<tiempoInicioSec) tiempoFinSec=tiempoFinSec+(24*3600);

        int duracionSec=tiempoFinSec-tiempoInicioSec;
        int hhD=duracionSec/3600;
        int mmD=(duracionSec%3600)/60;
        int ssD=duracionSec%60;

        cout
            << right << setw(2) << setfill('0') << hhD << ":" << setw(2) << mmD << ":"
            << setw(2) << ssD << setfill(' ')<< setw(6) << " ";

        double ritmo;
        if (tipoDeCarrera==2) ritmo=((double)duracionSec/60)/10;
        else if (tipoDeCarrera==3) ritmo=((double)duracionSec/60)/21;
        else if (tipoDeCarrera==4) ritmo=((double)duracionSec/60)/42;

        int ritmoMin=(int)ritmo;
        int ritmoSec=(ritmo-ritmoMin)*60; //ritmoSec es la parte decimal de ritmo

        cout
            << right << setw(2) << setfill('0') << ritmoMin << ":" << setw(2) << ritmoSec
            << setfill(' ') << endl;

        if (ritmo<ritmoMenor) {
            ritmoMenor=ritmo;
            codigoCorredorMenorRitmo=codigoDelCorredor;
        }
        if (ritmo>ritmoMayor) {
            ritmoMayor=ritmo;
            codigoCorredorMayorRitmo=codigoDelCorredor;
        }
    }
    resumen(cantRegistrosProcesados, cantRegisProcesados10K, cantRegisProcesados21K,
        cantRegisProcesados42K, codigoCorredorMenorRitmo, codigoCorredorMayorRitmo,
        ritmoMenor, ritmoMayor);
}
