#include "Bibliotecas/Funciones.h"

int main() {

    // ---------------------------------------------- REPORTE 1:

    ifstream cursos; //cursos.csv
    ifstream registro; //registroNotas.txt
    ofstream salida; //ReporteEstudiantes.txt

    if (!abrirArchivos(cursos, registro, salida)) {
        cout << "No se pudo abrir el archivo." << endl;
        exit(1);
    }

    generarReporte1(cursos, registro, salida);

    cerrarArchivos(cursos, registro, salida);

    // ---------------------------------------------- REPORTE 2:

    int codigosCursos[CAPACIDAD_CURSOS];
    int cantEstudiantesCursos[CAPACIDAD_CURSOS]{};
    int cantAprobadosCursos[CAPACIDAD_CURSOS]{};
    int cantDesaprobadosCursos[CAPACIDAD_CURSOS]{};
    double promediosCursos[CAPACIDAD_CURSOS]{};
    int numCursos, numAlumnos;

    cargarCursos("ArchivosDeDatos/cursos.csv", codigosCursos, numCursos);

    cargarRegistroNotas("ArchivosDeDatos/registroNotas.txt", codigosCursos, numCursos, cantEstudiantesCursos,
        cantAprobadosCursos, cantDesaprobadosCursos, promediosCursos, numAlumnos);

    ordenarCantEstudiantesAprobadosYPromedios_Burbuja(codigosCursos, numCursos, cantEstudiantesCursos, cantAprobadosCursos,
        cantDesaprobadosCursos, promediosCursos);

    generarReporte2("ArchivosDeReporte/ReporteCursos.txt", codigosCursos, numCursos, cantEstudiantesCursos,
        cantAprobadosCursos, cantDesaprobadosCursos, promediosCursos);


    return 0;
}
