//
// Created by PC on 2/09/2026.
//
#include <iostream>
#include "Funciones.h"
#include <iomanip>
using namespace std;

void separador(char c, int n) {
    for (int i = 1; i <= n; i++) cout << c;
    cout << endl;
}

void encabezado(int di, int mi, int ai, int df, int mf, int af) {
    cout
        << right << setw((ANCHO_DEL_REPORTE+30)/2) << "CLINICA DE URGENCIAS TP_SALUD" << endl
        << right << setw(((ANCHO_DEL_REPORTE+28))/2) << "REGISTRO DE LAS ATENCIONES" << endl
         << setw((ANCHO_DEL_REPORTE+10)/2) << "ATENCIONES REALIZADAS ENTRE EL "
        << setw(2) << setfill('0') << di << "/" << setw(2) << mi << "/" << ai << " Y EL "
        << setw(2) <<  df << "/" << setw(2) << mf << "/" << af << setfill(' ') << endl;
    separador('=', 195);
}

void secciones() {
    //PRIMERA LINEA:
    cout
    << "                    "
    << "                    "
    << "                    "
    << "                    "
    << left << setw(ANCHO_DEL_REPORTE/9) << "DURACION DE LA"
    << left << setw(ANCHO_DEL_REPORTE/9) << "COSTO DE LA"
    << "                    "
    << left << setw(ANCHO_DEL_REPORTE/9) << "PRESION ARTERIAL"
    << left << setw(ANCHO_DEL_REPORTE/9) << "NIVEL DE LA" << endl;

    //SEGUNDA LINEA:
    cout
        << left << setw(ANCHO_DEL_REPORTE/9) << "ID"
        << left << setw(ANCHO_DEL_REPORTE/9) << "NOMBRE"
        << left << setw(ANCHO_DEL_REPORTE/9) << "INGRESO"
        << left << setw(ANCHO_DEL_REPORTE/9) << "ALTA"
        << left << setw(ANCHO_DEL_REPORTE/9) << "ATENCION"
        << left << setw(ANCHO_DEL_REPORTE/9) << "ATENCION"
        << left << setw(ANCHO_DEL_REPORTE/9) << "TEMPERATURA"
        << left << setw(ANCHO_DEL_REPORTE/9) << "MEDIA"
        << left << setw(ANCHO_DEL_REPORTE/9) << "PRESION ARTERIAL" << endl;
}

bool infoSecciones(int &cantAtenciones, int &cantPacientesNivelNormal, int &cantPacientesNivelHiper2,
    int &n1MayorPreArtMed, int &n2MayorPreArtMed, int &n3MayorPreArtMed,double &mayorPreArtMed, int &tiempoTotalAtencionesSec,
    double &costoTotalAtenciones, bool seMuestraLaInfo) { ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    double temperatura, costo, presArtMedia;
    int sistolica, diastolica, hhi,mmi, ssi, hhf, mmf, ssf;
    char c;

    //////////////////////////////////////////////////////////////////////////////// PARTE IMPORTANTE
    //SE ATRAPAN Y CONSIDERAN LOS ESPACIOS EN BLANCO ENTRE LA FECHA Y EL ID:
    c=cin.get();
    while (c==' ') c=cin.get(); //LO TOMA Y EL PUNTERO SE POSICIONA AHI

    //SIEMPRE SE PREGUNTA SI YA ESTAMOS AL FINAL DE LA LINEA O DEL DIA DE ATENCION:
    if (c=='\n') return false;

    //SE ANALIZA EL ID, TENIENDO EN CUENTA QUE c=cin.get() ATRAPÓ EL 1ER CARACTER DEL CODIGO QUE ES EL 7:
    int n1=c-'0'; // n1='7'-'0' = 7

    while (cin.get(c) and c!='-') { //mientras se siga leyendo y posisionando el puntero y no haya un '-'
        n1=(n1*10)+(c-'0'); //1ra vuelta: (7*10)+(6-0) = 76
    }                       //2da vuelta: (76*10)+(6-0) = 766<-n1
    //3ra vuelta: NO HAY, porque ahora aparece el '-'

    int n2, n3;
    cin >> n2 >> c >> n3; //se leen normalmente los siguientes numeros que conforman el ID
    //////////////////////////////////////////////////////////////////////////////// PARTE IMPORTANTE

    if (seMuestraLaInfo) { //seMuestraLaInfo==true
        //SE IMPRIME EL ID:
        cout
            << right << setw(3) << setfill('0') << n1
            << right << setw(2) << n2
            << right << setw(4) << n3 << setfill(' ') << "           ";
    }

    //SE LEE E IMPRIME EL NOMBRE:
    leerImprimirNombre(seMuestraLaInfo);

    //SE LEE E IMPRIME EL TIEMPO DE INGRESO:
    cin >> ws;
    cin >> hhi >> c >> mmi >> c >> ssi;
    if (seMuestraLaInfo) {
        cout << right << setw(2) << setfill('0') << hhi << ":" << setw(2) << mmi << ":" << setw(2) << ssi << setfill(' ');
        cout << "            ";
    }

    //SE PASA ESE TIEMPO A SEGUNDOS:
    int tiempoIngresoSec=(hhi*3600)+(mmi*60)+ssi;

    //SE LEEN Y GUARDAN LOS SIGUIENTES DATOS:
    cin >> ws;
    cin >> temperatura >> sistolica >> diastolica;

    //SE LEE E IMPRIME EL TIEMPO DE ALTA/SALIDA:
    cin >> ws;
    cin >> hhf >> c >> mmf >> c >> ssf;
    if (seMuestraLaInfo) {
        cout << right << setw(2) << setfill('0') << hhf << ":" << setw(2) << mmf << ":" << setw(2) << ssf << setfill(' ');
        cout << "            ";
    }

    //SE PASA ESE TIEMPO A SEGUNDOS:
    int tiempoSalidaSec=(hhf*3600)+(mmf*60)+ssf;

    if (tiempoSalidaSec<tiempoIngresoSec) {
        tiempoSalidaSec=tiempoSalidaSec+(24*60*60);
    }

    //SE HALLA LA DURACION DE LA ATENCION:
    int duracionAtencionSec=tiempoSalidaSec-tiempoIngresoSec;

    //SE PASA ESA DURACION DE LA ATENCION AL FORMATO hh:mm:ss
    int hhD=duracionAtencionSec/3600;
    int mmD=(duracionAtencionSec%3600)/60;
    int ssD=duracionAtencionSec%60;

    if (seMuestraLaInfo) {

        //SE IMPRIME LA DURACION DE LA ATENCION:
        cout << right << setw(2) << setfill('0') << hhD << ":" << setw(2) << mmD << ":" << setw(2) << ssD << setfill(' ');
        cout << "            ";

        //SE CALCULA E IMPRIME EL COSTO DE LA ATENCION:
        costo=calcularCostoPorAtencion(duracionAtencionSec);
        cout << left << setw(20) << fixed << setprecision(2) << costo;

        //SE IMPRIME LA TEMPERATURA:
        cout << left << setw(20) << fixed << setprecision(1) << temperatura;

        //SE CALCULA E IMPRIME LA PRES. ART. MEDIA:
        presArtMedia=calcularPresArtMedia(sistolica, diastolica);
        cout << left << setw(20) << fixed << setprecision(2) << presArtMedia;

        //SE IMPRIME EL NIVEL DE LA PRESION ARTERIAL:
        cout << sistolica << "/" << diastolica;

        //SE HACEN SELECTIVAS PARA EL NIVEL:
        if (sistolica<120 and diastolica<80) {
            cout << " (Normal)" << endl;
            cantPacientesNivelNormal++; //ES DATO IMPORTANTE DEL RESUMEN DEL CANAL
        }
        else if ((sistolica<120 and diastolica>80) or (sistolica>=120 and sistolica<=129 and diastolica<80)) {
            cout << " (Elevada)" << endl;
        }
        else if ((sistolica>=130 and sistolica<=139) or (diastolica>=80 and diastolica<=89)) {
            cout << " (Hipertensión Nivel 1)" << endl;
        }
        else if (sistolica>=140 or diastolica>=90) {
            cout << " (Hipertensión Nivel 2)" << endl;
            cantPacientesNivelHiper2++; //ES DATO IMPORTANTE DEL RESUMEN DEL CANAL
        }
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    //LUEGO DE PROCESAR A 1 PACIENTE: <<--------------------------------------------------------
    cantAtenciones++;
    tiempoTotalAtencionesSec=tiempoTotalAtencionesSec+duracionAtencionSec;
    costoTotalAtenciones=costoTotalAtenciones+costo;

    if (presArtMedia>mayorPreArtMed) { //SE DESIGNA AL PACIENTE CON MAYOR PRE. ART. MED
        mayorPreArtMed=presArtMedia;
        n1MayorPreArtMed=n1; //SE ACTUALIZAN LAS VARIABLES
        n2MayorPreArtMed=n2;
        n3MayorPreArtMed=n3;
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    return true;
}

double calcularCostoPorAtencion(int duracionAtencionSec) { //SE SABE QUE 3600sec->575.00
    return (COSTO_POR_3600SEC*(double)duracionAtencionSec)/3600;
}

double calcularPresArtMedia(int sistolica, int diastolica) {
    return (double)(sistolica+(2*diastolica))/3;
}

void leerImprimirID(int n1, int n2, int n3) { /////////////// NO SE USA
    char c;
    cin >> ws;
    cin >> n1 >> c >> n2 >> c >> n3;
    cout << n1 << n2 << n3;
}

void leerImprimirNombre(bool seMuestraLaInfo) {
    char c;
    int cantCaracteres=0;
    cin >> ws;
    while(true) {
        c=cin.get();
        if (c==' ') break;
        if (c=='_') c=' ';
        if (c>='a' and c<='z') c=c-('a'-'A'); //para pasar a mayusculas
        if (seMuestraLaInfo) cout << c;
        cantCaracteres++;
    }

    //PARA COLOCAR LOS ESPACIOS CORRESPONDIENTES Y ESTÉ ALINEADO CON EL TIEMPO DE INGRESO:
    int anchoColumnaN=20;
    if (seMuestraLaInfo) cout << setw(anchoColumnaN-cantCaracteres) << " ";
}

void resumenDelCanal(int cantAtenciones, int cantPacientesNivelNormal, int cantPacientesNivelHiper2,
    int n1MayorPreArtMed, int n2MayorPreArtMed, int n3MayorPreArtMed, double mayorPreArtMed, int tiempoTotalAtencionesSec,
    double costoTotalAtenciones) { ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    //SE HALLA EL TIEMPO TOTAL EN EL FORMATO hh:mm:ss
    int hh=tiempoTotalAtencionesSec/3600;
    int mm=(tiempoTotalAtencionesSec%3600)/60;
    int ss=tiempoTotalAtencionesSec%60;
    cout << "         RESUMEN DEL CANAL: " << endl;
    cout << "         CANTIDAD DE ATENCIONES: " << cantAtenciones << endl;
    cout << "         CANTIDAD DE PACIENTES CON NIVEL DE LA PRESIÓN ARTERIAL EN NORMAL: " << cantPacientesNivelNormal << endl;
    cout << "         CANTIDAD DE PACIENTES CON NIVEL DE LA PRESIÓN ARTERIAL EN HIPERTENSIÓN NIVEL 2: " << cantPacientesNivelHiper2 << endl;
    cout << "         PACIENTE CON MAYOR PRESIÓN ARTERIAL MEDIA: ";
    cout << right << setw(3) << setfill('0') << n1MayorPreArtMed << "-" << setw(2) << n2MayorPreArtMed << "-" << setw(4) << n3MayorPreArtMed << " con " << setfill(' ');
    cout << fixed << setprecision(2) << mayorPreArtMed << endl;
    cout << "         TIEMPO TOTAL DESTINADO A LAS ATENCIONES: ";
    cout << right << setw(2) << setfill('0') << hh << ":" << setw(2) << mm << ":" << setw(2) << ss << setfill(' ') << endl;
    cout << "         COSTO TOTAL POR LAS ATENCIONES: ";
    cout << fixed << setprecision(2) << costoTotalAtenciones << endl;
}

void resumenFinal(int cantAtencionesDeTodosLosCanales, int tiempoTotalTodasLasAtencionesSec,
    double costoTotalTodasLasAtenciones) {

    //TIEMPO TOTAL A FORMATO hh:mm:ss
    int hh=tiempoTotalTodasLasAtencionesSec/3600;
    int mm=(tiempoTotalTodasLasAtencionesSec%3600)/60;
    int ss=tiempoTotalTodasLasAtencionesSec%60;

    cout << "RESUMEN FINAL: " << endl;
    cout << setw(5) << " " << "CANTIDAD DE ATENCIONES: " << cantAtencionesDeTodosLosCanales << endl;
    cout
        << setw(5) << " " << left << setw(43) <<  "TIEMPO TOTAL DESTINADO A LAS ATENCIONES: "
        << right << setw(2) << setfill('0') << hh << ":" << setw(2) << mm << ":" << setw(2) << ss << setfill(' ')<< endl;
    cout
        << setw(5) << " " << left << setw(43) << "COSTO TOTAL POR LAS ATENCIONES: "
        << fixed << setprecision(2) << costoTotalTodasLasAtenciones;
}


void generarReporte(int di, int mi, int ai, int df, int mf, int af) { ////////////////////////////////////////////////////////////////////////////////////////////////////////
    int dd, mm, aa;
    char c;
    encabezado(di, mi, ai, df, mf, af);

    //CONVERTIMOS LAS FECHAS FIJAS:
    int fechaInicio=(ai*10000)+(mi*100)+di;
    int fechaFinal=(af*10000)+(mf*100)+df;

    //DATOS PARA EL RESUMEN FINAL:
    int cantAtencionesDeTodosLosCanales=0, tiempoTotalTodasLasAtencionesSec=0;
    double costoTotalTodasLasAtenciones=0.0;

    while (cin >> dd) {
        cin >> c >> mm >> c >> aa;

        //CONVERTIMOS LA FECHA ACTUAL/ANALIZADA:
        int fechaActual=(aa*10000)+(mm*100)+dd;

        //SE VERIFICA SI ES UNA FECHA VALIDA:
        if (fechaActual>=fechaInicio and fechaActual<=fechaFinal) {
            cout << "FECHA: ";
            cout << right << setw(2) << setfill('0') << dd << "/" << setw(2) << mm << "/" << aa << setfill(' ') << endl;
            cout << "REGISTRO DE ATENCIONES: " << endl;
            separador('-', 195);
            secciones();

            //DATOS PARA EL RESUMEN DEL CANAL:
            int cantAtenciones=0,cantPacientesNivelNormal=0,cantPacientesNivelHiper2=0;
            int n1MayorPreArtMed=0, n2MayorPreArtMed=0, n3MayorPreArtMed=0, tiempoTotalAtencionesSec=0;
            double mayorPreArtMed=-1.0, costoTotalAtenciones=0.0;

            while (infoSecciones(cantAtenciones, cantPacientesNivelNormal, cantPacientesNivelHiper2, n1MayorPreArtMed,
                n2MayorPreArtMed, n3MayorPreArtMed,mayorPreArtMed, tiempoTotalAtencionesSec,
                costoTotalAtenciones, true)) { //MIENTRAS SEA TRUE, SE RETORNARÁ INFORMACION
                // La lectura e impresión se realiza dentro de infoSecciones()
            }
            separador('-', 195);
            resumenDelCanal(cantAtenciones,cantPacientesNivelNormal, cantPacientesNivelHiper2,
                n1MayorPreArtMed, n2MayorPreArtMed, n3MayorPreArtMed, mayorPreArtMed,tiempoTotalAtencionesSec, costoTotalAtenciones);
            separador('=', 195);

             /////////////////////////////////////////////////////////////////////
            //RESULTADOS PARA EL RESUMEN FINAL:
            cantAtencionesDeTodosLosCanales=cantAtencionesDeTodosLosCanales+cantAtenciones;
            tiempoTotalTodasLasAtencionesSec=tiempoTotalTodasLasAtencionesSec+tiempoTotalAtencionesSec;
            costoTotalTodasLasAtenciones=costoTotalTodasLasAtenciones+costoTotalAtenciones;
            /////////////////////////////////////////////////////////////////////

        }
        else {
            int cantAtenciones=0,cantPacientesNivelNormal=0,cantPacientesNivelHiper2=0, n1=0, n2=0, n3=0, tiempoSec=0;
            double mayorPreArtMed=-1.0, costo=0.0;

            while (infoSecciones(cantAtenciones, cantPacientesNivelNormal, cantPacientesNivelHiper2, n1,
                            n2, n2,mayorPreArtMed, tiempoSec,
                            costo, false)); //SE MANTIENEN LOS MISMOS VALORES NULOS
        }                                                   //Y seMuestraLaInfo RETORNA FALSO (no se muestra la info)
    }

    resumenFinal(cantAtencionesDeTodosLosCanales,tiempoTotalTodasLasAtencionesSec,costoTotalTodasLasAtenciones);
}
