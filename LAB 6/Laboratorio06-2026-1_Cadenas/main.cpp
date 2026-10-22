#include "Bibliotecas/Funciones.h"

int main() {

    //ARREGLOS DINÁMICOS
    int* codigosMedicos;
    double* tarifaMedicos;
    int numMedicos;

    cargarEspecMedicos("ArchivosDeDatos/Especialidades_Medicos_TP_Lab6.txt", codigosMedicos,
        tarifaMedicos, numMedicos);

    generarReporteSimple1("ArchivosDeReporte/ReporteSimple1.txt", codigosMedicos, tarifaMedicos, numMedicos);

    int* codigosPacientes;
    int* codigosSedesPacientes;
    int* duracionAtencionesPacientes;
    double* pagosTotalesPacientes;
    int numAtenciones;

    cargarAtenciones("ArchivosDeDatos/Atenciones_TP_Lab6.txt", codigosPacientes, codigosSedesPacientes,
        duracionAtencionesPacientes, pagosTotalesPacientes, numAtenciones, codigosMedicos, tarifaMedicos, numMedicos);

    ordenarSedeYPacientePorBurbuja(codigosPacientes, codigosSedesPacientes, duracionAtencionesPacientes,
        pagosTotalesPacientes, numAtenciones);

    generarReporteSimple2("ArchivosDeReporte/ReporteSimple2.txt", codigosPacientes, codigosSedesPacientes,
        duracionAtencionesPacientes, pagosTotalesPacientes, numAtenciones);

    generarReporte("ArchivosDeReporte/Reporte.txt", "ArchivosDeDatos/Sedes_TP_Lab6.txt",
        codigosMedicos, codigosPacientes, codigosSedesPacientes, duracionAtencionesPacientes, pagosTotalesPacientes,
        numAtenciones);

    delete[] codigosMedicos;
    delete[] tarifaMedicos;
    delete[] codigosPacientes;
    delete[] codigosSedesPacientes;
    delete[] duracionAtencionesPacientes;
    delete[] pagosTotalesPacientes;

    return 0;
}
