//
// Created by PC on 19/09/2026.
//

#include "Funciones.h"
#include <iomanip>

bool abrirArchivos(ifstream &entrada, ofstream &salida) {
    entrada.open("ArchivosDeDatos/turnos.json", ios::in);
    salida.open("ArchivosDeReportes/reporte.txt", ios::out);
    return entrada.is_open() && salida.is_open();
}

void separador(ofstream &salida, char c, int n) {
    for (int i = 0; i < n; i++) salida << c;
    salida << endl;
}

void encabezado(ofstream &salida) {
    separador(salida, '-', ANCHO);
    salida << "REPORTE DE PACIENTES POR TURNO" << endl;
    separador(salida, '-', ANCHO);
    salida << left << setw(10) << "Turno" << right << setw(11) << "Registros" << setw(10) << "Suma"
            << setw(12) << "Promedio" << setw(10) << "Minimo" << setw(10) << "Maximo" << endl;
    separador(salida, '-', ANCHO);
}

void acumularPacientes(int cantPacientes, int &cantRegistros, int &sumaPacientes, int &minCantPacientes,
                       int &maxCantPacientes) {
    cantRegistros++;
    sumaPacientes+=cantPacientes;
    if (cantPacientes<minCantPacientes) minCantPacientes=cantPacientes;
    if (cantPacientes>maxCantPacientes) maxCantPacientes=cantPacientes;
}

void generarReporte(ifstream &entrada, ofstream &salida) {
    encabezado(salida);
    int id, cantPacientes, cantRegistrosTurnoManana=0, cantRegistrosTurnoTarde=0, sumaPacientesTurnoManana=0;
    int sumaPacientesTurnoTarde=0, minCantPacientesTurnoManana=999, minCantPacientesTurnoTarde=999;
    int maxCantPacientesTurnoManana=-1, maxCantPacientesTurnoTarde=-1;
    char turno;

    while (entrada.peek()=='{') {
        entrada.ignore(1000, ':');
        entrada >> id;
        entrada.ignore(1000, ':');
        entrada.ignore(1000, '"');
        entrada >> turno;
        entrada.ignore(1000, ':');
        entrada >> cantPacientes;
        entrada.ignore(1000, '\n');

        if (turno=='M') acumularPacientes(cantPacientes, cantRegistrosTurnoManana, sumaPacientesTurnoManana,
                minCantPacientesTurnoManana, maxCantPacientesTurnoManana);
        else acumularPacientes(cantPacientes, cantRegistrosTurnoTarde, sumaPacientesTurnoTarde,
                minCantPacientesTurnoTarde, maxCantPacientesTurnoTarde);
    }

    double promedioTurnoManana=(cantRegistrosTurnoManana>0)?((double)sumaPacientesTurnoManana/cantRegistrosTurnoManana):0.0;
    double promedioTurnoTarde=(cantRegistrosTurnoTarde>0)?((double)sumaPacientesTurnoTarde/cantRegistrosTurnoTarde):0.0;
    int totalRegistrosAmbosTurnos=cantRegistrosTurnoManana+cantRegistrosTurnoTarde;
    int totalPacientesAmbosTurnos=sumaPacientesTurnoTarde+sumaPacientesTurnoManana;

    //TURNO M
    imprimirLineaConDatosPorTurno(salida, 'M', cantRegistrosTurnoManana, sumaPacientesTurnoManana,
        promedioTurnoManana, minCantPacientesTurnoManana,maxCantPacientesTurnoManana);

    //TURNO T
    imprimirLineaConDatosPorTurno(salida, 'T', cantRegistrosTurnoTarde, sumaPacientesTurnoTarde,
        promedioTurnoTarde, minCantPacientesTurnoTarde,maxCantPacientesTurnoTarde);

    resumen(salida, totalRegistrosAmbosTurnos, totalPacientesAmbosTurnos);
}

void imprimirLineaConDatosPorTurno(ofstream &salida, char turno, int registros, int suma, double promedio, int minimo,
    int maximo) {
    salida << left << setw(10) << turno << right << setw(11) << registros << setw(10) << suma
                << setw(12) << fixed << setprecision(2) << promedio << setw(10) << minimo
                << setw(10) << maximo << endl;
}

void resumen(ofstream &salida, int totalRegistrosAmbosTurnos, int totalPacientesAmbosTurnos) {
    separador(salida, '-', ANCHO);
    salida << left << setw(25) << "Total de registros: " << right << setw(10) << totalRegistrosAmbosTurnos << endl;
    salida << left << setw(25) << "Total de pacientes: " << right << setw(10) << totalPacientesAmbosTurnos << endl;
    separador(salida, '-', ANCHO);
}

void cerrarArchivos(ifstream &entrada, ofstream &salida) {
    entrada.close();
    salida.close();
}
