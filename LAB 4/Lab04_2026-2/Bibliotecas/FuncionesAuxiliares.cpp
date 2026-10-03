//
// Created by PC on 30/09/2026.
//

#include "FuncionesAuxiliares.h"

void leerAniosRevision(ifstream &entrada, int anioRevision) {
    while (entrada.peek()!='\n') {
        if (entrada >> anioRevision) {}
        else {
            entrada.clear();
            break;
        }
    }
}

void cargarVehiculosTXT(const char *nombre, int *codigosVehiculos, char *categoriasVehiculos, int &numVehiculos) {
    ifstream entrada(nombre);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    numVehiculos=0;
    int codigoVehiculo, dni, placa, anioRevision;
    char categoria, a, b, c;
    while (entrada >> codigoVehiculo){
        entrada >> categoria >> dni >> a >> b >> c >> placa;
        leerAniosRevision(entrada, anioRevision);
        codigosVehiculos[numVehiculos]=codigoVehiculo;
        categoriasVehiculos[numVehiculos]=categoria;
        numVehiculos++;
    }
}

void cargarCapturasCSV(const char *nombre, int *codigosVehiculosCapturas, double *velocidadesCapturas,
    int *carrilesCapturas, int *kilometrosCapturas, int *diasCapturas, int *mesCapturas, int *aniosCapturas,
    int *codigosCamarasCapturas, int &numCapturas) {
    ifstream entrada(nombre);
    if (!entrada) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    numCapturas=0;
    int codigoVehiculo, carril, km, dia, mes, anio, codigoCamara;
    double velocidad;
    char c;
    while (entrada >> codigoVehiculo) {
        entrada >> c >> velocidad >> c >> carril >> c >> km >> c >> dia >> c >> mes >> c >> anio >> c >> codigoCamara;
        codigosVehiculosCapturas[numCapturas]=codigoVehiculo;
        velocidadesCapturas[numCapturas]=velocidad;
        carrilesCapturas[numCapturas]=carril;
        kilometrosCapturas[numCapturas]=km;
        diasCapturas[numCapturas]=dia;
        mesCapturas[numCapturas]=mes;
        aniosCapturas[numCapturas]=anio;
        codigosCamarasCapturas[numCapturas]=codigoCamara;
        numCapturas++;
    }
}

void separador(ofstream &salida, char c, int n) {
    for (int i=0; i<n; i++) salida << c;
    salida << endl;
}

void encabezado1(ofstream &salida) {
    separador(salida, '=', ANCHO);
    salida << right << setw((ANCHO+35)/2) << "REPORTE DE INFRACCIONES DE TRANSITO" << endl;
    separador(salida, '=', ANCHO);
}

void encabezado2(const char *titulo, ofstream &salida) {
    salida << titulo << endl;
    separador(salida, '-', ANCHO);
}

int buscarPosicionMayorVelocidadEnCapturasCSV(double *velocidadesCapturas, int numCapturas) {
    if (numCapturas==0) return -1;
    int posicionMayor=-1;
    for (int i=0; i<numCapturas; i++) {
        if (posicionMayor==-1 or velocidadesCapturas[i]>velocidadesCapturas[posicionMayor]) {
            posicionMayor=i;
        }
    }
    return posicionMayor;
}

void buscarValidosEInvalidos(ofstream &salida, int codigoVehiculo, char categoria, int *codigosVehiculosCapturas,
    double *velocidadesCapturas, int *carrilesCapturas, int *kilometrosCapturas, int *diasCapturas, int *mesCapturas,
    int *aniosCapturas, int *codigosCamarasCapturas, int numCapturas, double &montoLocalInfraccM,
    double &montoLocalInfraccG, int &cantCapturasRegistradasLocal, int &posicionMayorVel) {
    for (int j=0; j<numCapturas; j++) {
        if (codigosVehiculosCapturas[j]==codigoVehiculo) {
                double velocidad=velocidadesCapturas[j];
                int carril=carrilesCapturas[j];
                int km=kilometrosCapturas[j];
                int dia=diasCapturas[j];
                int mes=mesCapturas[j];
                int anio=aniosCapturas[j];
                int codigoCamara=codigosCamarasCapturas[j];

                //PARA LAS CAPTURAS VALIDAS E INVALIDAS:
                if (velocidad>=0 and velocidad<=300) {
                    if (carril>=1 and carril<=4) {
                        cantCapturasRegistradasLocal++;
                        if (posicionMayorVel==-1 or velocidad>velocidadesCapturas[posicionMayorVel]) posicionMayorVel=j;
                        if (carril==1) {
                            if (categoria=='E') {} else montoLocalInfraccG+=428.00; //CARRIL INCORRECTO
                            if (velocidad<=80) {} else montoLocalInfraccM+=963.00; //VELOCIDAD NO PERMITIDA
                        }
                        else if (carril==2) {
                            if (categoria=='P') {} else montoLocalInfraccG+=428.00; //CARRIL INCORRECTO
                            if (velocidad<=60) {} else montoLocalInfraccM+=963.00; //VELOCIDAD NO PERMITIDA
                        }
                        else if (carril==3) {
                            if (categoria=='E' or categoria=='L' or categoria=='M') {} else montoLocalInfraccG+=428.00; //CARRIL INCORRECTO
                            if (velocidad>=80 and ((km>=1 and km<=100 and velocidad<=80) or (km>=101 and km<=200 and velocidad<=120) or (km>=201 and km<=300 and velocidad<=100))) {}
                            else montoLocalInfraccM+=963.00; //VELOCIDAD NO PERMITIDA
                        }
                        else if (carril==4) {
                            if (categoria=='L') {} else montoLocalInfraccG+=428.00; //CARRIL INCORRECTO
                            if (velocidad>=80 and ((km>=1 and km<=100 and velocidad<=120) or (km>=101 and km<=200 and velocidad<=160) or (km>=201 and km<=300 and velocidad<=140))) {}
                            else montoLocalInfraccM+=963.00; //VELOCIDAD NO PERMITIDA
                        }
                    }
                    else {
                        salida << codigosVehiculosCapturas[j] << "," << codigoCamara << "," << right << setw(2) << setfill('0') << dia << "/" << setw(2) << mes << "/"
                                << setw(4) << anio << setfill(' ') << ",CARRIL INVALIDO," << carril << endl;
                    }
                }
                else {
                    salida << codigosVehiculosCapturas[j] << "," << codigoCamara << "," << right << setw(2) << setfill('0') << dia << "/" << setw(2) << mes << "/"
                            << setw(4) << anio << setfill(' ') << ",VELOCIDAD INVALIDA," << fixed << setprecision(2) << velocidad << endl;
                }
        }
    }
}

void imprimirInfoDeCadaVehiculo(ofstream &salida, int codigoVehiculo, char categoria, double *montoInfraccM,
    double *montoInfraccG, int cantCapturasRegistradasLocal, double *velocidadesCapturas, int posicionMayorVel,
    int *diasCapturas, int *mesCapturas, int *aniosCapturas, int i) {
    salida << "VEHICULO " << codigoVehiculo << setw(24-13) << " " << left << setw(11) << "Categoria:" << setw(14) << categoria << endl;
    separador(salida, '-', ANCHO);
    salida << left << setw(44) << "Monto Exceso de velocidad (M)" << right << setw(18) << fixed << setprecision(2) << montoInfraccM[i] << endl;
    salida << left << setw(44) << "Monto Carril no permitido (G)" << right << setw(18) << fixed << setprecision(2) << montoInfraccG[i] << endl;
    separador(salida, '-', ANCHO);
    salida << left << setw(44) << "Capturas registradas" << right << setw(18) << cantCapturasRegistradasLocal << endl;
    if (posicionMayorVel!=-1) {
        salida << left << setw(44) << "Mayor velocidad (km/h)" << right << setw(18) << fixed << setprecision(2) << velocidadesCapturas[posicionMayorVel] << endl;
        salida << left << setw(44) << "Fecha de mayor velocidad" << right << setw(ANCHO-44-10) << " " << setw(2) << setfill('0') << diasCapturas[posicionMayorVel]
                << "/" << setw(2) << mesCapturas[posicionMayorVel] << "/" << setw(4) << aniosCapturas[posicionMayorVel] << setfill(' ') << endl;
    }
    separador(salida, '-', ANCHO);
}

void resumenGeneral(ofstream &salida, int numVehiculos, int cantVehiculosInfractores, int cantCapturasValidas,
    double montoTotalInfraccM, double montoTotalInfraccG) {
    double montoTotal=montoTotalInfraccM+montoTotalInfraccG;
    encabezado2("RESUMEN GENERAL", salida);
    salida << left << setw(44) << "Vehiculos procesados" << right << setw(18) << numVehiculos << endl;
    salida << left << setw(44) << "Vehiculos infractores" << right << setw(18) << cantVehiculosInfractores << endl;
    salida << left << setw(44) << "Capturas validas procesadas" << right << setw(18) << cantCapturasValidas << endl;
    salida << left << setw(44) << "Monto infracciones M (S/)" << right << setw(18) << fixed << setprecision(2) << montoTotalInfraccM << endl;
    salida << left << setw(44) << "Monto infracciones G (S/)" << right << setw(18) << fixed << setprecision(2) << montoTotalInfraccG << endl;
    salida << left << setw(44) << "Monto total recaudado (S/)" << right << setw(18) << fixed << setprecision(2) << montoTotal << endl;
    separador(salida, '=', ANCHO);
}

void generarReportes(const char *nombre1, const char *nombre2, int *codigosVehiculos, char *categoriasVehiculos,
    int numVehiculos, int *codigosVehiculosCapturas, double *velocidadesCapturas, int *carrilesCapturas,
    int *kilometrosCapturas, int *diasCapturas, int *mesCapturas, int *aniosCapturas, int *codigosCamarasCapturas,
    int numCapturas, double *montoInfraccM, double *montoInfraccG) {
    ofstream salida1(nombre1);
    if (!salida1) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
    ofstream salida2(nombre2);
    if (!salida2) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }

    encabezado1(salida1);
    int cantCapturasValidas=0, cantVehiculosInfractores=0;
    double montoTotalInfraccM=0.0, montoTotalInfraccG=0.0;

    for (int i=0; i<numVehiculos; i++) {
        int codigoVehiculo=codigosVehiculos[i];
        char categoria=categoriasVehiculos[i];
        double montoLocalInfraccM=0.0, montoLocalInfraccG=0.0;
        int cantCapturasRegistradasLocal=0;
        int posicionMayorVel=-1;
        buscarValidosEInvalidos(salida2, codigoVehiculo, categoria, codigosVehiculosCapturas,velocidadesCapturas,
            carrilesCapturas,kilometrosCapturas,diasCapturas,mesCapturas,aniosCapturas,codigosCamarasCapturas,
            numCapturas,montoLocalInfraccM,montoLocalInfraccG,cantCapturasRegistradasLocal,posicionMayorVel);

        //ACUMULAMOS EN LOS ARREGLOS Y VARIABLES
        montoInfraccM[i]=montoLocalInfraccM;
        montoInfraccG[i]=montoLocalInfraccG;
        cantCapturasValidas+=cantCapturasRegistradasLocal;

        if (montoInfraccM[i]>0.0 or montoInfraccG[i]>0.0) { //sólo muestra los vehículos que cometieron al menos 1 infracción
            cantVehiculosInfractores++;
            montoTotalInfraccM+=montoInfraccM[i];
            montoTotalInfraccG+=montoInfraccG[i];
            imprimirInfoDeCadaVehiculo(salida1, codigoVehiculo, categoria, montoInfraccM, montoInfraccG,
                cantCapturasRegistradasLocal, velocidadesCapturas, posicionMayorVel, diasCapturas, mesCapturas,aniosCapturas, i);
        }
    }
    resumenGeneral(salida1, numVehiculos, cantVehiculosInfractores, cantCapturasValidas, montoTotalInfraccM, montoTotalInfraccG);
}
