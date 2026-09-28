#include "Bibliotecas/Funciones.h"

int main() {

    int codigosAlumnos[CAPACIDAD_ALUMNOS];
    int ciclosAlumnos[CAPACIDAD_ALUMNOS];
    int codigosNotas[CAPACIDAD_NOTAS];
    double notas[CAPACIDAD_NOTAS];
    int codigosConsultas[CAPACIDAD_CONSULTAS];
    int numAlumnos, numNotas, numConsultas;

    cargarAlumnosCSV("ArchivosDeDatos/alumnos.csv", codigosAlumnos, ciclosAlumnos,numAlumnos);
    cargarNotasCSV("ArchivosDeDatos/notas.csv", codigosNotas, notas,numNotas);
    cargarConsultasTXT("ArchivosDeDatos/consultas.txt", codigosConsultas,numConsultas);

    // cout << numAlumnos << endl;
    // cout << numNotas << endl;
    // cout << numConsultas << endl;

    generarReporte("ArchivosDeReporte/reporte.txt", codigosAlumnos, ciclosAlumnos, numAlumnos,
        codigosNotas, notas, numNotas, codigosConsultas, numConsultas);

    return 0;
}
