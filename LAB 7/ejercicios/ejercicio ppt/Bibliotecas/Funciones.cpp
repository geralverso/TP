//
// Created by PC on 1/11/2026.
//

#include "Funciones.h"


//FUNCIONES PARA LEER Y CARGAR:

void abrirArchLectura(const char* nombreArch, ifstream& arch) {
    arch.open(nombreArch);
    if (!arch) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
}

char* leerCadenaExacta(ifstream &arch, char delimitador) {
    char buffer[CAP_BUFFER];
    arch.getline(buffer, CAP_BUFFER, delimitador);
    if (arch.eof()) return nullptr;
    char* cadena=new char[strlen(buffer)+1];
    strcpy(cadena, buffer);
    return cadena;
}

void cargarPersonal(const char *nombreArch, int *&dnis, char **&nombres, double *&sueldos, int &numPersonal) {
    ifstream entrada;
    abrirArchLectura(nombreArch, entrada);
    char c, *bufferNombres[CAP_BUFFER];
    int dni, bufferDNI[CAP_BUFFER];
    double sueldo, bufferSueldo[CAP_BUFFER];

    numPersonal=0;
    while (entrada >> dni >> c) {
        char* nombre=leerCadenaExacta(entrada, ',');
        entrada >> sueldo;
        // bufferDNI[numPersonal]=dni;
        // bufferNombres[numPersonal]=nombre;
        // bufferSueldo[numPersonal]=sueldo;
        // numPersonal++;
        insertarOrdenado(bufferNombres, bufferDNI, bufferSueldo, nombre,  dni, sueldo, numPersonal);
    }

    dnis=new int[numPersonal];
    nombres=new char*[numPersonal];
    sueldos=new double[numPersonal];
    for (int i=0;i<numPersonal;i++) {
        dnis[i]=bufferDNI[i];
        nombres[i]=bufferNombres[i];
        sueldos[i]=bufferSueldo[i];
    }
}

int insertarOrdenado(char** bufferNombres, int *bufferDNI, double* bufferSueldo, char* nombreNuevo, int dniNuevo,
    double sueldoNuevo, int &numPersonal) {
    int i=numPersonal-1;
    // bool cond1=strcmp(bufferNombres[i], nombreNuevo)>0;
    // bool cond2=bufferSueldo[i]<sueldoNuevo;

    while (i>=0 and strcmp(bufferNombres[i], nombreNuevo)>0) {
        bufferNombres[i+1]=bufferNombres[i];
        bufferDNI[i+1]=bufferDNI[i];
        bufferSueldo[i+1]=bufferSueldo[i];
        i--;
    }
    bufferNombres[i+1]=nombreNuevo;
    bufferDNI[i+1]=dniNuevo;
    bufferSueldo[i+1]=sueldoNuevo;
    numPersonal++;
    return i+1;
}


//FUNCIONES PARA ORDENAR:

void intercambiarCadena(char*&a, char*&b) {
    char* aux=a;
    a=b, b=aux;
}

void intercambiarEntero(int &a, int &b) {
    int aux=a;
    a=b, b=aux;
}

void intercambiarDecimal(double &a, double &b) {
    double aux=a;
    a=b, b=aux;
}

void ordenarPersonal(int* dnis, char** nombres, double* sueldos, int numPersonal) {
    for (int i=0;i<numPersonal-1;i++) {
        for (int j=i+1;j<numPersonal;j++) {
            if (sueldos[i]<sueldos[j]) {
                intercambiarCadena(nombres[i], nombres[j]);
                intercambiarEntero(dnis[i], dnis[j]);
                intercambiarDecimal(sueldos[i], sueldos[j]);
            }
        }
    }
}


//FUNCIONES PARA GENERAR REPORTES:

void abrirArchEscritura(const char* nombreArch, ofstream& arch) {
    arch.open(nombreArch);
    if (!arch) {
        cerr << "Error al abrir el archivo." << endl;
        exit(1);
    }
}

void generarReporte(const char *nombreArch, const int *dnis, char **nombres, const double *sueldos, int numPersonal) {
    ofstream salida;
    abrirArchEscritura(nombreArch, salida);
    salida << left << setw(10) << "DNI:" << setw(30) << "NOMBRE:" << "SUELDO:" << endl;
    for (int i=0; i<numPersonal; i++) {
        salida << left << setw(10) << dnis[i] << setw(30) << nombres[i] << setw(10) << fixed
                << setprecision(2) << sueldos[i] << endl;
    }
}


//FUNCIONES PARA LIBERAR RECURSOS:

void liberarMemoria(const int *dnis, char **nombres, const double *sueldos, int numPersonal) {
    for (int i=0;i<numPersonal;i++) delete [] nombres[i];
    delete [] nombres;
    delete [] dnis;
    delete [] sueldos;
}
