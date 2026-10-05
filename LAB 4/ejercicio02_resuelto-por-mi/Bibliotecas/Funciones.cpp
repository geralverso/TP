//
// Created by PC on 2/10/2026.
//

#include "Funciones.h"

void cargarAlumnosCSV(const char *nombre, int *codigosAlumnos, int *ciclosAlumnos, int &numAlumnos) {
    ifstream entrada(nombre);
    if (!entrada) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }
    numAlumnos=0;
    int codigo, ciclo;
    char c;
    while (entrada >> codigo) {
        entrada >> c >> ciclo;
        codigosAlumnos[numAlumnos] = codigo;
        ciclosAlumnos[numAlumnos] = ciclo;
        numAlumnos++;
    }
}

void cargarAlumnosEDITADO(const char *nombre, int *codigosAlumnos, char *nombresAlumnos, int *ciclosAlumnos,
    int &numAlumnosEDITADO) {

    ifstream entrada(nombre);
    if (!entrada) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }
    numAlumnosEDITADO=0;
    int codigo, ciclo;
    char nombreAlumno[25];
    while (entrada >> codigo) {
        entrada >> nombreAlumno >> ciclo;
        codigosAlumnos[numAlumnosEDITADO] = codigo;
        nombresAlumnos[numAlumnosEDITADO] = *nombreAlumno;
        ciclosAlumnos[numAlumnosEDITADO] = ciclo;
        numAlumnosEDITADO++;
    }
}

void cargarNotasCSV(const char *nombre, int *codigosAlumnosNotas, double *notasAlumnosNotas, int &numNotas) {
    ifstream entrada(nombre);
    if (!entrada) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }
    numNotas=0;
    int codigo;
    double nota;
    char c;
    while (entrada >> codigo) {
        entrada >> c >> nota;
        codigosAlumnosNotas[numNotas] = codigo;
        notasAlumnosNotas[numNotas] = nota;
        numNotas++;
    }
}

void encabezado(ofstream &salida) {
    salida << right << setw(ANCHO/3) << "CODIGO" << setw(ANCHO/3) << "CICLO" << setw(ANCHO/3) << "PROMEDIO" << endl;
}

void encabezado2(ofstream &salida) {
    salida << left << setw(ANCHO/4) << "CODIGO" << setw(ANCHO/3) << "ALUMNO" << setw(ANCHO/4) << "CICLO"
            << setw(ANCHO/4) << "PROMEDIO" << endl;
}

double calcularPromedioDeNotas(double *notasAlumnosNotas, int numNotas, int *codigosAlumnosNotas, int codigoBuscado) {
    int cantNotas=0;
    double sumaDeNotas=0.0;
    for (int i=0; i<numNotas; i++) {
        if (codigosAlumnosNotas[i]==codigoBuscado) {
            sumaDeNotas+=notasAlumnosNotas[i];
            cantNotas++;
        }
    }
    double promedio=(cantNotas>0)?(sumaDeNotas/cantNotas):0.0;
    return promedio;
}

void armarArregloPromediosNotas(int numAlumnos, int *codigosAlumnos, double *promedios, double *notasAlumnosNotas,
    int numNotas, int *codigosAlumnosNotas) {
    for (int i=0; i<numAlumnos; i++) {
        int codigo=codigosAlumnos[i];
        promedios[i]=calcularPromedioDeNotas(notasAlumnosNotas, numNotas, codigosAlumnosNotas, codigo);
    }
}

void generarReporte(const char *nombre, int *codigosAlumnos, int *ciclosAlumnos, int numAlumnos, double *promedios) {
    ofstream salida(nombre);
    if (!salida) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    encabezado(salida);
    for (int i=0; i<numAlumnos; i++) {
        int codigoAlumno=codigosAlumnos[i];
        int ciclo=ciclosAlumnos[i];
        salida << right << setw(ANCHO/3) << codigoAlumno << setw(ANCHO/3) << ciclo << setw(ANCHO/3) << fixed
                << setprecision(2) << promedios[i] << endl;
    }
}

void generarReporte2(const char *nombre, int *codigosAlumnos, char *nombresAlumnos, int *ciclosAlumnos,
    int numAlumnosEDITADO, int *codigosAlumnosNotas, double *notasAlumnosNotas, int numNotas) {
    ofstream salida(nombre);
    if (!salida) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }

    encabezado2(salida);

    for (int i=0; i<numAlumnosEDITADO; i++) {


        salida << right << setw(ANCHO/3) << codigosAlumnos[i];

        for (int j=0; j<30; j++) {
            salida << nombresAlumnos[j] << "  ";
        }

        salida << endl;

        //salida << setw(ANCHO/3) << "CICLO" << setw(ANCHO/3) << "PROMEDIO" << endl;






    }
}

//-----------------------------FUNCIONES DE ORDENAMIENTO

void intercambiarDouble(double &a, double &b) {
    double aux=a;
    a=b, b=aux;
}

void intercambiarInt(int &a, int &b) {
    int aux=a;
    a=b, b=aux;
}

//ORDENAR POR PROMEDIOS

void ordenarPorPromediosPorIntercambio(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos) {
    for (int i=0; i<(numAlumnos-1); i++) {
        for (int j=(i+1); j<numAlumnos; j++) {
            if (promedios[i]<promedios[j]) {
                intercambiarDouble(promedios[i], promedios[j]);
                intercambiarInt(codigosAlumnos[i], codigosAlumnos[j]);
                intercambiarInt(ciclosAlumnos[i], ciclosAlumnos[j]);
            }
        }
    }
}

void ordenarPorPromediosPorSeleccion(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos) {
    for (int i=0; i<(numAlumnos-1); i++) {
        int posicionMenor=i;
        for (int j=(i+1); j<numAlumnos; j++) {
            if (promedios[j]>promedios[posicionMenor]) posicionMenor=j;
        }
        if (posicionMenor!=i) {
            intercambiarDouble(promedios[i], promedios[posicionMenor]);
            intercambiarInt(codigosAlumnos[i], codigosAlumnos[posicionMenor]);
            intercambiarInt(ciclosAlumnos[i], ciclosAlumnos[posicionMenor]);
        }
    }
}

void ordenarPorPromediosPorBubble(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos) {
    for (int i=0; i<(numAlumnos-1); i++) {
        for (int j=0; j<(numAlumnos-1-i); j++) {
            if (promedios[j]<promedios[j+1]) {
                intercambiarDouble(promedios[j], promedios[j+1]);
                intercambiarInt(codigosAlumnos[j], codigosAlumnos[j+1]);
                intercambiarInt(ciclosAlumnos[j], ciclosAlumnos[j+1]);
            }
        }
    }
}

//ORDENAR POR CICLO

void ordenarPorCicloPorIntercambio(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos) {
    for (int i=0; i<(numAlumnos-1); i++) {
        for (int j=(i+1); j<numAlumnos; j++) {
            if (ciclosAlumnos[i]<ciclosAlumnos[j]) {
                intercambiarInt(codigosAlumnos[i], codigosAlumnos[j]);
                intercambiarInt(ciclosAlumnos[i], ciclosAlumnos[j]);
                intercambiarDouble(promedios[i], promedios[j]);
            }
        }
    }
}

void ordenarPorCicloPorSeleccion(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos) {
    for (int i=0; i<(numAlumnos-1); i++) {
        int posicionMenor=i;
        for (int j=(i+1); j<numAlumnos; j++) {
            if (ciclosAlumnos[j]>ciclosAlumnos[posicionMenor]) posicionMenor=j;
        }
        if (posicionMenor!=i) {
            intercambiarInt(codigosAlumnos[i], codigosAlumnos[posicionMenor]);
            intercambiarInt(ciclosAlumnos[i], ciclosAlumnos[posicionMenor]);
            intercambiarDouble(promedios[i], promedios[posicionMenor]);
        }
    }
}

void ordenarPorCicloPorBubble(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos) {
    for (int i=0; i<(numAlumnos-1); i++) {
        for (int j=0; j<(numAlumnos-1-i); j++) {
            if (ciclosAlumnos[j]<ciclosAlumnos[j+1]) {
                intercambiarInt(codigosAlumnos[j], codigosAlumnos[j+1]);
                intercambiarInt(ciclosAlumnos[j], ciclosAlumnos[j+1]);
                intercambiarDouble(promedios[j], promedios[j+1]);
            }
        }
    }
}

void ordenarPromediosyCiclosPorBubble(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos) {
    for (int i=0; i<(numAlumnos-1); i++) {
        for (int j=0; j<(numAlumnos-1-i); j++) {

            //SE QUIERE ORDENAR 1RO POR PROMEDIO (MAYOR A MENOR)
            //Y LUEGO POR CICLO (MAYOR A MENOR) EN CASO HAYAN DOS PROMEDIOS IGUALES:
            if (promedios[j]<promedios[j+1] or (promedios[j]==promedios[j+1] and ciclosAlumnos[j]<ciclosAlumnos[j+1])
                or (ciclosAlumnos[j]==ciclosAlumnos[j+1] and codigosAlumnos[j]<codigosAlumnos[j+1])) {
                intercambiarInt(codigosAlumnos[j], codigosAlumnos[j+1]);
                intercambiarInt(ciclosAlumnos[j], ciclosAlumnos[j+1]);
                intercambiarDouble(promedios[j], promedios[j+1]);
            }
        }
    }
}

void ordenarPromediosyCiclosPorSeleccion(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos) {
    for (int i=0; i<(numAlumnos-1); i++) {
        int posicionMenor=i;
        for (int j=(i+1); j<numAlumnos; j++) {
            if (promedios[j]>promedios[posicionMenor] or (promedios[j]==promedios[posicionMenor]
                and ciclosAlumnos[j]>ciclosAlumnos[posicionMenor]) or (ciclosAlumnos[j]==ciclosAlumnos[posicionMenor] and
                    codigosAlumnos[j]>codigosAlumnos[posicionMenor])) {
                posicionMenor=j;
            }
        }
        if (posicionMenor!=i) {
            intercambiarInt(codigosAlumnos[i], codigosAlumnos[posicionMenor]);
            intercambiarInt(ciclosAlumnos[i], ciclosAlumnos[posicionMenor]);
            intercambiarDouble(promedios[i], promedios[posicionMenor]);
        }
    }
}

void ordenarPromediosyCiclosPorIntercambio(double *promedios, int numAlumnos, int *codigosAlumnos, int *ciclosAlumnos) {
    for (int i=0; i<(numAlumnos-1); i++) {
        for (int j=(i+1); j<numAlumnos; j++) {
            if (promedios[i]<promedios[j] or (promedios[i]==promedios[j] and ciclosAlumnos[i]<ciclosAlumnos[j]) or
                (ciclosAlumnos[i]==ciclosAlumnos[j] and codigosAlumnos[i]<codigosAlumnos[j])) {
                intercambiarInt(codigosAlumnos[i], codigosAlumnos[j]);
                intercambiarInt(ciclosAlumnos[i], ciclosAlumnos[j]);
                intercambiarDouble(promedios[i], promedios[j]);
            }
        }
    }
}
