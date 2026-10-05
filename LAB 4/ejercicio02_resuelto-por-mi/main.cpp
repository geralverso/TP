#include "Bibliotecas/Funciones.h"

int main() {

    //ARREGLOS VACIOS
    int codigosAlumnos[CAPACIDAD_ALUMNOS];
    char nombresAlumnos[CAPACIDAD_ALUMNOS];
    int ciclosAlumnos[CAPACIDAD_ALUMNOS];
    int codigosAlumnosNotas[CAPACIDAD_NOTAS];
    double notasAlumnosNotas[CAPACIDAD_NOTAS];
    int numAlumnos, numAlumnosEDITADO, numNotas;
    double promedios[CAPACIDAD_ALUMNOS]{};

    cargarAlumnosCSV("ArchivosDeDatos/alumnos.csv", codigosAlumnos, ciclosAlumnos,numAlumnos);

    //cargarAlumnosEDITADO("ArchivosDeDatos/alumnosEditado.txt", codigosAlumnos, nombresAlumnos, ciclosAlumnos,numAlumnosEDITADO);

    cargarNotasCSV("ArchivosDeDatos/notas.csv", codigosAlumnosNotas, notasAlumnosNotas,numNotas);

    // cout << numAlumnos << endl;
    // cout << numNotas << endl;

    armarArregloPromediosNotas(numAlumnos, codigosAlumnos, promedios, notasAlumnosNotas, numNotas,codigosAlumnosNotas);

    //ordenarPorPromediosPorIntercambio(promedios, numAlumnos, codigosAlumnos, ciclosAlumnos);
    //ordenarPorPromediosPorSeleccion(promedios, numAlumnos, codigosAlumnos, ciclosAlumnos);
    //ordenarPorPromediosPorBubble(promedios, numAlumnos, codigosAlumnos, ciclosAlumnos);

    //ordenarPorCicloPorIntercambio(promedios, numAlumnos, codigosAlumnos, ciclosAlumnos);
    //ordenarPorCicloPorSeleccion(promedios, numAlumnos, codigosAlumnos, ciclosAlumnos);
    //ordenarPorCicloPorBubble(promedios, numAlumnos, codigosAlumnos, ciclosAlumnos);


    //SE QUIERE ORDENAR POR PROMEDIO (MAYOR A MENOR) Y LUEGO POR CICLO (MAYOR A MENOR):
    //ordenarPromediosyCiclosPorIntercambio(promedios, numAlumnos, codigosAlumnos, ciclosAlumnos);
    //ordenarPromediosyCiclosPorSeleccion(promedios, numAlumnos, codigosAlumnos, ciclosAlumnos);
    ordenarPromediosyCiclosPorBubble(promedios, numAlumnos, codigosAlumnos, ciclosAlumnos);


    generarReporte("ArchivosDeReporte/reporte.txt", codigosAlumnos, ciclosAlumnos,numAlumnos,promedios);

    //generarReporte2("ArchivosDeReporte/reporte2.txt", codigosAlumnos, nombresAlumnos, ciclosAlumnos, numAlumnosEDITADO,codigosAlumnosNotas, notasAlumnosNotas, numNotas);

    return 0;
}
