#include "Bibliotecas/Funciones.h"

int main() {

    int cantValidos[CAPACIDAD_REGISTROS]{};
    int cantInvalidos[CAPACIDAD_REGISTROS]{};
    int numRegistros;

    validarYGenerarReporte("ArchivosDeDatos/registros.csv", "ArchivosDeReporte/ReporteValidacion.txt",
        cantValidos, cantInvalidos,numRegistros);

    generarResumen("ArchivosDeReporte/ResumenValidacion.txt", cantValidos, cantInvalidos, numRegistros);

    return 0;
}
