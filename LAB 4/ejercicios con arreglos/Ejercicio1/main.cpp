#include <iostream>
#include "Bibliotecas/Funciones.h"

int main() {

    //ARREGLOS VACIOS:
    int codigos[CAPACIDAD_EMPLEADOS];
    char nombres[CAPACIDAD_EMPLEADOS];
    char areasDeTrabajo[CAPACIDAD_EMPLEADOS];
    double horasExtra[CAPACIDAD_EMPLEADOS];
    int numEmpleados; //SIRVE PARA HALLAR LA LONGITUD

    cargarEmpleadosTXT("ArchivosDeDatos/empleados.txt",codigos, nombres, areasDeTrabajo, horasExtra,
        numEmpleados);
    //cout << "La cantidad de empleados son: " << numEmpleados << endl;

    generarReportes("ArchivosDeReporte/reporte.txt", "ArchivosDeReporte/reporteOrdenado.txt",
        codigos, areasDeTrabajo, horasExtra, numEmpleados);

    return 0;
}
