//
// Created by PC on 15/09/2026.
//

#include "Funciones.h"
#include <iomanip>

bool abrirArchivos1(ifstream &csv, ofstream &json) {
    csv.open("ArchivosDeDatos/ventas.csv");
    json.open("ArchivosDeDatos/ventas.json");
    return csv.is_open() and json.is_open();
}

void imprimirFechaHora(ofstream &json, long long fechaHora) {
    int fecha=fechaHora/1000000;
    int anio=fecha/10000, mes=(fecha%10000)/100, dia=fecha%100;
    int tiempo=fechaHora%1000000;
    int hora=tiempo/10000,min=(tiempo%10000)/100, seg=tiempo%100;
    json << setw(4) << anio << "-" << right << setw(2) << setfill('0') << mes << "-"
        << setw(2) << dia << "T" << setw(2) << hora << ":" << setw(2) << min << ":"
        << setw(2) << seg << setfill(' ');
}

bool validarFechasHoras(int dia, int mes, int anio, int hora, int min, int seg) {
    if (anio<1) return false;
    if (mes<1 or mes>12) return false;
    if (dia<1 or dia>diasDelMes(mes, anio)) return false;
    if (hora<0 or hora>23) return false;
    if (min<0 or min>59) return false;
    if (seg<0 or seg>59) return false;
    return true;
}

bool esAnioBisiesto(int anio) {
    if (anio%400==0) return true;
    if (anio%100==0) return false;
    if (anio%4==0) return true;
    return false;
}

int diasDelMes(int mes, int anio) { //PARA CALCULAR LOS DIAS DEPENDIENDO DEL MES
    if (mes==1 or mes==3 or mes==5 or mes==7 or mes==8 or mes==10 or mes==12) return 31; //esos meses tienen 31 dias
    if (mes==4 or mes==6 or mes==9 or mes==11) return 30; //esos meses tienen 30 dias
    if (mes==2) return 28;
    if (esAnioBisiesto(anio)==true) return 29;
}

long long calcularFechaHora(int dia, int mes, int anio, int hora, int min, int seg) {
    int fecha=(anio*10000)+(mes*100)+dia;
    int tiempo=(hora*10000)+(min*100)+seg;
    long long fechaHora=((long long)fecha*1000000)+tiempo;
    return fechaHora;
}

void generarReporteJSON(ifstream &csv, ofstream &json) {
    int dia, mes, anio, hora, min, seg, cantidad, ID;
    double monto, importe, totalImporte=0.0, mayorImporte=-1.0, menorImporte=999.99;;
    char c, categoria;
    int cantVentasInvalidas=0, cantVentasValidas=0, IDmenorImporte, IDmayorImporte;
    long long fechaHora, fechaHoraMenorImp, fechaHoraMayorImp;

    while (csv >> dia) {
        csv >> c >> mes >> c >> anio >> c >> hora >> c >> min >> c >> seg >> c >> ID >> c >> categoria >> c >> cantidad >> c >> monto;
        importe = cantidad*monto;

        if (validarFechasHoras(dia, mes, anio, hora, min, seg)==true) {
            cantVentasValidas++;
            json << "{\"fechaHora\": \"";
            fechaHora=calcularFechaHora(dia, mes, anio, hora, min, seg);
            imprimirFechaHora(json, fechaHora);
            json << "\", \"id\": " << ID << ", \"categoria\": \"" << categoria << "\", \"importe\": "
            << fixed << setprecision(2) << importe << "}" << endl;
            totalImporte+=importe;

            if (importe<menorImporte) {
                menorImporte = importe;
                IDmenorImporte=ID;
                fechaHoraMenorImp=fechaHora;
            }
            if (importe>mayorImporte) {
                mayorImporte = importe;
                IDmayorImporte=ID;
                fechaHoraMayorImp=fechaHora;
            }
        }
        else cantVentasInvalidas++;
    }
    json << "{\"ventas\": " << cantVentasValidas << ", \"ventasInvalidas\": " << cantVentasInvalidas << ", \""
        << "total\": " << fixed << setprecision(2) << totalImporte << ", \"mayorImporte\": " << mayorImporte
        << ", \"mayorId\": " << IDmayorImporte << ", \"mayorFechaHora\": \"";
        imprimirFechaHora(json, fechaHoraMayorImp);
    json << "\", \"menorImporte\": " << menorImporte << ", \"menorId\": " << IDmenorImporte << ", \"menorFechaHora\": \"";
        imprimirFechaHora(json, fechaHoraMenorImp);
    json << "\"}";
}

void cerrarArchivos1(ifstream &csv, ofstream &json) {
    csv.close();
    json.close();
}

////////////////////////////////////////////////////////////////////////////////////////////

bool abrirArchivos2(ifstream &entrada, ofstream &salida) {
    entrada.open("ArchivosDeDatos/ventas.json");
    salida.open("ArchivosDeReportes/Reporte.txt");
    return entrada.is_open() and salida.is_open();
}

void separador(ofstream &salida, char c, int n) {
    for (int i = 0; i < n; i++) salida << c;
    salida << endl;
}

void encabezado(ofstream &salida) {
    separador(salida, '-', ANCHO_REPORTE);
    salida << "REPORTE DE VENTAS (leido desde JSON)" << endl;
    separador(salida, '-', ANCHO_REPORTE);
    salida << left << setw(ANCHO_REPORTE/2) << "Fecha y hora"
            << right << setw(ANCHO_REPORTE/8) << "Id" << setw(ANCHO_REPORTE/8) << "Cat"
            << setw(ANCHO_REPORTE/4) << "Importe" << endl;
    separador(salida, '-', ANCHO_REPORTE);
}

void resumen(ofstream &salida, int cantVentasValidas, int cantVentasInvalidas, double totalImporte,
    double importeMayor, int IDmayorImporte, long long fechaHoraMayorImporte, double importeMenor,
    int IDmenorImporte, long long fechaHoraMenorImporte) {
    salida << left << setw(25) << "Ventas:" << right << setw(23) << cantVentasValidas << endl;
    salida << left << setw(25) << "Fechas invalidas:" << right << setw(23) << cantVentasInvalidas << endl;
    salida << left << setw(25) << "Total importes:" << right << setw(23) << totalImporte << endl;
    salida << left << setw(25) << "Importe mayor:"
            << right << setw(23) << fixed << setprecision(2) << importeMayor << endl;
    imprimirIDyFechaHoraVenta(salida, IDmayorImporte, fechaHoraMayorImporte);
    salida << left << setw(25) << "Importe menor:"
             << right << setw(23) << fixed << setprecision(2) << importeMenor << endl;
    imprimirIDyFechaHoraVenta(salida, IDmenorImporte, fechaHoraMenorImporte);
    separador(salida, '-', ANCHO_REPORTE);
}

void leerFechaHora(ifstream &entrada, int &dia, int &mes, int &anio, int &hora, int &min, int &seg) {
    char c;
    entrada >> anio >> c >> mes >> c >> dia >> c >> hora >> c >> min >> c >> seg;
}

void imprimirIDyFechaHoraVenta(ofstream &salida, int ID, long long fechaHora) {
    salida << "  venta #" << ID << " del ";
    imprimirFechaHora(salida, fechaHora);
    salida << endl;
}

void generarReporteTXT(ifstream &entrada, ofstream &salida) {
    encabezado(salida);
    char categoria;
    int dia, mes, anio, hora, min, seg, ID, cantVentasValidas, cantVentasInvalidas, IDmayorImporte, IDmenorImporte;;
    double importe, totalImporte, importeMayor, importeMenor;;
    long long fechaHora, fechaHoraMayorImporte, fechaHoraMenorImporte;

    while (entrada.peek()=='{') {
        entrada.ignore(10, '"');
        if (entrada.peek()=='f') {
            entrada.ignore(1000, ':');
            entrada.ignore(1000, '"');
            leerFechaHora(entrada, dia, mes, anio, hora, min, seg);
            entrada.ignore(1000, ':');
            entrada >> ID;
            entrada.ignore(1000, ':');
            entrada.ignore(1000, '"');
            entrada >> categoria;
            entrada.ignore(1000, ':');
            entrada >> importe;
            entrada.ignore(1000, '\n'); //<--AL FINAL SIEMPRE EL SALTO DE LINEA
            fechaHora=calcularFechaHora(dia, mes, anio, hora, min, seg);
            imprimirFechaHora(salida,fechaHora);
            salida << left << setw((ANCHO_REPORTE/2)-19) << " " << right << setw(ANCHO_REPORTE/8) << ID
                    << setw(ANCHO_REPORTE/8) << categoria << setw(ANCHO_REPORTE/4) << fixed << setprecision(2) << importe << endl;
        }
        else { //entrada.peek()=='v'
            entrada.ignore(10, ':');
            entrada >> cantVentasValidas;
            entrada.ignore(1000, ':');
            entrada >> cantVentasInvalidas;
            entrada.ignore(1000, ':');
            entrada >> totalImporte;
            entrada.ignore(1000, ':');
            entrada >> importeMayor;
            entrada.ignore(1000, ':');
            entrada >> IDmayorImporte;
            entrada.ignore(1000, ':');
            entrada.ignore(1000, '"');
            leerFechaHora(entrada, dia, mes, anio, hora, min, seg);
            fechaHoraMayorImporte=calcularFechaHora(dia, mes, anio, hora, min, seg);
            entrada.ignore(1000, ':');
            entrada >> importeMenor;
            entrada.ignore(1000, ':');
            entrada >> IDmenorImporte;
            entrada.ignore(1000, ':');
            entrada.ignore(1000, '"');
            leerFechaHora(entrada, dia, mes, anio, hora, min, seg);
            fechaHoraMenorImporte=calcularFechaHora(dia, mes, anio, hora, min, seg);
            entrada.ignore(1000, '\n');
        }
    }
    separador(salida, '-', ANCHO_REPORTE);
    resumen(salida, cantVentasValidas, cantVentasInvalidas, totalImporte,importeMayor, IDmayorImporte,
        fechaHoraMayorImporte,  importeMenor,IDmenorImporte, fechaHoraMenorImporte);
}

void cerrarArchivos2(ifstream &entrada, ofstream &salida) {
    entrada.close();
    salida.close();
}