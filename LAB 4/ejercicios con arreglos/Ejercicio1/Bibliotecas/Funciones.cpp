//
// Created by PC on 25/09/2026.
//

#include "Funciones.h"

void cargarEmpleadosTXT(const char *nombreArchivo, int *codigos, char *nombres, char *areasDeTrabajo,
    double *horasExtra, int &numEmpleados) {

    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    numEmpleados = 0;
    int codigo;
    char nombre_completo[50];
    char area;
    double cantHorasExtra;

    while (entrada >> codigo) { //LEE POR LINEA
        entrada >> nombre_completo >> area >> cantHorasExtra;
        codigos[numEmpleados] = codigo;
        nombres[numEmpleados] = *nombre_completo;
        areasDeTrabajo[numEmpleados] = area;
        horasExtra[numEmpleados] = cantHorasExtra;
        numEmpleados++;
    }
}

void separador(ofstream &archivo, char c, int n) {
    for (int i = 0; i < n; i++) archivo << c;
    archivo << endl;
}

void encabezadoPrincipalArch1(ofstream &archivo1) {
    separador(archivo1, '=', ANCHO_REPORTE);
    archivo1 << right << setw((ANCHO_REPORTE+46)/2) << "REPORTE DE HORAS EXTRA - EMPRESA ANDINA TEXTIL" << endl;
    separador(archivo1, '=', ANCHO_REPORTE);
    archivo1 << left << setw(ANCHO_REPORTE/6) << "CODIGO" << setw(ANCHO_REPORTE/8) << "AREA"
            << setw(ANCHO_REPORTE/6) << "HORAS" << setw(ANCHO_REPORTE/5) << "PAGO (S/)"
            << setw(ANCHO_REPORTE/5) << "CLASIFICACION" << endl;
    separador(archivo1, '-', ANCHO_REPORTE);
}

void encabezadoPrincipalArch2(ofstream &archivo2) {
    separador(archivo2, '=', ANCHO_REPORTE);
    archivo2 << right << setw((ANCHO_REPORTE+46)/2) << "REPORTE DE HORAS EXTRA - EMPRESA ANDINA TEXTIL" << endl;
    archivo2 << right << setw((ANCHO_REPORTE+58)/2) << "(Ordenado por: Clasificacion -> Horas -> Area, ascendente)" << endl;
    separador(archivo2, '=', ANCHO_REPORTE);
    archivo2 << left << setw(ANCHO_REPORTE/6) << "CODIGO" << setw(ANCHO_REPORTE/8) << "AREA"
            << setw(ANCHO_REPORTE/6) << "HORAS" << setw(ANCHO_REPORTE/5) << "PAGO (S/)"
            << setw(ANCHO_REPORTE/5) << "CLASIFICACION" << endl;
    separador(archivo2, '-', ANCHO_REPORTE);
}

void encabezadoResumen(ofstream &archivo) {
    separador(archivo, '=', ANCHO_REPORTE);
    archivo << right << setw((ANCHO_REPORTE+16)/2) << "RESUMEN POR AREA" << endl;
    separador(archivo, '=', ANCHO_REPORTE);
}

double calcularPago(char area, double horasExtra) {
    double pagoPor1hora=0;
    if (area=='A') pagoPor1hora=8.50;
    if (area=='B') pagoPor1hora=7.80;
    if (area=='C') pagoPor1hora=9.20;
    return horasExtra*pagoPor1hora;
}

void imprimirDatosDelEmpleado(ofstream &archivo, int codigo, char area, double horasExtra, double pago) {
    archivo << left << setw(ANCHO_REPORTE/6) << codigo << setw(ANCHO_REPORTE/8) << area
            << setw(ANCHO_REPORTE/6) << horasExtra << setw(ANCHO_REPORTE/5)
            << fixed << setprecision(2) << pago;
    if (horasExtra>10.0) archivo << setw(ANCHO_REPORTE/5) << "EXCESO" << endl;
    else archivo << setw(ANCHO_REPORTE/5) << "NORMAL" << endl;
}

void imprimirListadoDeEmpleados(ofstream &archivo1, ofstream &archivo2, int *codigos, char *areasDeTrabajo,
    double *horasExtra, int numEmpleados, int &cantEmpleadosA, double &totalHorasExtraA, double &totalPagadoA,
    int &cantEmpleadosB, double &totalHorasExtraB, double &totalPagadoB, int &cantEmpleadosC, double &totalHorasExtraC,
    double &totalPagadoC) {

    cantEmpleadosA=0, cantEmpleadosB=0, cantEmpleadosC=0;
    totalHorasExtraA=0.0, totalHorasExtraB=0.0, totalHorasExtraC=0.0;
    totalPagadoA=0.0, totalPagadoB=0.0, totalPagadoC=0.0;

    for (int i = 0; i < numEmpleados; i++) {
        double pago=calcularPago(areasDeTrabajo[i], horasExtra[i]);
        imprimirDatosDelEmpleado(archivo1, codigos[i], areasDeTrabajo[i], horasExtra[i], pago);

        if (areasDeTrabajo[i]=='A'){
            cantEmpleadosA++;
            totalHorasExtraA+=horasExtra[i];
            totalPagadoA+=pago;
        }
        else if (areasDeTrabajo[i]=='B'){
            cantEmpleadosB++;
            totalHorasExtraB+=horasExtra[i];
            totalPagadoB+=pago;
        }
        else if (areasDeTrabajo[i]=='C'){
            cantEmpleadosC++;
            totalHorasExtraC+=horasExtra[i];
            totalPagadoC+=pago;
        }
    }

    //PARA EL REPORTE ORDENADO
    ordenarEmpleados(codigos, areasDeTrabajo, horasExtra, numEmpleados);

    for (int i = 0; i < numEmpleados; i++) {
        double pago=calcularPago(areasDeTrabajo[i], horasExtra[i]);
        imprimirDatosDelEmpleado(archivo2, codigos[i], areasDeTrabajo[i], horasExtra[i], pago);
    }
}

void resumenPorArea(ofstream &archivo1, char area, int cantEmpleados, double totalHorasExtra, double totalPagado,
    double* horasExtra, int *codigos, char *areasDeTrabajo, int numEmpleados) {
    if (area=='A') archivo1 << "Area " << area << " (Producción): " << endl;
    if (area=='B') archivo1 << "Area " << area << " (Logística): " << endl;
    if (area=='C') archivo1 << "Area " << area << " (Administración): " << endl;
    archivo1 << left << setw(28) << "  Empleados registrados" << ": " << cantEmpleados << endl;
    archivo1 << left << setw(28) << "  Total horas extra" << ": " << fixed << setprecision(2) << totalHorasExtra << endl;
    archivo1 << left << setw(28) << "  Total pagado (S/)" << ": " << fixed << setprecision(2) << totalPagado << endl;

    int posicionMayor=buscarPosicionMayorDeCadaArea(horasExtra, areasDeTrabajo, numEmpleados, area);
    if (posicionMayor!=-1) {
        archivo1 << left << setw(28) << "  Mayor horas extra" << ": " << fixed << setprecision(2) << horasExtra[posicionMayor]
                << " (Codigo: " << codigos[posicionMayor] << ")" << endl;
    }
}

void resumenDeTotales(ofstream &archivo, double totalPagadoTodasAreas, int numEmpleados) {
    separador(archivo, '=', ANCHO_REPORTE);
    archivo << "TOTAL GENERAL PAGADO EN HORAS EXTRA: S/ " << fixed << setprecision(2) << totalPagadoTodasAreas << endl;
    archivo << "TOTAL DE REGISTROS PROCESADOS: " << numEmpleados << endl;
    separador(archivo, '=', ANCHO_REPORTE);
}

int buscarPosicionMayorDeCadaArea(double *horasExtra, char *areasDeTrabajo, int numEmpleados, char areaBuscada) {

    if (numEmpleados==0) return -1;

    int posicionMayor=0;
    for (int i=0; i<numEmpleados; i++) {
        if (areasDeTrabajo[i]==areaBuscada) { //PARA BUSCAR RESPECTIVAMENTE DENTRO DE CADA AREA
            if (horasExtra[i]>horasExtra[posicionMayor]) {
                posicionMayor=i;
            }
        }
    }
    return posicionMayor;
}

void imprimirResumen(ofstream &archivo1, int *codigos, char *areasDeTrabajo, double *horasExtra,
    int numEmpleados, int cantEmpleadosA, double totalHorasExtraA, double totalPagadoA, int cantEmpleadosB,
    double totalHorasExtraB, double totalPagadoB, int cantEmpleadosC, double totalHorasExtraC, double totalPagadoC) {
    encabezadoResumen(archivo1);
    resumenPorArea(archivo1, 'A', cantEmpleadosA, totalHorasExtraA, totalPagadoA, horasExtra, codigos, areasDeTrabajo, numEmpleados);
    resumenPorArea(archivo1, 'B', cantEmpleadosB, totalHorasExtraB, totalPagadoB, horasExtra, codigos, areasDeTrabajo, numEmpleados);
    resumenPorArea(archivo1, 'C', cantEmpleadosC, totalHorasExtraC, totalPagadoC, horasExtra, codigos, areasDeTrabajo, numEmpleados);
    double totalPagadoTodasAreas=totalPagadoA+totalPagadoB+totalPagadoC;
    resumenDeTotales(archivo1, totalPagadoTodasAreas, numEmpleados);
}

void generarReportes(const char *nombreArchivo1, const char *nombreArchivo2, int *codigos, char *areasDeTrabajo,
    double *horasExtra, int numEmpleados) {

    ofstream salida1(nombreArchivo1);
    if (!salida1) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    ofstream salida2(nombreArchivo2);
    if (!salida2) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    int cantEmpleadosA, cantEmpleadosB, cantEmpleadosC;
    double totalHorasExtraA, totalHorasExtraB, totalHorasExtraC;
    double totalPagadoA, totalPagadoB, totalPagadoC;

    encabezadoPrincipalArch1(salida1);
    encabezadoPrincipalArch2(salida2);

    imprimirListadoDeEmpleados(salida1, salida2, codigos, areasDeTrabajo, horasExtra,
        numEmpleados, cantEmpleadosA, totalHorasExtraA, totalPagadoA, cantEmpleadosB,totalHorasExtraB,
        totalPagadoB,cantEmpleadosC, totalHorasExtraC,totalPagadoC);

    imprimirResumen(salida1, codigos, areasDeTrabajo, horasExtra, numEmpleados, cantEmpleadosA,
        totalHorasExtraA, totalPagadoA, cantEmpleadosB,totalHorasExtraB, totalPagadoB,
        cantEmpleadosC, totalHorasExtraC,totalPagadoC); //PARA EL REPORTE

    imprimirResumen(salida2, codigos, areasDeTrabajo, horasExtra, numEmpleados, cantEmpleadosA,
        totalHorasExtraA, totalPagadoA, cantEmpleadosB,totalHorasExtraB, totalPagadoB,
        cantEmpleadosC, totalHorasExtraC,totalPagadoC); //PARA EL REPORTE ORDENADO
}


//PARA EL REPORTE ORDENADO

void intercambiarInt(int &a, int &b) {
    int aCopia=a;
    a=b, b=aCopia;
}

void intercambiarChar(char &a, char &b) {
    char aCopia=a;
    a=b, b=aCopia;
}

void intercambiarDouble(double &a, double &b) {
    double aCopia=a;
    a=b, b=aCopia;
}

bool esMenor(double horasExtraI, char areaI, double horasExtraJ, char areaJ) {

    bool seClasificaExcesoI=(horasExtraI>10.0);
    bool seClasificaExcesoJ=(horasExtraJ>10.0);

    if (seClasificaExcesoI!=seClasificaExcesoJ) { // EXCESO != NORMAL
        return seClasificaExcesoI; //PRIMERO IRÁ EXCESO
    }

    if (horasExtraI!=horasExtraJ) { // DE HORA MENOR A HORA MAYOR (ASCENDENTE)
        return horasExtraI<horasExtraJ;
    }

    return areaI<areaJ; // A < B < C (ASCENDENTE)
}

void ordenarEmpleados(int *codigos, char *areasDeTrabajo, double *horasExtra, int numEmpleados) {
    for (int i=0; i<(numEmpleados-1); i++) {
        for (int j=(i+1); j<numEmpleados; j++) {
            if (esMenor(horasExtra[j], areasDeTrabajo[j],horasExtra[i], areasDeTrabajo[i])) {
                intercambiarInt(codigos[i], codigos[j]);
                intercambiarChar(areasDeTrabajo[i], areasDeTrabajo[j]);
                intercambiarDouble(horasExtra[i], horasExtra[j]);
            }
        }
    }
}
