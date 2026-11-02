#include "Bibliotecas/Funciones.h"

int main() {

    //CON MEMORIA DINÁMICA
    int* dnis;
    char** nombres;
    double* sueldos;
    int numPersonal;

    cargarPersonal("ArchivosDeDatos/personal.csv", dnis, nombres, sueldos, numPersonal);

    // ordenarPersonal(dnis, nombres, sueldos, numPersonal);

    generarReporte("ArchivosDeReporte/reporte.txt", dnis, nombres, sueldos, numPersonal);

    liberarMemoria(dnis, nombres, sueldos, numPersonal);

    return 0;
}
