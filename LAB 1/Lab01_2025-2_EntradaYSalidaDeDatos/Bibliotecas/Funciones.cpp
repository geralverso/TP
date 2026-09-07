//
// Created by PC on 6/09/2026.
//

#include "Funciones.h"
#include <iostream>
#include <iomanip>
using namespace std;

void separador(char c, int n) {
    for (int i=1; i<=n; i++) cout << c;
    cout << endl;
}

void encabezadoPrincipal(int ddi, int mmi, int aai, int ddf, int mmf, int aaf) {
    cout << setw((ANCHO_DEL_REPORTE+20)/2) << "PLATAFORMA TP_Twitch" << endl;
    cout << setw((ANCHO_DEL_REPORTE+30)/2) << "REGISTRO DE LOS CANALES AFILIADOS" << endl;
    cout <<  setw((ANCHO_DEL_REPORTE)/2) << "FECHAS DE CREACION ENTRE EL ";
    cout
        << right << setw(2) << setfill('0') << ddi << "/" << setw(2) << mmi << "/" << aai << " Y EL "
        << right << setw(2) << ddf << "/" << setw(2) << mmf << "/" << aaf << setfill(' ') << endl;
    separador('=', ANCHO_DEL_REPORTE);
}

void leerImprimirNombre() {
    char c;
    int cantCaracteres=0;
    cin >> ws;
    while (true) {
        c=cin.get();
        if (c==' ') break;
        if (c>='a' and c<='z') c=c-32;
        cout << c;
        cantCaracteres++;
    }
    int anchoColumna=14;
    cout << setw(anchoColumna-cantCaracteres) << " ";
}

bool infoUltimasReproducciones(int &duracionTotalReprodSec, int &fechaUltimaPublicacion, int &numTotalReprod,
double &ingresosPublicidad, bool seMuestraLaInfo, int &cantTotalStreamsCanales, int &duracionTotalStreamsCanalesSec) {
    char c;

    ////////////////////////////////////////////////////////////////////////////////////////// PARTE IMPORTANTE
    //LOS ESPACIOS EN BLANCO ENTRE LA FECHA Y EL ID SE ATRAPAN Y SE CONSIDERAN:
    c=cin.get();
    while (c==' ') c=cin.get(); //TOMA EL ESPACIO SIN RETORNARLO Y EL PUNTERO SE POSICIONA LUEGO DE ESE

    //SIEMPRE SE PREGUNTA SI YA ESTAMOS AL FINAL DE LA LINEA:
    if (c=='\n') return false;

    //DESPUES DE LA CANT SEGUIDORES,
    //SE ANALIZA EL DÍA DE LA SIGUIENTE FECHA, TENIENDO EN CUENTA QUE c=cin.get() ATRAPÓ EL 1ER CARACTER DE
    //ESA FECHA EL CUAL ES EL 1 DEL 16/07/2025:
    int dd=c-'0'; // d='1'-'0' = 1

    while (cin.get(c) and c!='/') { //mientras se siga leyendo y posisionando el puntero y no haya un '/'
        dd=(dd*10)+(c-'0'); //1ra vuelta: (1*10)+(6-0) = 16 = dd
    }                       //2da vuelta: NO HAY, porque ahora aparece el '/'

    int mm, aa;
    cin >> mm >> c >> aa; //se leen normalmente los siguientes numeros que conforman la fecha dd/mm/aa
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////


    //--------------------------------------------------------------------------------------------------------------------------------------

    //SE IMPRIME LA FECHA:
    if (seMuestraLaInfo==true) {
        cout
        << left << setw(12) << " " << right << setw(2) << setfill('0') << dd << "/"
        << setw(2) << mm << "/" << aa << setfill(' ') << setw(20) << " ";
    }

    //SE PASA ESA FECHA EN FORMATO aammdd:
    int fecha=(aa*10000)+(mm*100)+dd;

    //SE LEE E IMPRIME EL TIEMPO DE DURACION:
    int hora, min, sec, duracionReprodSec;
    cin >> ws >>hora >> c >> min >> c >> sec;
    if (seMuestraLaInfo==true) {
        cout << right << setw(2) << setfill('0') << hora << ":" << setw(2) << min << ":" << setw(2) << sec << setfill(' ');
        cout << setw(20) << " ";
    }

    //SE PASA ESE TIEMPO A SEGUNDOS:
    duracionReprodSec=(hora*3600)+(min*60)+sec;

    //SE LEE E IMPRIME EL NUM. REPRODUCCIONES
    int numReprod;
    cin >> ws >> numReprod;
    if (seMuestraLaInfo==true) cout << numReprod << endl;

    //-------------------------------------------------------------------------------------------------------------------------------------


    ///////////////////////////////////////////////////////////////////////////////////////////////////////////
    //LUEGO DE PROCESAR LOS DATOS DE UNA FECHA <<--------------------------------------------------------
    if (seMuestraLaInfo==true){
        //si se logró leer un stream correctamente, se habrá llegado hasta aquí
        cantTotalStreamsCanales++;
        duracionTotalStreamsCanalesSec=duracionTotalStreamsCanalesSec+duracionReprodSec;

        duracionTotalReprodSec=duracionTotalReprodSec+duracionReprodSec;
        numTotalReprod=numTotalReprod+numReprod;
        double ingresoPorUnaFecha=calcularIngresoPorPublicidad(numReprod);
        ingresosPublicidad=ingresosPublicidad+ingresoPorUnaFecha;

        if (fecha>fechaUltimaPublicacion) fechaUltimaPublicacion=fecha;  //SE ACTUALIZAN LAS VARIABLES
    }
    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    return true;
}

void resumenDelCanal(int duracionTotalReprodSec, int fechaUltimaPublicacion, int numTotalReprod,
    double ingresosPublicidad) {

    //DURACION TOTAL DE REPROD EN FORMATO hh:mm:ss
    int hhT=duracionTotalReprodSec/3600;
    int mmT=(duracionTotalReprodSec%3600)/60;
    int ssT=duracionTotalReprodSec%60;

    //FECHA DE LA ULTIMA PUBLIC EN FORMATO dd/mm/aa ---> ej. 20230427
    int aaUP=fechaUltimaPublicacion/10000;
    int mmUP=(fechaUltimaPublicacion%10000)/100;
    int ddUP=fechaUltimaPublicacion%100;

    cout << left << setw(5) << " " << "RESUMEN DEL CANAL: " << endl;
    cout << left << setw(5) << " " << setw(40) << "DURACION TOTAL DE LAS REPRODUCCIONES: ";
    cout << right << setw(2) << setfill('0') << hhT << ":" << setw(2) << mmT << ":" << setw(2) << ssT << setfill(' ');
    cout << endl;
    cout << left << setw(5) << " " << setw(40) << "ULTIMA PUBLICACION";
    cout << right << setw(2) << setfill('0') << ddUP << "/" << setw(2) << mmUP << "/" << aaUP << setfill(' ');
    cout << endl;
    cout << left << setw(5) << " " << setw(40) << "TOTAL DE REPRODUCCIONES: " << numTotalReprod << endl;
    cout << left << setw(5) << " " << setw(40) << "INGRESOS POR PUBLICIDAD: " << "$ ";
    cout << fixed << setprecision(2) << ingresosPublicidad << endl;
}

double calcularIngresoPorPublicidad(int num) {
    return (INGRESO_POR_1000REPROD*(double)num)/1000;
}

void resumenFinal(int cantTotalStreamsCanales, int duracionTotalStreamsCanalesSec, double ingresosTotalesCanales,
    char n1CodigoCanalMayorIngreso, int n2CodigoCanalMayorIngreso, double mayorIngreso) {

    //DURACION TOTAL DE TODOS LOS STREAMS DE LOS CANALES EN FORMATO hh:mm:ss
    int hour=duracionTotalStreamsCanalesSec/3600;
    int minute=(duracionTotalStreamsCanalesSec%3600)/60;
    int sec=duracionTotalStreamsCanalesSec%60;

    cout << "RESUMEN FINAL: " << endl;
    cout
        << left << setw(30) << "CANTIDAD TOTAL DE STREAMS COLOCADOS POR LOS CANALES: "
        << right << setw(5) << cantTotalStreamsCanales << endl;
    cout << left << setw(56) << "DURACIÓN TOTAL DE LOS STREAMS PUBLICADOS: ";

    if (hour<10) cout << '0';
    cout << hour << ":";
    cout <<  right << setw(2) << setfill('0')<< minute << ":" << setw(2) << sec << setfill(' ') << endl;
    cout
        << left << setw(55) << "INGRESOS TOTALES POR PUBLICIDAD: " << "$ "
        << fixed << setprecision(2) << ingresosTotalesCanales << endl;
    cout
        << "CANAL CON MAYORES INGRESOS POR PUBLICIDAD: " << n1CodigoCanalMayorIngreso << n2CodigoCanalMayorIngreso
        << " CON $ " << fixed << setprecision(2) << mayorIngreso << endl;
}

void generarReporte(int ddi, int mmi, int aai, int ddf, int mmf, int aaf) {
    int ddC, mmC, aaC, n2, cantSeguidores, cantCanales=0;
    char c, n1;

    //CALCULAMOS LAS FECHAS RANGO EN EL FORMATO aammdd:
    int fechaInicial=(aai*10000)+(mmi*100)+ddi;
    int fechaFinal=(aaf*10000)+(mmf*100)+ddf;

    encabezadoPrincipal(ddi, mmi, aai, ddf, mmf, aaf); //PLATAFORMA TP_Twitch,.....

    //SE DECLARAN LAS VARIABLES PARA EL RESUMEN FINAL
    int cantTotalStreamsCanales=0, duracionTotalStreamsCanalesSec=0, n2CodigoCanalMayorIngreso=-1.0;
    char n1CodigoCanalMayorIngreso='0';
    double ingresosTotalesCanales=0.0, mayorIngreso=-1.0;


    while (cin>>ddC) { //si lee el primer int de la 1ra linea..
        cin >> c >> mmC >> c >> aaC; // ddC/mmC/aaC es la fecha de Creacion de un canal

        //CALCULAMOS LA FECHA ACTUAL DE CREACION EN EL FORMATO aammdd:
        int fechaActualC=(aaC*10000)+(mmC*100)+ddC;

        //SE VERIFICA SI ES UNA FECHA VALIDA:
        if (fechaActualC>=fechaInicial and fechaActualC<=fechaFinal) {
            //se imprimen los datos del CANAL
            cantCanales++;

            /////////////////////////////////////////////////////////////////////////////////// ENCABEZADO 1
            cout << "CANAL No. " << cantCanales << endl;
            cout << setw(6) << " "; //
            cout << left << setw(14) << "NOMBRE";
            cout << left << setw(14) << "CODIGO";
            cout << left << setw(15) << "CREADO EL";
            cout << left << setw(25) << "NUMERO DE SEGUIDORES" << endl;

            cin >> ws >> n1 >> n2; //LEE Y GUARDA EL CODIGO
            cout << setw(6) << " ";
            leerImprimirNombre(); //NOMBRE DEL CANAL
            cout << n1 << n2 << setw(9) << " "; //IMPRIME EL CODIGO
            cout << right << setw(2) << setfill('0') << ddC << "/" << setw(2) << mmC << "/" << aaC << setfill(' ');
            cout << setw(5) << " "; //DIA DE CREACION
            cin >> ws >> cantSeguidores; //LEE Y GUARDA LA CANT DE SEGUIDORES
            cout << left << cantSeguidores << endl; //IMPRIME LA CANT DE SEGUIDORES
            separador('-', ANCHO_DEL_REPORTE);
            ////////////////////////////////////////////////////////////////////////////////////////////////

            // (...)

            /////////////////////////////////////////////////////////////////////////////////// ENCABEZADO 2

            cout << left << setw(5) << " " << "ULTIMAS REPRODUCCIONES" << endl;
            cout
                << left << setw(12) << " " << setw(25) << "FECHA DE PUBLICACION"
                << left << setw(24) << "TIEMPO DE DURACION"
                << left << setw(30) << "NUMERO DE REPRODUCCIONES" << endl;

            //DATOS DEL CANAL:
            int duracionTotalReprodSec=0, fechaUltimaPublicacion=0, numTotalReprod=0;
            double ingresosPublicidad=0.0;

            while (infoUltimasReproducciones(duracionTotalReprodSec, fechaUltimaPublicacion,
                numTotalReprod,ingresosPublicidad, true, cantTotalStreamsCanales,
                duracionTotalStreamsCanalesSec)) {
            }

            //PARA EL RESUMEN FINAL:
            if (ingresosPublicidad>mayorIngreso) {
                mayorIngreso=ingresosPublicidad;
                n1CodigoCanalMayorIngreso=n1;
                n2CodigoCanalMayorIngreso=n2;
            }
            ingresosTotalesCanales=ingresosTotalesCanales+ingresosPublicidad;
            ////////////////////////////////////////////////////////////////////////////////////////////////

            // (...)

            /////////////////////////////////////////////////////////////////////////////////// ENCABEZADO 3
            separador('-', ANCHO_DEL_REPORTE);
            resumenDelCanal(duracionTotalReprodSec, fechaUltimaPublicacion, numTotalReprod, ingresosPublicidad);
            separador('=', ANCHO_DEL_REPORTE);
            ////////////////////////////////////////////////////////////////////////////////////////////////

        }
        else {
            int duracionTotalReprodSec=0, fechaUltimaPublicacion=0, numTotalReprod=0;
            double ingresosPublicidad=0.0;
            int cantIgnorada=0, duracionIgnorada=0;

            while (infoUltimasReproducciones(duracionTotalReprodSec, fechaUltimaPublicacion, numTotalReprod,
                ingresosPublicidad, false, cantIgnorada,
                duracionIgnorada)); //FALSE PORQUE NO SE CUMPLE
                //ACÁ NO SE COLOCA NADA
        }

    }

    resumenFinal(cantTotalStreamsCanales, duracionTotalStreamsCanalesSec, ingresosTotalesCanales,
        n1CodigoCanalMayorIngreso, n2CodigoCanalMayorIngreso, mayorIngreso);
}
