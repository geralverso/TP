//
// Created by PC on 9/10/2026.
//

#include "Funciones.h"

// ---------------------------------------------- REPORTE 1:

void imprimirSeparador(ofstream &salida, char c, int n) {
    for (int i=0; i<n; i++) salida << c;
    salida << endl;
}

bool abrirArchivos(ifstream &cursos, ifstream &registro, ofstream &salida) {
    cursos.open("ArchivosDeDatos/cursos.csv");
    registro.open("ArchivosDeDatos/registroNotas.txt");
    salida.open("ArchivosDeReporte/ReporteEstudiantes.txt");
    return cursos.is_open() and registro.is_open() and salida.is_open();
}

void buscarCursosDelEstudiante(ifstream &registro, ifstream &cursos, ofstream &salida, int &cantCursosPorEstudiante,
    int &totalCreditosPorEstudiante, double &sumaNotasPorCreditos) {
    int codigoCurso, sumaCreditos=0.0;
    double nota, notasPorCreditos=0.0;
    while (registro.peek()!='\n') {
        cantCursosPorEstudiante++;
        registro >> codigoCurso >> nota;
        salida << left << setw(8) << codigoCurso;
        buscarNombreYCreditosDelCurso(cursos, salida, codigoCurso, sumaCreditos, notasPorCreditos, nota);
        salida << right << setw(8) << fixed << setprecision(1) << nota << endl;
        totalCreditosPorEstudiante=sumaCreditos;
        sumaNotasPorCreditos=notasPorCreditos;
    }
}

void buscarNombreYCreditosDelCurso(ifstream &cursos, ofstream &salida, int codigoCurso, int &sumaCreditos,
    double &notasPorCreditos, double nota) {
    int codigo, creditos;
    char c;
    cursos.clear();
    cursos.seekg(0);
    while (cursos >> codigo) {
        cursos >> c >> creditos >> c;
        if (codigo==codigoCurso) {
            leerEImprimirNombre(cursos, salida, true);
            salida << right << setw(9) << creditos;
            sumaCreditos+=creditos;
            notasPorCreditos+=creditos*nota;
        }
        else leerEImprimirNombre(cursos, salida, false);
    }
}

void leerEImprimirNombre(ifstream &entrada, ofstream &salida, bool seMuestra) {
    char c;
    int cantCaracteres=0;
    while (entrada.get(c)) {
        if (c=='_') c=' ';
        if (c=='\n') break;
        if (seMuestra==true) salida << c;
        cantCaracteres++;
    }
    if (seMuestra==true) salida << setw(35-cantCaracteres) << " ";
}

void imprimirEncabezado1(ofstream &salida, int codigoEstudiante) {
    imprimirSeparador(salida, '=', ANCHO_REPORTE1);
    salida << "CODIGO DE ESTUDIANTE: " << codigoEstudiante << endl;
    imprimirSeparador(salida, '=', ANCHO_REPORTE1);
    salida << left << setw(8) << "Codigo" << setw(35) << "Curso" << right << setw(9) << "Creditos" << setw(8)
            << "Nota" << endl;
    imprimirSeparador(salida, '-', ANCHO_REPORTE1);
}

void imprimirResumen(ofstream &salida, int cantCursosPorEstudiante, int totalCreditosPorEstudiante, double promPonderado) {
    imprimirSeparador(salida, '-', ANCHO_REPORTE1);
    salida << "Cantidad de cursos: " << cantCursosPorEstudiante << endl;
    salida << "Total de creditos: " << totalCreditosPorEstudiante << endl;
    salida << "Promedio general ponderado: " << fixed << setprecision(2) << promPonderado << "\n" << endl;
}

void generarReporte1(ifstream &cursos, ifstream &registro, ofstream &salida) {
    int codigoEstudiante;
    while (registro >> codigoEstudiante) {
        imprimirEncabezado1(salida, codigoEstudiante);
        int cantCursosPorEstudiante=0, totalCreditosPorEstudiante=0;
        double sumaNotasPorCreditos=0.0;
        buscarCursosDelEstudiante(registro, cursos, salida, cantCursosPorEstudiante,
            totalCreditosPorEstudiante, sumaNotasPorCreditos);
        double promPonderado=(totalCreditosPorEstudiante>0)?(sumaNotasPorCreditos/totalCreditosPorEstudiante):0.0;
        imprimirResumen(salida, cantCursosPorEstudiante, totalCreditosPorEstudiante, promPonderado);
    }
}

void cerrarArchivos(ifstream &cursos, ifstream &registro, ofstream &salida) {
    cursos.close();
    registro.close();
    salida.close();
}


// ---------------------------------------------- REPORTE 2:

void cargarCursos(const char *nombreArchivo, int *codigosCursos, int &numCursos) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }
    numCursos=0;
    int codigoCurso;
    while (entrada >> codigoCurso) {
        entrada.ignore(1000, '\n');
        insertarOrdenadoCursos(codigosCursos, codigoCurso, numCursos, CAPACIDAD_CURSOS);
    }
}

int insertarOrdenadoCursos(int *codigosCursos, int codCursoNuevo, int &numCursos, int capacidad) {
    if (numCursos >= capacidad) return -1;
    int i=numCursos-1;
    while (i>=0 && codigosCursos[i]>codCursoNuevo) {
        codigosCursos[i+1]=codigosCursos[i];
        i--;
    }
    codigosCursos[i+1]=codCursoNuevo;
    numCursos++;
    return i+1;
}

void cargarRegistroNotas(const char *nombreArchivo, int *codigosCursos, int numCursos, int *cantEstudiantesCursos,
    int *cantAprobadosCursos, int *cantDesaprobadosCursos, double *promediosCursos, int &numAlumnos) {
    ifstream entrada(nombreArchivo);
    if (!entrada) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }
    numAlumnos=0;
    int codigoAlumno, codigoCurso;
    double nota;
    while (entrada >> codigoAlumno) {
        while (entrada.peek()!='\n') {
            entrada >> codigoCurso >> nota;
            int posicion=buscarBinariaCurso(codigosCursos, numCursos, codigoCurso);
            if (posicion!=-1) {
                cantEstudiantesCursos[posicion]++;
                if (nota>=10.5) cantAprobadosCursos[posicion]++;
                else cantDesaprobadosCursos[posicion]++;
                promediosCursos[posicion]+=nota; //ACUMULAREMOS LA SUMA DE NOTAS AQUI POR AHORA
            }
        }
        numAlumnos++;
    }
}

int buscarBinariaCurso(int *codigosCursos, int numCursos, int codigoBuscado) {
    int posInicial=0, posFinal=numCursos-1;
    while (true) {
        int posMedio=(posInicial+posFinal)/2;
        if (codigosCursos[posMedio]==codigoBuscado) return posMedio;
        if (codigosCursos[posMedio]<codigoBuscado) posInicial=posMedio+1;
        else posFinal=posMedio-1;
        if (posInicial>posFinal) return -1;
    }
}

void intercambiarInt(int &a, int &b) {
    int aux=a;
    a=b, b=aux;
}

void intercambiarDouble(double &a, double &b) {
    double aux=a;
    a=b, b=aux;
}

void ordenarCantEstudiantesAprobadosYPromedios_Burbuja(int *codigosCursos, int numCursos, int *cantEstudiantesCursos,
    int *cantAprobadosCursos, int *cantDesaprobadosCursos, double *promediosCursos) {
    for (int i=0; i<(numCursos-1); i++) {
        for (int j=0; j<(numCursos-1-i); j++) {
            if (cantEstudiantesCursos[j]<cantEstudiantesCursos[j+1] or
                (cantEstudiantesCursos[j]==cantEstudiantesCursos[j+1] and cantAprobadosCursos[j]<cantAprobadosCursos[j+1]) or
                (cantEstudiantesCursos[j]==cantEstudiantesCursos[j+1] and cantAprobadosCursos[j]==cantAprobadosCursos[j+1] and
                promediosCursos[j]<promediosCursos[j+1])) {
                intercambiarInt(codigosCursos[j],codigosCursos[j+1]);
                intercambiarInt(cantEstudiantesCursos[j],cantEstudiantesCursos[j+1]);
                intercambiarInt(cantAprobadosCursos[j],cantAprobadosCursos[j+1]);
                intercambiarInt(cantDesaprobadosCursos[j],cantDesaprobadosCursos[j+1]);
                intercambiarDouble(promediosCursos[j],promediosCursos[j+1]);
            }
        }
    }
}

void imprimirEncabezado2(ofstream &salida) {
    salida << left << setw(9) << "Curso" << right << setw(11) << "Estudiantes" << setw(11) << "Aprobados"
            << setw(14) << "Desaprobados" << setw(10) << "Promedio" << endl;
    imprimirSeparador(salida, '-', ANCHO_REPORTE2);
}

void generarReporte2(const char *nombreArchivo, int *codigosCursos, int numCursos, int *cantEstudiantesCursos,
    int *cantAprobadosCursos, int *cantDesaprobadosCursos, double *promediosCursos) {
    ofstream salida(nombreArchivo);
    if (!salida) {
        cerr << "Error al abrir el archivo" << endl;
        exit(1);
    }
    imprimirEncabezado2(salida);
    for (int i=0; i<numCursos; i++) {
        int codigoCurso=codigosCursos[i];
        int cantEstudiantes=cantEstudiantesCursos[i];
        int cantAprobados=cantAprobadosCursos[i];
        int cantDesaprobados=cantDesaprobadosCursos[i];
        double promedio=(cantEstudiantes>0)?(promediosCursos[i]/cantEstudiantes):0.0; //AHORA SI ES EL PROMEDIO ACTUALIZADO
        salida << left << setw(9) << codigoCurso << right << setw(11) << cantEstudiantes << setw(11) << cantAprobados
            << setw(14) << cantDesaprobados << setw(10) << fixed << setprecision(2) << promedio << endl;
    }
}
