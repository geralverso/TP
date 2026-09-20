//
// Created by PC on 19/09/2026.
//

#include "Funciones.h"
#include <iomanip>

bool abrirArchivos1(ifstream &csv, ofstream &json) {
    csv.open("ArchivosDeDatos/reservas.csv");
    json.open("ArchivosDeDatos/reservas.json");
    return csv.is_open() && json.is_open();
}

bool esAnioBisiesto(int anio) {
    if (anio%400==0) return true;
    if (anio%100==0) return false;
    if (anio%4==0) return true;
    return false;
}

int calcularDiasDelMes(int mes, int anio) {
    if (mes==1 or mes==3 or mes==5 or mes==7 or mes==8 or mes==10 or mes==12) return 31;
    if (mes==4 or mes==6 or mes==9 or mes==11) return 30;
    if (mes==2) return 28;
    if (esAnioBisiesto(anio)) return 29;
}

bool validarFechaHora(int dia, int mes, int anio, int hora, int min, int seg) {
    if (anio<1) return false;
    if (mes<1 or mes>12) return false;
    if (dia<1 or dia>calcularDiasDelMes(mes, anio)) return false;
    if (hora<0 or hora>23) return false;
    if (min<0 or min>59) return false;
    if (seg<0 or seg>59) return false;
    return true;
}

long long calcularFechaHora(int dia, int mes, int anio, int hora, int min, int seg) {
    long long fecha=(anio*10000)+(mes*100)+dia;
    long long tiempo=(hora*10000)+(min*100)+seg;
    long long fechaHora=(fecha*1000000)+tiempo;
    return fechaHora;
}

void transformarFechaHoraISO(ofstream &json, long long fechaHora) {
    int fecha=fechaHora/1000000, anio=fecha/10000, mes=(fecha%10000)/100, dia=fecha%100;
    int tiempo=fechaHora%1000000, hora=tiempo/10000, min=(tiempo%10000)/100, seg=tiempo%100;
    json << right << setw(4) << setfill('0') << anio << "-" << setw(2) << mes << "-" << setw(2) << dia
         << "T" << setw(2) << hora << ":" << setw(2) << min << ":" << setw(2) << seg << setfill(' ');
}

void resumenJSON(ofstream &json, int cantReservasValidas, int cantReservasInvalidas, double importesTotales,
    double mayorImporte, int IDmayorImporte, long long fechaHoraMayorImporte, double menorImporte, int IDmenorImporte,
    long long fechaHoraMenorImporte) {
    json << "{\"reservas\": " << cantReservasValidas << ", \"reservasInvalidas\": " << cantReservasInvalidas
            << ", \"total\": " << importesTotales << ", \"mayorImporte\": " << mayorImporte << ", \"mayorId\": "
            << IDmayorImporte << ", \"mayorFechaHora\": \"";
    transformarFechaHoraISO(json, fechaHoraMayorImporte);
    json << "\", \"menorImporte\": " << menorImporte << ", \"menorId\": " << IDmenorImporte << ", \"menorFechaHora\": \"";
    transformarFechaHoraISO(json, fechaHoraMenorImporte);
    json << "\"}";
}

void generarJSON(ifstream &csv, ofstream &json) {
    int dia, mes, anio, hora, min, seg, id, cantNoches, cantReservasValidas=0, cantReservasInvalidas=0;
    long long fechaHora;
    char c, tipoDeHabitacion;
    double precioPorNoche, importe, importesTotales=0.0;

    double mayorImporte=-1.0, menorImporte=99999.99;
    int IDmayorImporte, IDmenorImporte;
    long long fechaHoraMayorImporte, fechaHoraMenorImporte;

    while (csv >> dia) {
        csv >> c >> mes >> c >> anio >> c >> hora >> c >> min >> c >> seg >> c >> id >> c >> tipoDeHabitacion
            >> c >> cantNoches >> c >> precioPorNoche;

        if (validarFechaHora(dia, mes, anio, hora, min, seg)==true) { //se imprimen solo las lineas validas
            cantReservasValidas++;
            fechaHora=calcularFechaHora(dia, mes, anio, hora, min, seg);
            importe=cantNoches*precioPorNoche;
            importesTotales+=importe;

            json << "{\"fechaHora\": \"";
            transformarFechaHoraISO(json, fechaHora);
            json << "\", \"id\": " << id << ", \"habitacion\": \"" << tipoDeHabitacion << "\", \"importe\": "
                    << fixed << setprecision(2) << importe << "}" << endl;

            if (importe>mayorImporte) {
                mayorImporte=importe;
                IDmayorImporte=id;
                fechaHoraMayorImporte=fechaHora;
            }
            if (importe<menorImporte) {
                menorImporte=importe;
                IDmenorImporte=id;
                fechaHoraMenorImporte=fechaHora;
            }
        }
        else {
            cantReservasInvalidas++;
        }
    }
    resumenJSON(json, cantReservasValidas, cantReservasInvalidas, importesTotales,mayorImporte, IDmayorImporte,
        fechaHoraMayorImporte, menorImporte, IDmenorImporte,fechaHoraMenorImporte);
}

void cerrarArchivos1(ifstream &csv, ofstream &json) {
    csv.close();
    json.close();
}

bool abrirArchivos2(ifstream &entrada, ofstream &salida) {
    entrada.open("ArchivosDeDatos/reservas.json");
    salida.open("ArchivosDeReportes/reporte.txt");
    return entrada.is_open() && salida.is_open();
}

void separador(ofstream &salida, char c, int n) {
    for (int i = 0; i < n; i++) salida << c;
    salida << endl;
}

void encabezadoTXT(ofstream &salida) {
    separador(salida, '-', ANCHO);
    salida << "REPORTE DE RESERVAS" << endl;
    separador(salida, '-', ANCHO);
    salida << left << setw(20) << "Fecha y hora" << right << setw(6) << "Id" << setw(7) << "Hab"
            << setw(47-33) << "Importe" << endl;
    separador(salida, '-', ANCHO);
}

bool esLineaDeReservaHab(ifstream &entrada) {
    entrada.ignore(10, '"');
    return entrada.peek()=='f';
}

long long leerYPasarFechaHoraISO(ifstream &entrada) {
    int dia, mes, anio, hora, min, seg;
    char c;
    entrada >> anio >> c >> mes >> c >> dia >> c >> hora >> c >> min >> c >> seg;
    return calcularFechaHora(dia, mes, anio, hora, min, seg);
}

void resumenTXT(ofstream &salida, int cantReservasValidas, int cantReservasInvalidas, double importeTotal,
    double mayorImporte, int IDmayorImporte, long long fechaHoraMayorImporte, double menorImporte, int IDmenorImporte,
    long long fechaHoraMenorImporte) {
    salida << left << setw(30) << "Reservas validas: " << right << setw(17) << cantReservasValidas << endl;
    salida << left << setw(30) << "Reservas invalidas: " << right << setw(17) << cantReservasInvalidas << endl;
    salida << left << setw(30) << "Total facturado: " << right << setw(17) << fixed << setprecision(2)
            << importeTotal << endl;
    salida << left << setw(30) << "Importe mayor: " << right << setw(17) << mayorImporte << endl;
    imprimirDatosMayorImporteTXT(salida,IDmayorImporte,fechaHoraMayorImporte);
    salida << left << setw(30) << "Importe menor: " << right << setw(17) << menorImporte << endl;
    imprimirDatosMayorImporteTXT(salida,IDmenorImporte,fechaHoraMenorImporte);
}

void imprimirDatosMayorImporteTXT(ofstream &salida, int id, long long fecha) {
    salida << "  reserva #" << id << " del ";
    transformarFechaHoraISO(salida, fecha);
    salida << endl;
}

void generarTXT(ifstream &entrada, ofstream &salida) {
    encabezadoTXT(salida);
    int id;
    char tipoHabitacion;
    double importe;
    int cantReservasValidas, cantReservasInvalidas, IDmayorImporte, IDmenorImporte;
    double importeTotal, mayorImporte, menorImporte;
    long long fechaHoraMayorImporte, fechaHoraMenorImporte, fechaHora;

    while (entrada.peek()=='{') {
        if (esLineaDeReservaHab(entrada)) { //se leen las reservas
            entrada.ignore(1000, ':');
            entrada.ignore(1000, '"'); fechaHora= leerYPasarFechaHoraISO(entrada);
            entrada.ignore(1000, ':'); entrada >> id;
            entrada.ignore(1000, ':');
            entrada.ignore(1000, '"'); entrada >> tipoHabitacion;
            entrada.ignore(1000, ':'); entrada >> importe;
            entrada.ignore(1000, '\n'); transformarFechaHoraISO(salida, fechaHora);
            salida << right << setw(7) << id << setw(7) << tipoHabitacion << setw(47-33)
                    << fixed << setprecision(2) << importe << endl;
        }
        else { //se lee el resumenJSON anterior
            entrada.ignore(1000, ':'); entrada >> cantReservasValidas;
            entrada.ignore(1000, ':'); entrada >> cantReservasInvalidas;
            entrada.ignore(1000, ':'); entrada >> importeTotal;
            entrada.ignore(1000, ':'); entrada >> mayorImporte;
            entrada.ignore(1000, ':'); entrada >> IDmayorImporte;
            entrada.ignore(1000, ':');
            entrada.ignore(1000, '"'); fechaHoraMayorImporte = leerYPasarFechaHoraISO(entrada);
            entrada.ignore(1000, ':'); entrada >> menorImporte;
            entrada.ignore(1000, ':'); entrada >> IDmenorImporte;
            entrada.ignore(1000, ':');
            entrada.ignore(1000, '"'); fechaHoraMenorImporte = leerYPasarFechaHoraISO(entrada);
            entrada.ignore(1000, '\n');
        }
    }
    separador(salida, '-', ANCHO);
    resumenTXT(salida,cantReservasValidas, cantReservasInvalidas, importeTotal,mayorImporte, IDmayorImporte,
        fechaHoraMayorImporte, menorImporte, IDmenorImporte, fechaHoraMenorImporte);
    separador(salida, '-', ANCHO);
}

void cerrarArchivos2(ifstream &entrada, ofstream &salida) {
    entrada.close();
    salida.close();
}
